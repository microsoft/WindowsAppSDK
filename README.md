# Project Reunion - Calling all Windows desktop apps!

| Delight users with modern UI | Access new platform features | Down-level support | 
|:--:|:--:|:--:|
| <img src="https://docs.microsoft.com/en-us/media/illustrations/biztalk-get-started-get-started.svg" width=250 alt="Modern navigation"/></br>Powerful WinUI 3 UI | <img src="https://docs.microsoft.com/en-us/media/illustrations/biztalk-get-started-scenarios.svg" width=250 alt="Platform logo"/></br>Localization + power status + more</br> | <img src="https://docs.microsoft.com/en-us/media/illustrations/biztalk-host-integration-install-configure.svg" width=250 alt="Down-level logo"/></br>Back to Windows 10 1809 |

...and more, **without having to rewrite your app!**

* Use your current installer *(no requirement to be MSIX/packaged, but there are [reliability/security benefits to using MSIX](https://docs.microsoft.com/windows/msix/overview#key-features)!)*
* 100% additive *(only add what you need, leave the rest of your app as-is)*
* Works with Win32, WPF, WinForms, and UWP apps

Plus, **it works down-level** to build 17763 (version 1809/October 2018 Update) of Windows 10!


### Try it now!
[Packaged MSIX desktop apps](https://docs.microsoft.com/windows/msix/overview) can try the preview of the 0.5 release now! (link to details on how to try it)

Some caveats about 0.5...

* Requires using MSIX (1.0 won't require MSIX)
* Only includes WinUI / DWriteCore / MRT Core right now
* WinUI 3 cannot yet be intermixed with other UI frameworks (XAML Islands will enable this in the future).  To use WinUI 3, either start with a new app, or you can replace your existing app's UI completely with WinUI 3


### Roadmap

Here's a snippet of what we intend to deliver in the year of 2021 *(all times/features/releases are tentative and subject to change)*: 

App type |      Reunion 0.5 (Q1 2021)      |         Reunion 0.8 (Q2 2021)    |       Reunion 1.0 (Q4 2021)     | 
-- | ------------------------------- | --------------------------------- | ------------------------------- |
[Packaged MSIX](https://docs.microsoft.com/windows/msix/overview) desktop apps</br>(WPF, Win32, WinForms, console) |                ✅ WinUI</br>✅ DWriteCore</br>✅ MRT Core  |                    ✅ WinUI</br>✅ DWriteCore</br>✅ MRT Core</br>🔄 AppLifecycle  | ✅ WinUI</br>✅ DWriteCore</br>✅ MRT Core</br>✅ AppLifecycle  | 
Unpackaged desktop apps</br>(WPF, Win32, WinForms, console) | ❌ Not supported  |                    🔄 AppLifecycle</br>🔄 DWriteCore</br>🔄 MRT Core  |  ✅ WinUI</br>✅ DWriteCore</br>✅ MRT Core</br>✅ AppLifecycle | 

✅ Supported | 🔄 Preview


See our [full roadmap](docs/roadmap.md) for a more detailed roadmap.



### Version Support

Project Reunion aims to work on supported versions of Windows. Right now we support down to build 17763 (version 1809/October 2018 Update) of Windows 10. We'll use techniques like '_polyfills_' 
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


### Contributing

[![Feature Proposals](https://img.shields.io/github/issues/microsoft/projectreunion/feature%20proposal)](https://github.com/microsoft/ProjectReunion/issues?q=is%3Aissue+is%3Aopen+label%3A%22feature+proposal%22)
[![Bugs](https://img.shields.io/github/issues/microsoft/projectreunion/bug)](https://github.com/microsoft/ProjectReunion/issues?q=is%3Aissue+is%3Aopen+label%3Abug)

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
