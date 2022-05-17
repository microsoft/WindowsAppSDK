# Windows App SDK Roadmap

This roadmap frames how the Windows Development Platform team will deliver the Windows App SDK (WinAppSDK) and various technologies contained within, focused on the year ahead. It is intended to be the best entry point to conceptualize what’s happening in the WinAppSDK, so you can form plans/strategies around this technology.

Details of this roadmap may change, and when they do, we’ll strive to update the roadmap with the new information in a timely way.

## Mission

Empower developers to create the richest & most engaging native apps & surfaces for the Windows ecosystem.

## Looking back at 2021

Windows App SDK 1.0 [shipped](https://docs.microsoft.com/windows/apps/windows-app-sdk/stable-channel#version-10) on Nov 16, 2021 bringing the full power of the modern Windows dev platform to the Win32 app community. 
This release was made possible by the excellent feedback & bug reports we received from you, the Windows development community! 
WinAppSDK 1.0 includes rich features for production-level apps including WinUI 3, high-quality text rendering (DWriteCore), streamlined resource management (MRT Core), app lifecycle management, and framework agnostic windowing APIs. 
There are also numerous ecosystem technologies that have begun building on top of Windows App SDK; see the [1.0 blog post](https://blogs.windows.com/windowsdeveloper/2022/02/11/window-app-sdk-ecosystem-update/) for a detailed look.

## Primary areas of focus for 2022

In 2022, our overarching goal is to build upon the 1.0 release by raising overall reliability, and increasing usage across the industry.  To do this, we’ll concentrate on three areas this year:

- Ship WinAppSDK 1.1 and 1.2 with a range of new enhancements & features focused on enabling the first set of industry leading WinAppSDK-based apps to ship into market.
- Expand usage of WinUI 3 in Microsoft’s own products, including apps that are built-in & ship with Windows, and also the Windows OS shell itself.  Having our own teams experience the platform firsthand will help us rapidly improve the product for everyone.
- Continue efforts to make WinAppSDK and WinUI 3 available to the .NET MAUI and React Native for Windows ecosystems.

You will see improved reliability and new exciting features as we focus on these three areas.

## Upcoming features & releases

We aim to ship a high-quality release about every six months; as work begins on an upcoming release, we also kick off planning for the subsequent release in parallel. 
Our next WinAppSDK release will be version 1.1, expected to arrive in the first half of 2022 (22H1). 
Headline features for this release include:

- Apps can create **multiple windows** with WinUI3 content on the same UI thread.
- **Mica** & **Background Acrylic** styles are available for WinUI 3 content.  
- **Improved default and custom title bar** with new functionalities like z-order, sizing/resizing, tall title bar, and extended show.
- Apps using the Windows App SDK can **run with elevated permissions**.
- Apps that deploy with all their dependencies together are now able to include the Windows App SDK as well.  **(self-contained deployment)**
- Apps can **push notifications** regardless of being packaged/unpackaged, or whether the app is published in the Store.
- The **environment variables** PATH, and PATHEXT can be managed and tracked at runtime using new convenient APIs.  
- Apps can **restart** manually or register themselves to be restarted if it was running when a system update occurs.

A list of 1.2 features, aimed to ship near the end of 2022, will be shared in a future roadmap update.

## Join in and stay connected!

Technologies within the Windows App SDK have already benefitted greatly from the incredible feedback and insights the community has provided around features to build, and bugs to fix. 
*Thank you* for your continued passion and drive to make Windows App SDK the best platform it can be; it has really made a difference!

We’re working on new strategies to try and tackle the volume of feedback in a timely manner. 
As we concentrate on the areas of focus for 2022 mentioned above, we’ll prioritize responding to feedback in those areas first, and we’ll also publish clearer policies on handling stale issues that are unlikely to be addressed within the next couple releases.

You can join in by contributing to existing issues, or filing a new issue on the [Windows App SDK](https://github.com/microsoft/WindowsAppSDK) or [WinUI](https://github.com/microsoft/microsoft-ui-xaml) GitHub repos. If you're interested in WinUI 3, come join us on our live monthly [WinUI Community Calls](https://www.youtube.com/playlist?list=PLI_J2v67C23ZqsolUDaHoFkF1GKvGrttB), which are hosted on the third Wednesday of every month at 9am PT. Finally, you can stay in touch with us on Twitter using [#WindowsAppSDK](https://twitter.com/search?q=%23WindowsAppSDK). 