#include "pch.h"
#include "StoragePickersImpl.h"
#include "ShObjIdl.h"

using namespace winrt;

namespace StoragePickersImpl {

    winrt::hstring FormatExtensionWithWildcard(winrt::hstring extension)
    {
        if (!extension.empty() && extension[0] == L'*')
        {
            return extension;
        }
        else
        {
            return L"*" + extension;
        }
    }

    winrt::hstring JoinExtensions(winrt::Windows::Foundation::Collections::IVectorView<winrt::hstring> extensions)
    {
        winrt::hstring result;
        bool first = true;
        for (const auto& ext : extensions)
        {
            if (first)
            {
                result = FormatExtensionWithWildcard(ext);
                first = false;
            }
            else
            {
                result = result + L";" + FormatExtensionWithWildcard(ext);
            }
        }
        return result;
    }

    /// <summary>
    /// Capture and processing pickers filter inputs and convert them into Common Item Dialog's accepting type, for FileOpenPicker
    /// </summary>
    /// <param name="buffer">temp buffer to hold dynamically transformed strings</param>
    /// <param name="filters">winrt style filters</param>
    void PickerParameters::CaptureFilterSpec(winrt::Windows::Foundation::Collections::IVectorView<winrt::hstring> filters)
    {
        size_t resultSize = filters.Size() + 1;   // A vector input will have unioned "All Files" category appended.
        FileTypeFilterData.clear();
        FileTypeFilterData.reserve(resultSize * static_cast<size_t>(2));

        std::wstring allFilesExtensionList;
        for (const auto& filter : filters)
        {
            auto ext = FormatExtensionWithWildcard(filter);
            FileTypeFilterData.push_back(L"");
            FileTypeFilterData.push_back(ext);

            allFilesExtensionList.reserve(allFilesExtensionList.length() + ext.size() + 1);
            allFilesExtensionList += ext;
            allFilesExtensionList += L";";
        }

        if (!allFilesExtensionList.empty())
        {
            allFilesExtensionList.pop_back(); // Remove the last semicolon
        }

        if (filters.Size() == 0)
        {
            // when filters not defined, set filter to All Files *.*
            FileTypeFilterData.push_back(L"");
            FileTypeFilterData.push_back(L"*");
        }
        else if (filters.Size() == 1 && allFilesExtensionList == L"*")
        {
            // when there're only one filter "*", set filter to All Files *.* (override the values pushed above)
            FileTypeFilterData[0] = L"";
            FileTypeFilterData[1] = L"*";
            resultSize = 1;
        }
        else
        {
            FileTypeFilterData.push_back(L"");
            FileTypeFilterData.push_back(allFilesExtensionList.c_str());
        }

        FileTypeFilterPara.clear();
        FileTypeFilterPara.reserve(resultSize);
        for (size_t i = 0; i < resultSize; i++)
        {
            FileTypeFilterPara.push_back({ FileTypeFilterData.at(i * 2).c_str(), FileTypeFilterData.at(i * 2 + 1).c_str() });
        }
    }

    /// <summary>
    /// Capture and processing pickers filter inputs and convert them into Common Item Dialog's accepting type, for FileSavePicker
    /// </summary>
    /// <param name="buffer">temp buffer to hold dynamically transformed strings</param>
    /// <param name="filters">winrt style filters</param>
    void PickerParameters::CaptureFilterSpec(winrt::Windows::Foundation::Collections::IMapView<winrt::hstring, winrt::Windows::Foundation::Collections::IVector<hstring>> filters)
    {
        size_t resultSize = filters.Size();
        FileTypeFilterData.clear();
        FileTypeFilterData.reserve(filters.Size() * static_cast<size_t>(2));

        for (const auto& filter : filters)
        {
            FileTypeFilterData.push_back(filter.Key());
            auto extensionList = JoinExtensions(filter.Value().GetView());
            FileTypeFilterData.push_back(extensionList);
        }

        if (filters.Size() == 0)
        {
            // when filters not defined, set filter to All Files *.*
            FileTypeFilterData.push_back(L"");
            FileTypeFilterData.push_back(L"*");
            resultSize = 1;
        }

        FileTypeFilterPara.clear();
        FileTypeFilterPara.reserve(resultSize);
        for (size_t i = 0; i < resultSize; i++)
        {
            FileTypeFilterPara.push_back({ FileTypeFilterData.at(i * 2).c_str(), FileTypeFilterData.at(i * 2 + 1).c_str() });
        }
    }

}
