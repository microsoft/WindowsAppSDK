# WinRT Registration

Windows App SDK provides WinRT types via *manifest-based* solutions:

* WinAppSDK used via MSIX packages declare types in their `appxmanifest.xml`
* WinAppSDK used via Self-Contained declare types in a SxS (aka Fusion) manifest
  (`application.manifest`) that must be compiled into the caller's PE file

## Registration Options

There are 3 ways to resolve a packaged WinRT's activatable class id (ACID):

A. **Via the process' package graph** -- Requires using WinAppSDK/MSIX and the ACID defined in
WinAppSDK's `appxmanifest.xml`

B. **Via RegFreeWinRT** -- Requires the ACID defined in the caller's SxS (Fusion) manifest and the
DLL found via LoadLibrary

C. **Via language projections** -- C#/WinRT and C++/WinRT support the same "we'll resolve it
ourselves" option crawling the filesystem looking for a DLL containing the implementation. Requires
caller uses a language project (C#/WinRT, C++/WinRT, etc), the WinRT runtimeclass implementation is
in a DLL and the DLL's filename matches the ACID's namespace/prefix.

WinAppSDK/MSIX uses option A.

WinAppSDK/Self-Contained uses option B.

# Appendix A - Frequently Asked Questions

## Why use manifested registration?

Windows App SDK uses options A+B (process package graph + RegFReeWinRT) for performance and complexity reasons.

Manifest-free resolution is simple for developers to use but weaker at meeting WinAppSDK's performance and implementation complexity.

Manifest-based registration allows explicit binding of type names to implementations. Windows App SDK's mapping of types to implementation DLLs may change over time, and being explicit ensures the mapping logic is centralized.

## Why not use manifest-free registration?

In the manifest-free option callers use OS mechanisms as well as language projections' own hunting
for a matching file, where the filename is named the same as the runtimeclass' namespace or prefix,
e.g. C#/WinRT and C++/WinRT can find a theoretical connection object with the ACID
`Microsoft.Network.Bluetooth.Connection` by calling...

* LoadLibrary("Microsoft.Network.Bluetooth.Connection.dll")
* LoadLibrary("Microsoft.Network.Bluetooth.dll")
* LoadLibrary("Microsoft.Network.dll")
* LoadLibrary("Microsoft.dll")

until 1st success or none match (i.e. not found).

This behavior in some language projections is sometimes referred to as the 'manifest-free' option.

The downsides are performance, required filenames and non-trivial objects (in both breadth and depth):

* **Performance** - this crawls the filesystem hunting for a matching DLL filename. Though the
  implementations differ filesystem access is orders magnitude slower than the manifested lookups.
* **Required Filenames** - a WinRT object's hosting DLL's filename becomes part of the de facto
  contract; you *can't* put runtime `A.Foo` in just any file. Unlike WinRT (and classic COM) the
  host's filename and location are no longer artifacts of implementation but part of the de facto
  API contracct. In addition, the filename/namespace rule poses challenges in both breadth and depth
  * **Breadth** -- it's not possible to put widgets with ACID `A.Foo` and `B.Foo` in the same DLL,
    even if their implementation would be best implemented in the same host (for a variety of
    reasons). It *is* possible to put `A.X.Foo` and `A.Y.Foo` in the same DLL if-and-only-if it's
    the common root `A.dll`
  * **Depth** -- deep hierarchies are forced to use the common root. For instance, the language
    projection hunt sequence requires
    [Microsoft.UI.Colors](https://docs.microsoft.com/windows/winui/api/microsoft.ui.colors?view=winui-3.0)
    exist in `Microsoft.UI.dll` or `Microsoft.dll`. Likewise,
    [Microsoft.UI.XAML.Controls.Button](https://docs.microsoft.com/windows/winui/api/microsoft.ui.xaml.controls.button?view=winui-3.0)
    could be found in `Microsoft.UI.XAML.Controls.dll`, `Microsoft.UI.XAML.dll`, `Microsoft.UI.dll`
    or `Microsoft.dll`.

    But having both doesn't work TL;DR this would require WinUI (XAML, Composition, Input, more) all
    in the same DLL. That's seriously sub-optimal for both producing (us) and consuming (you).
    WinAppSDK would need to only use namespaces 3+ levels deep.

    At first blush this might seem manageable for smaller feature areas and problem spaces such as
    `Microsoft.Windows.AppLifecycle` or `Microsoft.Windows.ApplicationModel.DynamicDependency`, but
    it would force `Microsoft.WindowsAppRuntime.dll` to explode into many DLLs (8 today. And the
    days are young...). This becomes even more daunting when you consider larger object models like
    WinUI and Composition where moving some types across namespaces would be necessary simply to
    work at all (e.g. see `Colors`). That would impose huge compatibility issues would for any
    migration of existing WinUI2 and System XAML users to WinAppSDK.

The manifest-free solution is convenient for smaller, simpler cases, where the object model and
performance impacts are small. Larger, more complex designs don't fare so well with the
manifest-free option and thus better suited to the manifested options.

### Why prefer MSIX's `appxmanifest.xml` registration?

MSIX's `appxmanifest.xml` is the optimal solution. Not only optimal performance but also the most
convenient and reliable - use WinAppSDK/MSIX and ItJustWorks, because the component author (in this
case, us) did the work needed for the components to be consumed (by developers), and any code
changes impacting the registration come hand-in-hand with the implementation.

Alas, the WinAppSDK/Self-Contained model makes the MSIX solution a non-option. We know the
ACIDs/DLLs layout and can define those relations in metadata (`application.manifest`) it's just a
SxS manifest *developers* (the component consumer) must ultimately provide at runtime with
*WinAppSDK's* information. Distasteful, but workable.

For those who dislike the Use WinAppSDK via MSIX packages. Then no need for RegFreeWinRT thus no problemo :-)

*NOTE:* You don't need to provide a single `application.manifest` at build-time. `mt.exe` is smart
enough to accept multiple manifests as input and smartly merge their content. WinAppSDK's NuGet and
provided templates should provide this behavior. Developers can still define their own
`application.manifest` for their own reasons
([dpiAwareness](https://docs.microsoft.com/windows/win32/sbscs/application-manifests#dpiAwareness),
[msix](https://docs.microsoft.com/windows/win32/sbscs/application-manifests#msix), etc) and even
define other non-WinAppSDK RegFreeWinRT objects, and have the appropriate info all merged into the
final linked binary.

That's why WinAppSDK uses manifested solutions for its WinRT components, and why `appxmanifest.xml`
is the preferred manifested solution. Other libraries may reach different decisions as they face
different tradeoffs.

## The Road Not Taken

Alternative registration options considered

1 Rename all WAS libraries and move the classes to the right spots. Requires WAS code change. Could
be considered a major change (2.0).

This would be hugely invasively *and* doesn't solve all the problems.

2 Change language projections to deal with non-ideal layout. Requires all projections to change.
Involves working with sensitive projection code. Projections could perhaps:

* consume the manifest (oracle)
* rename the libraries, creating a saner layout, adding numbers to "dupes" (e.g. UI.Xaml.1, UI.Xaml.2, ...)
* adjust activation factory search algorithm as needed

This is a projection-specific answer, requires new designs and complicated new machinery, and
doesn't solve all the problems without devolving to #1 but with more work.

These options were discussed at length (in 2021) before deciding to embrace manifested solutions
instead of language projections' manifest-free option. Not all component authors face the same
choices so YMMV but, for WinAppSDK, this was (and continues to be) an intentional decision for good
reasons
