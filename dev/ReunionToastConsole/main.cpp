#include "pch.h"
#include <windows.ui.notifications.h>
#include <wrl.h>
#include <wrl\wrappers\corewrappers.h>

using namespace winrt;
using namespace ::Windows::Foundation;
using namespace winrt::Microsoft::ToastNotificationsWinRt;
using namespace ABI::Windows::UI::Notifications;
using namespace ABI::Windows::Data::Xml::Dom;
using namespace ::Microsoft::WRL;
using namespace ::Microsoft::WRL::Wrappers;

void DisplayToast(PCWSTR appId)
{
    const std::wstring toastPayload = LR"(<toast launch="action=viewConversation&amp;conversationId=5">
        <visual>
        <binding template="ToastGeneric">
        <text>Andrew sent you a picture</text>
        <text>Check this out, The Enchantments!</text>
        </binding>
        </visual>
        <actions>
        <input id="tbReply" type="text" placeHolderContent="Type a response" />
        <action content="Reply" arguments="action=reply&amp;conversationId=5" />
        <action content="Like" arguments="action=like&amp;conversationId=5" />
        <action content="View" arguments="action=viewImage&amp;imageUrl=https://picsum.photos/364/202?image=883" />
        </actions>
        </toast>)";

    ComPtr<IXmlDocument> doc;
    THROW_IF_FAILED(ActivateInstance(HStringReference(RuntimeClass_Windows_Data_Xml_Dom_XmlDocument).Get(), &doc));

    ComPtr<IXmlDocumentIO> docIO;
    THROW_IF_FAILED(doc.As(&docIO));

    // Load the XML string
    THROW_IF_FAILED(docIO->LoadXml(HStringReference(toastPayload.c_str()).Get()));

    ComPtr<IToastNotificationManagerStatics> toastStatics;
    THROW_IF_FAILED(GetActivationFactory(
        HStringReference(RuntimeClass_Windows_UI_Notifications_ToastNotificationManager).Get(),
        &toastStatics));

    ComPtr<IToastNotifier> notifier;
    THROW_IF_FAILED(toastStatics->CreateToastNotifierWithId(HStringReference(appId).Get(), &notifier));

    ComPtr<IToastNotificationFactory> factory;
    THROW_IF_FAILED(GetActivationFactory(
        HStringReference(RuntimeClass_Windows_UI_Notifications_ToastNotification).Get(),
        &factory));

    ComPtr<IToastNotification> toast;
    THROW_IF_FAILED(factory->CreateToastNotification(doc.Get(), &toast));

    THROW_IF_FAILED(notifier->Show(toast.Get()));

    // This is a bug in the platform: Fixed in Mn and serviced down
    Sleep(50);
}

void DisplayToastActivated(PCWSTR appId)
{
    const std::wstring toastPayload = LR"(<toast launch="action=viewConversation&amp;conversationId=5">
        <visual>
        <binding template="ToastGeneric">
        <text>Toast Activated!!</text>
        </binding>
        </visual>
        </toast>)";

    ComPtr<IXmlDocument> doc;
    THROW_IF_FAILED(ActivateInstance(HStringReference(RuntimeClass_Windows_Data_Xml_Dom_XmlDocument).Get(), &doc));

    ComPtr<IXmlDocumentIO> docIO;
    THROW_IF_FAILED(doc.As(&docIO));

    // Load the XML string
    THROW_IF_FAILED(docIO->LoadXml(HStringReference(toastPayload.c_str()).Get()));

    ComPtr<IToastNotificationManagerStatics> toastStatics;
    THROW_IF_FAILED(GetActivationFactory(
        HStringReference(RuntimeClass_Windows_UI_Notifications_ToastNotificationManager).Get(),
        &toastStatics));

    ComPtr<IToastNotifier> notifier;
    THROW_IF_FAILED(toastStatics->CreateToastNotifierWithId(HStringReference(appId).Get(), &notifier));

    ComPtr<IToastNotificationFactory> factory;
    THROW_IF_FAILED(GetActivationFactory(
        HStringReference(RuntimeClass_Windows_UI_Notifications_ToastNotification).Get(),
        &factory));

    ComPtr<IToastNotification> toast;
    THROW_IF_FAILED(factory->CreateToastNotification(doc.Get(), &toast));

    THROW_IF_FAILED(notifier->Show(toast.Get()));

    // This is a bug in the platform: Fixed in Mn and serviced down
    Sleep(50);
}

int main(int argc, char* argv[], char* envp[])
{
    init_apartment();

    hstring appId = L"TestAppId";
    hstring clsid = L"{11E949A3-D621-4E9F-BA53-3811C3EFDECF}";
    hstring displayName = L"TestApp";
    hstring icon = L"D:\src\ProjectReunion\dev\ReunionToastConsole\Image.png";

    winrt::event_token eventToken = DesktopToastNotificationManagerCompat::ToastActivated([](const auto&, winrt::Microsoft::ToastNotificationsWinRt::ToastActivatedEventArgs toastArgs)
    {
        DisplayToastActivated(toastArgs.AppId().c_str());
    });

    DesktopToastNotificationManagerCompat::RegisterApplication(clsid, appId, displayName, icon);

    // If launched from a toast: Note this API call blocks till the toast activator is set
    if (DesktopToastNotificationManagerCompat::WasProcessToastActivated())
    {
        printf("Launched from Toast!\n");
    }
    else
    {
        printf("Launched by a click! Sending a new toast!\n");
        DisplayToast(appId.c_str());
    }
}
