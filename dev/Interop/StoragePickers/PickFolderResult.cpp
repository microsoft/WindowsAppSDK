#include "pch.h"
#include "PickFolderResult.h"
#include "Microsoft.Windows.Storage.Pickers.PickFolderResult.g.cpp"

namespace winrt::Microsoft::Windows::Storage::Pickers::implementation
{
    PickFolderResult::PickFolderResult(winrt::hstring const& path)
        : m_path(path)
    {
    }

    hstring PickFolderResult::Path()
    {
        return m_path;
    }
}
