# Badge Notifications in Windows App SDK

This is the spec for proposal: [Issue #138](https://github.com/microsoft/WindowsAppSDK/issues/138)

# Background

A notification badge conveys summary or status information specific to your app. They can be numeric
(1-99) or one of a set of system-provided glyphs. Examples of information best conveyed through a
badge include network connection status in an online game, user status in a messaging app, number of
unread mails in a mail app, and number of new posts in a social media app.

Example of a numeric badge in Taskbar (One new message in Whatsapp):

![Screenshot](NumericBadgeExample.png)

Example of a system-provided glyph in taskbar (New message in Outlook):

![Screenshot](GlyphBadgeExample.png)

This Badge notification functionality is missing in WinAppSDK, which not only blocks apps like
WhatsApp to move to WinAppSDK but also stops them from availing new features and goodness that we
are building in WinAppSDK. The scope of this document is to fill that gap and provide badge
notification capability in WinAppSDK as well.

> Note: This provids a subset of functionality present in WindowsSdk, but all that is necessary to
> post and clear a badge notification

# Description

Badge notifications provide users with a visual indicator of new or important content in your
application. This feature enhances user engagement by allowing them to quickly see updates without
needing to open the app. Badge notifications are already supported for UWP apps. This initiative is
to make badge notifications work in WindowsAppSdk.

For more details see:

-   [Badge Notification WinRT APIs](https://learn.microsoft.com/windows/apps/design/shell/tiles-and-notifications/badges)
    Defines all the API constructs that we have for Badge Notifications in WinRT today.

# Compatibility

## Supported Apps

This API requires package identity to match notifications to applications. See
[an overview of package identity](https://learn.microsoft.com/windows/apps/desktop/modernize/package-identity-overview)
for how to deploy your application as a package, or assign identity to your existing application
during its install time.

## Notification Type

The badge notifications are local to the device. No remote server interaction is required or
supported for updating the badge count.

# Examples

## Create a numeric badge (c++)

```c++
private void setBadgeNumber(uint32_t num)
{
   winrt::BadgeNotificationManager manager = winrt::BadgeNotificationManager::Current();
   manager.SetBadgeAsCount(num);
}
```

## Create a Glyph badge (c++)

```c++
private void updateBadgeGlyph()
{
   winrt::BadgeNotificationGlyph badgeNotificationGlyph = winrt::BadgeNotificationGlyph::Alert;
   winrt::BadgeNotificationManager manager = winrt::BadgeNotificationManager::Current();
   manager.SetBadgeAsGlyph(badgeNotificationGlyph);
}
```

## Clear a badge

```c++
private void clearBadge()
{
   winrt::BadgeNotificationManager manager = winrt::BadgeNotificationManager::Current();
   manager.ClearBadge();
}
```

## To set an expiration time in a badge (c++)

```c++
private void updateBadgeGlyph()
{
   winrt::BadgeNotificationGlyph badgeNotificationGlyph = winrt::BadgeNotificationGlyph::Alert

   DateTime expirationTime = clock::now() + std::chrono::hours(24);

   winrt::BadgeNotificationManager manager = winrt::BadgeNotificationManager::Current();
   manager.SetBadgeAsGlyph(badgeNotificationGlyph, expirationTime);
}
```

# API Description

## BadgeNotificationManager class

The `BadgeNotificationManager` class is the central point for managing badge notifications for an
application. It provides the functionality to update or clear the badge displayed on the app's tile.
This class allows developers to modify the badge's appearance by setting a numeric value or a glyph
and also to remove the badge when it is no longer needed.

## BadgeNotificationManager Properties

| Name    | Description                                                                                                        | Type                     |
| ------- | ------------------------------------------------------------------------------------------------------------------ | ------------------------ |
| Current | Provides a default instance of the `BadgeNotificationManager` for use in updating or clearing badge notifications. | BadgeNotificationManager |

## BadgeNotificationManager Methods

| Name            | Description                                                                                                                                                                                                      | Parameters                                                                    | Returns |
| --------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ----------------------------------------------------------------------------- | ------- |
| SetBadgeAsCount | Updates the badge on the app's tile to display a numeric value. This method is used to reflect a new status or count.                                                                                            | UInt32 `notificationCount`                                                    | void    |
| SetBadgeAsCount | Updates the badge on the app's tile to display a numeric value, with an expiration time after which the badge should be cleared.                                                                                 | UInt32 `notificationCount`, Windows.Foundation.DateTime `expiration`          | void    |
| SetBadgeAsGlyph | Updates the badge on the app's tile to display a glyph. This method is used to reflect a new status represented by a glyph.                                                                                      | BadgeNotificationGlyph `glyphValue`                                           | void    |
| SetBadgeAsGlyph | Updates the badge on the app's tile to display a glyph, with an expiration time after which the badge should be cleared.                                                                                         | BadgeNotificationGlyph `glyphValue`, Windows.Foundation.DateTime `expiration` | void    |
| ClearBadge      | Removes the badge notifications for the app from the action center. This method is useful for clearing any badge notifications when they are no longer relevant or when the app wants to reset its badge status. |                                                                               | void    |

> Note: For Numeric badge if the count is greater then 99 it will be reported as "99+"

## BadgeNotificationGlyph enum

The `BadgeNotificationGlyph` enum defines a set of predefined glyphs that can be used to represent
various statuses or notifications on an application's badge. These glyphs provide a visual cue on
the app's tile, allowing users to quickly understand the app's status or to be alerted to new
information without opening the app.

| Name        | Description                                                                                                 | Glyph                                |
| ----------- | ----------------------------------------------------------------------------------------------------------- | ------------------------------------ |
| None        | No glyph is displayed. The badge will not be shown at all. It is equivalent to ClearBadge.                  | (No Badge Shown)                     |
| Activity    | A glyph indicating some form of activity is taking place within the app.                                    | ![Screenshot](badge-activity.png)    |
| Alarm       | A glyph that represents an alarm, possibly indicating a set reminder or a timed event.                      | ![Screenshot](badge-alarm.png)       |
| Alert       | A glyph that suggests an alert or an important notification that may require immediate attention.           | ![Screenshot](badge-alert.png)       |
| Attention   | A glyph that signifies the need for attention, often used for notifications or new information.             | ![Screenshot](badge-attention.png)   |
| Available   | A glyph that indicates the user or a service is available, often used in communication apps.                | ![Screenshot](badge-available.png)   |
| Away        | A glyph that shows the user is away or inactive, commonly used in status indicators for communication apps. | ![Screenshot](badge-away.png)        |
| Busy        | A glyph that represents the user being busy or engaged in an activity, preventing interruptions.            | ![Screenshot](badge-busy.png)        |
| Error       | A glyph that denotes an error has occurred, which may require user action to resolve.                       | ![Screenshot](badge-error.png)       |
| NewMessage  | A glyph that indicates the arrival of a new message, often used in messaging and email applications.        | ![Screenshot](badge-newmessage.png)  |
| Paused      | A glyph that signifies a pause in activity or content, such as media playback being paused.                 | ![Screenshot](badge-paused.png)      |
| Playing     | A glyph that indicates media or content is currently playing.                                               | ![Screenshot](badge-playing.png)     |
| Unavailable | A glyph that shows the user or a service is not currently available or offline.                             | ![Screenshot](badge-unavailable.png) |

These glyphs are system-provided and standardized, ensuring a consistent look and feel across
different applications that use them. By using these glyphs, developers can convey specific states
or notifications to users in a visually intuitive manner.

> Note: Only system-provided badge images can be used.

# API Details

> Note: all of this new WinAppSDK API is to support Badge Notifications in WindowsAppSdk

```c++ (but really MIDL3)
namespace Microsoft.Windows.BadgeNotifications
{
    // Set of predefined glyphs that can be used to represent various statuses or notifications on an application's badge
    enum BadgeNotificationGlyph
    {
        None, // No glyph. A blank tile appears in the badge.
        Activity, // A glyph representing an activity
        Alarm, // A glyph representing an alarm
        Alert, // A glyph representing an alert
        Attention, // A glyph representing attention
        Available, // A glyph representing availability
        Away, // A glyph representing being away
        Busy, // A glyph representing being busy
        Error, // A glyph representing an error
        NewMessage, // A glyph representing a new message
        Paused, // A glyph representing being paused
        Playing, // A glyph representing playing
        Unavailable, // A glyph representing being unavailable
    };

    // The manager class which encompasses all Badge Notification API Functionality
    runtimeclass BadgeNotificationManager
    {
        // Gets a Default instance of a BadgeNotificationManager
        static BadgeNotificationManager Current{ get; };

        // Updates the badge on the app's icon on taskbar to display a numeric value.
        void SetBadgeAsCount(UInt32 notificationCount);

        // Updates the badge on the app's icon on taskbar to display a numeric value with an expiration time.
        void SetBadgeAsCount(UInt32 notificationCount, Windows.Foundation.DateTime expiration);

        // Updates the badge on the app's icon on taskbar to display a glyph.
        void SetBadgeAsGlyph(BadgeNotificationGlyph glyphValue);

        // Updates the badge on the app's icon on taskbar to display a glyph with an expiration time.
        void SetBadgeAsGlyph(BadgeNotificationGlyph glyphValue, Windows.Foundation.DateTime expiration);

        // Removes the Badge Notifications for the App from Action Center
        void ClearBadge();
    }
}
```
