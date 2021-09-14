# Welcome to MRT Core!

## Overview

### What is MRT Core?
Thanks for asking! MRT Core was born from the need for [Windows App SDK](https://aka.ms/windowsappsdk) applications to use MRT - Modern Resource Technology. MRT was introduced to Windows in the Windows 8 timeframe and has evolved as the resource management system since that time. You can use these links to learn more about [MRT and resource management](https://docs.microsoft.com/windows/uwp/app-resources/resource-management-system) as well as the benefits of [globalization and localization](https://docs.microsoft.com/windows/uwp/design/globalizing/globalizing-portal).

> If you're looking for Core MRT, you're in the right place! Internal project naming was Core MRT and so some of our external communication has also used that terminology - sorry for any confusion! But rest assured, Core MRT or MRT Core, you're in the right place! 😉

### So what does it do?
At its *core* 😎 MRT Core provides support to build resource Package Resource Index (PRI) files, and load resources from PRI files. [Learn more about PRI files at this link.](https://docs.microsoft.com/windows/uwp/app-resources/resource-management-system)

## Getting Started
Install the NuGet package from [https://aka.ms/MRTCore](https://aka.ms/MRTCore), and you are ready to build PRI files from Visual Studio
and use MRT Core APIs to load resources in your app.

The C APIs can be found in [mrm.h](mrt/Core/src/MRM.h). The WinRT APIs can be found in [Microsoft.Windows.ApplicationModel.Resources.idl](mrt/Microsoft.Windows.ApplicationModel.Resources/src/Microsoft.Windows.ApplicationModel.Resources.idl).

## Build and Test
Load [MrtCore.sln](mrt/MrtCore.sln) in Visual Studion 2019, and build the solution.

Run the tests in Test Explorer.

## Contribute

This project welcomes contributions and suggestions. Most contributions require you to
agree to a Contributor License Agreement (CLA) declaring that you have the right to,
and actually do, grant us the rights to use your contribution. For details, visit
https://cla.microsoft.com.

When you submit a pull request, a CLA-bot will automatically determine whether you need
to provide a CLA and decorate the PR appropriately (e.g., label, comment). Simply follow the
instructions provided by the bot. You will only need to do this once across all repositories using our CLA.

## Code of Conduct

This project has adopted the [Microsoft Open Source Code of Conduct](https://opensource.microsoft.com/codeofconduct/).
For more information see the [Code of Conduct FAQ](https://opensource.microsoft.com/codeofconduct/faq/) or
contact [opencode@microsoft.com](mailto:opencode@microsoft.com) with any additional questions or comments.

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
 and grant you a license to any code in the repository under the [MIT License](https://opensource.org/licenses/MIT), see the
[LICENSE](../../LICENSE) file.

Microsoft, Windows, Microsoft Azure and/or other Microsoft products and services referenced in the documentation
may be either trademarks or registered trademarks of Microsoft in the United States and/or other countries.
The licenses for this project do not grant you rights to use any Microsoft names, logos, or trademarks.
Microsoft's general trademark guidelines can be found at http://go.microsoft.com/fwlink/?LinkID=254653.

Privacy information can be found at https://privacy.microsoft.com/

Microsoft and any contributors reserve all other rights, whether under their respective copyrights, patents,
or trademarks, whether by implication, estoppel or otherwise.
