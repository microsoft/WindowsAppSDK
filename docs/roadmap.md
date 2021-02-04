# Roadmap

Project Reunion is a set of libraries, frameworks, components, and tools that you can use in your apps to access powerful Windows platform functionality from all kinds of apps on many versions of Windows.

The roadmap for Project Reunion supports the primary goals of breaking down the barriers between Win32 and UWP and making the Windows developer platform more agile, compatible, modern and open.

For a general overview, see the [readme](https://github.com/microsoft/ProjectReunion/tree/master/docs) and [FAQ](https://github.com/microsoft/ProjectReunion/blob/master/docs/faq.md).

Here's how we intend to roll out Project Reunion *(all times/features/releases are tentative and subject to change)*:

<table>
  <tbody>
    <tr>
      <th>Reunion 0.5 (March 2021)</th>
      <th>Reunion 0.8 (Summer 2021)</th>
      <th>Reunion 1.0 (Fall 2021)</th>
      <th>2022 and Beyond</th>
    </tr>
    <tr>
    <td>
      <ul>
          <li>1st supported public release</li>
            <li>WinUI 3 works in <a href="https://docs.microsoft.com/en-us/windows/msix/desktop/desktop-to-uwp-packaging-dot-net">Desktop Packaged (Win32)</a> Apps</li>
            <li>Win2D will be part of Reunion</li>
       </ul>
     </td>
     <td>
        <ul>
            <li>Better bridging the gap between Win32 and WinRT</li>
            <li>Enabling developers to install runtime packages for MSIX, Win32</li>
            <li>State Notifications is supported</li>
            <li>Framework Package Support</li>
         </ul>
     </td>
     <td>
        <ul>
            <li>Reunion Windowing support</li>
            <li>New Rendering and Input features</li>
            <li>Smooth WinUI input & composition system experience</li>
            <li>App Lifecycle features (Power Management, Activation)</li>   
         </ul>
     </td>
    <td>
        <ul>
            <li>Multiple releases per year</li>
            <li>Continue expanding existing app compatibility</li>
            <li>Continuous delivery of new easier to use capabilities</li>
         </ul>
     </td>
    </tr>
  </tbody>
</table>

## 2021 Focus Areas

The Windows platform team is currently focused on the four primary areas below for Project Reunion.

This isn't an exhaustive list: it's a sampling of some of the key infrastructure work we're doing to break down the barriers between Win32 and UWP and decouple the platform from the OS, plus some of the new functionality we're adding to enable new app capabilities and address top developer issues.

### 1. User experience

* [WinUI 3](https://github.com/microsoft/microsoft-ui-xaml/blob/master/docs/roadmap.md) - the Windows 10 native UI platform for Win32 and UWP
* [WebView2](https://docs.microsoft.com/microsoft-edge/webview2/) - embedding web content in Windows apps using the new Edge (Chromium) engine
* [React Native Windows](https://github.com/microsoft/react-native-windows/projects/30) - now targeting WinUI

### 2. Hardware light-up and delighters

* Touch, inking, display improvements

### 3. Platform fundamentals

* [Better options for app lifecycle management and power usage](https://github.com/microsoft/ProjectReunion/issues/111)
* [DirectWrite text rendering platform](https://github.com/microsoft/ProjectReunion/issues/112)
* Windowing [details forthcoming]

### 4. Platform unification and deployment

* Decoupling the Windows platform from the OS
  * faster updates that you can start using on day 1
* Ensuring features work on all supported Windows versions
  * initial min OS version = 1809
  * polyfilling features as needed
  * supporting both Win32 and UWP
  
* Moving engineering to GitHub
  * [Proposals](https://github.com/microsoft/ProjectReunion/issues?q=is%3Aissue+is%3Aopen+label%3A%22feature+proposal%22) -> [Specs](https://github.com/microsoft/ProjectReunion/tree/master/specs) -> [Code](https://github.com/microsoft/ProjectReunion/tree/master/dev)
