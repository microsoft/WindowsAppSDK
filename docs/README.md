# What Windows App SDK Brings

Windows App SDK functionality comes in three main categories - new APIs, converged APIs,
and API subsets.  Your apps can pick up each different level of functionality **at your
own pace**.

## New APIs

Whenever possible, new Windows functionality will be delivered as part of the Windows App SDK
Family. APIs and functionality delivered as "New" are identity-, packaging-,
and isolation- transparent to your application.  New functionality will share a common
interface for you to use whether your app is MSIX, MSI, setup.exe, Desktop Bridge, or
AppContainer.

![New APIs](images/new-apis-image.png)

Some of the APIs and functionality listed will come over time; they are listed as
examples of the category rather than fully supported on day 1.

These APIs are self-consistent and solve specific application problems or help you build
additional functionality into your application.  Potential categories of APIs here might
be:

* Application data storage and management to keep your data in one place and the user's
system tidy
* Cloud app support for identity and connectivity management to use the power of Azure
* Packaging and system integration so Windows understands what your app is doing
* App-to-app inter-process communication helpers so your apps can work with other app easily
* Privacy-aware resource access APIs for camera, microphone, location, and more

You'll start using these APIs by adding a reference to the Windows App SDK NuGet package
and then adding uses of the APIs in your app code.  Use as much or as little of Windows App SDK
as helps your application.  New Windows App SDK APIs will be available on all
supported versions of Windows and for all apps. Where certain APIs behave differently
(such as due to identity, isolation, or lifecycle differences) your app can detect it
with clear "TheType.IsSupported" checks.

## Converged APIs

Windows App SDK provides API surfaces that bridge the gap between Win32 and UWP/AppContainer
functionality already within the platform.  Authors of shared code (like frameworks) can
use a single method and avoid their own "if (AppContainer) { x } else { y }" checks.
Windows App SDK APIs provide "polyfill" implementations of APIs when necessary so your
app can run on more versions of Windows without additional "is this Windows 10 Creator's
Release?" checks.

![Converged APIs](images/converged-apis-image.png)

Converged API documentation also includes ways to find uses of the "un converged" code
in your project, along with guidance on how to move from common code patterns to the
new Windows App SDK converged APIs.  Examples of converged APIs include:

* Window Content Frame abstraction over Win32 and UWP windowing
* Application lifecycle behaviors like start, logoff, restart manager integration,
restart-for-update
* Startup and Background Task support to reduce your app's power and performance footprint
* Application resource management for strings, images, display resolutions, and locales
* Advanced clipboard access

Once your app adds a reference to the Windows App SDK codebase your app can start migrating
blocks of functionality to using these fully-supported converged APIs.  You can move as
much of your application to Windows App SDK functionality as necessary, keeping your
existing application style and behaviors.  Whenever possible these APIs will be similar
to their existing Windows SDK namespaced APIs, easing the transition to Windows App SDK
for your existing code.  For existing "flat C" Win32 APIs, an equivalent converged API
will be added and then projected to your language and runtime. If you prefer a "flat C"
style - or the APIs you want already have a "flat C" expression - we're working on
building out a projection of those APIs for you.

As your app migrates to Windows App SDK functionality it'll be easier to move between
deployment and isolation technologies. Windows App SDK handles the brokering of resource
access from a low integrity-level (low-IL) or AppContainer process so your app can
reference user resources while respecting user choice & privacy controls.

![Converged APIs](images/converged-apis-image-2.png)

## Subset API Family

Windows App SDK helps you stay within the set of APIs that Windows supports on all
editions and all endpoints.  Like the Windows Kit API partitions, Windows App SDK
defines a subset of supported Windows Platform APIs that work across all versions of
Windows.  If your code targets this subset - and uses Windows App SDK New + Windows App SDK
Converged functionality whenever possible - it'll work everywhere Windows works,
without needing additional support work.

Windows App SDK Subset APIs for your apps also let you start using Windows App SDK's
functionality with minimal changes to your existing code by using an updated and
streamlined set of headers and implementations.  Feature areas supported by the Windows App SDK
Subset include subsets of:

* Windowing, Input, Messaging, GDI, and GUI subsystem functionality
* Filesystem and storage access
* Networking
* Printing
* Process, threading, memory management, basic application services
* DirectX, D3D, DirectML

Migrate your app to the Windows App SDK Subset API set by first removing all references
to Windows Kit headers (windows.h, kernel32.lib, user32.lib, winsock.h, etc) and then
adding references to the core Windows App SDK Subset header and import libraries.
While many existing Windows Kit APIs are part of the Windows App SDK Subset, you may
have some minimal changes to make to your application's code or behavior.  Recompile
& relink your application then ship it with our support packages.

Is this "subset" model interesting for you and your apps? This feature of Windows App SDK
is still in planning for a future release. Let us know by
[filing an issue](https://github.com/microsoft/WindowsAppSDK/issues/new/choose)
with the "**subset**" tag on it and list the APIs and functionality you'd like to see.

# Coming soon

While we think these are interesting for applications, you tell us! Part of working in
the open is that we learn together about the needs of application developers.  Below are
a set of functionality that seems interesting to make available through a Converged or
New model, but you tell us! Some are linked to an issue thread proposing the functionality.
+1 the ones you like, comment on the detailed design & direction, and help us shape where
we're going.

* **Edge/Chromium-based WebView2** brings the ease of authoring your app in HTML+JS once
and reusing it on all platforms.  WebView2's use of Windows App SDK technologies like
WinUI3 as a hosting frame lets you run modern web-based UX on all editions of Windows.

* **Update Scan Integration** help keep your app up to date automatically while running at
the same time as other system maintenance tasks are happening.

* **Access to user resources** even from AppContainer and isolated applications.  Your
AppContainer apps can access powerful Win32 technologies like the clipboard, inter-process
communication, and the Windows Shell Namespace with user consent through brokering.

# Future direction
We aim to grow Windows App SDK to provide a modern, simple, and accessible version of much
of the power of the Windows Application Platform.  Working in the open with our development
community ensures we're doing the right things first to solve problems your apps are facing
on current and future versions of Windows.

Some functionality will be delivered first as Windows App SDK components. As we think about
evolving the platform it's important to make sure new functionality & features are available
to our developer community just as soon as they're ready to go.  Where there's newer
in-platform functionality to use Windows App SDK will help you adopt that as soon as it's
widely available, without you having to retarget or rewrite - the same Windows App SDK API
surface will continue to work.

As your app uses more Windows App SDK functionality it'll be ready for additional targets
such as packaging, identity, AppContainer, and other future Windows Editions. Depending on
Windows App SDK APIs means we take on the work to keep these APIs working as Windows evolves
forward. Staying within the Windows App SDK API surface ensures your app can address the
widest range of Windows editions and releases while using up-to-date functionality.

# How we are doing this

## Extending APIs

Some of what Windows App SDK provides is access to functionality that is inside Windows,
but for which there is no public API.  We're working on the details, but our plan is to
deliver a secondary package of code that provides a public API over those previously unexposed
components.  While those components will be implemented as closed-source they'll come with
a metadata-based publicly callable & supported API surface and be included in the Windows App SDK
framework packages for use by apps.

# What Windows App SDK isn't

Windows App SDK **isn't a new application model** or platform from Windows. There won't be a
"new Windows App SDK App" template for Visual Studio, VSCode, or other development environments.
You'll still have full access to the Windows SDK and associated kits.  Over time the features
that Windows App SDK provides will grow beyond just merging the existing Win32 and UWP models
and provide additional functionality for all apps to use.

Windows App SDK **isn't a new packaging or isolation model** for applications.  There won't
be required changes to your application in order to access Windows App SDK functionality other
than using the new functionality itself. If the APIs you use need identity or packaging these
requirements will be indicated.

Windows App SDK **isn't a new security or privacy model** for applications.  Your app's
existing security, privacy, reliability, and identity stories continue to work with Windows App SDK.
There may be places that Windows App SDK helps your app be more aware of customer
security or privacy concerns.  Windows App SDK helps you use modern security & privacy
functionality that evolves alongside your application's needs.

Windows App SDK **isn't a way to run your app in the cloud**.  Using Windows App SDK technology
will help get your app on modern API families that are cloud ready. Key components like modern
lifecycle and state isolation help get your app ready to run wherever your customers are.
