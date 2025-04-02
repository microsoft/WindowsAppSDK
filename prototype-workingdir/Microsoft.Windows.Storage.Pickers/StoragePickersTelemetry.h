#include "StoragePickersTelemetryHelper.h"

namespace StoragePickersTelemetry
{
    struct FolderPickerPickSingleFolder
    {
        static auto Start(StoragePickersTelemetryHelper& telemetryHelper)
        {
            // Mock implementation
            struct LogTelemetry
            {
                LogTelemetry(StoragePickersTelemetryHelper&) {}
                void Stop(StoragePickersTelemetryHelper&, bool) {}
            };
            return LogTelemetry{ telemetryHelper };
        }
    };

    // StoragePickersTelemetry::FileOpenPickerPickMultipleFile::Start(m_telemetryHelper)
    struct FileOpenPickerPickMultipleFile
    {
        static auto Start(StoragePickersTelemetryHelper& telemetryHelper)
        {
            // Mock implementation
            struct LogTelemetry
            {
                LogTelemetry(StoragePickersTelemetryHelper&) {}
                void Stop(StoragePickersTelemetryHelper&, bool, bool) {}
            };
            return LogTelemetry{ telemetryHelper };
        }
    };

    // StoragePickersTelemetry::FileOpenPickerPickSingleFile::Start(m_telemetryHelper)
    struct FileOpenPickerPickSingleFile
    {
        static auto Start(StoragePickersTelemetryHelper& telemetryHelper)
        {
            // Mock implementation
            struct LogTelemetry
            {
                LogTelemetry(StoragePickersTelemetryHelper&) {}
                void Stop(StoragePickersTelemetryHelper&, bool) {}
            };
            return LogTelemetry{ telemetryHelper };
        }
    };

    // FileSavePickerPickSingleFile::Start(m_telemetryHelper)
    struct FileSavePickerPickSingleFile
    {
        static auto Start(StoragePickersTelemetryHelper& telemetryHelper)
        {
            // Mock implementation
            struct LogTelemetry
            {
                LogTelemetry(StoragePickersTelemetryHelper&) {}
                void Stop(StoragePickersTelemetryHelper&, bool) {}
            };
            return LogTelemetry{ telemetryHelper };
        }
    };
}

// create a class in namespace that has method Microsoft::Windows::Storage::Pickers::Feature_StoragePickers::IsEnabled()
namespace Microsoft::Windows::Storage::Pickers
{
    struct Feature_StoragePickers
    {
        static bool IsEnabled()
        {
            return true;
        }
    };
}
