# Windows App SDK - Calling all Windows developers!

*Previously known as Project Reunion*.

| Delight users with modern UI | Access new platform features | Backwards compatible |
|:--:|:--:|:--:|
| <img src="https://docs.microsoft.com/media/illustrations/biztalk-get-started-get-started.svg" width=250 alt="Modern navigation"/><br>Powerful WinUI 3 UI | <img src="https://docs.microsoft.com/media/illustrations/biztalk-get-started-scenarios.svg" width=250 alt="Platform logo"/><br>Localization + power status + more<br> | <img src="https://docs.microsoft.com/media/illustrations/biztalk-host-integration-install-configure.svg" width=250 alt="Down-level logo"/><br>Down to Windows 10 1809 |

...and more, **without having to rewrite your app!**

* Use your current installer *(no requirement to use MSIX, but there are [reliability/security benefits to using MSIX](https://docs.microsoft.com/windows/msix/overview#key-features)!)*
* Additive platform APIs *(only add what you need, leave the rest of your app as-is)*
* Works with Win32, WPF, WinForms, and more apps

Plus, **create beautiful, modern apps for Windows 11 that are backwards compatible** to Windows 10 October 2018 Update (build 17763 / version 1809)!


### Use it now!

1.1 is [available today](https://docs.microsoft.com/windows/apps/windows-app-sdk/) and includes push notifications, multi-window support, elevation support and much more!

### Roadmap

Here's a snippet of what's currently available and what we intend to deliver in 2022 *(times/features/releases are tentative and subject to change)*:

App type |          1.0     |  1.1  |
--        |  ------------------------ |   -----  |
Desktop apps<br>(WinUI 3, WPF, etc) |  ✅ [WinUI 3](https://github.com/microsoft/microsoft-ui-xaml/blob/master/docs/roadmap.md#winui-3)\*\*<br>✅ [Text rendering](https://docs.microsoft.com/windows/apps/windows-app-sdk/dwritecore)<br>✅ [Resource management](https://docs.microsoft.com/windows/apps/windows-app-sdk/mrtcore/mrtcore-overview)<br>✅ [App lifecycle](https://docs.microsoft.com/windows/apps/develop/app-lifecycle-and-system-services)<br>✅ [Windowing](https://docs.microsoft.com/windows/apps/windows-app-sdk/windowing/windowing-overview)<br>🔁 [Push Notifications](https://docs.microsoft.com/en-us/windows/apps/windows-app-sdk/notifications/push-notifications/)  |  ✅ [WinUI 3](https://github.com/microsoft/microsoft-ui-xaml/blob/master/docs/roadmap.md#winui-3)\*\*<br>✅ [Text rendering](https://docs.microsoft.com/windows/apps/windows-app-sdk/dwritecore)<br>✅ [Resource management](https://docs.microsoft.com/windows/apps/windows-app-sdk/mrtcore/mrtcore-overview)<br>✅ [App lifecycle](https://docs.microsoft.com/windows/apps/develop/app-lifecycle-and-system-services)<br>✅ [Windowing](https://docs.microsoft.com/windows/apps/windows-app-sdk/windowing/windowing-overview)<br>✅ [Push Notifications](https://docs.microsoft.com/en-us/windows/apps/windows-app-sdk/notifications/push-notifications/)  <br>✅ [Multiple windows](https://portal.productboard.com/winappsdk/1-windows-app-sdk/c/35-multiple-window-support)<br> ✅ [Elevation support](https://portal.productboard.com/winappsdk/1-windows-app-sdk/c/37-elevated-admin-support)<br>  ✅ [Local toast notifications](https://portal.productboard.com/winappsdk/1-windows-app-sdk/c/15-local-toast-notifications)<br> ✅ [Environmental variables API](https://portal.productboard.com/winappsdk/1-windows-app-sdk/c/47-environment-variables-api)<br> ✅ [Restart API](https://portal.productboard.com/winappsdk/1-windows-app-sdk/c/54-restart-for-all-desktop-apps)<br> ✅ [Self-contained deployment](https://portal.productboard.com/winappsdk/1-windows-app-sdk/c/42-self-contained-xcopy-deployment-support)<br> |

✅ Supported | 🔁 Experimental

*\*\* - WinUI 3 in 1.0 and 1.1 is only supported for use by full WinUI 3 apps. You'll be able to use WinUI 3 in WPF/WinForms/other apps in a future release via XAML Islands.*

To see our full roadmap and features that are under consideration (or to submit feature requests), [visit our productboard portal](https://portal.productboard.com/winappsdk/1-windows-app-sdk).



### Version support

The Windows App SDK aims to work on supported versions of Windows.
Right now we support down to build 17763 (version 1809/October 2018 Update) of Windows 10.
Wherever possible, we'll use techniques like '_polyfills_'
and custom implementations to do the
heavy lifting for you and make sure your app works across Windows versions and devices.
In the future, there may be a couple APIs that are dependent on new OS features
(like new Action Center functionality),
however we will do our best to ensure
this is the exception and not the norm, and provide reasonable fallbacks when possible.


### Helpful links

* [More details about the Windows App SDK](https://github.com/microsoft/WindowsAppSDK/blob/master/docs/README.md) -
More on what the project is and how we're approaching the work.
* [Video on Windows App SDK](https://techcommunity.microsoft.com/t5/video-hub/enterprise-development-futures-project-reunion/m-p/2177278) - Learn about the Windows App SDK in a 22 minute video!
* [Roadmap + vote on features](https://portal.productboard.com/winappsdk/1-windows-app-sdk) - See what we're planning and influence what we build!
* [Contributor guide](docs/contributor-guide.md) - How to contribute to the Windows App SDK.
* [FAQ](docs/faq.md) - Frequently asked questions about the Windows App SDK.
* [Developer docs](https://aka.ms/windowsappsdkdocs) - Microsoft documentation covering a wide range of Windows App SDK topics.
* [Samples](https://github.com/microsoft/WindowsAppSDK-Samples) - Discover Windows App SDK samples to assist in learning how to use the latest features!

### Contributing

[![Bugs](https://img.shields.io/github/issues/microsoft/windowsappsdk/bug)](https://github.com/microsoft/WindowsAppSDK/issues?q=is%3Aissue+is%3Aopen+label%3Abug)

_We want to hear from you!_

File a [new issue!](https://github.com/microsoft/WindowsAppSDK/issues/new/choose) Tell us what problem you're
trying to solve, how you've tried to solve it so far, and what would be the ideal solution for your app. Bonus
points if there's a gist or existing repo we can look at with you.


1. **[Ask a question](https://github.com/microsoft/WindowsAppSDK/discussions/categories/q-a)**<br>
    Also, have a look at our [frequently asked questions](docs/faq.md) page which we will update periodically.

2. **[Start a discussion](https://github.com/microsoft/WindowsAppSDK/discussions)**<br>
   Discussions can be about any topics or ideas related to the Windows App SDK. For example,
   you might start a Discussion issue to see if others are interested in a cool new idea
   you've been thinking about that isn't quite ready to be filed as a more formal Feature Proposal.

3. **[Vote on or suggest features](https://portal.productboard.com/winappsdk/1-windows-app-sdk)**<br>
   What components or features do you want to see in the Windows App SDK? Tell us on our [productboard portal](https://portal.productboard.com/winappsdk/1-windows-app-sdk)!

**Over time, we will add Windows App SDK code into this repo and provide code contribution/developer guidelines.**

Read more about the [contribution guide here](docs/contributor-guide.md).

## Data collection

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

## Legal notices

Microsoft and any contributors grant you a license to the Microsoft documentation and other content
in this repository under the [Creative Commons Attribution 4.0 International Public License](https://creativecommons.org/licenses/by/4.0/legalcode),
see the [LICENSE](LICENSE) file, and grant you a license to any code in the repository under the [MIT License](https://opensource.org/licenses/MIT), see the
[LICENSE-CODE](LICENSE-CODE) file.

Microsoft, Windows, Microsoft Azure and/or other Microsoft products and services referenced in the documentation
may be either trademarks or registered trademarks of Microsoft in the United States and/or other countries.
The licenses for this project do not grant you rights to use any Microsoft names, logos, or trademarks.
Microsoft's general trademark guidelines can be found at http://go.microsoft.com/fwlink/?LinkID=254653.

Privacy information can be found at https://privacy.microsoft.com/

Microsoft and any contributors reserve all other rights, whether under their respective copyrights, patents,
or trademarks, whether by implication, estoppel or otherwise.
