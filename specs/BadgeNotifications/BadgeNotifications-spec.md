Badge Notifications in Windows App SDK
===

This is the spec for proposal: [Issue #138](https://github.com/microsoft/WindowsAppSDK/issues/138)

# Background

A notification badge conveys summary or status information specific to your app. They can be numeric (1-99) or one of a set of system-provided glyphs. Examples of information best conveyed through a badge include network connection status in an online game, user status in a messaging app, number of unread mails in a mail app, and number of new posts in a social media app. 

Example of a numeric badge in Taskbar (One new message in Whatsapp): 

![Screenshot](NumericBadgeExample.png)

Example of a system-provided glyph in taskbar (New message in Outlook): 

![Screenshot](GlyphBadgeExample.png)
 
This Badge notification functionality is missing in WinAppSDK, which not only blocks apps like WhatsApp to move to WinAppSDK but also stops them from availing new features and goodness that we are building in WinAppSDK. The scope of this document is to fill that gap and provide badge notification capability in WinAppSDK as well.   

# Description

Badge notifications provide users with a visual indicator of new or important content in your application. This feature enhances user engagement by allowing them to quickly see updates without needing to open the app. Badge notifications are already supported for UWP apps. This initiative is to make badge notifications work in WindowsAppSdk.

For more details see:

-   [Badge Notification WinRT APIs](https://learn.microsoft.com/en-us/windows/apps/design/shell/tiles-and-notifications/badges)
    Defines all the API constructs that we have for Badge Notifications in WinRT today.

# Examples

## Create a numeric badge (c++)

 ```c++
private void setBadgeNumber(uint32_t num)
{
    winrt::BadgeNotification badgeNotification(num);
    winrt::BadgeNotificationManager manager = winrt::BadgeNotificationManager::Default();
    manager.UpdateBadge(badgeNotification);
}
```

## Create a Glyph badge (c++)

 ```c++
private void updateBadgeGlyph()
{
    winrt::BadgeGlyphValue badgeGlyphValue = winrt::BadgeGlyphValue::alert
    winrt::BadgeNotification badgeNotification(badgeGlyphValue);
    winrt::BadgeNotificationManager manager = winrt::BadgeNotificationManager::Default();
    manager.UpdateBadge(badgeNotification);
}
```

## Clear a badge

 ```c++
private void clearBadge()
{
    winrt::BadgeNotificationManager manager = winrt::BadgeNotificationManager::Default();
    manager.ClearBadge();
}
```

## To set an expiration time in a badge (c++)

 ```c++
private void updateBadgeGlyph()
{
    winrt::BadgeGlyphValue badgeGlyphValue = winrt::BadgeGlyphValue::alert
    winrt::BadgeNotification badgeNotification(badgeGlyphValue);

    DateTime expirationTime = clock::now() + std::chrono::hours(24);
    badgeNotification.Expiration(expirationTime);

    winrt::BadgeNotificationManager manager = winrt::BadgeNotificationManager::Default();
    manager.UpdateBadge(badgeNotification);
}
```

# API pages

## BadgeNotification class

The `BadgeNotification` class is used to create badge notifications for apps on platforms such as Windows, where badges can be displayed on the app's tile. A badge can show a numeric value or a system-provided glyph, providing a visual indicator of some status or count directly on the app's icon.

## BadgeNotification constructors

| Name | Description |
|-|-|
| BadgeNotification(UInt32) | Creates a new `BadgeNotification` object with a numeric badge value. This is used to display a specific number on the app's badge. |
| BadgeNotification(BadgeGlyphValue) | Creates a new `BadgeNotification` object with a glyph value. This uses a predefined glyph from the `BadgeGlyphValue` enum to display a system-provided symbol on the app's badge. |

## BadgeNotification Properties
| Name | Description | Type |
|-|-|-|
| Expiration | Gets or sets the time after which the badge notification should no longer be displayed. This allows for the badge notification to be time-sensitive and automatically removed when it is no longer relevant. | Windows.Foundation.DateTime |

## BadgeNotificationManager class

The `BadgeNotificationManager` class is the central point for managing badge notifications for an application. It provides the functionality to update or clear the badge displayed on the app's tile. This class allows developers to modify the badge's appearance by setting a numeric value or a glyph and also to remove the badge when it is no longer needed.

## BadgeNotificationManager Properties

| Name | Description | Type |
|-|-|-|
| Default | Provides a default instance of the `BadgeNotificationManager` for use in updating or clearing badge notifications. | BadgeNotificationManager |

## BadgeNotificationManager Methods

| Name | Description | Parameters | Returns |
|-|-|-|-|
| UpdateBadge | Applies a change to the badge's glyph or number by providing a `BadgeNotification` object. This method is used to update the badge displayed on the app's tile to reflect a new status or count. | BadgeNotification `notification` | void |
| ClearBadge | Removes the badge notifications for the app from the action center. This method is useful for clearing any badge notifications when they are no longer relevant or when the app wants to reset its badge status. | | Windows.Foundation.IAsyncAction |

## BadgeGlyphValue enum

The `BadgeGlyphValue` enum defines a set of predefined glyphs that can be used to represent various statuses or notifications on an application's badge. These glyphs provide a visual cue on the app's tile, allowing users to quickly understand the app's status or to be alerted to new information without opening the app.

| Name | Description | Glyph |
|-|-|
| None | No glyph is displayed. The badge will appear blank or not be shown at all. | (No Badge Shown) |
| Activity | A glyph indicating some form of activity is taking place within the app. | ![Screenshot](badge-activity.png) |
| Alert | A glyph that suggests an alert or an important notification that may require immediate attention. | ![Screenshot](badge-alert.png) |
| Alarm | A glyph that represents an alarm, possibly indicating a set reminder or a timed event. | ![Screenshot](badge-alarm.png) |
| Attention | A glyph that signifies the need for attention, often used for notifications or new information. | ![Screenshot](badge-attention.png) |
| Available | A glyph that indicates the user or a service is available, often used in communication apps. | ![Screenshot](badge-available.png) |
| Away | A glyph that shows the user is away or inactive, commonly used in status indicators for communication apps. | ![Screenshot](badge-away.png) |
| Busy | A glyph that represents the user being busy or engaged in an activity, preventing interruptions. | ![Screenshot](badge-busy.png) |
| NewMessage | A glyph that indicates the arrival of a new message, often used in messaging and email applications. | ![Screenshot](badge-newmessage.png) |
| Paused | A glyph that signifies a pause in activity or content, such as media playback being paused. | ![Screenshot](badge-paused.png) |
| Playing | A glyph that indicates media or content is currently playing. | ![Screenshot](badge-playing.png) |
| Unavailable | A glyph that shows the user or a service is not currently available or offline. | ![Screenshot](badge-unavailable.png) |
| Error | A glyph that denotes an error has occurred, which may require user action to resolve. | ![Screenshot](badge-error.png) |

These glyphs are system-provided and standardized, ensuring a consistent look and feel across different applications that use them. By using these glyphs, developers can convey specific states or notifications to users in a visually intuitive manner.

# API Details

> Note: all of this new WinAppSDK API is to support 
  Badge Notifications in WindowsAppSdk
 
```c++ (but really MIDL3)
namespace Microsoft.Windows.BadgeNotifications
{
    // Set of predefined glyphs that can be used to represent various statuses or notifications on an application's badge
    enum BadgeGlyphValue
    {
        None, // No glyph. A blank tile appears in the badge.
        Activity, // A glyph representing an activity
        Alert, // A glyph representing an alert
        Alarm, // A glyph representing an alarm
        Attention, // A glyph representing attention
        Available, // A glyph representing availability
        Away, // A glyph representing being away
        Busy, // A glyph representing being busy
        NewMessage, // A glyph representing a new message
        Paused, // A glyph representing being paused
        Playing, // A glyph representing playing
        Unavailable, // A glyph representing being unavailable
        Error, // A glyph representing an error
    };

    runtimeclass BadgeNotification
    {
        // Constructs a BadgeNotification with a numeric badge value.
        // This constructor initializes the BadgeNotification with a number that will be displayed on the badge.
        // @param num The numeric value to be displayed on the badge.
        BadgeNotification(UInt32 num);

        // Constructs a BadgeNotification with a glyph value.
        // This constructor initializes the BadgeNotification with a predefined glyph from the BadgeGlyphValue enum.
        // @param value The BadgeGlyphValue representing a system-provided glyph to be displayed on the badge.
        BadgeNotification(BadgeGlyphValue value);

        // Gets or sets the time after which a Badge Notification should not be displayed.
        Windows.Foundation.DateTime Expiration;
    }

    // The manager class which encompasses all Badge Notification API Functionality
    runtimeclass BadgeNotificationManager
    {
        // Gets a Default instance of a BadgeNotificationManager
        static BadgeNotificationManager Default{ get; };

        // Applies a change to the badge's glyph or number.
        void UpdateBadge(BadgeNotification notification);

        // Removes the Badge Notifications for the App from Action Centre
        Windows.Foundation.IAsyncAction ClearBadge();
    }
}
```
