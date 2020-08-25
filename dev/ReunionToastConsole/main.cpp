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
        <input id="Reply" type="text" placeHolderContent="Type a response" />
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

HRESULT SetNodeValueString(HSTRING inputString, IXmlNode* node, IXmlDocument* xml)
{
    ComPtr<IXmlText> inputText;
    RETURN_IF_FAILED(xml->CreateTextNode(inputString, &inputText));

    ComPtr<IXmlNode> inputTextNode;
    RETURN_IF_FAILED(inputText.As(&inputTextNode));

    ComPtr<IXmlNode> appendedChild;
    return node->AppendChild(inputTextNode.Get(), &appendedChild);
}

HRESULT SetTextValues(const PCWSTR* textValues, UINT32 textValuesCount, IXmlDocument* toastXml)
{
    ComPtr<IXmlNodeList> nodeList;
    RETURN_IF_FAILED(toastXml->GetElementsByTagName(HStringReference(L"text").Get(), &nodeList));

    UINT32 nodeListLength;
    RETURN_IF_FAILED(nodeList->get_Length(&nodeListLength));

    // If a template was chosen with fewer text elements, also change the amount of strings
    // passed to this method.
    RETURN_IF_FAILED(textValuesCount <= nodeListLength ? S_OK : E_INVALIDARG);

    for (UINT32 i = 0; i < textValuesCount; i++)
    {
        ComPtr<IXmlNode> textNode;
        RETURN_IF_FAILED(nodeList->Item(i, &textNode));

        RETURN_IF_FAILED(SetNodeValueString(HStringReference(textValues[i]).Get(), textNode.Get(), toastXml));
    }

    return S_OK;
}

void DisplayToastActivated(_In_ PCWSTR appId, _In_ PCWSTR arguments, _In_ winrt::Windows::Foundation::Collections::IMap<hstring, hstring> const& userInput)
{
    const std::wstring toastPayload = LR"(<toast launch="action=viewConversation&amp;conversationId=5">
        <visual>
        <binding template="ToastGeneric">
        <text></text>
        <text></text>
        <text></text>
        </binding>
        </visual>
        </toast>)";

    ComPtr<IXmlDocument> doc;
    THROW_IF_FAILED(ActivateInstance(HStringReference(RuntimeClass_Windows_Data_Xml_Dom_XmlDocument).Get(), &doc));

    ComPtr<IXmlDocumentIO> docIO;
    THROW_IF_FAILED(doc.As(&docIO));

    // Load the XML string
    THROW_IF_FAILED(docIO->LoadXml(HStringReference(toastPayload.c_str()).Get()));

    std::wstring input = L"UserInput***** ";

    for (auto const& el : userInput)
    {
        if (!el.Value().empty())
        {
            input += L"key:";
            input += el.Key().c_str();
            input += L" ";
            input += L"value:";
            input += el.Value().c_str();
            input += L" ";
        }
    }

    PCWSTR textValues[] = {
        L"Toast Activated!",
        arguments,
        input.c_str()
    };
    THROW_IF_FAILED(SetTextValues(textValues, ARRAYSIZE(textValues), doc.Get()));

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
        DisplayToastActivated(toastArgs.AppId().c_str(), toastArgs.Arguments().c_str(), toastArgs.UserInput());
    });

    DesktopToastNotificationManagerCompat::RegisterApplication(clsid, appId, displayName, icon);

    // If launched from a toast, don't do anything
    if (!DesktopToastNotificationManagerCompat::WasProcessToastActivated())
    {
        printf("Launched by a click! Sending a new toast!\n");
        DisplayToast(appId.c_str());
    }
}
