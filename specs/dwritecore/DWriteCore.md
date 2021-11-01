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
 - A new `DWRITE_FACTORY_TYPE` enumeration value for creating an isolated factory object
 - A new method for getting pixel data from a bitmap render target
 - New methods for selecting fonts from a font set

# Factory Creation

The new `DWRITE_FACTORY_TYPE_ISOLATED2` enum value complements the existing factory types. It is similar to
`DWRITE_FACTORY_TYPE_ISOLATED`, but is more locked down in two ways. First, it only caches data in-process, and
will not attempt to either read from or write to a cross-process font cache or persisted cache file. Second,
a restricted factory only enumerates well-known fonts in the system font collection. The well-known-fonts
restriction enables DWriteCore to efficiently construct the system font collection without depending on a
cross-process or persistent cache. An example use case for the new factory type would be a web browser
rendering process with very limited permissions.

# Text Rendering

A _bitmap render target_ (`IDWriteBitmapRenderTarget`) is an API object that encapsulates a system memory bitmap
and enables rendering glyphs to the bitmap. On Windows, the object encapsulates a GDI memory DC with a GDI
device-dependent bitmap (DIB) selected into it. However, on non-Windows platforms, there is no GDI DC,
and the bitmap is just a system memory array. DWriteCore introduces a new version of the bitmap render target
interface that an application can use to access the bitmap data without going through GDI.

# Font Selection

The new `IDWriteFontSet4` interface exposes new methods for selecting fonts from a font set. The new methods
make it possible to transition to the _typographic font family model_ while maintaining compatibility with
existing applications, documents, and fonts.

Font selection (sometimes called font matching or font mapping) is the process of selecting the available
fonts that best match input parameters passed in by an application. The input parameters are sometimes
referred to collectively as a _logical font_. A font selection algorithm matches the logical font (the
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

The font family model used by GDI is sometimes called the "four-font model" or "RBIZ" model. Each font
family in this model typically has at most four fonts. The "RBIZ" label comes from the naming convention
used for some font files, for example:

File Name       | Font Style
----------------|-------------
verdana.ttf     | Regular
verdanab.ttf    | Bold
verdanai.ttf    | Italic
verdanaz.ttf    | Bold Italic

With GDI, the input parameters used to select a font are defined by the `LOGFONT` structure, which
includes family name (`lfFaceName`), weight (`lfWeight`) and italic (`lfItalic`) fields.

The `lfItalic` field is a BOOL so it can only be TRUE or FALSE. The `lfWeight` field can technically be
any weight in the range `FW_THIN` (100) to `FW_BLACK` (900), but is typically either `FW_NORMAL` (400)
or `FW_BOLD` (700). For historical reasons, fonts designed for the RBIZ model almost always have one of 
these two weights.

To understand why, it helps to think of fonts as evolving in an ecosystem that also includes
applications. Popular application user interfaces include an italic button (to turn italic on and off)
and a bold button (to toggle between normal and bold weight). This user interface design made sense at
a time when computer font families rarely had more than two weights. However, a side effect was that
subsequent fonts could only have two weights within an RBIZ family if they wanted to work with
existing applications.

Suppose you wanted to add a heavier "Black" weight to the Arial font family. Logically, this font is
part of the Arial family, so you might expect to select it by setting `lfFaceName` to "Arial" and 
`lfWeight` to `FW_BLACK`. However, there is no way for an application user to choose between three
weights using a two-state bold button. The solution was to give the new font a different family name,
so the user could select it by choosing "Arial Black" from the list of font families. Likewise, there
is no way to choose from among different widths in the same font family if your only affordances are
bold and italic buttons, so the narrow versions of Arial have different family names in the RBIZ
model. Thus we have "Arial", "Arial Black", and "Arial Narrow" font familes in the RBIZ model
even though typographically these all belong in one family.

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
be differentiated by stretch (or width). Second, there can be more than two weights in the same family.
This flexibility is sufficient to allow all the variants of Arial to be included in the same WWS family.
The following table compares RBIZ and WWS font properties for a selection of Arial fonts:

File Name       | RBIZ Family Name      | lfWeight  | lfItalic  | WWS FamilyName    | Weight    | Stretch   | Style
----------------|-----------------------|-----------|-----------|-------------------|-----------|-----------|---------
arial.ttf       | Arial                 | 400       | 0         | Arial             | 400       | 5         | 0
arialbd.ttf     | Arial                 | 700       | 0         | Arial             | 700       | 5         | 0
ariblk.ttf      | Arial Black           | 900       | 0         | Arial             | 900       | 5         | 0
ARIALN.TTF      | Arial Narrow          | 400       | 0         | Arial             | 400       | 3         | 0

As you can see, "Arial Narrow" has the same `lfWeight` and `lfItalic` values as Arial Regular, so it 
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

Advantages of the typographic font family model are:

  - Fonts can be grouped into families as intended by the designer, rather than being split into
    subfamilies due to limitations of the font family model.

  - An application can automatically select the correct "opsz" axis value based on the font size
    rather than exposing different optical sizes to the user as different font families.

  - Arbitrary instances of variable fonts can be selected. For example, if a variable font supports
    weights in the range 100-900, the typographic model can select _any_ weight in this range. The
    older font family models can only choose the nearest weight from among the named instances defined
    by the font.

However, migrating to the typographic font family model raises potential compatibility issues. The
next section describes these issues and how they are mitigated by the hybrid font selection model.

## Hybrid Font Selection Model

The hybrid font selection model combines aspects of the weight-stretch-style and typographic font family
models. This preserves the advantages of the typographic model while mitigating the following potential 
compatibility issues:

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

File                    | WWS Family   | Weight    | Stretch   | Style  | Typo Family   | wght  | wdth  | ital  | slnt
------------------------|--------------|-----------|-----------|--------|---------------|-------|-------|-------|------
Legacy-Regular.ttf      | Legacy       | 400       | 5         | 0      | Legacy        | 400   | 100   | 0     | 0
Legacy-Bold.ttf         | Legacy       | 700       | 5         | 0      | Legacy        | 700   | 100   | 0     | 0
Legacy-Black.ttf        | Legacy       | 900       | 5         | 0      | Legacy        | 900   | 100   | 0     | 0
Legacy-Soft.ttf         | Legacy Soft  | 400       | 5         | 0      | Legacy        | 400   | 100   | 0     | 0
Legacy-SoftBold.ttf     | Legacy Soft  | 700       | 5         | 0      | Legacy        | 700   | 100   | 0     | 0
Legacy-SoftBlack.ttf    | Legacy Soft  | 900       | 5         | 0      | Legacy        | 900   | 100   | 0     | 0

The "Legacy" typographic family has three weights and each weight has regular and "Soft" variants.
However, these fonts predate OpenType 1.8, so there is no "SOFT" axis, or any other axes that cannot
be derived from weight, stretch, and style. For each weight, there are two fonts with the same axis
values. Therefore, it is not possible to unambiguously select the above fonts using the typographic
family name and axis values alone.

The hybrid font selection model mitigates this by allowing the specified family name to be _either_
a typographic family name or a weight-stretch-style name. (It can also be an RBIZ name or full name.)
In the example above, an application can avoid ambiguity by specifying "Legacy" or "Legacy Soft"
as the family name. These two cases are handled as follows:

  - "Legacy Soft" does not match a typographic family name, so only fonts in the WWS family
    are considered. These can be differentiated by weight, so there is no ambiguity.

  - "Legacy" matches both a typographic family and a WWS family. All fonts in the typographic
    family are considered, but presence in the WWS family is used as a tie-breaker. For example,
    Legacy-Regular.ttf has the same weight as Legacy-Soft.ttf, but the former is preferred because
    it is in the "Legacy" WWS family.

Document and application compatibility issues are mitigated by allowing different types of font
names to be specified and also by providing a method of deriving axis values from weight, stretch,
and style parameters.

Suppose a document specifies a family name, weight, stretch, and style, but no axis values. The
application can first map the weight, stretch, style, and font size to axis values by calling the
`IDWriteFontSet4::GetDerivedFontAxisValues` method. The application can then pass both the family
name and axis values to `IDWriteFontSet4::GetMatchingFonts`. `GetMatchingFonts` returns a list of
matching fonts in priority order, and the result is appropriate whether the specified family name
is a typographic family name, weight-stretch-style family name, RBIZ family name, or full name.
If the specified family has an "opsz" axis, the appropriate optical size is automatically selected
based on the font size.

Suppose a document specifies weight, stretch, and style and _also_ specifies axis values. In this
case, the explicit axis values can also be passed in to `IDWriteFontSet4::GetDerivedFontAxisValues`,
and the derived axis values returned by the method will only include font axes that were not
specified explicitly. The application can then pass the combined axis values (explicit and derived)
to `IDWriteFontSet4::GetMatchingFonts`.

## Hybrid Font Selection APIs

The hybrid font selection model is implemented by the following `IDWriteFontSet4` methods:

  - The `GetDerivedFontAxisValues` method converts font size, weight, stretch, and style parameters
    to the corresponding axis values. Any explicit axis values passed in by the client are excluded
    from the derived axis values.

  - The `GetMatchingFonts` method returns a prioritized list of matching fonts given a family name
    and array of axis values. As described above, the family name parameter can be a typographic
    family name, weight-stretch-style family name, RBIZ family name, or full name. (Full name is
    allowed because GDI allows font matching by full name.)

The following other DirectWrite APIs also use the hybrid font selection algorithm:

  - [`IDWriteFontCollection2::GetMatchingFonts`](https://docs.microsoft.com/en-us/windows/win32/api/dwrite_3/nf-dwrite_3-idwritefontcollection2-getmatchingfonts)

  - `IDWriteFontFallback1::MapCharacters`

  - `IDWriteTextLayout` if the typographic font family model is enabled by calling 
    `IDWriteTextLayout4::SetFontAxisValues` or `IDWriteTextLayout4::SetAutomaticFontAxes`

# Examples

## Creating an isolated factory

An application calls the `DWriteCoreCreateFactory` function to create a factory object, which is the entry-point
to all other DirectWrite APIs. An application can specify the new `DWRITE_FACTORY_TYPE_ISOLATED2` enum value if it
wants to minimize interaction between DirectWriteCore and the host system. Specifically, the resulting factory only
caches data in-process. It neither reads from nor writes to a cross-process cache (e.g., a font cache process) or
persistent cache (i.e., a file). In addition, the resulting factory's sysetem font collection only includes
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
and `IDWriteFontSet4::GetDerivedFontAxisValues` methods.

The `IDWriteFontSet4::GetMatchingFonts` method returns a list of fonts in priority oder that match the
specified family name and axis values. The following `MatchAxisValues` function outputs the parameters 
to `GetMatchingFonts` followed by a string representation of the first matching font face reference.

```c++
#include <dwrite_core.h>
#include <wil/com.h>
#include <iostream>
#include <string>
#include <vector>

// Forward declarations of overloaded output operators used by MatchAxisValues.
std::wostream& operator<<(std::wostream& out, DWRITE_FONT_AXIS_VALUE axisValue);
std::wostream& operator<<(std::wostream& out, IDWriteFontFile& fileReference);
std::wostream& operator<<(std::wostream& out, IDWriteFontFaceReference1& faceReference);

//
// Outputs the first matching font for the given name and axis values
// using IDWriteFontSet4::GetMatchingFonts.
//
void MatchAxisValues(
    IDWriteFontSet4* fontSet,
    _In_z_ WCHAR const* familyName,
    std::vector<DWRITE_FONT_AXIS_VALUE> const& axisValues
    )
{
    // Write the input parameters.
    std::wcout << L"GetMatchingFonts(\"" << familyName << L"\", {";
    for (DWRITE_FONT_AXIS_VALUE axisValue : axisValues)
    {
        std::wcout << L' ' << axisValue;
    }
    std::wcout << L" }, ...)\n";

    // Test GetMatchingFonts with and without simulations allowed.
    for (bool allowSimulations : { true, false })
    {
        std::wcout << (allowSimulations ?
            L" - allow simulations => " :
            L" - no simulations    => ");

        // Get the matching fonts for the specified family name and axis values.
        wil::com_ptr<IDWriteFontSet4> matchingFonts;
        THROW_IF_FAILED(fontSet->GetMatchingFonts(
            familyName,
            axisValues.data(),
            static_cast<UINT32>(axisValues.size()),
            allowSimulations,
            &matchingFonts
        ));

        // Output the first matching font face reference.
        if (matchingFonts->GetFontCount() != 0)
        {
            wil::com_ptr<IDWriteFontFaceReference1> faceReference;
            THROW_IF_FAILED(matchingFonts->GetFontFaceReference(0, &faceReference));
            std::wcout << *faceReference;
        }

        std::wcout << L'\n';
    }

    std::wcout << L'\n';
}

```

An application might have weight, stretch, and style parameters instead of (or in addition to) axis values.
For example, the application might need to work with documents that reference fonts using RBIZ or
weight-stretch-style parameters. Even if the application adds support for specifying arbitrary axis
values, it might need to support the older parameters as well. To do so, the application can call the
`IDWriteFontSet4::GetDerivedFontAxisValues` before calling `IDWriteFontSet4::GetMatchingFonts`.

The following `MatchFont` function takes font size, weight, stretch, and style parameters in addition
to axis values. It forwards these parameters to `IDWriteFontSet4::GetDerivedAxisValues` method to compute
derived axis values. It then combines the input axis values with the derived axis values, and passes them
to the above `MatchAxisValues` function.

```c++
//
// Outputs the first matching font given both weight-stretch-style parameters
// and axis values. Calls IDWriteFontSet4::GetDerivedFontAxisValues to map the
// font size, weight, stretch, and style to axis values.
//
void MatchFont(
    IDWriteFactory7* factory,
    _In_z_ WCHAR const* familyName,
    float fontSize,
    DWRITE_FONT_WEIGHT fontWeight = DWRITE_FONT_WEIGHT_NORMAL,
    DWRITE_FONT_STRETCH fontStretch = DWRITE_FONT_STRETCH_NORMAL,
    DWRITE_FONT_STYLE fontStyle = DWRITE_FONT_STYLE_NORMAL,
    std::vector<DWRITE_FONT_AXIS_VALUE> axisValues = {}
    )
{
    wil::com_ptr<IDWriteFontSet2> fontSet2;
    THROW_IF_FAILED(factory->GetSystemFontSet(/*includeDownloadableFonts*/ false, &fontSet2));

    wil::com_ptr<IDWriteFontSet4> fontSet;
    THROW_IF_FAILED(fontSet2->QueryInterface(&fontSet));

    // Get derived axis value from the weight, stretch, style, and font size.
    // Any axes in the input vector are excluded from the output.
    DWRITE_FONT_AXIS_VALUE derivedAxisValues[DWRITE_STANDARD_FONT_AXIS_COUNT];
    UINT32 derivedAxisCount = fontSet->GetDerivedFontAxisValues(
        axisValues.data(),
        static_cast<UINT32>(axisValues.size()),
        fontWeight,
        fontStretch,
        fontStyle,
        fontSize,
        derivedAxisValues
        );

    // Append the derived axis values to the vector.
    axisValues.insert(
        axisValues.end(),
        derivedAxisValues, 
        derivedAxisValues + derivedAxisCount
        );

    // Pass the combined axis values to the overload of WriteMatchingFont that
    // just takes axis values.
    MatchAxisValues(fontSet.get(), familyName, axisValues);
}
```

The following function demonstrates the results of calling the above `MatchFont` function
with some example inputs:

```c++
// Outputs the results of some representative font selection cases.
void TestFontSelection(IDWriteFactory7* factory)
{
    // Output:
    //     GetMatchingFonts("Arial", { wght:900 wdth:100 ital:0 slnt:0 opsz:12 }, ...)
    //      - allow simulations => ariblk.ttf wght:900 wdth:100 ital:0 slnt:0
    //      - no simulations    => ariblk.ttf wght:900 wdth:100 ital:0 slnt:0
    // Notes:
    //   *  GetDerivedAxisValue converts font size in DIPs to opsz axis value in points.
    //   *  The resulting fonts in this case have no opsz axis.
    MatchFont(factory, L"Arial", 16.0f, DWRITE_FONT_WEIGHT_BLACK);

    // Output:
    //     GetMatchingFonts("Arial Black", { wght:400 wdth:100 ital:0 slnt:0 opsz:12 }, ...)
    //      - allow simulations => ariblk.ttf wght:900 wdth:100 ital:0 slnt:0
    //      - no simulations    => ariblk.ttf wght:900 wdth:100 ital:0 slnt:0
    // Notes:
    //   *  "Arial Black" matches the RBIZ family name of ariblk.ttf.
    //   *  Weight 400 was requested but the matching font (by name) has weight 900.
    MatchFont(factory, L"Arial Black", 16.0f);

    // Output:
    //     GetMatchingFonts("Arial", { wght:700 wdth:100 ital:0 slnt:0 opsz:12 }, ...)
    //      - allow simulations => arialbd.ttf wght:700 wdth:100 ital:0 slnt:0
    //      - no simulations    => arialbd.ttf wght:700 wdth:100 ital:0 slnt:0
    MatchFont(factory, L"Arial", 16.0f, DWRITE_FONT_WEIGHT_BOLD);

    // Output:
    //     GetMatchingFonts("Arial Bold", { wght:400 wdth:100 ital:0 slnt:0 opsz:12 }, ...)
    //      - allow simulations => arialbd.ttf wght:700 wdth:100 ital:0 slnt:0
    //      - no simulations    => arialbd.ttf wght:700 wdth:100 ital:0 slnt:0
    // Notes:
    //  *  "Arial Bold" matches the full name of arialbd.ttf.
    //  *  Weight 400 was requested but the matching font (by name) has weight 700.
    MatchFont(factory, L"Arial Bold", 16.0f);

    // Output:
    //     GetMatchingFonts("Centaur", { wght:700 wdth:100 ital:0 slnt:0 }, ...)
    //      - allow simulations => CENTAUR.TTF wght:400 wdth:100 ital:0 slnt:0 BOLDSIM
    //      - no simulations    => CENTAUR.TTF wght:400 wdth:100 ital:0 slnt:0
    // Notes:
    //  *  The "Centaur" family has no bold weight, so simulation is applied if allowed.
    //  *  The wght axis value of the result is the natural weight of the font, but
    //     IDWriteFontFace::GetWeight() would return bold.
    MatchFont(factory, L"Centaur", /*ignore size*/ 0.0f, DWRITE_FONT_WEIGHT_BOLD);

    // Output on Windows 10 with static Sitka fonts:
    //     GetMatchingFonts("Sitka", { wght:400 wdth:100 ital:0 slnt:0 opsz:12 }, ...)
    //      - allow simulations => Sitka.ttc#1 opsz:12 wght:400 ital:0 wdth:100 slnt:0
    //      - no simulations    => Sitka.ttc#1 opsz:12 wght:400 ital:0 wdth:100 slnt:0
    // Output on Windows 11 with variable Sitka fonts:
    //     GetMatchingFonts("Sitka", { wght:400 wdth:100 ital:0 slnt:0 opsz:12 }, ...)
    //      - allow simulations => SitkaVF.ttf opsz:12 wght:400 ital:0 wdth:100 slnt:0
    //      - no simulations    => SitkaVF.ttf opsz:12 wght:400 ital:0 wdth:100 slnt:0
    MatchFont(factory, L"Sitka", 16.0f);

    // Output on Windows 10 with static Sitka fonts:
    //     GetMatchingFonts("Sitka", { wght:400 wdth:100 ital:0 slnt:0 opsz:24 }, ...)
    //      - allow simulations => Sitka.ttc#5 opsz:24 wght:400 ital:0 wdth:100 slnt:0
    //      - no simulations    => Sitka.ttc#5 opsz:24 wght:400 ital:0 wdth:100 slnt:0
    // Output on Windows 11 with variable Sitka fonts:
    //     GetMatchingFonts("Sitka", { wght:400 wdth:100 ital:0 slnt:0 opsz:24 }, ...)
    //      - allow simulations => SitkaVF.ttf opsz:24 wght:400 ital:0 wdth:100 slnt:0
    //      - no simulations    => SitkaVF.ttf opsz:24 wght:400 ital:0 wdth:100 slnt:0
    // Notes:
    //   *  "Sitka" matches a typographic family name.
    //   *  The resulting "opsz" value is clamped to the axis range of the matching font.
    //   *  The "opsz" axis range for the nearest static font ("Sitka Display") is 23.5-27.5.
    //   *  The "opsz" axis range for the variable Sitka font is 6-27.5 pt.
    MatchFont(factory, L"Sitka", 32.0f);

    // Output on Windows 10 with static Sitka fonts:
    //     GetMatchingFonts("Sitka Text", { wght:400 wdth:100 ital:0 slnt:0 opsz:24 }, ...)
    //      - allow simulations => Sitka.ttc#1 opsz:13.5 wght:400 ital:0 wdth:100 slnt:0
    //      - no simulations    => Sitka.ttc#1 opsz:13.5 wght:400 ital:0 wdth:100 slnt:0
    // Output on Windows 11 with variable Sitka fonts:
    //     GetMatchingFonts("Sitka Text", { wght:400 wdth:100 ital:0 slnt:0 opsz:24 }, ...)
    //      - allow simulations => SitkaVF.ttf opsz:24 wght:400 ital:0 wdth:100 slnt:0
    //      - no simulations    => SitkaVF.ttf opsz:24 wght:400 ital:0 wdth:100 slnt:0
    // Notes:
    //   *  "Sitka Text" matches a weight-stretch-style family name.
    //   *  The resulting "opsz" value is clamped to the axis range of the matching font.
    //   *  The "opsz" axis range for the static "Sitka Text" font is 9.70-13.5 pt.
    //   *  The "opsz" axis range for the variable Sitka font is 6-27.5 pt.
    MatchFont(factory, L"Sitka Text", 32.0f);

    // Output on Windows 10 with static Sitka fonts:
    //     GetMatchingFonts("Sitka", { wght:700 opsz:72 wdth:100 ital:0 slnt:0 }, ...)
    //      - allow simulations => SitkaB.ttc#5 opsz:72 wght:700 ital:0 wdth:100 slnt:0
    //      - no simulations    => SitkaB.ttc#5 opsz:72 wght:700 ital:0 wdth:100 slnt:0
    // Output on Windows 11 with variable Sitka fonts:
    //     GetMatchingFonts("Sitka", { wght:700 opsz:72 wdth:100 ital:0 slnt:0 }, ...)
    //      - allow simulations => SitkaVF.ttf opsz:27.5 wght:700 ital:0 wdth:100 slnt:0
    //      - no simulations    => SitkaVF.ttf opsz:27.5 wght:700 ital:0 wdth:100 slnt:0
    // Notes:
    //   *  Explicit "opsz" and "wght" axes take precedence over fontSize and fontWeight.
    MatchFont(
        factory, L"Sitka",
        16.0f, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_FONT_STYLE_NORMAL,
        { { DWRITE_FONT_AXIS_TAG_WEIGHT, 700.0f }, { DWRITE_FONT_AXIS_TAG_OPTICAL_SIZE, 72.0f } }
    );
}
```

Following are the implementations of the overloaded operators declared above. These are used
by `MatchAxisValues` to write the input axis values and the resulting font face references:

```c++
// Output a file name given a font file reference.
std::wostream& operator<<(std::wostream& out, IDWriteFontFile& fileReference)
{
    wil::com_ptr<IDWriteFontFileLoader> loader;
    THROW_IF_FAILED(fileReference.GetLoader(&loader));

    wil::com_ptr<IDWriteLocalFontFileLoader> localLoader;
    if (SUCCEEDED(loader->QueryInterface(&localLoader)))
    {
        const void* fileKey;
        UINT32 fileKeySize;
        THROW_IF_FAILED(fileReference.GetReferenceKey(&fileKey, &fileKeySize));

        WCHAR filePath[MAX_PATH];
        THROW_IF_FAILED(localLoader->GetFilePathFromKey(fileKey, fileKeySize, filePath, MAX_PATH));

        WCHAR* fileName = wcsrchr(filePath, L'\\');
        fileName = (fileName != nullptr) ? fileName + 1 : filePath;

        out << fileName;
    }
    return out;
}

// Output a font axis value.
std::wostream& operator<<(std::wostream& out, DWRITE_FONT_AXIS_VALUE axisValue)
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

// Output a font face reference.
std::wostream& operator<<(std::wostream& out, IDWriteFontFaceReference1& faceReference)
{
    // Output the font file name.
    wil::com_ptr<IDWriteFontFile> fileReference;
    THROW_IF_FAILED(faceReference.GetFontFile(&fileReference));
    std::wcout << *fileReference;

    // Output the face index if nonzero.
    UINT32 const faceIndex = faceReference.GetFontFaceIndex();
    if (faceIndex != 0)
    {
        out << L'#' << faceIndex;
    }

    // Output the axis values.
    UINT32 const axisCount = faceReference.GetFontAxisValueCount();
    std::vector<DWRITE_FONT_AXIS_VALUE> axisValues(axisCount);
    THROW_IF_FAILED(faceReference.GetFontAxisValues(axisValues.data(), axisCount));
    for (DWRITE_FONT_AXIS_VALUE axisValue : axisValues)
    {
        out << L' ' << axisValue;
    }

    // Output the simulations.
    DWRITE_FONT_SIMULATIONS simulations = faceReference.GetSimulations();
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

To round out the sample, following are command-line parsing functions and the main function:

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
"\n";

struct CmdArgs
{
    std::wstring familyName;
    float fontSize = 0.0f;
    DWRITE_FONT_WEIGHT fontWeight = DWRITE_FONT_WEIGHT_NORMAL;
    DWRITE_FONT_STRETCH fontStretch = DWRITE_FONT_STRETCH_NORMAL;
    DWRITE_FONT_STYLE fontStyle = DWRITE_FONT_STYLE_NORMAL;
    std::vector<DWRITE_FONT_AXIS_VALUE> axisValues;
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
            if (!ParseFloat(argv[argIndex], &cmd.fontSize))
                return false;
        }
        else if (!wcscmp(arg, L"-bold"))
        {
            cmd.fontWeight = DWRITE_FONT_WEIGHT_BOLD;
        }
        else if (!wcscmp(arg, L"-weight"))
        {
            if (++argIndex == argc)
                return false;
            if (!ParseEnum(argv[argIndex], 100, 900, &cmd.fontWeight))
                return false;
        }
        else if (!wcscmp(arg, L"-italic"))
        {
            cmd.fontStyle = DWRITE_FONT_STYLE_ITALIC;
        }
        else if (!wcscmp(arg, L"-oblique"))
        {
            cmd.fontStyle = DWRITE_FONT_STYLE_OBLIQUE;
        }
        else if (!wcscmp(arg, L"-stretch"))
        {
            if (++argIndex == argc)
                return false;
            if (!ParseEnum(argv[argIndex], 1, 9, &cmd.fontStretch))
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
        else
        {
            return false;
        }
    }

    return true;
}

int wmain(int argc, WCHAR** argv)
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
            cmd.fontSize,
            cmd.fontWeight,
            cmd.fontStretch,
            cmd.fontStyle,
            std::move(cmd.axisValues)
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
    /// <param name="outputAxisValues">Pointer to an output array to which derived axis values are written.
    /// The size of this array must be at least DWRITE_STANDARD_FONT_AXIS_COUNT (5). The return value is 
    /// the actual number of axis values written to this array.</param>
    /// <returns>Returns the actual number of derived axis values written to the output array.</returns>
    STDMETHOD_(UINT32, GetDerivedFontAxisValues)(
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
    /// family name, or GDI (RBIZ) family name.</param>
    /// <param name="fontAxisValues">List of font axis values.</param>
    /// <param name="fontAxisValueCount">Number of font axis values.</param>
    /// <param name="allowSimulations">Specify TRUE to automatically apply algorithmic emboldening or slant to
    /// matching fonts if necessary to match the specified axis values.</param>
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
        BOOL allowSimulations,
        _COM_Outptr_ IDWriteFontSet4** matchingFonts
        ) PURE;
};
```
