# DWriteCore

DWriteCore is the Windows App SDK version of DirectWrite, the text rendering and layout component
that ships in Windows. DWriteCore implements the same API as DirectWrite, with a few additions
described in this document. See the
[DirectWrite documentation](https://docs.microsoft.com/windows/win32/api/_directwrite/) for more
information.

For an application that already uses DirectWrite, switching to DWriteCore requires minimal changes:

-   Add a reference to the Windows App SDK package.
-   Include dwrite_core.h instead of dwrite_3.h.
-   Link to DWriteCore.lib instead of DWrite.lib.
-   Call DWriteCoreCreateFactory instead of DWriteCreateFactory.

In return, the application gets the benefits of Windows App SDK, namely, access to the newest APIs
and functionality regardless of what version of Windows your customer is running.

## Background

The DWriteCore API is the same as the existing public DirectWrite API, with a few additions. These
additions should eventually be incorporated into the in-box DirectWrite as well, so it is
appropriate to think of the DWriteCore API as just the latest version of the DirectWrite API. This
document focuses primarily on the additions.

### API Versioning

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
copy of dwrite_3.h in the DWriteCore package therefore uses the following convention to
conditionalize API definitions:

```c++
#if DWRITE_CORE || NTDDI_VERSION >= NTDDI_WIN10_MN
    . . . APIs introduced in MN . . .
#endif // DWRITE_CORE || NTDDI_VERSION >= NTDDI_WIN10_MN

#if DWRITE_CORE
    . . . New APIs not yet in any in-box version of DWrite . . .
#endif // DWRITE_CORE
```

The DWriteCore NuGet package includes a header file named dwrite_core.h as well as the newest
versions of the existing DirectWrite header files (dwrite_3.h, dwrite_2.h, and dwrite_1.h,
dwrite.h). The dwrite_core.h simply defines the DWRITE_CORE preprocessor symbol and then includes
dwrite_3.h. In this way, an application that includes dwrite_core.h has access to all DirectWrite
APIs regardless of the NTDDI_VERSION.

### Cross-Platform Considerations

DWriteCore runs on non-Windows platforms in addition to the down-level Windows versions targetted by
Windows App SDK. In order to compile cross-platform, it is necessary to have definitions of Windows
types and constants used by the DirectWrite API -- for example, IUnknown, HRESULT, etc. The
DWriteCore project has an “xplatwin” directory with a set of header files that contain portable
definitions of these things, as well as mechanisms to avoid the use of compiler extensions like
**declspec(uuid(x)) and **uuidof.

Another consideration on non-Windows platforms is the definition of WCHAR. Most projects define
WCHAR as wchar_t which is a 32-bit type everywhere except Windows, but Office relies on WCHAR being
16 bits. Therefore, DWriteCore’s cross-platform headers defines WCHAR as either char16_t or wchar_t,
depending on a preprocessor definition, and we build both 16-bit and 32-bit flavors.

This is outside the scope of the API itself, but is mentioned here because other cross-platform
libraries will have to solve the same problem, and if each library solves the problem in its own
way, we may end up with interoperability issues.

## Description

New APIs introduced by DWriteCore include:

-   The exported function is renamed `DWriteCoreCreateFactory` to avoid a naming collision with the
    `DWriteCreateFactory` function exported by the system version of DirectWrite (DWrite.dll)
-   A new `DWRITE_FACTORY_TYPE` value which specifies an isolated factory object
-   A new method for getting pixel data from a bitmap render target
-   New methods for selecting fonts from a font set
-   A new factory method to release unreferenced fonts

## Factory Creation

The new `DWRITE_FACTORY_TYPE_ISOLATED2` enumerator complements the existing factory types. It is
similar to `DWRITE_FACTORY_TYPE_ISOLATED`, but is more locked down in two ways. First, it only
caches data in-process, and will not attempt to either read from or write to a cross-process font
cache or persisted cache file. Second, a `DWRITE_FACTORY_TYPE_ISOLATED2` factory only enumerates
well-known fonts in the system font collection. The well-known-fonts restriction enables the
implementation to efficiently construct the system font collection without depending on a
cross-process or persistent cache. An example use case for the new factory type would be a web
browser rendering process with very limited permissions.

## Text Rendering

A _bitmap render target_ (`IDWriteBitmapRenderTarget`) is an API object that encapsulates a system
memory bitmap and enables rendering glyphs to the bitmap. On Windows, the object encapsulates a GDI
memory DC with a GDI device-independent bitmap (DIB) selected into it. However, on non-Windows
platforms, there is no GDI DC, and the bitmap is just a system memory array. DWriteCore introduces a
new version of the bitmap render target interface that an application can use to access the bitmap
data without going through GDI.

## Font Selection

The new `IDWriteFontSet4` interface exposes new methods for selecting fonts from a font set. The new
methods make it possible to transition to the _typographic font family model_ while maintaining
compatibility with existing applications, documents, and fonts.

Font selection (sometimes called font matching or font mapping) is the process of selecting the
available fonts that best match input parameters passed in by an application. The input parameters
are sometimes referred to collectively as a _logical font_. A logical font includes a font family
name plus other attributes indicating a particular font within the family. A font selection
algorithm matches the logical font (the "font you want") to an available _physical font_ (a "font
you have").

A _font family_ is a named group of fonts that share a common design but may differ in attributes
such as weight. A _font family model_ defines what attributes may be used to differentiate fonts
within a family. The new _typographic font family model_ has many advantages over the two previous
font family models used on Windows. Unfortunately, changing font family models creates opportunities
for confusion and compatibility issues. The methods exposed by the `IDWriteFontSet4` interface
implement a hybrid approach that offers the advantages of the typographic font family model while
mitigating compatibility issues.

The following sections compare the older font family models with the typographic font family model,
explain compatibility challenges posed by changing font family models, and finally explains how
those challenges can be overcome by using the `IDWriteFontSet4` methods.

### RBIZ Font Family Model

The de facto font family model used in the GDI application ecosystem is sometimes called the
"four-font model" or "RBIZ" model. Each font family in this model typically has at most four fonts.
The "RBIZ" label comes from the naming convention used for some font files, for example:

| File Name    | Font Style  |
| ------------ | ----------- |
| verdana.ttf  | Regular     |
| verdanab.ttf | Bold        |
| verdanai.ttf | Italic      |
| verdanaz.ttf | Bold Italic |

With GDI, the input parameters used to select a font are defined by the `LOGFONT` structure, which
includes family name (`lfFaceName`), weight (`lfWeight`) and italic (`lfItalic`) fields. The
`lfItalic` field is either TRUE or FALSE. GDI allows the `lfWeight` field to be any value in the
range `FW_THIN` (100) to `FW_BLACK` (900), but for historical reasons fonts have long been designed
such that there are no more than two weights in the same GDI font family.

Popular application user interfaces from early on included an italic button (to turn italic on and
off) and a bold button (to toggle between normal and bold weights). The use of these two buttons to
select fonts within a family assumes the RBIZ model. Therefore, even though GDI itself supports more
than two weights, application compatibility led font developers to set the GDI family name (OpenType
name ID 1) in a way that was consistent with the RBIZ model.

For example, suppose you wanted to add a heavier "Black" weight to the Arial font family. Logically,
this font is part of the Arial family, so you might expect to select it by setting `lfFaceName` to
"Arial" and `lfWeight` to `FW_BLACK`. However, there is no way for an application user to choose
between three weights using a two-state bold button. The solution was to give the new font a
different family name, so the user could select it by choosing "Arial Black" from the list of font
families. Likewise, there is no way to choose from among different widths in the same font family
using only bold and italic buttons, so the narrow versions of Arial have different family names in
the RBIZ model. Thus we have "Arial", "Arial Black", and "Arial Narrow" font familes in the RBIZ
model even though typographically these all belong in one family.

From these examples, one can see how the limitations of a font family model can affect how fonts are
grouped into families. Since font families are identified by name, this means the same font can have
different family names depending on which font family model you're using.

DirectWrite does not directly support the RBIZ font family model, but it does provide methods of
converting to and from the RBIZ model, such as `IDWriteGdiInterop::CreateFontFromLOGFONT` and
`IDWriteGdiInterop::ConvertFontToLOGFONT`. You can also get the RBIZ family name of a font by
calling its `GetInformationalStrings` method and specifying
`DWRITE_INFORMATIONAL_STRING_WIN32_FAMILY_NAMES`.

### Weight-Stretch-Style Font Family Model

The weight-stretch-style font family model is the original font family model used by DirectWrite
before the typographic font family model was introduced. It is also known as weight-width-slope
(WWS). In the WWS model, fonts within the same family can be differented by three properties: weight
(`DWRITE_FONT_WEIGHT`), stretch (`DWRITE_FONT_STRETCH`), and style (`DWRITE_FONT_STYLE`).

The WWS model is more flexible than the RBIZ model in two ways. First, fonts in the same family can
be differentiated by stretch (or width) as well as weight and style (regular, italic or oblique).
Second, there can be more than two weights in the same family. This flexibility is sufficient to
allow all the variants of Arial to be included in the same WWS family. The following table compares
RBIZ and WWS font properties for a selection of Arial fonts:

| Full Name         | RBIZ Family Name | lfWeight | lfItalic | WWS FamilyName | Weight | Stretch | Style |
| ----------------- | ---------------- | -------- | -------- | -------------- | ------ | ------- | ----- |
| Arial             | Arial            | 400      | 0        | Arial          | 400    | 5       | 0     |
| Arial Bold        | Arial            | 700      | 0        | Arial          | 700    | 5       | 0     |
| Arial Black       | Arial Black      | 900      | 0        | Arial          | 900    | 5       | 0     |
| Arial Narrow      | Arial Narrow     | 400      | 0        | Arial          | 400    | 3       | 0     |
| Arial Narrow Bold | Arial Narrow     | 700      | 0        | Arial          | 700    | 3       | 0     |

As you can see, "Arial Narrow" has the same `lfWeight` and `lfItalic` values as "Arial", so it has a
different RBIZ family name to avoid ambiguity. "Arial Black" has a different RBIZ family name to
avoid having more than two weights in the "Arial" family. By contrast, all of these fonts are in the
same weight-stretch-style family.

Nevertheless, the weight-stretch-style model is not open-ended. If two fonts have the same weight,
stretch, and style but differ in some other way (e.g., optical size), they cannot be included in the
same WWS font family. This brings us to the typographic font family model.

### Typographic Font Family Model

Unlike its predecessors, the typographic font family model is open-ended. It supports any number of
axes of variation within a font family.

If you think of font selection parameters as coordinates in a design space, the weight-stretch-style
model defines a three-dimensional coordinate system with weight, stretch, and style as the axes.
Each font in a WWS family must have a unique location defined by its coordinates along those three
axes. To select a font, one specifies a WWS family name and weight, stretch, and style parameters.

By contrast, the typographic font family model has an N-dimensional design space. A font designer
can define any number of design axes, each identified by a four-character _axis tag_. A given font’s
location in the N-dimensional design space is defined by an array of _axis values_, where each axis
value comprises an axis tag and a floating-point value. To select a font, one specifies a
typographic family name and an array of axis values (`DWRITE_FONT_AXIS_VALUE` structures).

Although the number of font axes is open-ended, there are a few registered axes with standard
meanings, and the weight, stretch, and style values can be mapped to registered axis values.
`DWRITE_FONT_WEIGHT` can be mapped to a "wght" (`DWRITE_FONT_AXIS_TAG_WEIGHT`) axis value.
`DWRITE_FONT_STRETCH` can be mapped to a "wdth" (`DWRITE_FONT_AXIS_TAG_WIDTH`) axis value.
`DWRITE_FONT_STYLE` can be mapped to a combination of "ital" and "slnt"
(`DWRITE_FONT_AXIS_TAG_ITALIC` and `DWRITE_FONT_AXIS_TAG_SLANT`) axis values.

Another registered axis is "opsz" (`DWRITE_FONT_AXIS_TAG_OPTICAL_SIZE`). An optical font family such
as Sitka includes fonts that differ along the "opsz" axis, meaning they are designed to be used at
different point sizes. The WWS font family model does not have an optical size axis, so the Sitka
font family must be split into multiple WWS font families: "Sitka Small", "Sitka Text", "Sitka
Subheading", and so on. Each WWS font family corresponds to a different optical size, and it's left
to the user to specify the right WWS family name for a given font size. With the typographic font
family model, the user can simply choose "Sitka", and the application can automatically set the
"opsz" axis value based on the font size.

### Typographic Font Selection and Variable Fonts

The concept of axes of variation is often associated with variable fonts, but it also applies to
static fonts. The OpenType
[STAT (style attributes)](https://docs.microsoft.com/typography/opentype/spec/stat) table declares
what design axes a font has and the values of those axes. This table is required for variable fonts
but is also relevant to static fonts.

The DirectWrite API exposes "wght", "wdth", "ital", and "slnt" axis values for every font, even if
they are not present in the STAT table or if there is no STAT table. These values are derived from
the STAT table if possible. Otherwise, they are derived from the font weight, font stretch, and font
style.

Font axes may be variable or non-variable. A static font has only non-variable axes whereas a
variable font may have both. To use a variable font, one must create a variable font _instance_ in
which all the variable axes have been bound to particular values. The `IDWriteFontFace` interface
represents either a static font or a particular _instance_ of a variable font. It is possible to
create an _arbitrary instance_ of a variable font with specified axis values. In addition, a
variable font may declare _named instances_ in the `STAT` table with predefined combinations of axis
values. Named instances enable a variable font to behave much like a collection of static fonts.
When you enumerate elements of an `IDWriteFontFamily` or `IDWriteFontSet`, there is one element for
each static font and for each named variable font instance.

The typographic font matching algorithm first selects potential match candidates based on the family
name. If the match candidates include variable fonts, all the match candidates for the same variable
font are collapsed into one match candidate in which each variable axis is assigned a specific value
as close as possible to the requested value for that axis. If there is no requested value for a
variable axis, it is assigned the default value for that axis. The order of the match candidates is
then determined by comparing their axis values with the requested axis values.

For example, consider the Sitka typographic family in Windows. Sitka is an optical font family,
meaning it has an "opsz" axis. In Windows 11, Sitka is implemented as two variable fonts with the
following axis values. Note that the `opsz` and `wght` axes are variable while the other axes are
non-variable.

| File Name          | "opsz" | "wght"  | "wdth" | "ital" | "slnt" |
| ------------------ | ------ | ------- | ------ | ------ | ------ |
| SitkaVF.ttf        | 6-27.5 | 400-700 | 100    | 0      | 0      |
| SitkaVF-Italic.ttf | 6-27.5 | 400-700 | 100    | 1      | -12    |

Suppose the requested axis values are `opsz:12 wght:475 wdth:100 ital:0 slnt:0`. For each variable
font, we create a reference to a variable font _instance_ in which each variable axis is assigned a
specific value. Namely, the `opsz` and `wght` axes are set to `12` and `475`, respectively. This
yields the following matching fonts, with the non-italic font ranked first because it's a better
match for the `ital` and `slnt` axes:

```
SitkaVF.ttf opsz:12 wght:475 wdth:100 ital:0 slnt0
SitkaVF-Italic.ttf opsz:12 wght:475 wdth:100 ital:1 slnt:-12
```

In the above example, the matching fonts are arbitrary variable font instances. There is no named
instance of Sitka with weight 475. In contrast, the weight-stretch-style matching algorithm only
returns named instances.

### Font Matching Order

There are different overloaded `GetMatchingFonts` methods for the weight-stretch-style font family
model and the typographic font family model. In both cases, the output is a list of matching fonts
in descending order of priority based on how well each candidate font matches the input properties.
This section describes how the priority is determined.

In the weight-stretch-style model, the input parameters are font weight (`DWRITE_FONT_WEIGHT`), font
stretch (`DWRITE_FONT_STRETCH`) and font style (`DWRITE_FONT_STYLE`). The algorithm for finding the
best match was documented in a 2006 white paper titled "WPF Font Selection Model" by Mikhail Leonov
and David Brown. See the section "Matching a face from the candidate face list." This paper was
about Windows Presentation Foundation (WPF), but DirectWrite later used the same approach.

The algorithm uses the notion of _font attribute vector_, which for a given combination of weight,
stretch, and style is computed as follows:

```
FontAttributeVector.X = (stretch - 5) * 1100;
FontAttributeVector.Y = style * 700;
FontAttributeVector.Z = (weight - 400) * 5;
```

Note that each vector coordinate is normalized by subtracting the "normal" value for the
corresponding attribute and multiplying by a constant. The multipliers compensate for the fact that
the ranges of input values for weight, stretch, and style are very different. Otherwise, weight
(100..999) would dominate over style (0..2).

For each match candidate, a vector distance and a dot product are computed between the match
candidate's font attribute vector and the input font attribute vector. When comparing two match
candidates, the candidate with the smaller vector distance is the better match. If the distances are
the same, the candidate with the smaller dot product is a better match. If the dot product is also
the same, the distances along the X, Y, and Z axes are compared in that order.

Comparing distances is intuitive enough, but using dot product as a secondary measure may require
some explanation. Suppose the input weight is semibold (600) and two candidate weights are black
(900) and semilight (300). The distance of each candidate weight from the input weight is the same,
but the black weight is in the same direction from the origin (i.e., 400 or normal), so it will have
a smaller dot product.

The typographic matching algorithm is a generalization of the one for weight-stretch-style. Each
axis value is treated as a coordinate in an N-dimensional font attribute vector. For each match
candidate, a vector distance and a dot product are computed between the match candidate's font
attribute vector and the input font attribute vector. The candidate with the smaller vector distance
is the better match. If the distances are the same, the candidate with the smaller dot product is a
better match. If the dot product is also the same, presence in a specified weight-stretch-style
family can be used as a tie-breaker.

To compute the vector distance and dot product, a match candidate's font attribute vector and the
input font attribute vector must have the same axes. Therefore, any missing axis value in either
vector is filled in by substituting the standard value for that axis. Vector coordinates are
normalized by subtracting the standard (or "normal") value for the corresponding axis and
multiplying the result by an axis-specific multiplier. Following are the multipliers and standard
values for each axis:

| Axis   | Multiplier | Standard Value |
| ------ | ---------- | -------------- |
| "wght" | 5          | 400            |
| "wdth" | 55         | 100            |
| "ital" | 1400       | 0              |
| "slnt" | 35         | 0              |
| "opsz" | 1          | 12             |
| other  | 1          | 0              |

The multipliers are consistent with those used by the weight-stretch-style algorithm, but scaled as
necessary. For example, normal width is 100, which is equivalent to stretch 5. This yields a
multiplier of 55 vs. 1100. The legacy style attribute (0..2) entangles italic and obliqueness, which
in the typographic model are decomposed into an "ital" axis (0..1) and a "slnt" axis (-90..90). The
chosen multipliers for these two axes give equivalent results to the legacy algorithm if we assume a
default 20-degree slant for oblique fonts.

### Typographic Font Selection and Optical Size

An application using the typographic font family model can implement optical sizing by specifying an
`opsz` axis value as a font selection parameter. For example, a word processing application could
specify an `opsz` axis value equal to the font size in points. In this case, a user could select
"Sitka" as the font family and the application would automatically select an instance of Sitka with
the correct `opsz` axis value. Under the WWS model, each optical size is exposed as a different
family name and it's up to the user to select the right one.

In theory, one could implement automatic optical sizing under the weight-stretch-style model by
overriding the `opsz` axis value as a separate step _after_ font selection. However, this only works
if the first matching font is a variable font with a variable `opsz` axis. Specifying `opsz` as a
font selection parameter works equally well for static fonts. For example, the Sitka font family is
implemented as variable fonts in Windows 11 but as a collection of static fonts in Windows 10. The
static fonts have different, non-overlapping `opsz` axis ranges. (These are declared as ranges for
font selection purposes, but they are not variable axes.) Specifying `opsz` as a font selection
parameter enables the correct static font for the optical size to be selected.

### Typographic Font Selection Advantages and Compatibility Issues

The typographic font selection model has several advantages over earlier models, but in its pure
form it has some potential compatibility issues. This section describes the advantages and
compatibility issues. The next section describes a hybrid font selection model that preserves the
advantages while mitigating the compatibility issues.

Advantages of the typographic font family model are:

-   Fonts can be grouped into families as intended by the designer, rather than being split into
    subfamilies due to limitations of the font family model.

-   An application can automatically select the correct "opsz" axis value based on the font size
    rather than exposing different optical sizes to the user as different font families.

-   Arbitrary instances of variable fonts can be selected. For example, if a variable font supports
    weights in the continuous range 100-900, the typographic model can select _any_ weight in this
    range. The older font family models can only choose the nearest weight from among the named
    instances defined by the font.

Compatibility issues with the typographic font selection model are:

-   Some older fonts cannot be selected unambiguously using only the typographic family name and
    axis values.

-   Existing documents might refer to fonts by WWS family name or RBIZ family name. Users might also
    expect to use WWS and RBIZ family names. For example, a document might specify "Sitka
    Subheading" (a WWS family name) instead of "Sitka" (a typographic family name).
-   A library or framework might adopt the typographic font family model to take advantage of
    automatic optical sizing, but not provide an API for specifing arbitrary axis values. Even if a
    new API is provided, the framework might need to work with existing applications that specify
    only weight, stretch, and style parameters.

The compatibility issue with older fonts arises because the concept of typographic family name
predates the concept of font axis values, which were introduced along with variable fonts in
OpenType 1.8. Before OpenType 1.8, the typographic family name merely expressed the designer's
intent that a set fonts were related, but with no guarantee that those fonts could be
programmatically differentiated based on their properties. As a hypothetical example, suppose all of
the following fonts have the typographic family name "Legacy":

| Full Name         | WWS Family  | Weight | Stretch | Style | Typo Family | wght | wdth | ital | slnt |
| ----------------- | ----------- | ------ | ------- | ----- | ----------- | ---- | ---- | ---- | ---- |
| Legacy            | Legacy      | 400    | 5       | 0     | Legacy      | 400  | 100  | 0    | 0    |
| Legacy Bold       | Legacy      | 700    | 5       | 0     | Legacy      | 700  | 100  | 0    | 0    |
| Legacy Black      | Legacy      | 900    | 5       | 0     | Legacy      | 900  | 100  | 0    | 0    |
| Legacy Soft       | Legacy Soft | 400    | 5       | 0     | Legacy      | 400  | 100  | 0    | 0    |
| Legacy Soft Bold  | Legacy Soft | 700    | 5       | 0     | Legacy      | 700  | 100  | 0    | 0    |
| Legacy Soft Black | Legacy Soft | 900    | 5       | 0     | Legacy      | 900  | 100  | 0    | 0    |

The "Legacy" typographic family has three weights and each weight has regular and "Soft" variants.
If these were new fonts, they could be implemented as declaring a SOFT design axis. However, these
fonts predate OpenType 1.8, so their only design axes are those derived from weight, stretch, and
style. For each weight, this font family has two fonts with identical axis values, so it is not
possible to unambiguously select a font in this family using axis values alone.

### Hybrid Font Selection Algorithm

The font selection APIs described in the next section use a hybrid font selection algorithm that
preserves the advantages of typographic font selection while mitigating its compatibilty issues.

Hybrid font selection provides a bridge from older font family models by enabling font weight, font
stretch, and font style values to be mapped to corresponding font axis values. This helps address
document and application compatibility issues.

In addition, the hybrid font selection algorithm allows the specified family name to be a
typographic family name, weight-stretch-style family name, GDI/RBIZ family name, or a full font
name. Matching occurs in one of the following ways, in descending order of priority:

1.  The name matches a typographic family (e.g., Sitka). Matching occurs within the typographic
    family and all requested axis values are used. If the name also matches a WWS subfamily (i.e.,
    one smaller than the typographic family) then membership in the WWS subfamily is used as a
    tie-breaker.

2.  The name matches a WWS family (e.g., Sitka Text). Matching occurs within the WWS family and
    requested axis values other than "wght", "wdth", "ital", and "slnt" are ignored.

3.  The name matches an GDI family (e.g., Bahnschrift Condensed). Matching occurs within the RBIZ
    family and requested axis values other than "wght", "ital", and "slnt" are ignored.

4.  The name matches a full name (e.g., Bahnschrift Bold Condensed). The font matching the full name
    is returned. Requested axis values are ignored. Matching by full font name is allowed because
    GDI supports it.

The previous section described an ambiguous typographic family called "Legacy". The hybrid algorithm
enables the ambiguity to be avoided by specifying either "Legacy" or "Legacy Soft" as the family
name. If "Legacy Soft" is specified, then there is no ambiguity because matching occurs only within
the WWS family. If "Legacy" is specfiied then all fonts in the typographic family are considered as
match candidates, but ambiguity is avoided by using membership in the "Legacy" WWS family as a
tie-breaker.

Suppose a document specifies a family name and weight, stretch, and style parameters, but no axis
values. The application can first convert the weight, stretch, style, and font size to axis values
by calling `IDWriteFontSet4::ConvertWeightStretchStyleToFontAxisValues`. The application can then
pass both the family name and axis values to `IDWriteFontSet4::GetMatchingFonts`. `GetMatchingFonts`
returns a list of matching fonts in priority order, and the result is appropriate whether the
specified family name is a typographic family name, weight-stretch-style family name, RBIZ family
name, or full name. If the specified family has an "opsz" axis, the appropriate optical size is
automatically selected based on the font size.

Suppose a document specifies weight, stretch, and style and _also_ specifies axis values. In this
case, the explicit axis values can also be passed in to
`IDWriteFontSet4::ConvertWeightStretchStyleToFontAxisValues`, and the derived axis values returned
by the method will only include font axes that were not specified explicitly. Thus, axis values
specified explicitly by the document (or application) take precedence over axis values derived from
weight, stretch, style, and font size.

### Hybrid Font Selection APIs

The hybrid font selection model is implemented by the following `IDWriteFontSet4` methods:

-   The `ConvertWeightStretchStyleToFontAxisValues` method converts font size, weight, stretch, and
    style parameters to the corresponding axis values. Any explicit axis values passed in by the
    client are excluded from the derived axis values.

-   The `GetMatchingFonts` method returns a prioritized list of matching fonts given a family name
    and array of axis values. As described above, the family name parameter can be a typographic
    family name, WWS family name, RBIZ family name, or full name. (The full name identifies a
    particular font style, such as "Arial Bold Italic". `GetMatchingFonts` supports matching by full
    name for greater comaptibiltiy with GDI, which also allows it.)

The following other DirectWrite APIs also use the hybrid font selection algorithm:

-   [`IDWriteFontCollection2::GetMatchingFonts`](https://docs.microsoft.com/windows/win32/api/dwrite_3/nf-dwrite_3-idwritefontcollection2-getmatchingfonts)

-   `IDWriteFontFallback1::MapCharacters`

-   `IDWriteTextLayout` if the typographic font family model is enabled by calling
    `IDWriteTextLayout4::SetFontAxisValues` or `IDWriteTextLayout4::SetAutomaticFontAxes`

## Color Font Support

By default, a glyph has a shape but no intrinsic color. Both DirectWrite and Direct2D have
`DrawGlyphRun` methods that render glyph runs by filling the glyph shapes with a specified text
color. For convenience, we will refer to this as _monochrome_ glyph rendering. All fonts have
monochrome glyphs, but a color font also has color representations of some glyphs. To render glyphs
in color, an application must use different glyph rendering APIs instead of calling the monochrome
`DrawGlyphRun` method.

Because color font support is implemented at the glyph rendering level, it does not affect text
layout. This is true whether a client uses the `IDWriteTextLayout` interface or implements its own
text layout algorithm. The mapping of characters to glyphs and the positioning of those glyphs all
use monochrome glyph IDs and their associated metrics. The output of the text layout process is a
sequence of monochrome glyph runs. Color font support can be enabled by translating those monochrome
"base" glyph runs to color glyphs runs at rendering time.

The easiest way to enable color is to call the `DrawGlyphRunWithColorSupport` method instead of
calling `DrawGlyphRun`. Direct2D exposes this method through the `ID2D1DeviceContext7` interface.
DirectWrite exposes this method through the `IDWriteBitmapRenderTarget3` interface.

At a lower level, enabling color involves translating the monochrome _base glyph run_ to a sequence
of _color glyph runs_. Each color glyph run must then be rendered using the appropriate method,
depending on its _glyph image format_. The translation is performed by the factory object's
`TranslateColorGlyphRun` method. It and related APIs are described in the following sections.

### Using TranslateColorGlyphRun

The `TranslateColorGlyphRun` factory method translates a monochrome _base glyph run_ into a sequence
of _color glyph runs_. There are multiple ways of representing color glyphs, known as _glyph image
formats_ and identified by the `DWRITE_GLYPH_IMAGE_FORMATS` enumeration. When calling
`TranslateColorGlyphRun`, the client specifies the combination of glyph image formats it supports.
The `TranslateColorGlyphRun` returns a _glyph run enumerator_ object
(`IDWriteColorGlyphRunEnumerator1` interface), which the client uses to iterate over the sequence of
color glyph runs, represented by the `DWRITE_COLOR_GLYPH_RUN1` structure. Each color glyph run has a
glyph image format. The client branches on the color run's glyph image format to determine how to
render the color run.

If the base glyph run does not have color glyphs in any of the requested glyph image formats, the
`TranslateColorGlyphRun` method returns `DWRITE_E_NOCOLOR`, in which case the client should render
the base glyph run as a monochrome glyph run.

Otherwise, the base glyph run may contain a mix of color glyphs in different glyph image formats as
well as monochrome glyphs. For each base glyph, the `TranslateColorGlyphRun` method determines the
available glyph image format (if any) that best matches the requested formats. The base glyph run is
split into subranges based on the matching glyph image format. Glyphs that do not support any of the
requested formats are treated as monochrome glyphs.

The glyph image formats fall into four general categories:

-   Monochrome glyphs (`DWRITE_GLYPH_IMAGE_FORMATS_TRUETYPE` or `DWRITE_GLYPH_IMAGE_FORMATS_CFF`)
-   Layers of solid-color glyphs (`DWRITE_GLYPH_IMAGE_FORMATS_COLR`)
-   Color bitmaps embedded in the font (`DWRITE_GLYPH_IMAGE_FORMATS_PNG`,
    `DWRITE_GLYPH_IMAGE_FORMATS_JPEG`, `DWRITE_GLYPH_IMAGE_FORMATS_TIFF`, and
    `DWRITE_GLYPH_IMAGE_FORMATS_PREMULTIPLIED_B8G8R8A8`)
-   Vector graphics encoded as SVG in the font (`DWRITE_GLYPH_IMAGE_FORMATS_SVG`)
-   Vector graphics as a tree of "paint" elements (`DWRITE_GLYPH_IMAGE_FORMATS_COLR_PAINT_TREE`)

The following subsections describe each of these approaches.

### Monochrome glyphs

The `DWRITE_GLYPH_IMAGE_FORMATS_TRUETYPE` and `DWRITE_GLYPH_IMAGE_FORMATS_CFF` glyph image formats
represent monochrome glyphs, which can be rendered using the `DrawGlyphRun` method. The two formats
correspond to different ways of representing glyph outlines in the font. An enumerated
`DWRITE_COLOR_GLYPH_RUN1` structure can specify these formats for one of two reasons:

-   One or more of the base glyphs do not support any of the requested glyph image formats, and so
    should be rendered as monochrome glyphs.
-   The best matching glyph image format for a glyph was `DWRITE_GLYPH_IMAGE_FORMATS_COLR`. Glyphs
    in this image format are rendered by enumerating a monochrome run in a specified color for each
    layer, as described in the next section.

In the first case, the enumerated glyph run should be rendered using the application-defined
foreground brush. This is indicated by setting the `paletteIndex` member of the
`DWRITE_COLOR_GLYPH_RUN` structure to `DWRITE_NO_PALETTE_INDEX` (0xFFFF). If the `paletteIndex`
member has any other value, the client should render the text in the specified color.

### Layers of solid color glyphs

The `DWRITE_GLYPH_IMAGE_FORMATS_COLR` value specifies a color format that supports version 0 of the
OpenType COLR table. In this format, a color glyph is rendered by drawing multiple monochrome glyphs
on top of each other, each in a specified color.

The calling pattern used with this image format is different than with all other glyph image
formats. That's because what gets rendered at the end of the day is just a series of ordinary,
monochrome glyph runs -- just with different glyph IDs and different colors than were specified to
begin with. Because the enumerated color glyph runs are rendered as ordinary monochrome glyph runs,
their glyph image formats are either `DWRITE_GLYPH_IMAGE_FORMATS_TRUETYPE` or
`DWRITE_GLYPH_IMAGE_FORMATS_CFF`.

For example, suppose the base glyph run specifies a smiley face glyph. If we rendered the base glyph
run using `DrawGlyphRun`, the visual result would be a monochrome representation of a smiley face
(the base glyph ID). The COLR table in the font maps this base glyph ID to an array of _layer
records_, each of which specifies a _replacement glyph ID_ and an index into a font-defined color
palette. The `IDWriteColorGlyphRunEnumerator` object returned by `TranslateColorGlyphRun` enumerates
one color glyph run for each of those layer records. Each color glyph run has a position, a single
glyph ID (the replacement glyph ID for the layer), and a color (derived from the palette entry
index). The client draws the enumerated color glyph runs in the specified colors at the specified
coordinates to produce the desired visual result. In the smiley face example, this might comprise a
filled-circle glyph rendered in yellow followed by an eyes-and-mouth glyph rendered in black.

### Color bitmaps embedded in the font

The `DWRITE_GLYPH_IMAGE_FORMATS` enumeration includes values for several bitmap formats: PNG, JPEG,
TIFF, and premultiplied BGRA32 format. A font may represent color glyphs by embedding bitmaps in any
of these formats in the font. A font may include bitmaps or multiple sizes to support different font
sizes and DPI scales, though this comes at an obvious cost in terms of file size.

If the client requests bitmap image formats then `TranslateColorGlyphRun` checks if the font has
color bitmaps for the specified input glyphs in the specified formats. If so, then the enumerated
color glyph runs specify the base glyph IDs and the matching image format. Note that there are no
replacement glyph IDs in this case, like there are with `DWRITE_GLYPH_IMAGE_FORMATS_COLR`. However,
the base glyph run may still be split into multiple color runs if different input glyphs have color
bitmaps in different image formats, or some glyphs have color representations and others are
monochrome only.

A client using Direct2D can render the enumerated color glyph runs in these formats by calling the
`ID2DDeviceContext3::DrawColorBitmapGlyphRun` method.

A lower-level client can call the `IDWriteFontFace3::GetGlyphImageData` to get the raw bitmap data
for each glyph in the returned image format. The client is then responsible for decoding and
rendering the bitmaps itself. Direct2D's internal implementation of `DrawColorBitmapGlyphRun` calls
`GetGlyphImageData` to get the bitmaps for each glyph.

### Vector graphics encoded as SVG in the font

The `DWRITE_GLYPH_IMAGE_FORMATS_SVG` value specifies a glyph image format in which color glyphs are
represented as vector graphics in SVG (Scaled Vector Graphics) format embedded in the font. The
embedded SVG may be stored with gzip compression.

The calling pattern used with SVG is similar to that with the bitmap formats, and unlike the calling
pattern for `DWRITE_GLYPH_IMAGE_FORMATS_COLR`. If the client requests SVG format, and specified
glyph IDs have SVG representations, then the enumerated color glyph runs specify the base glyph IDs
and the SVG image format.

A client using Direct2D can render enumerated color glyph runs in this format by calling the
`ID2DDeviceContext3::DrawSvgGlyphRun` method.

A lower-level client can call the `IDWriteFontFace3::GetGlyphImageData` to get the raw SVG data for
each glyph. The client is then responsible for parsing and rendering the SVG itself. Direct2D's
internal implementation of `DrawSvgGlyphRun` calls `GetGlyphImageData` to get the SVG data for each
glyph.

### Vector graphics as a tree of "paint" elements

In version 1 of the OpenType COLR table, color glyphs are represented by a tree of _paint elements_.
There are different types of paint elements for geometries (represented as glyphs), transforms,
solid and gradient fills, and composition. The `DWRITE_GLYPH_IMAGE_FORMATS_COLR` format only
supports layering solid-color glyphs on top of each other, so a different glyph image format is
required to support COLR version 1 and greater: `DWRITE_GLYPH_IMAGE_FORMATS_COLR_PAINT_TREE`. When
using this glyph image format, the client must also specify the maximum _paint feature level_
(`DWRITE_PAINT_FEATURE_LEVEL`) it supports. This enables future versions of the COLR table to be
supported without having to define additional glyph image formats.

The calling pattern used with this glyph image format is similar to that used with SVG. If the
client requests the COLR-paint format and the specified glyph IDs have COLR representations, then
the enumerated color glyph runs specify the base glyph IDs and the COLR-paint image format.

A client using Direct2D can render enumerated color glyph runs in this format by calling the
`ID2DDeviceContext7::DrawPaintGlyphRun` method. A client using DirectWrite's bitmap render target
API can call `IDWriteBitmapRenderTarget3::DrawPaintGlyphRun`.

A lower-level client can use the color paint APIs described in the next section to get the tree of
paint elements for each glyph and render it. Direct2D's and DirectWrite's implementations of
`DrawPaintGlyphRun` internally use these lower-level APIs.

### Color paint APIs

A glyph in the `DWRITE_GLYPH_IMAGE_FORMATS_COLR_PAINT_TREE` image format is represented as a tree of
_paint elements_. (The OpenType COLR table spec describes a directed acyclic graph of paint records,
but the subgraph for a specific glyph is always a tree.) A client can use a _paint reader_ object
(`IDWritePaintReader` interface) to read the tree of paint elements for a glyph.

Each paint element has a _paint type_ (`DWRITE_PAINT_TYPE` enumeration). There are different paint
types for graphical elements such as geometries (represented as glyphs), transforms, and solid and
gradient fills. Paint reader methods return information about a paint element by filling in a
`DWRITE_PAINT_ELEMENT` structure, which comprises a paint type and a union.

Additional paint types may be added in future versions of the COLR specification. To allow for this,
a client must specify the maximum _paint feature level_ (`DWRITE_PAINT_FEATURE_LEVEL`) it supports
when creating a paint reader object or calling `TranslateColorGlyphRun`. Only paint elements of
types supported by the specified feature level are returned by paint reader methods. In addition,
methods that take an output parameter of type `DWRITE_PAINT_ELEMENT` also take a size parameter,
since the structure size may change when additional paint types are defined.

The algorithm for rendering a color glyph is to recursively render the paint elements, each
according to its type. The following paint types are defined:

| Paint Type                          | Rendering Action                                                                         |
| ----------------------------------- | ---------------------------------------------------------------------------------------- |
| `DWRITE_PAINT_TYPE_NONE`            | No action                                                                                |
| `DWRITE_PAINT_TYPE_LAYERS`          | Render the child paint elements in bottom-up order.                                      |
| `DWRITE_PAINT_TYPE_SOLID_GLYPH`     | Fill the specified glyph shape with the specified color.                                 |
| `DWRITE_PAINT_TYPE_SOLID`           | Fill the current clip with the specified color.                                          |
| `DWRITE_PAINT_TYPE_LINEAR_GRADIENT` | Fill the current clip with the specified gradient.                                       |
| `DWRITE_PAINT_TYPE_RADIAL_GRADIENT` | Fill the current clip with the specified gradient.                                       |
| `DWRITE_PAINT_TYPE_SWEEP_GRADIENT`  | Fill the current clip with the specified gradient.                                       |
| `DWRITE_PAINT_TYPE_GLYPH`           | Fill the specified glyph shape with child paint element.                                 |
| `DWRITE_PAINT_TYPE_COLOR_GLYPH`     | Render the child paint element.                                                          |
| `DWRITE_PAINT_TYPE_TRANSFORM`       | Render the child paint element with the specified transform.                             |
| `DWRITE_PAINT_TYPE_COMPOSITE`       | Render the two child paint elements and compose them using the specified composite mode. |

For more information about paint types, see the
[OpenType COLR Table](https://docs.microsoft.com/typography/opentype/spec/colr) specification. Note
that some paint types in the DirectWrite API correspond to multiple paint formats in the COLR table.
This is because the API hides some complexities, such as differences in how some paint elements are
encoded in variable vs. non-variable fonts.

## Examples

### Creating an isolated factory

An application calls the `DWriteCoreCreateFactory` function to create a factory object, which is the
entry-point to all other DirectWrite APIs. An application can specify the new
`DWRITE_FACTORY_TYPE_ISOLATED2` enum value if it wants to minimize interaction between
DirectWriteCore and the host system. Specifically, the resulting factory only caches data
in-process. It neither reads from nor writes to a cross-process cache (e.g., a font cache process)
or persistent cache (i.e., a file). In addition, the resulting factory's system font collection only
includes well-known system fonts.

The following example creates an isolated factory.

```c++
ComPtr<IDWriteFactory7> spFactory;
HRESULT hr = DWriteCoreCreateFactory(
    DWRITE_FACTORY_TYPE_ISOLATED2,
    __uuidof(IDWriteFactory7),
    (IUnknown**)&spFactory
    );
```

### Drawing glyphs to a system memory bitmap

An application creates a bitmap render target by calling
[`IDWriteGdiInterop::CreateBitmapRenderTarget`](https://docs.microsoft.com/windows/win32/api/dwrite/nf-dwrite-idwritegdiinterop-createbitmaprendertarget).
A bitmap render target encapsulates a bitmap in system memory, and enables rendering glyphs to the
bitmap. On Windows, the bitmap is actually a GDI DIB selected into a memory HDC, and it is possible
to get the bitmap pixels using GDI functions. However, DWriteCore introduces a simpler method
through the new IDWriteBitmapRenderTarget2 interface. The following example shows both the old way
and the new way.

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

### Using Font Selection APIs

This section shows a complete console application that demonstrates the
`IDWriteFontSet4::GetMatchingFonts` and `IDWriteFontSet4::ConvertWeightStretchStyleToFontAxisValues`
methods. First let's include some headers:

```c++
#include <dwrite_core.h>
#include <wil/com.h>
#include <iostream>
#include <string>
#include <vector>
```

The `IDWriteFontSet4::GetMatchingFonts` method returns a list of fonts in priority order that match
the specified family name and axis values. The following `MatchAxisValues` function outputs the
parameters to `GetMatchingFonts` and the list of matching fonts in the returned font set.

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
    for (DWRITE_FONT_AXIS_VALUE const& axisValue : axisValues)
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

An application might have weight, stretch, and style parameters instead of (or in addition to) axis
values. For example, the application might need to work with documents that reference fonts using
RBIZ or weight-stretch-style parameters. Even if the application adds support for specifying
arbitrary axis values, it might need to support the older parameters as well. To do so, the
application can call the `IDWriteFontSet4::ConvertWeightStretchStyleToFontAxisValues` before calling
`IDWriteFontSet4::GetMatchingFonts`.

The following `MatchFont` function takes weight, stretch, style, and font size parameters in
addition to axis values. It forwards these parameters to the
`IDWriteFontSet4::ConvertWeightStretchStyleToFontAxisValues` method to compute derived axis values,
which are appended to the input axis values. It passes the combined axis values to the above
`MatchAxisValues` function.

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
// MatchFont calls IDWriteFontSet4::ConvertWeightStretchStyleToFontAxisValues to convert
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
    UINT32 derivedAxisCount = fontSet->ConvertWeightStretchStyleToFontAxisValues(
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

The following function demonstrates the results of calling the above `MatchFont` function with some
example inputs:

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

Following are the implementations of the overloaded operators declared above. These are used by
`MatchAxisValues` to write the input axis values and the resulting font face references:

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

### Rendering Color Glyph Runs

This section shows a sample `TextRenderer::DrawGlyphRun` method that implements the `DrawGlyphRun`
method of the `IDWriteTextRenderer` interface. The `IDWriteTextRenderer` callback interface is used
by `IDWriteTextLayout::Draw` to render glyph runs, underlines, and so on. The use of a callback
interface enables the text layout API to be decoupled from the specific graphics engine. For
example, it is possible to implement `IDWriteTextRenderer` in terms of Direct2D, in terms of
`IDWriteBitmapRenderTarget`, or in some other way. This example uses Direct2D.

The example includes only the `DrawGlyphRun` method. The rest of the `TextRenderer` class is omitted
for brevity, but the example assumes the class implements the `IDWriteTextRenderer` interface and
has the following member variables:

```c++
wil::com_ptr<IDWriteFactory4> m_dwriteFactory;
wil::com_ptr<ID2D1DeviceContext4> m_deviceContext;
wil::com_ptr<ID2D1Brush> m_foregroundBrush;
```

The example method renders color glyphs in one of two ways. The easy way is to call
`ID2D1DeviceContext7::DrawGlyphRunWithColorSupport`. However, the example also includes a fallback
code path in case the available version of Direct2D does not implement the `ID2D1DeviceContext7`
interface. The fallback code path uses `TranslateColorGlyphRun`.

```c++
// Implementation of IDWriteTextRenderer::DrawGlyphRun
HRESULT STDMETHODCALLTYPE TextRenderer::DrawGlyphRun(
    _In_opt_ void* clientDrawingContext,
    FLOAT baselineOriginX,
    FLOAT baselineOriginY,
    DWRITE_MEASURING_MODE measuringMode,
    _In_ DWRITE_GLYPH_RUN const* glyphRun,
    _In_ DWRITE_GLYPH_RUN_DESCRIPTION const* glyphRunDescription,
    _In_opt_ IUnknown* clientDrawingEffect
) noexcept
{
    D2D_POINT_2F baselineOrigin{ baselineOriginX, baselineOriginY };

    // If a brush is specified via the clientDrawingEffect parameter, use it as
    // the foreground brush for this glyph run. Otherwise, use the brush specified
    // by the m_foregroundBrush member.
    wil::com_ptr<ID2D1Brush> foregroundBrush;
    if (clientDrawingEffect != nullptr)
    {
        foregroundBrush = wil::try_com_query<ID2D1Brush>(clientDrawingEffect);
    }
    if (foregroundBrush == nullptr)
    {
        foregroundBrush = m_foregroundBrush;
    }

    // If available, use the ID2D1DeviceContext7 interface to draw
    // the glyph run with color the "easy" way.
    if (auto deviceContext7 = m_deviceContext.try_query<ID2D1DeviceContext7>())
    {
        // Note: Direct2D drawing methods return void. If a drawing
        // operation fails, an error is returned by EndDraw.
        deviceContext7->DrawGlyphRunWithColorSupport(
            baselineOrigin,
            glyphRun,
            foregroundBrush.get(),
            measuringMode,
            /*colorPaletteIndex*/ 0
        );
        return S_OK;
    }

    // If we fall through to here, we're using an older version of
    // Direct2D that does not implement the ID2D1DeviceContext7 interface.
    // We will need to call TranslateColorGlyphRun. First determine the
    // world to device transform.
    D2D_MATRIX_3X2_F transform;
    m_deviceContext->GetTransform(&transform);
    float dpiX, dpiY;
    m_deviceContext->GetDpi(&dpiX, &dpiY);
    transform = transform * D2D1::Matrix3x2F::Scale(dpiX, dpiY);

    // Combination of image formats we support. Do *not* include
    // DWRITE_GLYPH_IMAGE_FORMATS_COLR_PAINT_TREE because this code
    // path is for an older version of D2D which does not support
    // the ID2D1DeviceContext7 interface.
    constexpr DWRITE_GLYPH_IMAGE_FORMATS desiredGlyphImageFormats =
        DWRITE_GLYPH_IMAGE_FORMATS_TRUETYPE |
        DWRITE_GLYPH_IMAGE_FORMATS_CFF |
        DWRITE_GLYPH_IMAGE_FORMATS_COLR |
        DWRITE_GLYPH_IMAGE_FORMATS_SVG |
        DWRITE_GLYPH_IMAGE_FORMATS_PNG |
        DWRITE_GLYPH_IMAGE_FORMATS_JPEG |
        DWRITE_GLYPH_IMAGE_FORMATS_TIFF |
        DWRITE_GLYPH_IMAGE_FORMATS_PREMULTIPLIED_B8G8R8A8;

    // Perform color translation.
    wil::com_ptr<IDWriteColorGlyphRunEnumerator1> colorRunEnumerator;
    HRESULT hr = m_dwriteFactory->TranslateColorGlyphRun(
        baselineOrigin,
        glyphRun,
        glyphRunDescription,
        desiredGlyphImageFormats,
        measuringMode,
        reinterpret_cast<DWRITE_MATRIX const*>(&transform),
        /*colorPaletteIndex*/ 0,
        /*out*/ & colorRunEnumerator
    );

    // Handle DWRITE_E_NOCOLOR, which is returned if the base glyph run does not
    // have any color glyphs in the desired glyph image formats. In this case,
    // just render the base glyph run as a monochrome glyph run.
    if (hr == DWRITE_E_NOCOLOR)
    {
        // Note: Direct2D drawing methods return void. If a drawing
        // operation fails, an error is returned by EndDraw.
        m_deviceContext->DrawGlyphRun(
            baselineOrigin,
            glyphRun,
            foregroundBrush.get(),
            measuringMode
        );
        return S_OK;
    }

    // Any other failure HRESULT from TranslateColorGlyphRun is an error.
    RETURN_IF_FAILED(hr);

    // Solid color brush to be lazily created if needed.
    wil::com_ptr<ID2D1SolidColorBrush> solidBrush;

    // Use the returned enumerator object to iterate over the color glyph runs.
    for (;;)
    {
        // Advanced to the first or next run.
        BOOL haveRun;
        RETURN_IF_FAILED(colorRunEnumerator->MoveNext(&haveRun));
        if (!haveRun)
            break;

        // Get a pointer to the color glyph run structure.
        DWRITE_COLOR_GLYPH_RUN1 const* colorGlyphRun;
        RETURN_IF_FAILED(colorRunEnumerator->GetCurrentRun(&colorGlyphRun));

        // Determine the brush to use for this color glyph run.
        wil::com_ptr<ID2D1Brush> runBrush;
        if (colorGlyphRun->paletteIndex == DWRITE_NO_PALETTE_INDEX)
        {
            // Special palette index meaning use the text foreground brush.
            runBrush = foregroundBrush;
        }
        else
        {
            // Use the specified color from the font's color palette.
            // Lazily create the solid color brush, or set its color if already created.
            if (solidBrush == nullptr)
            {
                RETURN_IF_FAILED(m_deviceContext->CreateSolidColorBrush(
                    colorGlyphRun->runColor,
                    &solidBrush
                    ));
            }
            else
            {
                solidBrush->SetColor(colorGlyphRun->runColor);
            }

            // Use the solid color brush as the current run's brush.
            runBrush = solidBrush;
        }

        // Branch depending on the run's glyph image format.
        switch (colorGlyphRun->glyphImageFormat)
        {
        case DWRITE_GLYPH_IMAGE_FORMATS_NONE:
            // do nothing
            break;

        case DWRITE_GLYPH_IMAGE_FORMATS_PNG:
        case DWRITE_GLYPH_IMAGE_FORMATS_JPEG:
        case DWRITE_GLYPH_IMAGE_FORMATS_TIFF:
        case DWRITE_GLYPH_IMAGE_FORMATS_PREMULTIPLIED_B8G8R8A8:
            // Note: Direct2D drawing methods return void. If a drawing
            // operation fails, an error is returned by EndDraw.
            m_deviceContext->DrawColorBitmapGlyphRun(
                colorGlyphRun->glyphImageFormat,
                baselineOrigin,
                &colorGlyphRun->glyphRun,
                colorGlyphRun->measuringMode,
                D2D1_COLOR_BITMAP_GLYPH_SNAP_OPTION_DEFAULT
            );
            break;

        case DWRITE_GLYPH_IMAGE_FORMATS_SVG:
            // Note: Direct2D drawing methods return void. If a drawing
            // operation fails, an error is returned by EndDraw.
            m_deviceContext->DrawSvgGlyphRun(
                baselineOrigin,
                &colorGlyphRun->glyphRun,
                runBrush.get(),
                /*SVG style*/ nullptr,
                /*colorPaletteIndex*/ 0,
                colorGlyphRun->measuringMode
            );
            break;

        default:
            // Treat any other format as a monochrome glyph run.
            // This is used for monochrome glyphs, or for each layer
            // of a glyph in DWRITE_GLYPH_IMAGE_FORMATS_COLR.
            m_deviceContext->DrawGlyphRun(
                baselineOrigin,
                &colorGlyphRun->glyphRun,
                colorGlyphRun->glyphRunDescription,
                runBrush.get(),
                colorGlyphRun->measuringMode
            );
            break;
        }
    }
    return S_OK;
}
```

### Using Color Paint APIs

A color glyph in the `DWRITE_GLYPH_IMAGE_FORMATS_COLR_PAINT_TREE` format is represented as a visual
tree of graphical elements called _paint elements_. The example in this section demonstrates how to
use the `IDWritePaintReader` interface to traverse the tree of paint elements for a glyph.

The `DumpPaintTree` sample function in this section does not render a color glyph, but outputs a
textual representation of its paint tree. Following is an example of the output:

```
  - glyphIndex: 35
  - clipBox: { 0, -1, 0.5, -0.5 }
  - attributes: DWRITE_PAINT_ATTRIBUTES_USES_PALETTE
  - paintTree:
    DWRITE_PAINT_TYPE_COMPOSITE:
      - mode: DWRITE_COLOR_COMPOSITE_SRC_OVER
      - children (source, destination):
        DWRITE_PAINT_TYPE_SOLID_GLYPH:
          - glyphIndex: 84
          - color: { 0.501961, 0.501961, 0.501961, 0.400024 }
        DWRITE_PAINT_TYPE_COLOR_GLYPH:
          - glyphIndex: 88
          - clipBox: { 0.1, -0.9, 0.9, -0.1 }
          - child:
            DWRITE_PAINT_TYPE_COLOR_GLYPH:
              - glyphIndex: 20
              - clipBox: { 0, -1, 1, -0 }
              - child:
                DWRITE_PAINT_TYPE_GLYPH:
                  - glyphIndex: 82
                  - child:
                    DWRITE_PAINT_TYPE_RADIAL_GRADIENT:
                      - center0: (0.166, -0.768)
                      - radius0: 0
                      - center1: (0.166, -0.768)
                      - radius1: 0.256
                      - extendMode: D2D1_EXTEND_MODE_MIRROR (2)
                      - gradientStops:
                        D2D1_GRADIENT_STOP:
                          - position: 0
                          - color: { 0, 0.501961, 0, 1 }
                        D2D1_GRADIENT_STOP:
                          - position: 0.5
                          - color: { 1, 1, 1, 1 }
                        D2D1_GRADIENT_STOP:
                          - position: 1
                          - color: { 1, 0, 0, 1 }
```

For convenience, the sample defines `Indent` and `PropName` helper types with associated stream
output opreators. It also defines stream output operators for various API types. These helper types
and operators are shown at the end of this section.

The `DumpPaintTree` function creates an `IDWritePaintReader` object, sets the current glyph, outputs
the glyph properties, and then calls the recursive `DumpPaintElement` function to output the tree of
paint elements.

```c++
void DumpPaintTree(std::ostream& out, IDWriteFontFace7* fontFace, uint32_t glyphIndex)
{
    wil::com_ptr<IDWritePaintReader> paintReader;
    THROW_IF_FAILED(fontFace->CreatePaintReader(
        DWRITE_GLYPH_IMAGE_FORMATS_COLR_PAINT_TREE,
        DWRITE_PAINT_FEATURE_LEVEL_COLR_V1,
        &paintReader
    ));

    DWRITE_PAINT_ELEMENT paintElement;
    D2D_RECT_F clipBox;
    DWRITE_PAINT_ATTRIBUTES attributes;
    THROW_IF_FAILED(paintReader->SetCurrentGlyph(glyphIndex, &paintElement, &clipBox, &attributes));

    out << PropName{ "glyphIndex" } << glyphIndex << '\n'
        << PropName{ "clipBox" } << clipBox << '\n'
        << PropName{ "attributes" } << attributes << '\n'
        << PropName{ "paintTree" } << '\n';
    DumpPaintElement(out, Indent{ 1 }, paintReader.get(), paintElement);
}
```

The recursive `DumpPaintElement` function outputs a description of the specified paint element and
its children. The `DWRITE_PAINT_ELEMENT` structure is a tagged union. The `DumpPaintElement`
branches on its `paintType` member to determine what to write.

```c++
void DumpPaintElement(std::ostream& out, Indent indent, IDWritePaintReader* reader, DWRITE_PAINT_ELEMENT& element)
{
    // Helper to write gradient information, for gradient paint types.
    auto WriteGradient = [&](D2D1_EXTEND_MODE extendMode, uint32_t gradientStopCount)
    {
        out << indent << PropName{ "extendMode" } << extendMode << '\n';
        out << indent << PropName{ "gradientStops" } << '\n';
        DumpGradientStops(out, indent + 1, reader, gradientStopCount);
    };

    // Helper to recursively call DumpPaintElement for a child paint element.
    auto Recurse = [&]()
    {
        DumpPaintElement(out, indent + 1, reader, element);
    };

    // Helper to write the specified number of children.
    // The number of children is specified by the caller because it depends on
    // the paint type. See the description of the DWRITE_PAINT_ELEMENT structure
    // for more information.
    auto WriteChildren = [&](uint32_t childCount)
    {
        if (childCount != 0)
        {
            HR(reader->MoveToFirstChild(&element));
            Recurse();

            for (uint32_t i = 1; i < childCount; i++)
            {
                HR(reader->MoveToNextSibling(&element));
                Recurse();
            }

            HR(reader->MoveToParent());
        }
    };

    // Write information about the paint element, depending on its type.
    switch (element.paintType)
    {
    case DWRITE_PAINT_TYPE_NONE:
        out << indent << "DWRITE_PAINT_TYPE_NONE\n";
        break;

    case DWRITE_PAINT_TYPE_LAYERS:
    {
        out << indent << "DWRITE_PAINT_TYPE_LAYERS:\n";
        auto const& paint = element.paint.layers;
        // Write the children.
        // A layers paint element has a variable number of children.
        WriteChildren(paint.childCount);
        break;
    }

    case DWRITE_PAINT_TYPE_SOLID_GLYPH:
    {
        auto const& paint = element.paint.solidGlyph;
        // Write the properties.
        // A solid glyph paint element has no children.
        out << indent << "DWRITE_PAINT_TYPE_SOLID_GLYPH:\n"
            << indent << PropName{ "glyphIndex" } << paint.glyphIndex << '\n'
            << indent << PropName{ "color" } << paint.color.value << '\n';
        break;
    }

    case DWRITE_PAINT_TYPE_SOLID:
    {
        auto const& paint = element.paint.solid;
        // Write the properties.
        // A solid paint element has no children.
        out << indent << "DWRITE_PAINT_TYPE_SOLID:\n"
            << indent << PropName{ "color" } << paint.value << '\n';
        break;
    }

    case DWRITE_PAINT_TYPE_LINEAR_GRADIENT:
    {
        auto const& paint = element.paint.linearGradient;
        // Write the properties, including gradient stops.
        // A linear gradient paint element has no children.
        out << indent << "DWRITE_PAINT_TYPE_LINEAR_GRADIENT:\n"
            << indent << PropName{ "p0" } << D2D_POINT_2F{ paint.x0, paint.y0 } << '\n'
            << indent << PropName{ "p1" } << D2D_POINT_2F{ paint.x1, paint.y1 } << '\n'
            << indent << PropName{ "p2" } << D2D_POINT_2F{ paint.x2, paint.y2 } << '\n';
        WriteGradient(static_cast<D2D1_EXTEND_MODE>(paint.extendMode), paint.gradientStopCount);
        break;
    }

    case DWRITE_PAINT_TYPE_RADIAL_GRADIENT:
    {
        auto const& paint = element.paint.radialGradient;
        // Write the properties, including gradient stops.
        // A radial gradient paint element has no children.
        out << indent << "DWRITE_PAINT_TYPE_RADIAL_GRADIENT:\n"
            << indent << PropName{ "center0" } << D2D_POINT_2F{ paint.x0, paint.y0 } << '\n'
            << indent << PropName{ "radius0" } << paint.radius0 << '\n'
            << indent << PropName{ "center1" } << D2D_POINT_2F{ paint.x1, paint.y1 } << '\n'
            << indent << PropName{ "radius1" } << paint.radius1 << '\n';
        WriteGradient(static_cast<D2D1_EXTEND_MODE>(paint.extendMode), paint.gradientStopCount);
        break;
    }

    case DWRITE_PAINT_TYPE_SWEEP_GRADIENT:
    {
        auto const& paint = element.paint.sweepGradient;
        // Write the properties, including gradient stops.
        // A sweep gradient paint element has no children.
        out << indent << "DWRITE_PAINT_TYPE_SWEEP_GRADIENT:\n"
            << indent << PropName{ "center" } << D2D_POINT_2F{ paint.centerX, paint.centerY } << '\n'
            << indent << PropName{ "startAngle" } << paint.startAngle << '\n'
            << indent << PropName{ "endAngle" } << paint.endAngle << '\n';
        WriteGradient(static_cast<D2D1_EXTEND_MODE>(paint.extendMode), paint.gradientStopCount);
        break;
    }

    case DWRITE_PAINT_TYPE_GLYPH:
    {
        auto const& paint = element.paint.glyph;
        // Write the properties and the child element.
        // A glyph paint element always has one child, which represents the fill
        // for the glyph shape.
        out << indent << "DWRITE_PAINT_TYPE_GLYPH:\n"
            << indent << PropName{ "glyphIndex" } << paint.glyphIndex << '\n'
            << indent << PropName{ "child" } << '\n';
        WriteChildren(1);
        break;
    }

    case DWRITE_PAINT_TYPE_COLOR_GLYPH:
    {
        auto const& paint = element.paint.colorGlyph;
        // Write the properties and the child element.
        // A color glyph paint element always has one child, which is the root
        // of the paint tree for the glyph specified by glyphIndex.
        out << indent << "DWRITE_PAINT_TYPE_COLOR_GLYPH:\n"
            << indent << PropName{ "glyphIndex" } << paint.glyphIndex << '\n'
            << indent << PropName{ "clipBox" } << paint.clipBox << '\n'
            << indent << PropName{ "child" } << '\n';
        WriteChildren(1);
        break;
    }

    case DWRITE_PAINT_TYPE_TRANSFORM:
    {
        DWRITE_MATRIX const& paint = element.paint.transform;
        // Write the properties and the child element.
        // A transform paint element always has one child, which represents the
        // transformed content.
        out << indent << "DWRITE_PAINT_TYPE_TRANSFORM:\n"
            << indent << PropName{ "transform" } << paint << '\n'
            << indent << PropName{ "child" } << '\n';
        WriteChildren(1);
        break;
    }

    case DWRITE_PAINT_TYPE_COMPOSITE:
    {
        auto const& paint = element.paint.composite;
        // Write the properties and the child elements.
        // A composite paint element always has two children, which represent
        // the source and destination of the composite operation.
        out << indent << "DWRITE_PAINT_TYPE_COMPOSITE:\n"
            << indent << PropName{ "mode" } << paint.mode << '\n'
            << indent << PropName{ "children (source, destination)" } << '\n';
        WriteChildren(2);
        break;
    }

    default:
        out << indent << "Unknown paint type: " << element.paintType << '\n';
        break;
    }
}
```

The `DumpPaintElement` function calls the following `DumpGradientStops` function to output the array
of gradient stops for a paint element:

```c++
void DumpGradientStops(std::ostream& out, Indent indent, IDWritePaintReader* reader, uint32_t gradientStopCount)
{
    std::vector<D2D1_GRADIENT_STOP> stops;
    stops.resize(gradientStopCount);
    HR(reader->GetGradientStops(0, gradientStopCount, /*out*/ stops.data()));

    for (auto& stop : stops)
    {
        out << indent << "D2D1_GRADIENT_STOP:\n"
            << indent << PropName{ "position" } << stop.position << '\n'
            << indent << PropName{ "color" } << stop.color << '\n';
    }
}

```

The `Indent` helper type represents the indent level. Its associated stream operator outputs four
spaces for each level of indent:

```c++
struct Indent { int value; };
std::ostream& operator<<(std::ostream& out, Indent const& indent)
{
    for (int i = 0; i < indent.value; i++)
    {
        out << "    ";
    }
    return out;
}
Indent operator+(Indent lhs, int rhs)
{
    return Indent{ lhs.value + rhs };
}
```

The `PropName` helper type represents a property name:

```c++
struct PropName { char const* name; };
std::ostream& operator<<(std::ostream& out, PropName const& value)
{
    return out << "  - " << value.name << ": ";
}
```

For convenience, the sample uses the following stream output operators:

```c++
std::ostream& operator<<(std::ostream& out, DWRITE_COLOR_F const& value)
{
    return out << "{ " << value.r << ", " << value.g << ", " << value.b << ", " << value.a << " }";
}

std::ostream& operator<<(std::ostream& out, D2D_POINT_2F const& value)
{
    return out << '(' << value.x << ", " << value.y << ')';
}

std::ostream& operator<<(std::ostream& out, D2D_RECT_F const& value)
{
    return out << "{ "
        << value.left << ", "
        << value.top << ", "
        << value.right << ", "
        << value.bottom
        << " }";
}

std::ostream& operator<<(std::ostream& out, DWRITE_MATRIX const& value)
{
    return out << "{ "
        << value.m11 << ", "
        << value.m12 << ", "
        << value.m21 << ", "
        << value.m22 << ", "
        << value.dx << ", "
        << value.dy << " }";
}

std::ostream& operator<<(std::ostream& out, D2D1_EXTEND_MODE value)
{
    switch (value)
    {
    case D2D1_EXTEND_MODE_CLAMP: return out << "D2D1_EXTEND_MODE_CLAMP (0)";
    case D2D1_EXTEND_MODE_WRAP: return out << "D2D1_EXTEND_MODE_WRAP (1)";
    case D2D1_EXTEND_MODE_MIRROR: return out << "D2D1_EXTEND_MODE_MIRROR (2)";
    default: return out << (int)value;
    }
}

std::ostream& operator<<(std::ostream& out, DWRITE_PAINT_ATTRIBUTES value)
{
    switch (value)
    {
    case DWRITE_PAINT_ATTRIBUTES_USES_PALETTE:
        return out << "DWRITE_PAINT_ATTRIBUTES_USES_PALETTE";

    case DWRITE_PAINT_ATTRIBUTES_USES_TEXT_COLOR:
        return out << "DWRITE_PAINT_ATTRIBUTES_USES_TEXT_COLOR";

    case DWRITE_PAINT_ATTRIBUTES_USES_PALETTE | DWRITE_PAINT_ATTRIBUTES_USES_TEXT_COLOR:
        return out << "DWRITE_PAINT_ATTRIBUTES_USES_PALETTE | DWRITE_PAINT_ATTRIBUTES_USES_TEXT_COLOR";

    default:
        return out << (int)value;
    }
}

std::ostream& operator<<(std::ostream& out, DWRITE_COLOR_COMPOSITE_MODE value)
{
    switch (value)
    {
    case DWRITE_COLOR_COMPOSITE_CLEAR: return out << "DWRITE_COLOR_COMPOSITE_CLEAR";
    case DWRITE_COLOR_COMPOSITE_SRC: return out << "DWRITE_COLOR_COMPOSITE_SRC";
    case DWRITE_COLOR_COMPOSITE_DEST: return out << "DWRITE_COLOR_COMPOSITE_DEST";
    case DWRITE_COLOR_COMPOSITE_SRC_OVER: return out << "DWRITE_COLOR_COMPOSITE_SRC_OVER";
    case DWRITE_COLOR_COMPOSITE_DEST_OVER: return out << "DWRITE_COLOR_COMPOSITE_DEST_OVER";
    case DWRITE_COLOR_COMPOSITE_SRC_IN: return out << "DWRITE_COLOR_COMPOSITE_SRC_IN";
    case DWRITE_COLOR_COMPOSITE_DEST_IN: return out << "DWRITE_COLOR_COMPOSITE_DEST_IN";
    case DWRITE_COLOR_COMPOSITE_SRC_OUT: return out << "DWRITE_COLOR_COMPOSITE_SRC_OUT";
    case DWRITE_COLOR_COMPOSITE_DEST_OUT: return out << "DWRITE_COLOR_COMPOSITE_DEST_OUT";
    case DWRITE_COLOR_COMPOSITE_SRC_ATOP: return out << "DWRITE_COLOR_COMPOSITE_SRC_ATOP";
    case DWRITE_COLOR_COMPOSITE_DEST_ATOP: return out << "DWRITE_COLOR_COMPOSITE_DEST_ATOP";
    case DWRITE_COLOR_COMPOSITE_XOR: return out << "DWRITE_COLOR_COMPOSITE_XOR";
    case DWRITE_COLOR_COMPOSITE_PLUS: return out << "DWRITE_COLOR_COMPOSITE_PLUS";

    case DWRITE_COLOR_COMPOSITE_SCREEN: return out << "DWRITE_COLOR_COMPOSITE_SCREEN";
    case DWRITE_COLOR_COMPOSITE_OVERLAY: return out << "DWRITE_COLOR_COMPOSITE_OVERLAY";
    case DWRITE_COLOR_COMPOSITE_DARKEN: return out << "DWRITE_COLOR_COMPOSITE_DARKEN";
    case DWRITE_COLOR_COMPOSITE_LIGHTEN: return out << "DWRITE_COLOR_COMPOSITE_LIGHTEN";
    case DWRITE_COLOR_COMPOSITE_COLOR_DODGE: return out << "DWRITE_COLOR_COMPOSITE_COLOR_DODGE";
    case DWRITE_COLOR_COMPOSITE_COLOR_BURN: return out << "DWRITE_COLOR_COMPOSITE_COLOR_BURN";
    case DWRITE_COLOR_COMPOSITE_HARD_LIGHT: return out << "DWRITE_COLOR_COMPOSITE_HARD_LIGHT";
    case DWRITE_COLOR_COMPOSITE_SOFT_LIGHT: return out << "DWRITE_COLOR_COMPOSITE_SOFT_LIGHT";
    case DWRITE_COLOR_COMPOSITE_DIFFERENCE: return out << "DWRITE_COLOR_COMPOSITE_DIFFERENCE";
    case DWRITE_COLOR_COMPOSITE_EXCLUSION: return out << "DWRITE_COLOR_COMPOSITE_EXCLUSION";
    case DWRITE_COLOR_COMPOSITE_MULTIPLY: return out << "DWRITE_COLOR_COMPOSITE_MULTIPLY";

    case DWRITE_COLOR_COMPOSITE_HSL_HUE: return out << "DWRITE_COLOR_COMPOSITE_HSL_HUE";
    case DWRITE_COLOR_COMPOSITE_HSL_SATURATION: return out << "DWRITE_COLOR_COMPOSITE_HSL_SATURATION";
    case DWRITE_COLOR_COMPOSITE_HSL_COLOR: return out << "DWRITE_COLOR_COMPOSITE_HSL_COLOR";
    case DWRITE_COLOR_COMPOSITE_HSL_LUMINOSITY: return out << "DWRITE_COLOR_COMPOSITE_HSL_LUMINOSITY";
    default: return out << (int)value;
    }
}
```

## API Details

### DWRITE_FACTORY_TYPE Enumeration

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

### DWriteCoreCreateFactory Function

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

### DWRITE_BITMAP_DATA_BGRA32 Structure

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

### IDWriteBitmapRenderTarget2 Interface

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

### IDWriteFontSet4 Interface

```c++
DWRITE_BEGIN_INTERFACE(IDWriteFontSet4, "EEC175FC-BEA9-4C86-8B53-CCBDD7DF0C82") : IDWriteFontSet3
{
    /// <summary>
    /// Computes derived font axis values from the specified font weight, stretch, style, and size.
    /// </summary>
    /// <param name="inputAxisValues">Pointer to an optional array of input axis values. Axes present
    /// in this array are excluded from the output. This is so explicit axis values take precedence over
    /// derived axis values.</param>
    /// <param name="inputAxisCount">Size of the array of input axis values.</param>
    /// <param name="fontWeight">Font weight, used to compute "wght" axis value.</param>
    /// <param name="fontStretch">Font stretch, used to compute "wdth" axis value.</param>
    /// <param name="fontStyle">Font style, used to compute "slnt" and "ital" axis values.</param>
    /// <param name="fontSize">Font size in DIPs, used to compute "opsz" axis value. If this parameter is zero,
    /// no "opsz" axis value is added to the output array.</param>
    /// <param name="outputAxisValues">Pointer to an output array to which derived axis values are written.
    /// The size of this array must be at least DWRITE_STANDARD_FONT_AXIS_COUNT (5). The return value is
    /// the actual number of axis values written to this array.</param>
    /// <returns>Returns the actual number of derived axis values written to the output array.</returns>
    /// <remarks>The caller should concatenate the output axis values to the input axis values (if any),
    /// and pass the combined axis values to the GetMatchingFonts method. This does not result in duplicates
    /// because the output does not include any axes present in the inputAxisValues array.
    /// </remarks>
    STDMETHOD_(UINT32, ConvertWeightStretchStyleToFontAxisValues)(
        _In_reads_opt_(inputAxisCount) DWRITE_FONT_AXIS_VALUE const* inputAxisValues,
        UINT32 inputAxisCount,
        DWRITE_FONT_WEIGHT fontWeight,
        DWRITE_FONT_STRETCH fontStretch,
        DWRITE_FONT_STYLE fontStyle,
        float fontSize,
        _Out_writes_to_(DWRITE_STANDARD_FONT_AXIS_COUNT, return) DWRITE_FONT_AXIS_VALUE* outputAxisValues
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

### IDWriteFactory7 Interface

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

### DWRITE_GLYPH_IMAGE_FORMATS Enumeration

This enumeration defines formats that may be used to represent color glyphs in a font.

```c++
/// <summary>
/// Fonts may contain multiple drawable data formats for glyphs. These flags specify which formats
/// are supported in the font, either at a font-wide level or per glyph, and the app may use them
/// to tell DWrite which formats to return when splitting a color glyph run.
/// </summary>
enum DWRITE_GLYPH_IMAGE_FORMATS
{
    /// <summary>
    /// Indicates no data is available for this glyph.
    /// </summary>
    DWRITE_GLYPH_IMAGE_FORMATS_NONE = 0x00000000,

    /// <summary>
    /// The glyph has TrueType outlines.
    /// </summary>
    DWRITE_GLYPH_IMAGE_FORMATS_TRUETYPE = 0x00000001,

    /// <summary>
    /// The glyph has CFF outlines.
    /// </summary>
    DWRITE_GLYPH_IMAGE_FORMATS_CFF = 0x00000002,

    /// <summary>
    /// The glyph has multilayered COLR data.
    /// </summary>
    DWRITE_GLYPH_IMAGE_FORMATS_COLR = 0x00000004,

    /// <summary>
    /// The glyph has SVG outlines as standard XML.
    /// </summary>
    /// <remarks>
    /// Fonts may store the content gzip'd rather than plain text,
    /// indicated by the first two bytes as gzip header {0x1F 0x8B}.
    /// </remarks>
    DWRITE_GLYPH_IMAGE_FORMATS_SVG = 0x00000008,

    /// <summary>
    /// The glyph has PNG image data, with standard PNG IHDR.
    /// </summary>
    DWRITE_GLYPH_IMAGE_FORMATS_PNG = 0x00000010,

    /// <summary>
    /// The glyph has JPEG image data, with standard JIFF SOI header.
    /// </summary>
    DWRITE_GLYPH_IMAGE_FORMATS_JPEG = 0x00000020,

    /// <summary>
    /// The glyph has TIFF image data.
    /// </summary>
    DWRITE_GLYPH_IMAGE_FORMATS_TIFF = 0x00000040,

    /// <summary>
    /// The glyph has raw 32-bit premultiplied BGRA data.
    /// </summary>
    DWRITE_GLYPH_IMAGE_FORMATS_PREMULTIPLIED_B8G8R8A8 = 0x00000080,

    /// <summary>
    /// The glyph is represented by a tree of paint elements in the
    /// font's COLR table.
    /// </summary>
    DWRITE_GLYPH_IMAGE_FORMATS_COLR_PAINT_TREE = 0x00000100,
};

#ifdef DEFINE_ENUM_FLAG_OPERATORS
DEFINE_ENUM_FLAG_OPERATORS(DWRITE_GLYPH_IMAGE_FORMATS);
#endif

#define DWRITE_GLYPH_IMAGE_FORMATS_COLR_PAINT_TREE_DEFINED
```

The above enumeration is defined in `dcommon.h`, which is not a lifted header file.

The `DWRITE_GLYPH_IMAGE_FORMATS_COLR_PAINT_TREE_DEFINED` symbol exists so lifted `dwrite_3.h` can
conditionally define `DWRITE_GLYPH_IMAGE_FORMATS_COLR_PAINT_TREE` as a macro if it is not already
defined in the included version of `dcommon.h`. This is accomplished as follows in `dwrite_3.h`:

```c++
/// <summary>
/// DWRITE_GLYPH_IMAGE_FORMATS_COLR_PAINT_TREE image format represents a color glyph that can be
/// rendered by drawing paint elements returned by IDWritePaintReader.
/// </summary>
#ifndef DWRITE_GLYPH_IMAGE_FORMATS_COLR_PAINT_TREE_DEFINED
#define DWRITE_GLYPH_IMAGE_FORMATS_COLR_PAINT_TREE_DEFINED
#define DWRITE_GLYPH_IMAGE_FORMATS_COLR_PAINT_TREE static_cast<DWRITE_GLYPH_IMAGE_FORMATS>(0x00000100)
#endif
```

### DWRITE_PAINT_FEATURE_LEVEL Enumeration

```c++
/// <summary>
/// Defines known feature level for use with the IDWritePaintReader interface and
/// related APIs. A feature level represents a level of functionality. For example, it
/// determines what DWRITE_PAINT_TYPE values might be returned.
/// </summary>
/// <remarks>
/// See the DWRITE_PAINT_TYPE enumeration for which paint types are required for each
/// feature level.
/// </remarks>
enum DWRITE_PAINT_FEATURE_LEVEL
{
    /// <summary>
    /// No paint API support.
    /// </summary>
    DWRITE_PAINT_FEATURE_LEVEL_NONE = 0,

    /// <summary>
    /// Specifies a level of functionality corresponding to OpenType COLR version 0.
    /// </summary>
    DWRITE_PAINT_FEATURE_LEVEL_COLR_V0 = 1,

    /// <summary>
    /// Specifies a level of functionality corresponding to OpenType COLR version 1.
    /// </summary>
    DWRITE_PAINT_FEATURE_LEVEL_COLR_V1 = 2
};
```

### DWRITE_PAINT_ATTRIBUTES Enumeration

```c++
/// <summary>
/// Combination of flags specifying attributes of a color glyph or of specific color values in
/// a color glyph.
/// </summary>
enum DWRITE_PAINT_ATTRIBUTES
{
    DWRITE_PAINT_ATTRIBUTES_NONE = 0,

    /// <summary>
    /// Specifies that the color value (or any color value in the glyph) comes from the font's
    /// color palette. This means the appearance may depend on the current palette index, which
    /// may be important to clients that cache color glyphs.
    /// </summary>
    DWRITE_PAINT_ATTRIBUTES_USES_PALETTE = 0x01,

    /// <summary>
    /// Specifies that the color value (or any color value in the glyph) comes from the client-specified
    /// text color. This means the appearance may depend on the text color, which may be important to
    /// clients that cache color glyphs.
    /// </summary>
    DWRITE_PAINT_ATTRIBUTES_USES_TEXT_COLOR = 0x02
};
#ifdef DEFINE_ENUM_FLAG_OPERATORS
DEFINE_ENUM_FLAG_OPERATORS(DWRITE_PAINT_ATTRIBUTES)
#endif
```

### DWRITE_PAINT_COLOR Structure

```c++
/// <summary>
/// Represents a color in a color glyph.
/// </summary>
struct DWRITE_PAINT_COLOR
{
    /// <summary>
    /// Color value (not premultiplied). See the colorAttributes member for information about how
    /// the color is determined.
    /// </summary>
    DWRITE_COLOR_F value;

    /// <summary>
    /// If the colorAttributes member is DWRITE_PAINT_ATTRIBUTES_USES_PALETTE, this member is
    /// the index of a palette entry in the selected color palette. Otherwise, this member is
    /// DWRITE_NO_PALETTE_INDEX (0xFFFF).
    /// </summary>
    UINT16 paletteEntryIndex;

    /// <summary>
    /// Specifies an alpha value multiplier in the range 0 to 1 that was used to compute the color
    /// value. Color glyph descriptions may include alpha values to be multiplied with the alpha
    /// values of palette entries.
    /// </summary>
    float alphaMultiplier;

    /// <summary>
    /// Specifies how the color value is determined. If this member is
    /// DWRITE_PAINT_ATTRIBUTES_USES_PALETTE, the color value is determined by getting the color at
    /// paletteEntryIndex in the current color palette. The color's alpha value is then multiplied
    /// by alphaMultiplier. If a font has multiple color palettes, a client can set the current color
    /// palette using the IDWritePaintReader::SetColorPaletteIndex method. A client that uses a custom
    /// palette can use the paletteEntryIndex and alphaMultiplier methods to compute the color. If this
    /// member is DWRITE_PAINT_ATTRIBUTES_USES_TEXT_COLOR, the color value is equal to the text
    /// foreground color, which can be set using the IDWritePaintReader::SetTextColor method.
    /// </summary>
    DWRITE_PAINT_ATTRIBUTES colorAttributes;
};
```

### DWRITE_COLOR_COMPOSITE_MODE Enumeration

```c++
/// <summary>
/// Specifies a composite mode for combining source and destination paint elements in a
/// color glyph. These are taken from the W3C Compositing and Blending Level 1 specification.
/// </summary>
enum DWRITE_COLOR_COMPOSITE_MODE
{
    // Porter-Duff modes.
    DWRITE_COLOR_COMPOSITE_CLEAR,
    DWRITE_COLOR_COMPOSITE_SRC,
    DWRITE_COLOR_COMPOSITE_DEST,
    DWRITE_COLOR_COMPOSITE_SRC_OVER,
    DWRITE_COLOR_COMPOSITE_DEST_OVER,
    DWRITE_COLOR_COMPOSITE_SRC_IN,
    DWRITE_COLOR_COMPOSITE_DEST_IN,
    DWRITE_COLOR_COMPOSITE_SRC_OUT,
    DWRITE_COLOR_COMPOSITE_DEST_OUT,
    DWRITE_COLOR_COMPOSITE_SRC_ATOP,
    DWRITE_COLOR_COMPOSITE_DEST_ATOP,
    DWRITE_COLOR_COMPOSITE_XOR,
    DWRITE_COLOR_COMPOSITE_PLUS,

    // Separable color blend modes.
    DWRITE_COLOR_COMPOSITE_SCREEN,
    DWRITE_COLOR_COMPOSITE_OVERLAY,
    DWRITE_COLOR_COMPOSITE_DARKEN,
    DWRITE_COLOR_COMPOSITE_LIGHTEN,
    DWRITE_COLOR_COMPOSITE_COLOR_DODGE,
    DWRITE_COLOR_COMPOSITE_COLOR_BURN,
    DWRITE_COLOR_COMPOSITE_HARD_LIGHT,
    DWRITE_COLOR_COMPOSITE_SOFT_LIGHT,
    DWRITE_COLOR_COMPOSITE_DIFFERENCE,
    DWRITE_COLOR_COMPOSITE_EXCLUSION,
    DWRITE_COLOR_COMPOSITE_MULTIPLY,

    // Non-separable color blend modes.
    DWRITE_COLOR_COMPOSITE_HSL_HUE,
    DWRITE_COLOR_COMPOSITE_HSL_SATURATION,
    DWRITE_COLOR_COMPOSITE_HSL_COLOR,
    DWRITE_COLOR_COMPOSITE_HSL_LUMINOSITY
};
```

### DWRITE_PAINT_TYPE Enumeration

```c++
/// <summary>
/// Identifies a type of paint element in a color glyph. A color glyph's visual representation
/// is defined by a tree of paint elements. A paint element's properties are specified by a
/// DWRITE_PAINT_ELEMENT structure, which combines a paint type an a union.
/// </summary>
/// <remarks>
/// For more information about each paint type, see DWRITE_PAINT_ELEMENT.
/// </remarks>
enum DWRITE_PAINT_TYPE
{
    // The following paint types may be returned for color feature levels greater than
    // or equal to DWRITE_PAINT_FEATURE_LEVEL_COLR_V0.
    DWRITE_PAINT_TYPE_NONE,
    DWRITE_PAINT_TYPE_LAYERS,
    DWRITE_PAINT_TYPE_SOLID_GLYPH,

    // The following paint types may be returned for color feature levels greater than
    // or equal to DWRITE_PAINT_FEATURE_LEVEL_COLR_V1.
    DWRITE_PAINT_TYPE_SOLID,
    DWRITE_PAINT_TYPE_LINEAR_GRADIENT,
    DWRITE_PAINT_TYPE_RADIAL_GRADIENT,
    DWRITE_PAINT_TYPE_SWEEP_GRADIENT,
    DWRITE_PAINT_TYPE_GLYPH,
    DWRITE_PAINT_TYPE_COLOR_GLYPH,
    DWRITE_PAINT_TYPE_TRANSFORM,
    DWRITE_PAINT_TYPE_COMPOSITE
};
```

### DWRITE_PAINT_ELEMENT Structure

```c++
/// <summary>
/// Specifies properties of a paint element, which is one node in a visual tree associated
/// with a color glyph. This is passed as an output parameter to various IDWritePaintReader
/// methods.
/// </summary>
/// <remarks>
/// For a detailed description of how paint elements should be rendered, see the OpenType COLR
/// table specification. Comments below reference the COLR paint record formats associated with
/// each paint type.
/// </remarks>
struct DWRITE_PAINT_ELEMENT
{
    /// <summary>
    /// Specifies the paint type, and thus which member of the union is valid.
    /// </summary>
    DWRITE_PAINT_TYPE paintType;

    /// <summary>
    /// Specifies type-specific properties of the paint element.
    /// </summary>
    union PAINT_UNION
    {
        /// <summary>
        /// Valid for paint elements of type DWRITE_PAINT_TYPE_LAYERS.
        /// Contains one or more child paint elements to be drawn in bottom-up order.
        /// </summary>
        /// <remarks>
        /// This corresponds to a PaintColrLayers record in the OpenType COLR table.
        /// Or it may correspond to a BaseGlyph record defined by COLR version 0.
        /// </remarks>
        struct PAINT_LAYERS
        {
            /// <summary>
            /// Number of child paint elements in bottom-up order. Use the IDWritePaintReader
            /// interface's MoveFirstChild and MoveNextSibling methods to retrieve the child paint
            /// elements. Use the MoveParent method to return to the parent element.
            /// </summary>
            UINT32 childCount;
        } layers;

        /// <summary>
        /// Valid for paint elements of type DWRITE_PAINT_TYPE_SOLID_GLYPH.
        /// Specifies a glyph with a solid color fill.
        /// This paint element has no child elements.
        /// </summary>
        /// <remarks>
        /// This corresponds to a combination of two paint records in the OpenType COLR table:
        /// a PaintGlyph record, which references either a PaintSolid or PaintVarSolid record.
        /// Or it may correspond to a Layer record defined by COLR version 0.
        /// </remarks>
        struct PAINT_SOLID_GLYPH
        {
            /// <summary>
            /// Glyph index defining the shape to be filled.
            /// </summary>
            UINT32 glyphIndex;

            /// <summary>
            /// Glyph color used to fill the glyph shape.
            /// </summary>
            DWRITE_PAINT_COLOR color;
        } solidGlyph;

        /// <summary>
        /// Valid for paint elements of type DWRITE_PAINT_TYPE_SOLID.
        /// Specifies a solid color used to fill the current shape or clip.
        /// This paint element has no child elements.
        /// </summary>
        /// <remarks>
        /// This corresponds to a PaintSolid or PaintVarSolid record in the OpenType COLR table.
        /// </remarks>
        DWRITE_PAINT_COLOR solid;

        /// <summary>
        /// Valid for paint elements of type DWRITE_PAINT_TYPE_LINEAR_GRADIENT.
        /// Specifies a linear gradient used to fill the current shape or clip.
        /// This paint element has no child elements.
        /// </summary>
        /// <remarks>
        /// This corresponds to a PaintLinearGradient or PaintVarLinearGradient record in the OpenType
        /// COLR table.
        /// </remarks>
        struct PAINT_LINEAR_GRADIENT
        {
            /// <summary>
            /// D2D1_EXTEND_MODE value speciying how colors outside the interval are defined.
            /// </summary>
            UINT32 extendMode;

            /// <summary>
            /// Number of gradient stops. Use the IDWritePaintReader::GetGradientStops method to
            /// get the gradient stops.
            /// </summary>
            UINT32 gradientStopCount;

            /// <summary>
            /// X coordinate of the start point of the color line.
            /// </summary>
            float x0;

            /// <summary>
            /// Y coordinate of the start point of the color line.
            /// </summary>
            float y0;

            /// <summary>
            /// X coordinate of the end point of the color line.
            /// </summary>
            float x1;

            /// <summary>
            /// Y coordinate of the end point of the color line.
            /// </summary>
            float y1;

            /// <summary>
            /// X coordinate of the rotation point of the color line.
            /// </summary>
            float x2;

            /// <summary>
            /// Y coordinate of the rotation point of the color line.
            /// </summary>
            float y2;
        } linearGradient;

        /// <summary>
        /// Valid for paint elements of type DWRITE_PAINT_TYPE_RADIAL_GRADIENT.
        /// Specifies a radial gradient used to fill the current shape or clip.
        /// This paint element has no child elements.
        /// </summary>
        /// <remarks>
        /// This corresponds to a PaintRadialGradient or PaintVarRadialGradient record in the OpenType
        /// COLR table.
        /// </remarks>
        struct PAINT_RADIAL_GRADIENT
        {
            /// <summary>
            /// D2D1_EXTEND_MODE value speciying how colors outside the interval are defined.
            /// </summary>
            UINT32 extendMode;

            /// <summary>
            /// Number of gradient stops. Use the IDWritePaintReader::GetGradientStops method to
            /// get the gradient stops.
            /// </summary>
            UINT32 gradientStopCount;

            /// <summary>
            /// Center X coordinate of the start circle.
            /// </summary>
            float x0;

            /// <summary>
            /// Center Y coordinate of the start circle.
            /// </summary>
            float y0;

            /// <summary>
            /// Radius of the start circle.
            /// </summary>
            float radius0;

            /// <summary>
            /// Center X coordinate of the end circle.
            /// </summary>
            float x1;

            /// <summary>
            /// Center Y coordinate of the end circle.
            /// </summary>
            float y1;

            /// <summary>
            /// Radius of the end circle.
            /// </summary>
            float radius1;
        } radialGradient;

        /// <summary>
        /// Valid for paint elements of type DWRITE_PAINT_TYPE_SWEEP_GRADIENT.
        /// Specifies a sweep gradient used to fill the current shape or clip.
        /// This paint element has no child elements.
        /// </summary>
        /// <remarks>
        /// This corresponds to a PaintSweepGradient or PaintVarSweepGradient record in the OpenType
        /// COLR table.
        /// </remarks>
        struct PAINT_SWEEP_GRADIENT
        {
            /// <summary>
            /// D2D1_EXTEND_MODE value speciying how colors outside the interval are defined.
            /// </summary>
            UINT32 extendMode;

            /// <summary>
            /// Number of gradient stops. Use the IDWritePaintReader::GetGradientStops method to
            /// get the gradient stops.
            /// </summary>
            UINT32 gradientStopCount;

            /// <summary>
            /// Center X coordinate.
            /// </summary>
            float centerX;

            /// <summary>
            /// Center Y coordinate.
            /// </summary>
            float centerY;

            /// <summary>
            /// Start of the angular range of the gradient, measured in counter-clockwise degrees
            /// from the direction of the positive x axis.
            /// </summary>
            float startAngle;

            /// <summary>
            /// End of the angular range of the gradient, measured in counter-clockwise degrees
            /// from the direction of the positive x axis.
            /// </summary>
            float endAngle;
        } sweepGradient;

        /// <summary>
        /// Valid for paint elements of type DWRITE_PAINT_TYPE_GLYPH.
        /// Specifies a glyph shape to be filled or, equivalently, a clip region.
        /// This paint element has one child element.
        /// </summary>
        /// <remarks>
        /// The child paint element defines how the glyph shape is filled. The child element can be a single paint
        /// element, such as a linear gradient. Or the child element can be the root of a visual tree to be rendered
        /// with the glyph shape as a clip region.
        /// This corresponds to a PaintGlyph record in the OpenType COLR table.
        /// </remarks>
        struct PAINT_GLYPH
        {
            /// <summary>
            /// Glyph index of the glyph that defines the shape to be filled.
            /// </summary>
            UINT32 glyphIndex;
        } glyph;

        /// <summary>
        /// Valid for paint elements of type DWRITE_PAINT_TYPE_COLOR_GLYPH.
        /// Specifies another color glyph, used as a reusable component.
        /// This paint element has one child element, which is the root paint element of the specified color glyph.
        /// </summary>
        /// <remarks>
        /// This corresponds to a PaintColorGlyph record in the OpenType COLR table.
        /// </remarks>
        struct PAINT_COLOR_GLYPH
        {
            /// <summary>
            /// Glyph index of the referenced color glyph.
            /// </summary>
            UINT32 glyphIndex;

            /// <summary>
            /// Clip box of the referenced color glyph, in ems. This is an empty rectangle of the color glyph does
            /// not specify a clip box. If it is not an empty rect, the client is required to clip the child content
            /// to this box.
            /// </summary>
            D2D_RECT_F clipBox;
        } colorGlyph;

        /// <summary>
        /// Valid for paint elements of type DWRITE_PAINT_TYPE_TRANSFORM.
        /// Specifies an affine transform to be applied to child content.
        /// This paint element has one child element, which is the transformed content.
        /// </summary>
        /// <remarks>
        /// This corresponds to paint formats 12 through 31 in the OpenType COLR table.
        /// </remarks>
        DWRITE_MATRIX transform;

        /// <summary>
        /// Valid for paint elements of type DWRITE_PAINT_TYPE_COMPOSITE.
        /// Combines the two child paint elements using the specified compositing or blending mode.
        /// This paint element has two child elements. The first child is the paint source. The
        /// second child is the paint destination (or backdrop).
        /// </summary>
        /// <remarks>
        /// This corresponds to a PaintComposite record in the OpenType COLR table.
        /// </remarks>
        struct PAINT_COMPOSITE
        {
            /// <summary>
            /// Specifies the compositing or blending mode.
            /// </summary>
            DWRITE_COLOR_COMPOSITE_MODE mode;
        } composite;
    } paint;
};
```

### IDWritePaintReader Interface

```c++
/// <summary>
/// Interface used to read color glyph data for a specific font. A color glyph is
/// represented as a visual tree of paint elements.
/// </summary>
DWRITE_BEGIN_INTERFACE(IDWritePaintReader, "8128E912-3B97-42A5-AB6C-24AAD3A86E54") : IUnknown
{
    /// <summary>
    /// Sets the current glyph and positions the reader on the root paint element of the
    /// selected glyph's visual tree.
    /// </summary>
    /// <param name="glyphIndex">Glyph index to get the color glyph representation for.</param>
    /// <param name="paintElement">Receives information about the root paint element of the
    /// glyph's visual tree.</param>
    /// <param name="structSize">Size of the DWRITE_PAINT_ELEMENT structure, in bytes.</param>
    /// <param name="clipBox">Receives a precomputed glyph box (in ems) for the specified glyph,
    /// if one is specified by the font. Otherwise, the glyph box is set to an empty rectangle
    /// (all zeros). If a non-empty clip box is specified, the client must clip the color
    /// glyph's representation to the specified box.</param>
    /// <param name="glyphAttributes">Receives optional paint attributes for the glyph.</param>
    /// <returns>
    /// Standard HRESULT error code.
    /// </returns>
    /// <remarks>
    /// If the specified glyph index is not a color glyph, the method succeeds, but the paintType
    /// member of the DWRITE_PAINT_ELEMENT structure is set to DWRITE_PAINT_TYPE_NONE. In this
    /// case, the application should draw the input glyph as a non-color glyph.
    /// </remarks>
    STDMETHOD(SetCurrentGlyph)(
        UINT32 glyphIndex,
        _Out_writes_bytes_(structSize) DWRITE_PAINT_ELEMENT* paintElement,
        UINT32 structSize,
        _Out_ D2D_RECT_F* clipBox,
        _Out_opt_ DWRITE_PAINT_ATTRIBUTES* glyphAttributes = nullptr
        ) PURE;

    // Inline overload of SetCurrentGlyph, in which structSize is implied.
    HRESULT SetCurrentGlyph(
        UINT32 glyphIndex,
        _Out_writes_bytes_(structSize) DWRITE_PAINT_ELEMENT* paintElement,
        _Out_ D2D_RECT_F* clipBox,
        _Out_opt_ DWRITE_PAINT_ATTRIBUTES* glyphAttributes = nullptr
        )
    {
        return SetCurrentGlyph(
            glyphIndex,
            paintElement,
            sizeof(DWRITE_PAINT_ELEMENT),
            clipBox,
            glyphAttributes
            );
    }

    /// <summary>
    /// Sets the client-defined text color. The default value is transparent black. Changing the text color
    /// can affect the appearance of a glyph if its definition uses the current text color. If this is the
    /// case, the SetCurrentGlyph method returns the DWRITE_PAINT_ATTRIBUTES_USES_TEXT_COLOR flag via the
    /// glyphAttributes output parameter.
    /// </summary>
    /// <param name="textColor">Specifies the text color.</param>
    /// <returns>
    /// Standard HRESULT error code.
    /// </returns>
    STDMETHOD(SetTextColor)(
        DWRITE_COLOR_F const& textColor
        ) PURE;

    /// <summary>
    /// Sets the current color palette index. The default value is zero. Changing the palette index can affect
    /// the appearance of a glyph if its definition references colors in the color palette. If this is the case,
    /// the SetCurrentGlyph method returns the DWRITE_PAINT_ATTRIBUTES_USES_PALETTE flag via the glyphAttributes
    /// output parameter.
    /// </summary>
    /// <param name="textColor">Specifies the color palette index.</param>
    /// <returns>
    /// Standard HRESULT error code.
    /// </returns>
    STDMETHOD(SetColorPaletteIndex)(
        UINT32 colorPaletteIndex
        ) PURE;

    /// <summary>
    /// Sets a custom color palette with client-defined palette entries instead of using a font-defined color
    /// palette. Changing the color palette can affect the appearance of a glyph if its definition references
    /// colors in the color palette. If this is the case, the SetCurrentGlyph method returns the
    /// DWRITE_PAINT_ATTRIBUTES_USES_PALETTE flag via the glyphAttributes output parameter.
    /// </summary>
    /// <param name="paletteEntries">Array of palette entries for the client-defined color palette.</param>
    /// <param name="paletteEntryCount">Size of the paletteEntries array. This must equal the font's palette
    /// entry count as returned by IDWriteFontFace2::GetPaletteEntryCount.</param>
    /// <returns>
    /// Standard HRESULT error code.
    /// </returns>
    STDMETHOD(SetCustomColorPalette)(
        _In_reads_(paletteEntryCount) DWRITE_COLOR_F const* paletteEntries,
        UINT32 paletteEntryCount
        ) PURE;

    /// <summary>
    /// Sets the current position in the visual tree to the first child of the current paint element, and returns
    /// the newly-selected element's properties via the paintElement output parameter.
    /// </summary>
    /// <param name="paintElement">Receives the properties of the newly-selected element.</param>
    /// <param name="structSize">Size of the DWRITE_PAINT_ELEMENT structure, in bytes.</param>
    /// <returns>
    /// Standard HRESULT error code. The return value is E_INVALIDARG if the current paint element doesn't have
    /// any children.
    /// </returns>
    /// <remarks>
    /// Whether a paint element has children (and how many) can be determined a priori from its paint type and
    /// properties. For more information, see DWRITE_PAINT_ELEMENT.
    /// </remarks>
    STDMETHOD(MoveToFirstChild)(
        _Out_writes_bytes_(structSize) DWRITE_PAINT_ELEMENT* paintElement,
        UINT32 structSize = sizeof(DWRITE_PAINT_ELEMENT)
        ) PURE;

    /// <summary>
    /// Sets the current position in the visual tree to the next sibling of the current paint element, and returns
    /// the newly-selected element's properties via the paintElement output parameter.
    /// </summary>
    /// <param name="paintElement">Receives the properties of the newly-selected element.</param>
    /// <param name="structSize">Size of the DWRITE_PAINT_ELEMENT structure, in bytes.</param>
    /// <returns>
    /// Standard HRESULT error code. The return value is E_INVALIDARG if the current paint element doesn't have
    /// a next sibling.
    /// </returns>
    /// <remarks>
    /// Whether a paint element has children (and how many) can be determined a priori from its paint type and
    /// properties. For more information, see DWRITE_PAINT_ELEMENT.
    /// </remarks>
    STDMETHOD(MoveToNextSibling)(
        _Out_writes_bytes_(structSize) DWRITE_PAINT_ELEMENT* paintElement,
        UINT32 structSize = sizeof(DWRITE_PAINT_ELEMENT)
        ) PURE;

    /// <summary>
    /// Sets the current position in the visual tree to the parent of the current paint element.
    /// </summary>
    /// <returns>
    /// Standard HRESULT error code. The return value is E_INVALIDARG if the current paint element is the root
    /// element of the visual tree.
    /// </returns>
    STDMETHOD(MoveToParent)() PURE;

    /// <summary>
    /// Returns gradient stops of the current paint element.
    /// </summary>
    /// <param name="firstGradientStopIndex">Index of the first gradient stop to get.</param>
    /// <param name="gradientStopCount">Number of gradient stops to get.</param>
    /// <param name="gradientStops">Receives the gradient stops.</param>
    /// <returns>Standard HRESULT error code.</returns>
    STDMETHOD(GetGradientStops)(
        UINT32 firstGradientStopIndex,
        UINT32 gradientStopCount,
        _Out_writes_(gradientStopCount) D2D1_GRADIENT_STOP* gradientStops
        ) PURE;

    /// <summary>
    /// Returns color information about each gradient stop, such as palette indices.
    /// </summary>
    /// <param name="firstGradientStopIndex">Index of the first gradient stop to get.</param>
    /// <param name="gradientStopCount">Number of gradient stops to get.</param>
    /// <param name="gradientStopColors">Receives the gradient stop colors.</param>
    /// <returns>Standard HRESULT error code.</returns>
    STDMETHOD(GetGradientStopColors)(
        UINT32 firstGradientStopIndex,
        UINT32 gradientStopCount,
        _Out_writes_(gradientStopCount) DWRITE_PAINT_COLOR* gradientStopColors
        ) PURE;
};
```

### IDWriteFontFace7 Interface

```c++
DWRITE_BEGIN_INTERFACE(IDWriteFontFace7, "3945B85B-BC95-40F7-B72C-8B73BFC7E13B") : IDWriteFontFace6
{
    /// <summary>
    /// Returns the maximum paint feature level supported for the specified glyph image format.
    /// Possible values are specified by the DWRITE_PAINT_FEATURE_LEVEL enumeration,
    /// but additional feature levels may be added over time.
    /// </summary>
    /// <param name="glyphImageFormat">Glyph image format to get the paint feature level for.
    /// The return value is zero if the image format is not supported by the IDWritePaintReader API,
    /// or if the font doesn't contain image data in that format.</param>
    STDMETHOD_(DWRITE_PAINT_FEATURE_LEVEL, GetPaintFeatureLevel)(
        DWRITE_GLYPH_IMAGE_FORMATS glyphImageFormat
        ) PURE;

    /// <summary>
    /// Creates a paint reader object, which can be used to retrieve vector graphic information
    /// for color glyphs in the font.
    /// </summary>
    /// <param name="glyphImageFormat">Specifies the type of glyph data the reader will obtain. The only
    /// glyph image format currently supported by this method is DWRITE_GLYPH_IMAGE_FORMATS_COLR_PAINT_TREE.</param>
    /// <param name="paintFeatureLevel">Specifies the maximum paint feature level supported by the client.
    /// This affects the types of paint elements that may be returned by the paint reader.</param>
    /// <param name="paintReader">Receives a pointer to the newly-created object.</param>
    /// <returns>Standard HRESULT error code.</returns>
    STDMETHOD(CreatePaintReader)(
        DWRITE_GLYPH_IMAGE_FORMATS glyphImageFormat,
        DWRITE_PAINT_FEATURE_LEVEL paintFeatureLevel,
        _COM_Outptr_ IDWritePaintReader** paintReader
        ) PURE;
};
```

### IDWriteFactory8 Interface

The `IDWriteFactory8` interface adds a new version of `TranslateColorGlyphRun`. The new method adds
a new _paintFeatureLevel_ parameter, but is otherwise identical to
`IDWriteFactory4::TranslateColorGlyphRun`.

```c++
DWRITE_BEGIN_INTERFACE(IDWriteFactory8, "EE0A7FB5-DEF4-4C23-A454-C9C7DC878398") : IDWriteFactory7
{
    /// <summary>
    /// Translates a glyph run to a sequence of color glyph runs, which can be
    /// rendered to produce a color representation of the original "base" run.
    /// </summary>
    /// <param name="baselineOriginX">Horizontal and vertical origin of the base glyph run in
    /// pre-transform coordinates.</param>
    /// <param name="glyphRun">Pointer to the original "base" glyph run.</param>
    /// <param name="glyphRunDescription">Optional glyph run description.</param>
    /// <param name="desiredGlyphImageFormats">Which data formats TranslateColorGlyphRun
    /// should split the runs into.</param>
    /// <param name="paintFeatureLevel">Paint feature level supported by the caller. Used
    /// when desiredGlyphImageFormats includes DWRITE_GLYPH_IMAGE_FORMATS_COLR_PAINT_TREE. See
    /// DWRITE_PAINT_FEATURE_LEVEL for more information.</param>
    /// <param name="measuringMode">Measuring mode, needed to compute the origins
    /// of each glyph.</param>
    /// <param name="worldToDeviceTransform">Matrix converting from the client's
    /// coordinate space to device coordinates (pixels), i.e., the world transform
    /// multiplied by any DPI scaling.</param>
    /// <param name="colorPaletteIndex">Zero-based index of the color palette to use.
    /// Valid indices are less than the number of palettes in the font, as returned
    /// by IDWriteFontFace2::GetColorPaletteCount.</param>
    /// <param name="colorEnumerator">If the function succeeds, receives a pointer
    /// to an enumerator object that can be used to obtain the color glyph runs.
    /// If the base run has no color glyphs, then the output pointer is NULL
    /// and the method returns DWRITE_E_NOCOLOR.</param>
    /// <returns>
    /// Returns DWRITE_E_NOCOLOR if the font has no color information, the glyph run
    /// does not contain any color glyphs, or the specified color palette index
    /// is out of range. In this case, the client should render the original glyph
    /// run. Otherwise, returns a standard HRESULT error code.
    /// </returns>
    /// <remarks>
    /// The old IDWriteFactory2::TranslateColorGlyphRun is equivalent to passing
    /// DWRITE_GLYPH_IMAGE_FORMATS_TRUETYPE|CFF|COLR.
    /// </remarks>
    STDMETHOD(TranslateColorGlyphRun)(
        D2D1_POINT_2F baselineOrigin,
        _In_ DWRITE_GLYPH_RUN const* glyphRun,
        _In_opt_ DWRITE_GLYPH_RUN_DESCRIPTION const* glyphRunDescription,
        DWRITE_GLYPH_IMAGE_FORMATS desiredGlyphImageFormats,
        DWRITE_PAINT_FEATURE_LEVEL paintFeatureLevel,
        DWRITE_MEASURING_MODE measuringMode,
        _In_opt_ DWRITE_MATRIX const* worldAndDpiTransform,
        UINT32 colorPaletteIndex,
        _COM_Outptr_ IDWriteColorGlyphRunEnumerator1** colorEnumerator
        ) PURE;
};
```

### IDWriteBitmapRenderTarget3 Interface

```c++
/// <summary>
/// Encapsulates a bitmap which can be used for rendering glyphs.
/// </summary>
DWRITE_BEGIN_INTERFACE(IDWriteBitmapRenderTarget3, "AEEC37DB-C337-40F1-8E2A-9A41B167B238") : IDWriteBitmapRenderTarget2
{
    /// <summary>
    /// Returns the paint feature level supported by this render target.
    /// A client can pass the return value of this method to IDWriteFactory8::TranslateColorGlyphRun.
    /// </summary>
    STDMETHOD_(DWRITE_PAINT_FEATURE_LEVEL, GetPaintFeatureLevel)() PURE;

    /// <summary>
    /// Draws a glyph run in a "paint" image format returned by IDWriteColorGlyphRunEnumerator1.
    /// </summary>
    /// <param name="baselineOriginX">X-coordinate of the baseline.</param>
    /// <param name="baselineOriginY">Y-coordinate of the baseline.</param>
    /// <param name="measuringMode">Specifies measuring mode for positioning glyphs in the run.</param>
    /// <param name="glyphRun">The glyph run to draw.</param>
    /// <param name="glyphImageFormat">The image format of the color glyph run, as returned by
    /// IDWriteColorGlyphRunEnumerator1. This must be one of the "paint" image formats.</param>
    /// <param name="textColor">Foreground color of the text, used in cases where a color glyph
    /// uses the text color.</param>
    /// <param name="colorPaletteIndex">Zero-based index of the font-defined color palette to use.</param>
    /// <param name="blackBoxRect">Optional rectangle that receives the bounding box (in pixels not DIPs) of all the pixels affected by
    /// drawing the glyph run. The black box rectangle may extend beyond the dimensions of the bitmap.</param>
    /// <returns>
    /// Standard HRESULT error code.
    /// </returns>
    STDMETHOD(DrawPaintGlyphRun)(
        FLOAT baselineOriginX,
        FLOAT baselineOriginY,
        DWRITE_MEASURING_MODE measuringMode,
        _In_ DWRITE_GLYPH_RUN const* glyphRun,
        DWRITE_GLYPH_IMAGE_FORMATS glyphImageFormat,
        COLORREF textColor,
        UINT32 colorPaletteIndex = 0,
        _Out_opt_ RECT* blackBoxRect = NULL
        ) PURE;

    /// <summary>
    /// Draws a glyph run, using color representations of glyphs if available in the font.
    /// </summary>
    /// <param name="baselineOriginX">X-coordinate of the baseline.</param>
    /// <param name="baselineOriginY">Y-coordinate of the baseline.</param>
    /// <param name="measuringMode">Specifies measuring mode for positioning glyphs in the run.</param>
    /// <param name="glyphRun">The glyph run to draw.</param>
    /// <param name="renderingParams">Object that controls rendering behavior.</param>
    /// <param name="textColor">Foreground color of the text.</param>
    /// <param name="colorPaletteIndex">Zero-based index of the font-defined color palette to use.</param>
    /// <param name="blackBoxRect">Optional rectangle that receives the bounding box (in pixels not DIPs) of all the pixels affected by
    /// drawing the glyph run. The black box rectangle may extend beyond the dimensions of the bitmap.</param>
    /// <returns>
    /// Standard HRESULT error code.
    /// </returns>
    /// <remarks>
    /// This method internally calls TranslateColorGlyphRun and then automatically calls the appropriate
    /// lower-level methods to render monochrome or color glyph runs.
    /// </remarks>
    STDMETHOD(DrawGlyphRunWithColorSupport)(
        FLOAT baselineOriginX,
        FLOAT baselineOriginY,
        DWRITE_MEASURING_MODE measuringMode,
        _In_ DWRITE_GLYPH_RUN const* glyphRun,
        _In_ IDWriteRenderingParams* renderingParams,
        COLORREF textColor,
        UINT32 colorPaletteIndex = 0,
        _Out_opt_ RECT* blackBoxRect = NULL
        ) PURE;
};
```
