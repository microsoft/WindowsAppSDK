# Project Reunion

[![Feature Proposals](https://img.shields.io/github/issues/microsoft/projectreunion/feature%20proposal)](https://github.com/microsoft/ProjectReunion/issues?q=is%3Aissue+is%3Aopen+label%3A%22feature+proposal%22)
[![Bugs](https://img.shields.io/github/issues/microsoft/projectreunion/bug)](https://github.com/microsoft/ProjectReunion/issues?q=is%3Aissue+is%3Aopen+label%3Abug)


### What is Project Reunion?
Project Reunion is our vision for unifying and evolving the Windows developer platform to make it easier
to build great apps that work across all the Windows 10 versions and devices people use.

Project Reunion makes it easier to build a great Windows app by providing a unified platform for new 
and existing Win32 and UWP apps. It will unify access to existing Win32 and UWP APIs and make them 
available decoupled from the OS, via tools like NuGet. 

Project Reunion will help you update and modernize your existing apps with the latest functionality, 
whether they're C++, .NET (including WPF, Windows Forms, and UWP) or React Native. As we decouple 
existing APIs and add new APIs, we are also doing the work to polyfill, as needed, so the APIs work 
down-level across supported versions of Windows. 


### How can I use Project Reunion?
Check out our roadmap and what's supported with Project Reunion **[here](docs/roadmap.md)**!

We have already started with APIs like 
**[WinUI 3](https://github.com/microsoft/microsoft-ui-xaml)**,
**[WebView2](https://docs.microsoft.com/en-us/microsoft-edge/webview2/)** and 
**[MSIX](https://docs.microsoft.com/en-us/windows/msix/overview)**
**([MSIX-Core](https://github.com/microsoft/msix-packaging))** 
which you can start using today!

WinUI 3 Preview 1 is one of the first components in the Project Reunion journey: it’s the modern 
native UI framework for Windows, now available to all Windows app developers across both UWP and 
Desktop apps. Using WinUI you will be able to create new apps with modern UI that adapts and scales 
across devices, or incrementally modernize the UI of existing desktop apps including C++, WPF and 
WinForms.

[Help us figure out what Project Reunion becomes to support your application.](https://github.com/microsoft/ProjectReunion/issues/new/choose)

![Project Reunion](docs/images/projectreunion.gif)

### Project Reunion Principles

**Compatible**

Project Reunion works in all your apps - Win32, Packaged, and UWP - and across many versions of Windows.

**Modern**

Project Reunion supports your app's use of modern software libraries for UI, AI, ML, packaging, frameworks, 
and libraries. Language projections for C++, Rust, C#, and JavaScript expand the benefits to all your 
apps.  Cloud-backed apps, streaming, and edge-compute apps are all great places to use Project Reunion's 
capabilities.

**Agile**

Project Reunion ships out of band with OS releases, with regular previews. You get to incrementally 
adopt Project Reunion components for your existing apps and middleware libraries using NuGet.

**Open**

We're committing to engineering Project Reunion in the open on GitHub, so you have a more direct 
say in how the platform evolves and can even help out.

## Contributing

_We want to hear from you!_

File a [new issue!](https://github.com/microsoft/ProjectReunion/issues/new/choose) Tell us what problem you're
trying to solve, how you've tried to solve it so far, and what would be the ideal solution for your app.  Bonus
points if there's a gist or existing repo we can look at with you.


1. **[Ask a question](https://github.com/microsoft/ProjectReunion/issues/new?assignees=&labels=question&template=question.md&title=Question%3A+%5Byour+question+here%5D)**<br>
    Also, have a look at our [frequently asked questions](docs/faq.md) page which we will update periodically.

2. **[Start a discussion](https://github.com/microsoft/ProjectReunion/discussions)**<br>
   Discussions can be about any topics or ideas related to Project Reunion. For example,
   you might start a Discussion issue to see if others are interested in a cool new idea
   you've been thinking about that isn't quite ready to be filed as a more formal Feature Proposal.

3. **[Make a feature proposal](https://github.com/microsoft/ProjectReunion/issues/new?assignees=&labels=feature+proposal&template=feature-proposal.md&title=)**<br>
   What components do you want to see in Project Reunion? For example you can propose a new API on an existing type, or an idea for a new API.
   It's fine if you don't have all the details: you can start with a summary and rationale.

**Over time, we will add Project Reunion code and samples into this repo and provide code contribution/developer guidelines.**

Read more about the [contribution guide here](docs/contributor-guide.md).

### Version Support

Project Reunion aims to work on supported versions of Windows. We'll use techniques like '_polyfills_' 
and custom implementations to do the heavy lifting for you and make sure your app works across Windows
versions and devices.

### Documentation

* [More details about Project Reunion](https://github.com/microsoft/ProjectReunion/blob/master/docs/README.md) - 
More on what the project is and how we're approaching the work.
* [Roadmap](docs/roadmap.md) - Where we're going. We're following this roadmap that 
gets us to building a first version of Project Reunion exploring some basic common features.
  [You can help by filing issues for features you'd like to see](https://github.com/microsoft/ProjectReunion/issues/new/choose)!
* [Contributor guide](docs/contributor-guide.md) - How to contribute to Project Reunion.
* [FAQ](docs/faq.md) - Frequently asked questions about Project Reunion.

## Data Collection

The software may collect information about you and your use of the software and send it
to Microsoft. Microsoft may use this information to provide services and improve our
products and services. You may turn off the telemetry as described in the repository.
There are also some features in the software that may enable you and Microsoft to collect
data from users of your applications. If you use these features, you must comply with
applicable law, including providing appropriate notices to users of your applications
together with a copy of Microsoft's privacy statement. Our privacy statement is located
at https://go.microsoft.com/fwlink/?LinkID=824704. You can learn more about data collection
and use in the help documentation and our privacy statement. Your use of the software
operates as your consent to these practices.

## Legal Notices

Microsoft and any contributors grant you a license to the Microsoft documentation and other content
in this repository under the [Creative Commons Attribution 4.0 International Public License](https://creativecommons.org/licenses/by/4.0/legalcode),
see the [LICENSE](LICENSE) file, and grant you a license to any code in the repository under the [MIT License](https://opensource.org/licenses/MIT), see the
[LICENSE-CODE](LICENSE-CODE) file.

Microsoft, Windows, Microsoft Azure and/or other Microsoft products and services referenced in the documentation
may be either trademarks or registered trademarks of Microsoft in the United States and/or other countries.
The licenses for this project do not grant you rights to use any Microsoft names, logos, or trademarks.
Microsoft's general trademark guidelines can be found at http://go.microsoft.com/fwlink/?LinkID=254653.

Privacy information can be found at https://privacy.microsoft.com/en-us/

Microsoft and any contributors reserve all other rights, whether under their respective copyrights, patents,
or trademarks, whether by implication, estoppel or otherwise.
