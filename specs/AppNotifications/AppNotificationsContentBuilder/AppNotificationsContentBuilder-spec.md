# App Notifications Content Builder

# Examples
## App Notification with Avatar Image

To generate a toast like this one:

![App Notification With Avatar Image](ToastWithAvatarImage.png)

Developers have to write something like this:

``` c++
    int sequenceId {1234};
    std::wstring pathToImage {LR"(path\to\my\image.png)"};

    winrt::hstring xmlPayload{
        L"<toast launch = \"action=ToastClick&amp;sequence=" + to_wstring(sequenceId) + L"\">\
            <visual>\
                <binding template = \"ToastGeneric\">\
                    <image placement = \"appLogoOverride\" hint-crop=\"circle\" src = \"" + pathToImage + L"\"/>\
                    <text>Toast Notification with Avatar Image</text>\
                    <text>This is an example message using XML</text>\
                </binding>\
            </visual>\
            <actions>\
                <action\
                    content = \"Open App\"\
                    arguments = \"action=OpenApp&amp;sequence=" + to_wstring(sequenceId) + L"\"/>\
            </actions>\
        </toast>" };

    auto toast{ winrt::AppNotification(xmlPayload) };
    winrt::AppNotificationManager::Default().Show(toast);
```

but it doesn't have to be. They could write something like this instead (using a fluent builder):

``` c++
int sequenceId {1234};
std::wstring pathToImage {LR"(path\to\my\image.png)"};

AppNotificationContentBuilder("ToastClick")
    .AddLaunchArgument(L"sequence", sequenceId)
    .AddImage(new ImageConfig(pathToImage)
        .SetIsAppLogo()
        .SetHintCrop(AdaptiveImageCrop::Circle))
    .AddText(L"Toast Notification with Avatar Image")
    .AddText(L"This is an example message")
    .AddButton(new ButtonConfig(L"Open App")
        .AddArgument(L"action", "OpenAppButton")
        .AddArgument(L"sequence", sequenceId))
    .Show();
```

or like this (without a fluent builder):

``` c++
int sequenceId {1234};
std::wstring pathToImage {LR"(path\to\my\image.png)"};

image = new ImageConfig(L"Path\\To\\My\\Image.png");
image.SetIsAppLogo();
image.SetHintCrop(AdaptiveImageCrop::Circle);

button = new ButtonConfig(L"Open App");
button.AddArgument(L"action", "OpenAppButton");
button.AddArgument(L"sequence", sequenceId);

builder = new AppNotificationContentBuilder("ToastClick");
builder.AddLaunchArgument(L"sequence", sequenceId)
builder.AddImage(image);
builder.AddText(L"Toast Notification with Avatar Image");
builder.AddText(L"This is an example message");
builder.AddButton(button);
builder.Show();
```

## App Notification with Avatar And Text Box

To generate a toast like this one:

![App Notification With Avatar Image](ToastWithTextBox.png)

Developers have to write something like this:

``` c++
    winrt::hstring xmlPayload{
        LR"<toast launch = "action=ToastClick&amp;">\
            <visual>\
                <binding template = "ToastGeneric">\
                    <image placement = "appLogoOverride" hint-crop="circle" src = "Path\To\My\Image.png"/>\
                    <text>This is an example message</text>\
                </binding>\
            </visual>\
            <actions>\
                <input\
                    id = "textboxReply"\
                    type = "text"\
                    placeHolderContent = "Type a reply"/>\
                <action\
                    content = "Reply"\
                    arguments = "action=ReplyButton&amp;Sequence=1234"/>\
                    hint-inputId="textboxReply"/>\
            </actions>\
        </toast>" };

    auto toast{ winrt::AppNotification(xmlPayload) };
    winrt::AppNotificationManager::Default().Show(toast);
```

but it doesn't have to be. They could write something like this instead (using a fluent builder):

``` c++
AppNotificationContentBuilder("ToastClick")
    .AddImage(new Image(L"Path\\To\\My\\Image.png")
        .Placement(Placement::appLogoOverride)
        .Crop(Crop::Circle))
    .AddText(L"Toast Notification with Avatar Image")
    .AddText(L"This is an example message")
    .AddTextBox(new TextBox("textboxReply")
        .PlaceHolderContent("Type a reply"))
    .AddButton(new Button(L"Reply", L"ReplyButton")
        .GroupingHint("textboxReply"))
    .AddArgument(L"Sequence", L"1234")
    .Show();
```

or like this (without a fluent builder):

``` c++
AppNotificationContentBuilder("ToastClick")
    .AddImage(new Image(L"Path\\To\\My\\Image.png")
        .Placement(Placement::appLogoOverride)
        .Crop(Crop::Circle))
    .AddText(L"Toast Notification with Avatar Image")
    .AddText(L"This is an example message")
    .AddTextBox(new TextBox("textboxReply")
        .PlaceHolderContent("Type a reply"))
    .AddButton(new Button(L"Reply", L"ReplyButton")
        .GroupingHint("textboxReply"))
    .AddArgument(L"Sequence", L"1234")
    .Show();
```