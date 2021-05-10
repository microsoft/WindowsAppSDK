#include <winrt/Windows.ApplicationModel.background.h>
#include <winrt/Windows.Storage.Streams.h>
#include <TestDef.h>
struct MockRawNotification: winrt::Windows::Networking::PushNotifications::IRawNotification3
{
    public:
    winrt::Windows::Storage::Streams::IBuffer ContentBytes()
    {
        winrt::Windows::Storage::Streams::DataWriter dataWriter{};
        dataWriter.WriteString(c_rawNotificationPayload);
        return dataWriter.DetachBuffer();
    }
};
