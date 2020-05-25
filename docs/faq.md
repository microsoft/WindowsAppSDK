# Frequently Asked Questions
We will update this page periodically.

> **Note** - Sometimes where this FAQ says "we will" and "can" and "is", we're stating
> what we _want_ to have happen. As we build out Project Reunion we might change course
> based on feedback from you.

## How do I start using Project Reunion in my app?
If you have a Desktop Win32 or UWP app there are multiple components available now.

These components are available for you to use now and adhere to the 'Project Reunion Family Promise' 
that they have a single API for use in all kinds of applications.

- **[WinUI 3 for XAML](https://github.com/microsoft/microsoft-ui-xaml)** in your Win32 app helps you 
build fluent UX with the ease of XAML. This component is part of the Project Reunion 
Family of functionality, building on the identity + packaging + deployment transparent ideas that
Project Reunion supports for your app as well.
- **[C++/WinRT](https://github.com/microsoft/cppwinrt)**, 
**[RUST/WinRT](https://github.com/microsoft/winrt-rs)**, 
and **[C#/WinRT](https://github.com/microsoft/cswinrt)** 
provide language-native projections of Windows, Project Reunion, 
and your own custom types defined in metadata. Consume APIs from the Windows Kit, produce them for 
use by other supported projections, create your own new language projections.
- **[MSIX](https://docs.microsoft.com/en-us/windows/msix/overview)** and 
**[MSIX-Core](https://github.com/microsoft/msix-packaging)** 
let you package your application for distribution to Windows Desktop machines 
via the store or your own delivery pipeline. MSIX-Core lets you use the reuse parts of the MSIX 
packaging story on older versions of Windows.

  _Coming soon_
- **[Microsoft Edge's WebView2](https://docs.microsoft.com/en-us/microsoft-edge/webview2)**

[Tell us what other components you'd like to see as part of the Project reunion Family](https://github.com/microsoft/ProjectReunion/issues/new/choose)

## Do I need to be packaged to use Project Reunion?
Your app does not need to be packaged to use Project Reunion functionality.

If you are packaged using either a Universal Windows Application package or a Desktop Bridge package, 
referencing the NuGet package is enough to start using Project Reunion right away.

If you have your own installer, we'll have instructions to carry the Project Reunion components with your app 
and how to install them using some common installers.

## How do I contribute?
Use this repo's GitHub Issues to [ask questions, start a discussion or make a feature proposal](https://github.com/microsoft/ProjectReunion/issues/new/choose).

## Is Reunion a new App Model?

No.

Project Reunion is a set of libraries and content you add to your existing app
[within its app model](https://docs.microsoft.com/en-us/windows/apps/desktop/choose-your-platform)
and start coding. Some parts of Project Reunion work _better_ if your app is
[a UWP app](https://docs.microsoft.com/en-us/windows/uwp/get-started/), or
[Desktop Bridge](https://docs.microsoft.com/en-us/windows/apps/desktop/modernize/desktop-to-uwp-extensions),
or [has identity](https://aka.ms/sparsepkgblog).

Your existing app model's activation, deployment, lifecycle, and presentation
will continue to work as you bring in more Project Reunion functionality. The
more functionality you use from Project Reunion the easier it'll be if you
want to _change_ your app model, since the same code will just keep working!

## What Languages and Runtimes are Supported?

Project Reunion's API surface will be [defined in metadata](https://docs.microsoft.com/en-us/uwp/winrt-cref/winmd-files)
similar to WinRT APIs already part of Windows. We'll support projections of that metadata
through projects like C++/WinRT, C#/WinRT, and Rust/WinRT so access to Project Reunion
APIs is familiar to you.

Project Reunion aims to directly target the Windows public API surface and does not
rely on any other frameworks or runtimes, so you can use it with _any_ runtime for
which there's a projection. This means you'll be able to use Project Reunion without
retargeting, other than a reference to the metadata + projection that's right for you.

Practically speaking, any language & runtime that can handle COM objects _can_ support
Project Reunion.  Please file an issue with a specific language or runtime in mind.

## Can my App Mix Win32 and Project Reunion?

Yes.

Project Reunion is additive to your existing application code. If your app relies
on Win32 API constructs you can keep doing so while starting to use more
Project Reunion functionality. Anywhere Project Reunion wraps a lower-level
currency (like, a file `HANDLE` or an `HWND` or an `HKEY`) there'll be a way for
your app to grab it and "call through" Project Reunion to the underlying Windows API
surface.

## Does Project Reunion Replace or Deprecate Win32 APIs?

The Windows Kit will continue to exist for your apps to use. Project Reunion does not
attempt to replicate or replace the breadth of the Windows Public API surface.

Project Reunion will bring new ways to use the existing public API surface, guiding
your app towards modernized constructs and code that can use new technologies on
later OS versions while still working when running on older editions.

## What Kinds of APIs are out of scope?

Project Reunion can't change fundamental Windows behaviors like processes, threads,
memory management, handles, tokens, security boundaries, networking, sockets, shell
windowing behaviors, user identity, etc.  What we can change are behaviors that are
specific to your apps.

We're looking to support:

* Better app lifecycle notifications
* Bridging gaps between packaged & unpackaged, identity and non-identity apps
* Helpers that simplify transition to/from Windowing models
* Resource management for all kinds of apps (think MRT and MUI support)
* Improved access to user data from AppContainer apps

## What's a UWP?

Referenced throughout this repo, the term "UWP" references a
[Universal Windows Platform App](https://docs.microsoft.com/en-us/windows/uwp/get-started/) -
an app running inside an app container, at a lower privilege level, with
package identity, delivered via an MSIX. This app's lifecycle from activation
through termination is controlled by the platform for best power and resource
usage. Its access to the user's resources are gated by a Request model so the
user is in control. Windows and views created by the app are positioned by the
OS shell. Its UX is either drawn using XAML or Composition objects or a
framework that produces XAML or Composition objects.

## I don't see my question here! [Create an issue to ask a question or start a discussion](https://github.com/microsoft/ProjectReunion/issues/new/choose).

