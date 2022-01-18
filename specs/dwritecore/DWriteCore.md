# DWriteCore

DWriteCore is the Windows App SDK version of DirectWrite, the text rendering and layout
component that ships in Windows. DWriteCore implements the same API as DirectWrite,
with a few additions described in this document. See the [DirectWrite documentation](https://docs.microsoft.com/windows/win32/api/_directwrite/)
for more information.

For an application that already uses DirectWrite, switching to DWriteCore requires minimal changes:

 - Add a reference to the Windows App SDK package.
 - Include dwrite_core.h instead of dwrite_3.h.
 - Link to DWriteCore.lib instead of DWrite.lib.
 - Call DWriteCoreCreateFactory instead of DWriteCreateFactory.

In return, the application gets the benefits of Windows App SDK, namely, access to the newest APIs
and functionality regardless of what version of Windows your customer is running.

# Background

The DWriteCore API is the same as the existing public DirectWrite API, with a few additions. These
additions should eventually be incorporated into the in-box DirectWrite as well, so it is appropriate
to think of the DWriteCore API as just the latest version of the DirectWrite API. This document focuses
primarily on the additions.

## API Versioning

The DirectWrite API has grown over time, and many APIs have multiple versions: IDWriteFactory,
IDWriteFactory1, IDWriteFactory2, etc. Prior to Windows 10, each new version got a new header file.
Starting in TH1, new APIs have been added to dwrite_3.h, but conditionalized based on NTDDI_VERSION.
API definitions in dwrite_3.h in the Windows SDK are conditionalized as follows:

```c++
#if NTDDI_VERSION >= NTDDI_WIN10_MN
    . . . APIs introduced in MN . . .
#endif // NTDDI_VERSION >= NTDDI_WIN10_MN
```

DWriteCore always implements the latest version of the API, so there needs to be a mechanism for an
application using DWriteCore to get access to all the latest APIs regardless of NTDDI_VERSION. The
copy of dwrite_3.h in the DWriteCore package therefore uses the following convention to conditinalize
API definitions:

```c++
#if DWRITE_CORE || NTDDI_VERSION >= NTDDI_WIN10_MN
    . . . APIs introduced in MN . . .
#endif // DWRITE_CORE || NTDDI_VERSION >= NTDDI_WIN10_MN

#if DWRITE_CORE
    . . . New APIs not yet in any in-box version of DWrite . . .
#endif // DWRITE_CORE
```

The DWriteCore NuGet package includes a header file named dwrite_core.h as well as the newest
versions of the existing DirectWrite header files (dwrite_3.h, dwrite_2.h, and dwrite_1.h, dwrite.h).
The dwrite_core.h simply defines the DWRITE_CORE preprocessor symbol and then includes dwrite_3.h.
In this way, an application that includes dwrite_core.h has access to all DirectWrite APIs regardless
of the NTDDI_VERSION.

## Cross-Platform Considerations

DWriteCore runs on non-Windows platforms in addition to the down-level Windows versions targetted by
Windows App SDK. In order to compile cross-platform, it is necessary to have definitions of Windows types
and constants used by the DirectWrite API -- for example, IUnknown, HRESULT, etc. The DWriteCore project
has an “xplatwin” directory with a set of header files that contain portable definitions of these things,
as well as mechanisms to avoid the use of compiler extensions like __declspec(uuid(x)) and __uuidof.

Another consideration on non-Windows platforms is the definition of WCHAR. Most projects define WCHAR as
wchar_t which is a 32-bit type everywhere except Windows, but Office relies on WCHAR being 16 bits.
Therefore, DWriteCore’s cross-platform headers defines WCHAR as either char16_t or wchar_t, depending on
a preprocessor definition, and we build both 16-bit and 32-bit flavors.

This is outside the scope of the API itself, but is mentioned here because other cross-platform libraries
will have to solve the same problem, and if each library solves the problem in its own way, we may end up
with interoperability issues.

# Description

New APIs introduced by DWriteCore include:

 - The exported function is renamed `DWriteCoreCreateFactory` to avoid a naming collision with the
   `DWriteCreateFactory` function exported by the system version of DirectWrite (DWrite.dll)
 - A new `DWRITE_FACTORY_TYPE` value which specifies an isolated factory object
 - A new method for getting pixel data from a bitmap render target
 - New methods for selecting fonts from a font set
 - A new factory method to release unreferenced fonts

# Factory Creation

The new `DWRITE_FACTORY_TYPE_ISOLATED2` enumerator complements the existing factory types. It is similar to
`DWRITE_FACTORY_TYPE_ISOLATED`, but is more locked down in two ways. First, it only caches data in-process, and
will not attempt to either read from or write to a cross-process font cache or persisted cache file. Second,
a `DWRITE_FACTORY_TYPE_ISOLATED2` factory only enumerates well-known fonts in the system font collection. The well-known-fonts
restriction enables the implementation to efficiently construct the system font collection without depending on a
cross-process or persistent cache. An example use case for the new factory type would be a web browser
rendering process with very limited permissions.

# Text Rendering

A _bitmap render target_ (`IDWriteBitmapRenderTarget`) is an API object that encapsulates a system memory bitmap
and enables rendering glyphs to the bitmap. On Windows, the object encapsulates a GDI memory DC with a GDI
device-independent bitmap (DIB) selected into it. However, on non-Windows platforms, there is no GDI DC,
and the bitmap is just a system memory array. DWriteCore introduces a new version of the bitmap render target
interface that an application can use to access the bitmap data without going through GDI.

# Font Selection

The new `IDWriteFontSet4` interface exposes new methods for selecting fonts from a font set. The new methods
make it possible to transition to the _typographic font family model_ while maintaining compatibility with
existing applications, documents, and fonts.

Font selection (sometimes called font matching or font mapping) is the process of selecting the available
fonts that best match input parameters passed in by an application. The input parameters are sometimes
referred to collectively as a _logical font_. A logical font includes a font family name plus other attributes
indicating a particular font within the family. A font selection algorithm matches the logical font (the
"font you want") to an available _physical font_ (a "font you have").

A _font family_ is a named group of fonts that share a common design but may differ in attributes such as
weight. A _font family model_ defines what attributes may be used to differentiate fonts within a family.
The new _typographic font family model_ has many advantages over the two previous font family models used
on Windows. Unfortunately, changing font family models creates opportunities for confusion and compatibility
issues. The methods exposed by the `IDWriteFontSet4` interface implement a hybrid approach that offers the
advantages of the typographic font family model while mitigating compatibility issues.

The following sections compare the older font family models with the typographic font family model,
explain compatibility challenges posed by changing font family models, and finally explains how those
challenges can be overcome by using the `IDWriteFontSet4` methods.

## RBIZ Font Family Model

The de facto font family model used in the GDI application ecosystem is sometimes called the "four-font
model" or "RBIZ" model. Each font family in this model typically has at most four fonts. The "RBIZ"
label comes from the naming convention used for some font files, for example:

File Name       | Font Style
----------------|-------------
verdana.ttf     | Regular
verdanab.ttf    | Bold
verdanai.ttf    | Italic
verdanaz.ttf    | Bold Italic

With GDI, the input parameters used to select a font are defined by the `LOGFONT` structure, which
includes family name (`lfFaceName`), weight (`lfWeight`) and italic (`lfItalic`) fields. The `lfItalic` 
field is either TRUE or FALSE. GDI allows the `lfWeight` field to be any value in the range `FW_THIN`
(100) to `FW_BLACK` (900), but for historical reasons fonts have long been designed such that there
are no more than two weights in the same GDI font family.

Popular application user interfaces from early on included an italic button (to turn italic on and
off) and a bold button (to toggle between normal and bold weights). The use of these two buttons to
select fonts within a family assumes the RBIZ model. Therefore, even though GDI itself supports more 
than two weights, application compatibility led font developers to set the GDI family name (OpenType
name ID 1) in a way that was consistent with the RBIZ model.

For example, suppose you wanted to add a heavier "Black" weight to the Arial font family. Logically,
this font is part of the Arial family, so you might expect to select it by setting `lfFaceName` to
"Arial" and `lfWeight` to `FW_BLACK`. However, there is no way for an application user to choose 
between three weights using a two-state bold button. The solution was to give the new font a different
family name, so the user could select it by choosing "Arial Black" from the list of font families.
Likewise, there is no way to choose from among different widths in the same font family using only bold
and italic buttons, so the narrow versions of Arial have different family names in the RBIZ model.
Thus we have "Arial", "Arial Black", and "Arial Narrow" font familes in the RBIZ model even though
typographically these all belong in one family.

From these examples, one can see how the limitations of a font family model can affect how fonts are
grouped into families. Since font families are identified by name, this means the same font can have
different family names depending on which font family model you're using.

DirectWrite does not directly support the RBIZ font family model, but it does provide methods of
converting to and from the RBIZ model, such as `IDWriteGdiInterop::CreateFontFromLOGFONT` and
`IDWriteGdiInterop::ConvertFontToLOGFONT`. You can also get the RBIZ family name of a font by calling
its `GetInformationalStrings` method and specifying `DWRITE_INFORMATIONAL_STRING_WIN32_FAMILY_NAMES`.

## Weight-Stretch-Style Font Family Model

The weight-stretch-style font family model is the original font family model used by DirectWrite before
the typographic font family model was introduced. It is also known as weight-width-slope (WWS). In the
WWS model, fonts within the same family can be differented by three properties: weight (`DWRITE_FONT_WEIGHT`),
stretch (`DWRITE_FONT_STRETCH`), and style (`DWRITE_FONT_STYLE`).

The WWS model is more flexible than the RBIZ model in two ways. First, fonts in the same family can
be differentiated by stretch (or width) as well as weight and style (regular, italic or oblique). Second,
there can be more than two weights in the same family. This flexibility is sufficient to allow all the
variants of Arial to be included in the same WWS family. The following table compares RBIZ and WWS font
properties for a selection of Arial fonts:

Full Name           | RBIZ Family Name      | lfWeight  | lfItalic  | WWS FamilyName    | Weight    | Stretch   | Style
--------------------|-----------------------|-----------|-----------|-------------------|-----------|-----------|---------
Arial               | Arial                 | 400       | 0         | Arial             | 400       | 5         | 0
Arial Bold          | Arial                 | 700       | 0         | Arial             | 700       | 5         | 0
Arial Black         | Arial Black           | 900       | 0         | Arial             | 900       | 5         | 0
Arial Narrow        | Arial Narrow          | 400       | 0         | Arial             | 400       | 3         | 0
Arial Narrow Bold   | Arial Narrow          | 700       | 0         | Arial             | 700       | 3         | 0

As you can see, "Arial Narrow" has the same `lfWeight` and `lfItalic` values as "Arial", so it 
has a different RBIZ family name to avoid ambiguity. "Arial Black" has a different RBIZ family name
to avoid having more than two weights in the "Arial" family. By contrast, all of these fonts are in
the same weight-stretch-style family.

Nevertheless, the weight-stretch-style model is not open-ended. If two fonts have the same weight,
stretch, and style but differ in some other way (e.g., optical size), they cannot be included in the
same WWS font family. This brings us to the typographic font family model.

## Typographic Font Family Model

Unlike its predecessors, the typographic font family model is open-ended. It supports any number of axes
of variation within a font family.

If you think of font selection parameters as coordinates in a design space, the weight-stretch-style
model defines a three-dimensional coordinate system with weight, stretch, and style as the axes. Each
font in a WWS family must have a unique location defined by its coordinates along those three axes. To
select a font, one specifies a WWS family name and weight, stretch, and style parameters.

By contrast, the typographic font family model has an N-dimensional design space. A font designer can 
define any number of design axes, each identified by a four-character _axis tag_. A given font’s location 
in the N-dimensional design space is defined by an array of _axis values_, where each axis value comprises 
an axis tag and a floating-point value. To select a font, one specifies a typographic family name and an 
array of axis values (`DWRITE_FONT_AXIS_VALUE` structures).

Although the number of font axes is open-ended, there are a few registered axes with standard meanings,
and the weight, stretch, and style values can be mapped to registered axis values. `DWRITE_FONT_WEIGHT`
can be mapped to a "wght" (`DWRITE_FONT_AXIS_TAG_WEIGHT`) axis value. `DWRITE_FONT_STRETCH` can be mapped
to a "wdth" (`DWRITE_FONT_AXIS_TAG_WIDTH`) axis value. `DWRITE_FONT_STYLE` can be mapped to a combination
of "ital" and "slnt" (`DWRITE_FONT_AXIS_TAG_ITALIC` and `DWRITE_FONT_AXIS_TAG_SLANT`) axis values. 

Another registered axis is "opsz" (`DWRITE_FONT_AXIS_TAG_OPTICAL_SIZE`). An optical font family such as
Sitka includes fonts that differ along the "opsz" axis, meaning they are designed to be used at different
point sizes. The WWS font family model does not have an optical size axis, so the Sitka font family must
be split into multiple WWS font families: "Sitka Small", "Sitka Text", "Sitka Subheading", and so on. Each
WWS font family corresponds to a different optical size, and it's left to the user to specify the right
WWS family name for a given font size. With the typographic font family model, the user can simply choose
"Sitka", and the application can automatically set the "opsz" axis value based on the font size.

## Typographic Font Selection and Variable Fonts

The concept of axes of variation is often associated with variable fonts, but it also applies to static
fonts. The OpenType [STAT (style attributes)](https://docs.microsoft.com/en-us/typography/opentype/spec/stat)
table declares what design axes a font has and the values of those axes. This table is required for variable
fonts but is also relevant to static fonts.

The DirectWrite API exposes "wght", "wdth", "ital", and "slnt" axis values for every font, even if they
are not present in the STAT table or if there is no STAT table. These values are derived from the STAT
table if possible. Otherwise, they are derived from the font weight, font stretch, and font style.

Font axes may be variable or non-variable. A static font has only non-variable axes whereas a variable font
may have both. To use a variable font, one must create a variable font _instance_ in which all the variable
axes have been bound to particular values. The `IDWriteFontFace` interface represents either a static font or
a particular _instance_ of a variable font. It is possible to create an _arbitrary instance_ of a variable
font with specified axis values. In addition, a variable font may declare _named instances_ in the `STAT`
table with predefined combinations of axis values. Named instances enable a variable font to behave much
like a collection of static fonts. When you enumerate elements of an `IDWriteFontFamily` or `IDWriteFontSet`,
there is one element for each static font and for each named variable font instance.

The typographic font matching algorithm first selects potential match candidates based on the family name.
If the match candidates include variable fonts, all the match candidates for the same variable font
are collapsed into one match candidate in which each variable axis is assigned a specific value as
close as possible to the requested value for that axis. If there is no requested value for a variable
axis, it is assigned the default value for that axis. The order of the match candidates is then
determined by comparing their axis values with the requested axis values.

For example, consider the Sitka typographic family in Windows. Sitka is an optical font family,
meaning it has an "opsz" axis. In Windows 11, Sitka is implemented as two variable fonts with
the following axis values. Note that the `opsz` and `wght` axes are variable while the other
axes are non-variable.

File Name           | "opsz"    | "wght"    | "wdth"    | "ital"    | "slnt"
--------------------|-----------|-----------|-----------|-----------|----------
SitkaVF.ttf         | 6-27.5    | 400-700   | 100       | 0         | 0
SitkaVF-Italic.ttf  | 6-27.5    | 400-700   | 100       | 1         | -12

Suppose the requested axis values are `opsz:12 wght:475 wdth:100 ital:0 slnt:0`. For each variable
font, we create a reference to a variable font _instance_ in which each variable axis is assigned
a specific value. Namely, the `opsz` and `wght` axes are set to `12` and `475`, respectively.
This yields the following matching fonts, with the non-italic font ranked first because it's a
better match for the `ital` and `slnt` axes:

```
SitkaVF.ttf opsz:12 wght:475 wdth:100 ital:0 slnt0
SitkaVF-Italic.ttf opsz:12 wght:475 wdth:100 ital:1 slnt:-12
```

In the above example, the matching fonts are arbitrary variable font instances. There is no named
instance of Sitka with weight 475. In contrast, the weight-stretch-style matching algorithm only
returns named instances.

## Font Matching Order

There are different overloaded `GetMatchingFonts` methods for the weight-stretch-style font family
model and the typographic font family model. In both cases, the output is a list of matching fonts
in descending order of priority based on how well each candidate font matches the input properties.
This section describes how the priority is determined.

In the weight-stretch-style model, the input parameters are font weight (`DWRITE_FONT_WEIGHT`),
font stretch (`DWRITE_FONT_STRETCH`) and font style (`DWRITE_FONT_STYLE`). The algorithm for
finding the best match was documented in a 2006 white paper titled "WPF Font Selection Model" by
Mikhail Leonov and David Brown. See the section "Matching a face from the candidate face list."
This paper was about Windows Presentation Foundation (WPF), but DirectWrite later used the
same approach.

The algorithm uses the notion of _font attribute vector_, which for a given combination of
weight, stretch, and style is computed as follows:

```
FontAttributeVector.X = (stretch - 5) * 1100;
FontAttributeVector.Y = style * 700;
FontAttributeVector.Z = (weight - 400) * 5;
```

Note that each vector coordinate is normalized by subtracting the "normal" value for the
corresponding attribute and multiplying by a constant. The multipliers compensate for the fact
that the ranges of input values for weight, stretch, and style are very different. Otherwise,
weight (100..999) would dominate over style (0..2).

For each match candidate, a vector distance and a dot product are computed between the match
candidate's font attribute vector and the input font attribute vector. When comparing two match
candidates, the candidate with the smaller vector distance is the better match. If the distances
are the same, the candidate with the smaller dot product is a better match. If the dot product
is also the same, the distances along the X, Y, and Z axes are compared in that order.

Comparing distances is intuitive enough, but using dot product as a secondary measure may
require some explanation. Suppose the input weight is semibold (600) and two candidate
weights are black (900) and semilight (300). The distance of each candidate weight from the
input weight is the same, but the black weight is in the same direction from the origin
(i.e., 400 or normal), so it will have a smaller dot product.

The typographic matching algorithm is a generalization of the one for weight-stretch-style.
Each axis value is treated as a coordinate in an N-dimensional font attribute vector. For each
match candidate, a vector distance and a dot product are computed between the match candidate's
font attribute vector and the input font attribute vector. The candidate with the smaller vector
distance is the better match. If the distances are the same, the candidate with the smaller 
dot product is a better match. If the dot product is also the same, presence in a specified
weight-stretch-style family can be used as a tie-breaker.

To compute the vector distance and dot product, a match candidate's font attribute vector and
the input font attribute vector must have the same axes. Therefore, any missing axis value in
either vector is filled in by substituting the standard value for that axis. Vector coordinates
are normalized by subtracting the standard (or "normal") value for the corresponding axis and
multiplying the result by an axis-specific multiplier. Following are the multipliers and 
standard values for each axis:

Axis    | Multiplier    | Standard Value
--------|---------------|---------------
"wght"  | 5             | 400
"wdth"  | 55            | 100
"ital"  | 1400          | 0
"slnt"  | 35            | 0
"opsz"  | 1             | 12
other   | 1             | 0

The multipliers are consistent with those used by the weight-stretch-style algorithm, but scaled
as necessary. For example, normal width is 100, which is equivalent to stretch 5. This yields a
multiplier of 55 vs. 1100. The legacy style attribute (0..2) entangles italic and obliqueness,
which in the typographic model are decomposed into an "ital" axis (0..1) and a "slnt" axis
(-90..90). The chosen multipliers for these two axes give equivalent results to the legacy
algorithm if we assume a default 20-degree slant for oblique fonts.

## Typographic Font Selection and Optical Size

An application using the typographic font family model can implement optical sizing by specifying
an `opsz` axis value as a font selection parameter. For example, a word processing application could
specify an `opsz` axis value equal to the font size in points. In this case, a user could select
"Sitka" as the font family and the application would automatically select an instance of Sitka
with the correct `opsz` axis value. Under the WWS model, each optical size is exposed as a different
family name and it's up to the user to select the right one.

In theory, one could implement automatic optical sizing under the weight-stretch-style model by
overriding the `opsz` axis value as a separate step _after_ font selection. However, this only works
if the first matching font is a variable font with a variable `opsz` axis. Specifying `opsz` as a
font selection parameter works equally well for static fonts. For example, the Sitka font family
is implemented as variable fonts in Windows 11 but as a collection of static fonts in Windows 10.
The static fonts have different, non-overlapping `opsz` axis ranges. (These are declared as ranges
for font selection purposes, but they are not variable axes.) Specifying `opsz` as a font selection
parameter enables the correct static font for the optical size to be selected.

## Typographic Font Selection Advantages and Compatibility Issues

The typographic font selection model has several advantages over earlier models, but in its
pure form it has some potential compatibility issues. This section describes the advantages and
compatibility issues. The next section describes a hybrid font selection model that preserves
the advantages while mitigating the compatibility issues.

Advantages of the typographic font family model are:

  - Fonts can be grouped into families as intended by the designer, rather than being split into
    subfamilies due to limitations of the font family model.

  - An application can automatically select the correct "opsz" axis value based on the font size
    rather than exposing different optical sizes to the user as different font families.

  - Arbitrary instances of variable fonts can be selected. For example, if a variable font supports
    weights in the continuous range 100-900, the typographic model can select _any_ weight in this range.
    The older font family models can only choose the nearest weight from among the named instances defined
    by the font.

Compatibility issues with the typographic font selection model are:

  - Some older fonts cannot be selected unambiguously using only the typographic family name and
    axis values.

  - Existing documents might refer to fonts by WWS family name or RBIZ family name. Users might also 
    expect to use WWS and RBIZ family names. For example, a document might specify "Sitka Subheading" 
    (a WWS family name) instead of "Sitka" (a typographic family name).
    
  - A library or framework might adopt the typographic font family model to take advantage of automatic
    optical sizing, but not provide an API for specifing arbitrary axis values. Even if a new API is
    provided, the framework might need to work with existing applications that specify only weight,
    stretch, and style parameters.

The compatibility issue with older fonts arises because the concept of typographic family name predates
the concept of font axis values, which were introduced along with variable fonts in OpenType 1.8. Before
OpenType 1.8, the typographic family name merely expressed the designer's intent that a set fonts were
related, but with no guarantee that those fonts could be programmatically differentiated based on their
properties. As a hypothetical example, suppose all of the following fonts have the typographic family
name "Legacy":

Full Name               | WWS Family   | Weight    | Stretch   | Style  | Typo Family   | wght  | wdth  | ital  | slnt
------------------------|--------------|-----------|-----------|--------|---------------|-------|-------|-------|------
Legacy                  | Legacy       | 400       | 5         | 0      | Legacy        | 400   | 100   | 0     | 0
Legacy Bold             | Legacy       | 700       | 5         | 0      | Legacy        | 700   | 100   | 0     | 0
Legacy Black            | Legacy       | 900       | 5         | 0      | Legacy        | 900   | 100   | 0     | 0
Legacy Soft             | Legacy Soft  | 400       | 5         | 0      | Legacy        | 400   | 100   | 0     | 0
Legacy Soft Bold        | Legacy Soft  | 700       | 5         | 0      | Legacy        | 700   | 100   | 0     | 0
Legacy Soft Black       | Legacy Soft  | 900       | 5         | 0      | Legacy        | 900   | 100   | 0     | 0

The "Legacy" typographic family has three weights and each weight has regular and "Soft" variants.
If these were new fonts, they could be implemented as declaring a SOFT design axis. However, these fonts
predate OpenType 1.8, so their only design axes are those derived from weight, stretch, and style. For
each weight, this font family has two fonts with identical axis values, so it is not possible to 
unambiguously select a font in this family using axis values alone.

## Hybrid Font Selection Algorithm

The font selection APIs described in the next section use a hybrid font selection algorithm that
preserves the advantages of typographic font selection while mitigating its compatibilty issues.

Hybrid font selection provides a bridge from older font family models by enabling font weight,
font stretch, and font style values to be mapped to corresponding font axis values. This helps
address document and application compatibility issues.

In addition, the hybrid font selection algorithm allows the specified family name to be a 
typographic family name, weight-stretch-style family name, GDI/RBIZ family name, or a full 
font name. Matching occurs in one of the following ways, in descending order of priority:

 1. The name matches a typographic family (e.g., Sitka). Matching occurs within the typographic
    family and all requested axis values are used. If the name also matches a WWS subfamily
    (i.e., one smaller than the typographic family) then membership in the WWS subfamily is 
    used as a tie-breaker.

 2. The name matches a WWS family (e.g., Sitka Text). Matching occurs within the WWS family
    and requested axis values other than "wght", "wdth", "ital", and "slnt" are ignored.

 3. The name matches an GDI family (e.g., Bahnschrift Condensed). Matching occurs within 
    the RBIZ family and requested axis values other than "wght", "ital", and "slnt" are
    ignored.

 4. The name matches a full name (e.g., Bahnschrift Bold Condensed). The font matching the
    full name is returned. Requested axis values are ignored. Matching by full font name
    is allowed because GDI supports it.

The previous section described an ambiguous typographic family called "Legacy". The hybrid
algorithm enables the ambiguity to be avoided by specifying either "Legacy" or "Legacy Soft"
as the family name. If "Legacy Soft" is specified, then there is no ambiguity because matching
occurs only within the WWS family. If "Legacy" is specfiied then all fonts in the typographic
family are considered as match candidates, but ambiguity is avoided by using membership in
the "Legacy" WWS family as a tie-breaker.

Suppose a document specifies a family name and weight, stretch, and style parameters, but no axis
values. The application can first map the weight, stretch, style, and font size to axis values by
calling `IDWriteFontSet4::DeriveAxisValuesFromWeightStretchStyle`. The application can then pass both the family
name and axis values to `IDWriteFontSet4::GetMatchingFonts`. `GetMatchingFonts` returns a list of
matching fonts in priority order, and the result is appropriate whether the specified family name
is a typographic family name, weight-stretch-style family name, RBIZ family name, or full name.
If the specified family has an "opsz" axis, the appropriate optical size is automatically selected
based on the font size.

Suppose a document specifies weight, stretch, and style and _also_ specifies axis values. In this
case, the explicit axis values can also be passed in to `IDWriteFontSet4::DeriveAxisValuesFromWeightStretchStyle`,
and the derived axis values returned by the method will only include font axes that were not
specified explicitly. Thus, axis values specified explicitly by the document (or application) take
precedence over axis values derived from weight, stretch, style, and font size.

## Hybrid Font Selection APIs

The hybrid font selection model is implemented by the following `IDWriteFontSet4` methods:

  - The `DeriveAxisValuesFromWeightStretchStyle` method converts font size, weight, stretch, and style parameters
    to the corresponding axis values. Any explicit axis values passed in by the client are excluded
    from the derived axis values.

  - The `GetMatchingFonts` method returns a prioritized list of matching fonts given a family name
    and array of axis values. As described above, the family name parameter can be a typographic
    family name, WWS family name, RBIZ family name, or full name. (The full name identifies a 
    particular font style, such as "Arial Bold Italic". `GetMatchingFonts` supports matching by
    full name for greater comaptibiltiy with GDI, which also allows it.)

The following other DirectWrite APIs also use the hybrid font selection algorithm:

  - [`IDWriteFontCollection2::GetMatchingFonts`](https://docs.microsoft.com/windows/win32/api/dwrite_3/nf-dwrite_3-idwritefontcollection2-getmatchingfonts)

  - `IDWriteFontFallback1::MapCharacters`

  - `IDWriteTextLayout` if the typographic font family model is enabled by calling 
    `IDWriteTextLayout4::SetFontAxisValues` or `IDWriteTextLayout4::SetAutomaticFontAxes`

# Examples

## Creating an isolated factory

An application calls the `DWriteCoreCreateFactory` function to create a factory object, which is the entry-point
to all other DirectWrite APIs. An application can specify the new `DWRITE_FACTORY_TYPE_ISOLATED2` enum value if it
wants to minimize interaction between DirectWriteCore and the host system. Specifically, the resulting factory only
caches data in-process. It neither reads from nor writes to a cross-process cache (e.g., a font cache process) or
persistent cache (i.e., a file). In addition, the resulting factory's system font collection only includes
well-known system fonts.

The following example creates an isolated factory.

```c++
ComPtr<IDWriteFactory7> spFactory;
HRESULT hr = DWriteCoreCreateFactory(
    DWRITE_FACTORY_TYPE_ISOLATED2,
    __uuidof(IDWriteFactory7),
    (IUnknown**)&spFactory
    );
```

## Drawing glyphs to a system memory bitmap

An application creates a bitmap render target by calling [`IDWriteGdiInterop::CreateBitmapRenderTarget`](https://docs.microsoft.com/windows/win32/api/dwrite/nf-dwrite-idwritegdiinterop-createbitmaprendertarget).
A bitmap render target encapsulates a bitmap in system memory, and enables rendering glyphs to the bitmap. On Windows,
the bitmap is actually a GDI DIB selected into a memory HDC, and it is possible to get the bitmap pixels using GDI
functions. However, DWriteCore introduces a simpler method through the new IDWriteBitmapRenderTarget2 interface.
The following example shows both the old way and the new way.

```c++
DWRITE_BITMAP_DATA_BGRA32 TextRenderer::GetBitmapData(_In_ IDWriteBitmapRenderTarget* renderTarget)
{
    DWRITE_BITMAP_DATA_BGRA32 result = {};

    // Query the bitmap render target for the new interface.
    ComPtr<IDWriteBitmapRenderTarget2> renderTarget2;
    HRESULT hr = renderTarget->QueryInterface(&renderTarget2);
    if (SUCCEEDED(hr))
    {
        // IDWriteBitmapRenderTarget2 exists, so we can get the bitmap the easy way.
        hr = renderTarget2->GetBitmapData(&result);
        if (FAILED(hr))
        {
            throw Exception{ hr };
        }
    }
    else
    {
        // We're using an older version that doesn't implement IDWriteBitmapRenderTarget2,
        // so we have to get the bitmap by going through GDI. First get the bitmap handle.
        HDC hdc = renderTarget->GetMemoryDC();
        HGDIOBJ dibHandle = GetCurrentObject(hdc, OBJ_BITMAP);
        if (dibHandle == nullptr)
        {
            throw Exception{ HRESULT_FROM_WIN32(GetLastError()) };
        }

        // Call a GDI function to fill in the DIBSECTION structure for the bitmap.
        DIBSECTION dib;
        if (GetObjectW(dibHandle, sizeof(dib), &dib) != sizeof(dib))
        {
            throw Exception{ HRESULT_FROM_WIN32(GetLastError()) };
        }

        result.width = dib.dsBm.bmWidth;
        result.height = 0u - dib.dsBm.bmHeight; // bmHeight is negative for top-down DIB
        result.pixels = static_cast<uint32_t*>(dib.dsBm.bmBits);
    }

    return result;
}
```

## Using Font Selection APIs

This section shows a complete console application that demonstrates the `IDWriteFontSet4::GetMatchingFonts`
and `IDWriteFontSet4::DeriveAxisValuesFromWeightStretchStyle` methods. First let's include some headers:

```c++
#include <dwrite_core.h>
#include <wil/com.h>
#include <iostream>
#include <string>
#include <vector>
```

The `IDWriteFontSet4::GetMatchingFonts` method returns a list of fonts in priority order that match the
specified family name and axis values. The following `MatchAxisValues` function outputs the parameters 
to `GetMatchingFonts` and the list of matching fonts in the returned font set.

```c++
// Forward declarations of overloaded output operators used by MatchAxisValues.
std::wostream& operator<<(std::wostream& out, DWRITE_FONT_AXIS_VALUE const& axisValue);
std::wostream& operator<<(std::wostream& out, IDWriteFontFile* fileReference);
std::wostream& operator<<(std::wostream& out, IDWriteFontFaceReference1* faceReference);

//
// MatchAxisValues calls IDWriteFontSet4::GetMatchingFonts with the
// specified parameters and outputs the matching fonts.
//
void MatchAxisValues(
    IDWriteFontSet4* fontSet,
    _In_z_ WCHAR const* familyName,
    std::vector<DWRITE_FONT_AXIS_VALUE> const& axisValues,
    DWRITE_FONT_SIMULATIONS allowedSimulations
    )
{
    // Write the input parameters.
    std::wcout << L"GetMatchingFonts(\"" << familyName << L"\", {";
    for (DWRITE_FONT_AXIS_VALUE axisValue : axisValues)
    {
        std::wcout << L' ' << axisValue;
    }
    std::wcout << L" }, " << allowedSimulations << L"):\n";

    // Get the matching fonts for the specified family name and axis values.
    wil::com_ptr<IDWriteFontSet4> matchingFonts;
    THROW_IF_FAILED(fontSet->GetMatchingFonts(
        familyName,
        axisValues.data(),
        static_cast<UINT32>(axisValues.size()),
        allowedSimulations,
        &matchingFonts
    ));

    // Output the matching font face references.
    UINT32 const fontCount = matchingFonts->GetFontCount();
    for (UINT32 fontIndex = 0; fontIndex < fontCount; fontIndex++)
    {
        wil::com_ptr<IDWriteFontFaceReference1> faceReference;
        THROW_IF_FAILED(matchingFonts->GetFontFaceReference(fontIndex, &faceReference));
        std::wcout << L"    " << faceReference.get() << L'\n';
    }

    std::wcout << std::endl;
}
```

An application might have weight, stretch, and style parameters instead of (or in addition to) axis values.
For example, the application might need to work with documents that reference fonts using RBIZ or
weight-stretch-style parameters. Even if the application adds support for specifying arbitrary axis
values, it might need to support the older parameters as well. To do so, the application can call the
`IDWriteFontSet4::DeriveAxisValuesFromWeightStretchStyle` before calling `IDWriteFontSet4::GetMatchingFonts`.

The following `MatchFont` function takes weight, stretch, style, and font size parameters in addition to
axis values. It forwards these parameters to the `IDWriteFontSet4::DeriveAxisValuesFromWeightStretchStyle` 
method to compute derived axis values, which are appended to the input axis values. It passes the combined 
axis values to the above `MatchAxisValues` function.

```c++
struct FontStyleParams
{
    FontStyleParams() {}
    FontStyleParams(DWRITE_FONT_WEIGHT fontWeight) : fontWeight{ fontWeight } {}
    FontStyleParams(float fontSize) : fontSize{ fontSize } {}

    DWRITE_FONT_WEIGHT fontWeight = DWRITE_FONT_WEIGHT_NORMAL;
    DWRITE_FONT_STRETCH fontStretch = DWRITE_FONT_STRETCH_NORMAL;
    DWRITE_FONT_STYLE fontStyle = DWRITE_FONT_STYLE_NORMAL;
    float fontSize = 0.0f;
};

//
// MatchFont calls IDWriteFontSet4::DeriveAxisValuesFromWeightStretchStyle to convert
// the input parameters to axis values and then calls MatchAxisValues.
//
void MatchFont(
    IDWriteFactory7* factory,
    _In_z_ WCHAR const* familyName,
    FontStyleParams styleParams = {},
    std::vector<DWRITE_FONT_AXIS_VALUE> axisValues = {},
    DWRITE_FONT_SIMULATIONS allowedSimulations = DWRITE_FONT_SIMULATIONS_BOLD | DWRITE_FONT_SIMULATIONS_OBLIQUE
    )
{
    wil::com_ptr<IDWriteFontSet2> fontSet2;
    THROW_IF_FAILED(factory->GetSystemFontSet(/*includeDownloadableFonts*/ false, &fontSet2));

    wil::com_ptr<IDWriteFontSet4> fontSet;
    THROW_IF_FAILED(fontSet2->QueryInterface(&fontSet));

    // Ensure the total number of axis values can't overflow a UINT32.
    size_t const inputAxisCount = axisValues.size();
    if (inputAxisCount > UINT32_MAX - DWRITE_STANDARD_FONT_AXIS_COUNT)
    {
        THROW_HR(E_INVALIDARG);
    }

    // Reserve space at the end of axisValues vector for the derived axis values.
    // The maximum number of derived axis values is DWRITE_STANDARD_FONT_AXIS_COUNT.
    axisValues.resize(inputAxisCount + DWRITE_STANDARD_FONT_AXIS_COUNT);

    // Convert the weight, stretch, style, and font size to derived axis values.
    UINT32 derivedAxisCount = fontSet->DeriveAxisValuesFromWeightStretchStyle(
        /*inputAxisValues*/ axisValues.data(),
        static_cast<UINT32>(inputAxisCount),
        styleParams.fontWeight,
        styleParams.fontStretch,
        styleParams.fontStyle,
        styleParams.fontSize,
        /*out*/ axisValues.data() + inputAxisCount
        );

    // Resize the vector based on the actual number of derived axis values returned.
    axisValues.resize(inputAxisCount + derivedAxisCount);

    // Pass the combined axis values (explicit and derived) to MatchAxisValues.
    MatchAxisValues(fontSet.get(), familyName, axisValues, allowedSimulations);
}
```

The following function demonstrates the results of calling the above `MatchFont` function
with some example inputs:

```c++
void TestFontSelection(IDWriteFactory7* factory)
{
    // Request "Cambria" with bold weight, with and without allowing simulations.
    //  - Matches a typographic/WWS family.
    //  - Result includes all fonts in the family ranked by priority.
    //  - Useful because Cambria Bold might have fewer glyphs than Cambria Regular.
    //  - Simulations may be applied if allowed.
    MatchFont(factory, L"Cambria", DWRITE_FONT_WEIGHT_BOLD);
    MatchFont(factory, L"Cambria", DWRITE_FONT_WEIGHT_BOLD, {}, DWRITE_FONT_SIMULATIONS_NONE);

    // Request "Cambria Bold".
    //  - Matches the full name of one static font.
    MatchFont(factory, L"Cambria Bold");

    // Request "Bahnschrift" with bold weight.
    //  - Matches a typographic/WWS family.
    //  - Returns an arbitrary instance of the variable font.
    MatchFont(factory, L"Bahnschrift", DWRITE_FONT_WEIGHT_BOLD);

    // Request "Segoe UI Variable" with two different font sizes.
    //  - Matches a typographic family name only (not a WWS family name).
    //  - Font size maps to "opsz" axis value (Note conversion from DIPs to points.)
    //  - Returns an arbitrary instance of the variable font.
    MatchFont(factory, L"Segoe UI Variable", 16.0f);
    MatchFont(factory, L"Segoe UI Variable", 32.0f);

    // Same as above with an explicit opsz axis value.
    // The explicit value is used instead of an "opsz" value derived from the font size.
    MatchFont(factory, L"Segoe UI Variable", 16.0f, { { DWRITE_FONT_AXIS_TAG_OPTICAL_SIZE, 32.0f } });

    // Request "Segoe UI Variable Display".
    //  - Matches a WWS family (NOT a typographic family).
    //  - The input "opsz" value is ignored; the optical size of the family is used.
    MatchFont(factory, L"Segoe UI Variable Display", 16.0f);

    // Request "Segoe UI Variable Display Bold".
    //  - Matches the full name of a variable font instance.
    //  - All input axes are ignored; the axis values of the matching font are used.
    MatchFont(factory, L"Segoe UI Variable Display Bold", 16.0f);
}
```

Following is the output of the above `TestFontSelection` function:

```
GetMatchingFonts("Cambria", { wght:700 wdth:100 ital:0 slnt:0 }, 3):
    cambriab.ttf wght:700 wdth:100 ital:0 slnt:0
    cambria.ttc wght:400 wdth:100 ital:0 slnt:0 BOLDSIM
    cambriaz.ttf wght:700 wdth:100 ital:1 slnt:-12.4
    cambriai.ttf wght:400 wdth:100 ital:1 slnt:-12.4 BOLDSIM

GetMatchingFonts("Cambria", { wght:700 wdth:100 ital:0 slnt:0 }, 0):
    cambriab.ttf wght:700 wdth:100 ital:0 slnt:0
    cambriaz.ttf wght:700 wdth:100 ital:1 slnt:-12.4
    cambria.ttc wght:400 wdth:100 ital:0 slnt:0
    cambriai.ttf wght:400 wdth:100 ital:1 slnt:-12.4

GetMatchingFonts("Cambria Bold", { wght:400 wdth:100 ital:0 slnt:0 }, 3):
    cambriab.ttf wght:700 wdth:100 ital:0 slnt:0

GetMatchingFonts("Bahnschrift", { wght:700 wdth:100 ital:0 slnt:0 }, 3):
    bahnschrift.ttf wght:700 wdth:100 ital:0 slnt:0

GetMatchingFonts("Segoe UI Variable", { wght:400 wdth:100 ital:0 slnt:0 opsz:12 }, 3):
    SegUIVar.ttf opsz:12 wght:400 wdth:100 ital:0 slnt:0

GetMatchingFonts("Segoe UI Variable", { wght:400 wdth:100 ital:0 slnt:0 opsz:24 }, 3):
    SegUIVar.ttf opsz:24 wght:400 wdth:100 ital:0 slnt:0

GetMatchingFonts("Segoe UI Variable", { opsz:32 wght:400 wdth:100 ital:0 slnt:0 }, 3):
    SegUIVar.ttf opsz:32 wght:400 wdth:100 ital:0 slnt:0

GetMatchingFonts("Segoe UI Variable Display", { wght:400 wdth:100 ital:0 slnt:0 opsz:12 }, 3):
    SegUIVar.ttf opsz:36 wght:400 wdth:100 ital:0 slnt:0

GetMatchingFonts("Segoe UI Variable Display Bold", { wght:400 wdth:100 ital:0 slnt:0 opsz:12 }, 3):
    SegUIVar.ttf opsz:36 wght:700 wdth:100 ital:0 slnt:0
```

Following are the implementations of the overloaded operators declared above. These are used
by `MatchAxisValues` to write the input axis values and the resulting font face references:

```c++
// Output a font axis value.
std::wostream& operator<<(std::wostream& out, DWRITE_FONT_AXIS_VALUE const& axisValue)
{
    UINT32 tagValue = axisValue.axisTag;
    WCHAR tagChars[5] =
    {
        static_cast<WCHAR>(tagValue & 0xFF),
        static_cast<WCHAR>((tagValue >> 8) & 0xFF),
        static_cast<WCHAR>((tagValue >> 16) & 0xFF),
        static_cast<WCHAR>((tagValue >> 24) & 0xFF),
        '\0'
    };

    return out << tagChars << L':' << axisValue.value;
}

// Output a file name given a font file reference.
std::wostream& operator<<(std::wostream& out, IDWriteFontFile* fileReference)
{
    wil::com_ptr<IDWriteFontFileLoader> loader;
    THROW_IF_FAILED(fileReference->GetLoader(&loader));

    wil::com_ptr<IDWriteLocalFontFileLoader> localLoader;
    if (SUCCEEDED(loader->QueryInterface(&localLoader)))
    {
        const void* fileKey;
        UINT32 fileKeySize;
        THROW_IF_FAILED(fileReference->GetReferenceKey(&fileKey, &fileKeySize));

        WCHAR filePath[MAX_PATH];
        THROW_IF_FAILED(localLoader->GetFilePathFromKey(fileKey, fileKeySize, filePath, MAX_PATH));

        WCHAR* fileName = wcsrchr(filePath, L'\\');
        fileName = (fileName != nullptr) ? fileName + 1 : filePath;

        out << fileName;
    }
    return out;
}

// Output a font face reference.
std::wostream& operator<<(std::wostream& out, IDWriteFontFaceReference1* faceReference)
{
    // Output the font file name.
    wil::com_ptr<IDWriteFontFile> fileReference;
    THROW_IF_FAILED(faceReference->GetFontFile(&fileReference));
    std::wcout << fileReference.get();

    // Output the face index if nonzero.
    UINT32 const faceIndex = faceReference->GetFontFaceIndex();
    if (faceIndex != 0)
    {
        out << L'#' << faceIndex;
    }

    // Output the axis values.
    UINT32 const axisCount = faceReference->GetFontAxisValueCount();
    std::vector<DWRITE_FONT_AXIS_VALUE> axisValues(axisCount);
    THROW_IF_FAILED(faceReference->GetFontAxisValues(axisValues.data(), axisCount));
    for (DWRITE_FONT_AXIS_VALUE const& axisValue : axisValues)
    {
        out << L' ' << axisValue;
    }

    // Output the simulations.
    DWRITE_FONT_SIMULATIONS simulations = faceReference->GetSimulations();
    if (simulations & DWRITE_FONT_SIMULATIONS_BOLD)
    {
        out << L" BOLDSIM";
    }
    if (simulations & DWRITE_FONT_SIMULATIONS_OBLIQUE)
    {
        out << L" OBLIQUESIM";
    }

    return out;
}
```

To round out the sample, following are command-line parsing functions and the `main` function:

```c++
char const g_usage[] =
"ParseCmdLine <args>\n"
"\n"
" -test             Test sample font selection parameters.\n"
" <familyname>      Sets the font family name.\n"
" -size <value>     Sets the font size in DIPs.\n"
" -bold             Sets weight to bold (700).\n"
" -weight <value>   Sets a weight in the range 100-900.\n"
" -italic           Sets style to DWRITE_FONT_STYLE_ITALIC.\n"
" -oblique          Sets style to DWRITE_FONT_STYLE_OBLIQUE.\n"
" -stretch <value>  Sets a stretch in the range 1-9.\n"
" -<axis>:<value>   Sets an axis value (e.g., -opsz:24).\n"
" -nosim            Disallow font simulations.\n"
"\n";

struct CmdArgs
{
    std::wstring familyName;
    FontStyleParams styleParams;
    std::vector<DWRITE_FONT_AXIS_VALUE> axisValues;
    DWRITE_FONT_SIMULATIONS allowedSimulations = DWRITE_FONT_SIMULATIONS_BOLD | DWRITE_FONT_SIMULATIONS_OBLIQUE;
    bool test = false;
};

template<typename T>
_Success_(return)
bool ParseEnum(_In_z_ WCHAR const* arg, long minValue, long maxValue, _Out_ T* result)
{
    WCHAR* endPtr;
    long value = wcstol(arg, &endPtr, 10);
    *result = static_cast<T>(value);
    return value >= minValue && value <= maxValue && *endPtr == L'\0';
}

_Success_(return)
bool ParseFloat(_In_z_ WCHAR const* arg, _Out_ float* value)
{
    WCHAR* endPtr;
    *value = wcstof(arg, &endPtr);
    return *arg != L'\0' && *endPtr == L'\0';
}

bool ParseCommandLine(int argc, WCHAR** argv, CmdArgs& cmd)
{
    for (int argIndex = 1; argIndex < argc; argIndex++)
    {
        WCHAR const* arg = argv[argIndex];

        if (*arg != L'-')
        {
            if (!cmd.familyName.empty())
                return false;

            cmd.familyName = argv[argIndex];
        }
        else if (!wcscmp(arg, L"-test"))
        {
            cmd.test = true;
        }
        else if (!wcscmp(arg, L"-size"))
        {
            if (++argIndex == argc)
                return false;
            if (!ParseFloat(argv[argIndex], &cmd.styleParams.fontSize))
                return false;
        }
        else if (!wcscmp(arg, L"-bold"))
        {
            cmd.styleParams.fontWeight = DWRITE_FONT_WEIGHT_BOLD;
        }
        else if (!wcscmp(arg, L"-weight"))
        {
            if (++argIndex == argc)
                return false;
            if (!ParseEnum(argv[argIndex], 100, 900, &cmd.styleParams.fontWeight))
                return false;
        }
        else if (!wcscmp(arg, L"-italic"))
        {
            cmd.styleParams.fontStyle = DWRITE_FONT_STYLE_ITALIC;
        }
        else if (!wcscmp(arg, L"-oblique"))
        {
            cmd.styleParams.fontStyle = DWRITE_FONT_STYLE_OBLIQUE;
        }
        else if (!wcscmp(arg, L"-stretch"))
        {
            if (++argIndex == argc)
                return false;
            if (!ParseEnum(argv[argIndex], 1, 9, &cmd.styleParams.fontStretch))
                return false;
        }
        else if (wcslen(arg) > 5 && arg[5] == L':')
        {
            // Example: -opsz:12
            DWRITE_FONT_AXIS_VALUE axisValue;
            axisValue.axisTag = DWRITE_MAKE_FONT_AXIS_TAG(arg[1], arg[2], arg[3], arg[4]);
            if (!ParseFloat(arg + 6, &axisValue.value))
                return false;
            cmd.axisValues.push_back(axisValue);
        }
        else if (!wcscmp(arg, L"-nosim"))
        {
            cmd.allowedSimulations = DWRITE_FONT_SIMULATIONS_NONE;
        }
        else
        {
            return false;
        }
    }

    return true;
}

int __cdecl wmain(int argc, WCHAR** argv)
{
    CmdArgs cmd;
    if (!ParseCommandLine(argc, argv, cmd))
    {
        std::cerr << "Invalid command. Type TestFontSelection with no arguments for usage.\n";
        return 1;
    }

    if (cmd.familyName.empty() && !cmd.test)
    {
        std::cout << g_usage;
        return 0;
    }

    wil::com_ptr<IDWriteFactory7> factory;
    THROW_IF_FAILED(DWriteCoreCreateFactory(
        DWRITE_FACTORY_TYPE_SHARED,
        __uuidof(IDWriteFactory7),
        (IUnknown**)&factory
    ));

    if (!cmd.familyName.empty())
    {
        MatchFont(
            factory.get(),
            cmd.familyName.c_str(),
            cmd.styleParams,
            std::move(cmd.axisValues),
            cmd.allowedSimulations
        );
    }

    if (cmd.test)
    {
        TestFontSelection(factory.get());
    }
}
```

# API Details

## DWRITE_FACTORY_TYPE Enumeration

```c++
/// <summary>
/// Specifies the type of DirectWrite factory object.
/// DirectWrite factory contains internal state such as font loader registration and cached font data.
/// In most cases it is recommended to use the shared factory object, because it allows multiple components
/// that use DirectWrite to share internal DirectWrite state and reduce memory usage.
/// However, there are cases when it is desirable to reduce the impact of a component,
/// such as a plug-in from an untrusted source, on the rest of the process by sandboxing and isolating it
/// from the rest of the process components. In such cases, it is recommended to use an isolated factory for the sandboxed
/// component.
/// </summary>
enum DWRITE_FACTORY_TYPE
{
    /// <summary>
    /// This is the recommended value in most cases. The shared factory is a singleton, so mulitiple
    /// components in a process that create a shared factory share a single instance. This enables
    /// reuse of cached font data and other state across multiple components. In addition, objects
    /// created from a shared factory can read from and/or modify a cross-process or persistent cache.
    /// </summary>
    DWRITE_FACTORY_TYPE_SHARED,

    /// <summary>
    /// Objects created from an isolated factory do not modify internal state or cached data used by
    /// objects from other factories. However, they may still read from a cross-process or persistent
    /// cache.
    /// </summary>
    DWRITE_FACTORY_TYPE_ISOLATED,

#if DWRITE_CORE
    /// <summary>
    /// Objects created from an "isolated2" factory do not use or modify internal state or cached data
    /// used by other factories. In addition, the system font collection contains only well-known fonts.
    /// </summary>
    // Warning: Make sure any additional new enum values are consistent between different versions of
    // this header in DWriteCore and the Windows SDK.
    DWRITE_FACTORY_TYPE_ISOLATED2
#endif
};
```

## DWriteCoreCreateFactory Function

```c++
/// <summary>
/// Creates a factory object that is used for subsequent creation of individual DWriteCore objects.
/// </summary>
/// <param name="factoryType">Identifies whether the factory object will be shared or isolated.</param>
/// <param name="iid">Identifies the DirectWrite factory interface, such as UUIDOF(IDWriteFactory).</param>
/// <param name="factory">Receives the DirectWrite factory object.</param>
/// <returns>
/// Standard HRESULT error code.
/// </returns>
/// <remarks>
/// This is functionally the same as the DWriteCreateFactory function exported by the system version
/// of DirectWrite. The DWriteCore function has a different name to avoid ambiguity.
/// </remarks>
EXTERN_C HRESULT DWRITE_EXPORT DWriteCoreCreateFactory(
    _In_ DWRITE_FACTORY_TYPE factoryType,
    _In_ REFIID iid,
    _COM_Outptr_ IUnknown** factory
);
```

## DWRITE_BITMAP_DATA_BGRA32 Structure

```c++
/// <summary>
/// Contains information about a bitmap associated with an IDWriteBitmapRenderTarget.
/// The bitmap is top-down with 32-bits per pixel and no padding between scan lines.
/// </summary>
struct DWRITE_BITMAP_DATA_BGRA32
{
    UINT32 width;
    UINT32 height;
    _Field_size_(width * height) UINT32* pixels;
};
```

## IDWriteBitmapRenderTarget2 Interface

```c++
/// <summary>
/// Encapsulates a bitmap which can be used for rendering glyphs.
/// </summary>
DWRITE_BEGIN_INTERFACE(IDWriteBitmapRenderTarget2, "C553A742-FC01-44DA-A66E-B8B9ED6C3995") : IDWriteBitmapRenderTarget1
{
    /// <summary>
    /// Gets the demensions and a pointer to the system memory bitmap encapsulated by this
    /// bitmap render target object. The pointer is owned by the render target object, and
    /// remains valid as long as the object exists.
    /// </summary>
    STDMETHOD(GetBitmapData)(_Out_ DWRITE_BITMAP_DATA_BGRA32* bitmapData) PURE;
};
```

## IDWriteFontSet4 Interface

```c++
DWRITE_BEGIN_INTERFACE(IDWriteFontSet4, "EEC175FC-BEA9-4C86-8B53-CCBDD7DF0C82") : IDWriteFontSet3
{
    /// <summary>
    /// Computes derived font axis values from the specified font weight, stretch, style, and size.
    /// </summary>
    /// <param name="inputAxisValues">Pointer to an optional array of input axis values. Any axes present
    /// in this array are not included in the output. This is so explicit axis values take precedence over 
    /// derived axis values.</param>
    /// <param name="inputAxisCount">Size of the array of input axis values.</param>
    /// <param name="fontWeight">Font weight, used to compute "wght" axis value.</param>
    /// <param name="fontStretch">Font stretch, used to compute "wdth" axis value.</param>
    /// <param name="fontStyle">Font style, used to compute "slnt" and "ital" axis values.</param>
    /// <param name="fontSize">Font size in DIPs, used to compute "opsz" axis value. If this parameter is zero,
    /// no "opsz" axis value is added to the output array.</param>
    /// <param name="derivedAxisValues">Pointer to an output array to which derived axis values are written.
    /// The size of this array must be at least DWRITE_STANDARD_FONT_AXIS_COUNT (5). The return value is 
    /// the actual number of axis values written to this array.</param>
    /// <returns>Returns the actual number of derived axis values written to the output array.</returns>
    STDMETHOD_(UINT32, DeriveAxisValuesFromWeightStretchStyle)(
        _In_reads_opt_(inputAxisCount) DWRITE_FONT_AXIS_VALUE const* inputAxisValues,
        UINT32 inputAxisCount,
        DWRITE_FONT_WEIGHT fontWeight,
        DWRITE_FONT_STRETCH fontStretch,
        DWRITE_FONT_STYLE fontStyle,
        float fontSize,
        _Out_writes_to_(DWRITE_STANDARD_FONT_AXIS_COUNT, return) DWRITE_FONT_AXIS_VALUE* derivedAxisValues
        ) PURE;

    /// <summary>
    /// Generates a matching font set based on the requested inputs, ordered so that nearer matches are earlier.
    /// </summary>
    /// <param name="familyName">Font family name. This can be a typographic family name, weight/stretch/style
    /// family name, GDI (RBIZ) family name, or full name.</param>
    /// <param name="fontAxisValues">Array of font axis values.</param>
    /// <param name="fontAxisValueCount">Number of font axis values.</param>
    /// <param name="allowedSimulations">Specifies which simulations (i.e., algorithmic emboldening and/or slant)
    /// may be applied to matching fonts to better match the specified axis values. No simulations are applied if
    /// this parameter is DWRITE_FONT_SIMULATIONS_NONE (0).</param>
    /// <param name="matchingFonts">Receives a pointer to a newly-created font set, which contains a prioritized 
    /// list of fonts that match the specified inputs.</param>
    /// <returns>
    /// Standard HRESULT error code.
    /// </returns>
    /// <remarks>
    /// This can yield distinct items that were not in the original font set, including items with simulation flags
    /// (if they would be a closer match to the request) and instances that were not named by the font author.
    /// Items from the same font resources are collapsed into one, the closest possible match.
    /// </remarks>
    STDMETHOD(GetMatchingFonts)(
        _In_z_ WCHAR const* familyName,
        _In_reads_(fontAxisValueCount) DWRITE_FONT_AXIS_VALUE const* fontAxisValues,
        UINT32 fontAxisValueCount,
        DWRITE_FONT_SIMULATIONS allowedSimulations,
        _COM_Outptr_ IDWriteFontSet4** matchingFonts
        ) PURE;
};
```

## IDWriteFactory7 Interface

```c++
DWRITE_BEGIN_INTERFACE(IDWriteFactory8, "202D44F0-84AC-4D6F-B8D0-704B27675CAA") : IDWriteFactory7
{
    /// <summary>
    /// Releases recently used font objects and font file streams that that may be cached by the
    /// factory object. An application might call this method to ensure file handles are closed
    /// before uninstalling a font.
    /// </summary>
    /// <remarks>
    /// This method does not release fonts to which the application still holds references. For
    /// example, an application might hold a font references through an IDWriteFontFace object
    /// or indirectly through an IDWriteTextLayout object.
    /// This method only releases fonts cached by the current factory. It does not affect other
    /// factories or other processes.
    /// </remarks>
    STDMETHOD_(void, ReleaseUnreferencedFonts)(
        ) PURE;
};
```
