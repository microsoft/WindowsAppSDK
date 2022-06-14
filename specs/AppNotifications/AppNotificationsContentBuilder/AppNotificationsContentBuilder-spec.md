# App Notifications Content Builder

# Examples
## Toast Notification with Avatar Image

To generate a toast like this one:

![Toast With Avatar Image](ToastWithAvatarImage.png)

developpers have to write something like this:
``` c++
    winrt::hstring xmlPayload{
        L"<toast launch = \"action=ToastClick&amp;\">\
            <visual>\
                <binding template = \"ToastGeneric\">\
                    <image placement = \"appLogoOverride\" hint-crop=\"circle\" src = \"Path\\To\\My\\Image.png\"/>\
                    <text>This is an example message</text>\
                </binding>\
            </visual>\
            <actions>\
                <action\
                    content = \"Open App\"\
                    arguments = \"action=OpenApp&amp;Sequence=1234\"/>\
            </actions>\
        </toast>" };

    auto toast{ winrt::AppNotification(xmlPayload) };
    winrt::AppNotificationManager::Default().Show(toast);
```

but it doesn't have to be. They could write something like this instead:

``` c++
auto contentBuilder{ new AppNotificationContentBuilder()
    .AddImage(L"Path\\To\\My\\Image.png", Placement::appLogoOverride, Crop::Circle)
    .AddText(L"Toast Notification with Avatar Image")
    .AddText(L"This is an example message")
    .AddButton(L"Open App", L"OpenAppAction")
    .AddArgument(L"Sequence", L"1234") };
    .Show();
auto appNotification{ new AppNotification(contentBuilder.GetXml()) };
AppNotificationManager.Default.Show(toast);
```


