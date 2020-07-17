# Roadmap

Project Reunion is an umbrella of work that we will develop together over time.

The roadmap for Project Reunion supports the primary goals of breaking down the barriers between Win32 and UWP and making the Windows developer platform more agile, compatible, modern and open.

For a general overview, see the [readme](https://github.com/microsoft/ProjectReunion/tree/master/docs) and [FAQ](https://github.com/microsoft/ProjectReunion/blob/master/docs/faq.md).

Here's how we intend to roll out Project Reunion:

<table>
  <tbody>
    <tr>
      <th>//BUILD 2020</th>
      <th>End of 2020</th>
      <th>2021++</th>
    </tr>
    <tr>
      <td>
        <ul>
            <li>WinUI preview for UWP & Win32</li>
            <li>Windows Virtual Desktop</li>
            <li>WebView2 Preview</li>
            <li>Project Reunion repo</li>
         </ul>
     </td>
      <td>
        <ul>
            <li>WinUI "go-live" Preview</li>
            <li>Project Reunion Preview</li>
         </ul>
     </td>
    <td>
        <ul>
            <li>Multiple releases per year</li>
            <li>Continue expanding existing app compatibility</li>
            <li>Continue delivery of new capabilities</li>
         </ul>
     </td>
    </tr>
  </tbody>
</table>

## 2020-2021 Focus Areas

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
