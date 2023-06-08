// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#include <pch.h>
#include "ValueMarshaling.h"
#include "RedirectionRequest.h"
#include "ExtensionContract.h"
#include "Association.h"

namespace winrt::Microsoft::Windows::AppLifecycle::implementation
{
    void RedirectionRequest::Open(const std::wstring& name)
    {
        m_data.Open(name);
        m_name = name;
    }

    void RedirectionRequest::MarshalArguments(Microsoft::Windows::AppLifecycle::AppActivationArguments const& args)
    {
        auto internalArgs = args.Data().try_as<IInternalValueMarshalable>();
        bool supportInternalValueMarshaling = (internalArgs != nullptr);
        
        ULONG streamSize{ 0 };
        std::wstring uri;
        com_ptr<::IUnknown> unk{ args.as<::IUnknown>() };
        const auto uuidofArgs = guid_of<AppActivationArguments>();

        if (supportInternalValueMarshaling)
        {
            uri = internalArgs->Serialize().AbsoluteUri().c_str();

            // Ensure supportInternalValueMarshaling's data is accounted for in the size.
            streamSize = static_cast<ULONG>((uri.length() + 1) * sizeof(wchar_t));
        }
        else
        {
            THROW_IF_FAILED(CoGetMarshalSizeMax(&streamSize, uuidofArgs, unk.get(), MSHCTX_LOCAL, nullptr, MSHLFLAGS_NORMAL));   
        }

        // Add space for the marshaling type data and resize the backing storage.
        m_data.Resize(sizeof(bool) + streamSize);

        // Mark payload with marshaling type information.
        bool* marshalingMarker = reinterpret_cast<bool*>(m_data.Get());
        *marshalingMarker = supportInternalValueMarshaling;

        uint8_t* streamStart = (m_data.Get() + sizeof(bool));

        if (supportInternalValueMarshaling)
        {
            THROW_IF_FAILED(StringCchCopy(reinterpret_cast<LPWSTR>(streamStart), (uri.length() + 1), uri.c_str()));
        }
        else
        {
            // Use COM stream marshaling.
            com_ptr<IStream> stream;
            THROW_IF_FAILED(CreateStreamOnHGlobal(nullptr, TRUE, stream.put()));
            THROW_IF_FAILED(CoMarshalInterface(stream.get(), uuidofArgs, unk.get(), MSHCTX_LOCAL, nullptr, MSHLFLAGS_NORMAL));

            const LARGE_INTEGER headOffset{};
            auto resetStreamOnExit = wil::scope_exit([&stream, &headOffset]
            {
                stream->Seek(headOffset, STREAM_SEEK_SET, nullptr);
                CoReleaseMarshalData(stream.get());
            });

            THROW_IF_FAILED(stream->Seek(headOffset, STREAM_SEEK_SET, nullptr));

            STATSTG stats{};
            THROW_IF_FAILED(stream->Stat(&stats, STATFLAG_NONAME));
            THROW_HR_IF(E_FAIL, static_cast<ULONG>(stats.cbSize.QuadPart) > streamSize);

            ULONG bytesRead{ 0 };
            THROW_IF_FAILED(stream->Read(streamStart, static_cast<ULONG>(stats.cbSize.QuadPart), &bytesRead));
            resetStreamOnExit.release();
        }
    }

    Microsoft::Windows::AppLifecycle::AppActivationArguments RedirectionRequest::UnmarshalArguments()
    {
        // The first byte holds data about the marshaling type to use.
        uint8_t* streamStart = (m_data.Get() + sizeof(bool));
        ULONG streamSize = (static_cast<ULONG>(m_data.Size()) - sizeof(bool));

        bool supportInternalValueMarshaling = *(reinterpret_cast<bool*>(m_data.Get()));
        if (supportInternalValueMarshaling)
        {
            std::wstring_view uri_data{ reinterpret_cast<wchar_t*>(streamStart) };

            ExtendedActivationKind kind;
            winrt::Windows::Foundation::IInspectable args;
            std::tie(kind, args) = DecodeActivatedEventArgs(winrt::Windows::Foundation::Uri{ uri_data });
            return make<AppActivationArguments>(args.as<IActivatedEventArgs>());
        }
        else
        {
            // Use COM stream marshaling.
            com_ptr<IStream> stream;
            THROW_IF_FAILED(CreateStreamOnHGlobal(nullptr, TRUE, stream.put()));

            ULONG bytesWritten = 0;
            THROW_IF_FAILED(stream->Write(streamStart, streamSize, &bytesWritten));

            const LARGE_INTEGER headOffset{};
            THROW_IF_FAILED(stream->Seek(headOffset, STREAM_SEEK_SET, nullptr));

            com_ptr<::IUnknown> unk;
            THROW_IF_FAILED(CoUnmarshalInterface(stream.get(), guid_of<AppActivationArguments>(), unk.put_void()));
            return unk.as<winrt::Microsoft::Windows::AppLifecycle::AppActivationArguments>();
        }
    }
}
