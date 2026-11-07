// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <Windows.h>
#include <unknwn.h>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <cwchar>
#include <string>
#include <string_view>
#include <thread>
#include <wil/cppwinrt.h>
#include <wil/resource.h>
#include <wil/result_macros.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Microsoft.Windows.Storage.h>

namespace Storage = winrt::Microsoft::Windows::Storage;

namespace
{
    constexpr PCWSTR c_resourcePublisher{ L"TestApplicationDataContext_ResourcePublisher" };
    constexpr PCWSTR c_resourceProduct{ L"ResourceProduct" };
    constexpr PCWSTR c_apiPublisher{ L"TestApplicationDataContext_ApiPublisher" };
    constexpr PCWSTR c_apiProduct{ L"ApiProduct" };
    constexpr HRESULT c_alreadyAssigned{ HRESULT_FROM_WIN32(ERROR_ALREADY_ASSIGNED) };

    template <typename Callback>
    void ExpectFailure(HRESULT expected, Callback&& callback)
    {
        HRESULT actual{ S_OK };
        try
        {
            callback();
        }
        catch (...)
        {
            actual = winrt::to_hresult();
        }
        THROW_HR_IF_MSG(E_FAIL, actual != expected, "Expected 0x%08X, got 0x%08X", expected, actual);
    }

    Storage::ApplicationData CheckContext(Storage::IApplicationDataStatics2 const& explicitStatics,
                                         Storage::IApplicationDataStatics3 const& contextStatics,
                                         PCWSTR publisher, PCWSTR product)
    {
        const auto actual{ contextStatics.GetForUnpackaged() };
        const auto expected{ explicitStatics.GetForUnpackaged(publisher, product) };
        THROW_HR_IF_MSG(E_FAIL, actual.LocalPath() != expected.LocalPath(), "Unexpected local path");
        THROW_HR_IF_MSG(E_FAIL, actual.TemporaryPath() != expected.TemporaryPath(), "Unexpected temporary path");
        return actual;
    }

    void CheckSetter(Storage::IApplicationDataStatics2 const& explicitStatics,
                     Storage::IApplicationDataStatics3 const& contextStatics)
    {
        constexpr PCWSTR invalidNames[]{ L"", L".", L"..", L"foo/bar", L"foo\\bar", L"foo@bar", L"lpt1", L"lpt1.invalid" };
        for (const auto invalidName : invalidNames)
        {
            ExpectFailure(E_INVALIDARG, [&] { contextStatics.SetContextForUnpackaged(invalidName, c_apiProduct); });
            ExpectFailure(E_INVALIDARG, [&] { contextStatics.SetContextForUnpackaged(c_apiPublisher, invalidName); });
        }

        contextStatics.SetContextForUnpackaged(c_apiPublisher, c_apiProduct);
        auto first{ CheckContext(explicitStatics, contextStatics, c_apiPublisher, c_apiProduct) };
        auto second{ CheckContext(explicitStatics, contextStatics, c_apiPublisher, c_apiProduct) };
        first.Close();
        THROW_HR_IF(E_FAIL, second.LocalPath().empty());
        ExpectFailure(c_alreadyAssigned, [&] { contextStatics.SetContextForUnpackaged(c_apiPublisher, c_apiProduct); });
        ExpectFailure(c_alreadyAssigned, [&] { contextStatics.SetContextForUnpackaged(L"AnotherPublisher", L"AnotherProduct"); });
        CheckContext(explicitStatics, contextStatics, c_apiPublisher, c_apiProduct);
    }

    void CheckConcurrency(Storage::IApplicationDataStatics2 const& explicitStatics,
                          Storage::IApplicationDataStatics3 const& contextStatics)
    {
        constexpr size_t count{ 8 };
        std::array<winrt::hstring, count> publishers;
        std::array<winrt::hstring, count> products;
        std::array<winrt::hstring, count + 1> paths;
        std::array<HRESULT, count> setterResults{};
        std::array<HRESULT, count * 2> workerResults{};
        std::array<std::thread, count * 2> workers;
        for (size_t i{}; i < count; ++i)
        {
            publishers[i] = L"TestApplicationDataContext_Publisher" + std::to_wstring(i);
            products[i] = L"Product" + std::to_wstring(i);
            paths[i] = explicitStatics.GetForUnpackaged(publishers[i], products[i]).LocalPath();
        }
        paths[count] = explicitStatics.GetForUnpackaged(c_resourcePublisher, c_resourceProduct).LocalPath();
        const auto checkSnapshot{ [&](bool allowResourceContext)
        {
            const auto path{ contextStatics.GetForUnpackaged().LocalPath() };
            const auto candidates{ count + (allowResourceContext ? 1 : 0) };
            bool knownPath{};
            for (size_t i{}; i < candidates; ++i)
            {
                knownPath = knownPath || (path == paths[i]);
            }
            THROW_HR_IF_MSG(E_FAIL, !knownPath, "Mixed or stale publisher/product context");
        } };

        wil::unique_event start;
        start.create(wil::EventOptions::ManualReset);
        auto joinWorkers{ wil::scope_exit([&]
        {
            start.SetEvent();
            for (auto& worker : workers)
            {
                if (worker.joinable())
                {
                    worker.join();
                }
            }
        }) };
        for (size_t i{}; i < count; ++i)
        {
            workers[i] = std::thread([&, i]
            {
                try
                {
                    winrt::init_apartment();
                    auto uninitialize{ wil::scope_exit([] { winrt::uninit_apartment(); }) };
                    start.wait();
                    try
                    {
                        contextStatics.SetContextForUnpackaged(publishers[i], products[i]);
                    }
                    catch (...)
                    {
                        setterResults[i] = winrt::to_hresult();
                    }
                    for (size_t read{}; read < 16; ++read)
                    {
                        checkSnapshot(false);
                    }
                }
                catch (...)
                {
                    workerResults[i] = winrt::to_hresult();
                }
            });
            workers[count + i] = std::thread([&, i]
            {
                try
                {
                    winrt::init_apartment();
                    auto uninitialize{ wil::scope_exit([] { winrt::uninit_apartment(); }) };
                    start.wait();
                    for (size_t read{}; read < 64; ++read)
                    {
                        checkSnapshot(true);
                    }
                }
                catch (...)
                {
                    workerResults[count + i] = winrt::to_hresult();
                }
            });
        }
        start.SetEvent();
        joinWorkers.reset();

        size_t winners{};
        for (size_t i{}; i < count; ++i)
        {
            THROW_IF_FAILED(workerResults[i]);
            THROW_IF_FAILED(workerResults[count + i]);
            if (setterResults[i] == S_OK)
            {
                ++winners;
                CheckContext(explicitStatics, contextStatics, publishers[i].c_str(), products[i].c_str());
            }
            else
            {
                THROW_HR_IF(E_FAIL, setterResults[i] != c_alreadyAssigned);
            }
        }
        THROW_HR_IF_MSG(E_FAIL, winners != 1, "Exactly one setter must succeed");
    }
}

int wmain(int argc, wchar_t** argv)
{
    try
    {
        THROW_HR_IF(E_INVALIDARG, argc != 4);
        winrt::init_apartment();
        auto uninitialize{ wil::scope_exit([] { winrt::uninit_apartment(); }) };
        wil::unique_hmodule module{ ::LoadLibraryExW(argv[2], nullptr, LOAD_WITH_ALTERED_SEARCH_PATH) };
        THROW_LAST_ERROR_IF(!module);
        using GetFactory = HRESULT(__stdcall*)(HSTRING, void**);
        const auto getFactory{ reinterpret_cast<GetFactory>(::GetProcAddress(module.get(), "DllGetActivationFactory")) };
        THROW_LAST_ERROR_IF(!getFactory);
        winrt::Windows::Foundation::IActivationFactory factory{ nullptr };
        const winrt::hstring className{ L"Microsoft.Windows.Storage.ApplicationData" };
        winrt::check_hresult(getFactory(static_cast<HSTRING>(winrt::get_abi(className)), winrt::put_abi(factory)));
        auto explicitStatics{ factory.as<Storage::IApplicationDataStatics2>() };
        const std::wstring_view scenario{ argv[1] };
        if (scenario == L"disabled")
        {
            ExpectFailure(E_NOINTERFACE, [&] { factory.as<Storage::IApplicationDataStatics3>(); });
            const auto independent{ explicitStatics.GetForUnpackaged(c_apiPublisher, c_apiProduct) };
            THROW_HR_IF(E_FAIL, independent.LocalPath().empty());
            return 0;
        }
        auto contextStatics{ factory.as<Storage::IApplicationDataStatics3>() };

        if (scenario == L"resources")
        {
            explicitStatics.GetForUnpackaged(c_apiPublisher, c_apiProduct);
            CheckContext(explicitStatics, contextStatics, c_resourcePublisher, c_resourceProduct);
        }
        else if (scenario == L"setter")
        {
            CheckSetter(explicitStatics, contextStatics);
        }
        else if (scenario == L"late-set")
        {
            const auto prior{ CheckContext(explicitStatics, contextStatics, c_resourcePublisher, c_resourceProduct) };
            const auto priorPath{ prior.LocalPath() };
            contextStatics.SetContextForUnpackaged(c_apiPublisher, c_apiProduct);
            CheckContext(explicitStatics, contextStatics, c_apiPublisher, c_apiProduct);
            THROW_HR_IF(E_FAIL, prior.LocalPath() != priorPath);
            const auto independent{ explicitStatics.GetForUnpackaged(c_resourcePublisher, c_resourceProduct) };
            THROW_HR_IF(E_FAIL, independent.LocalPath() != priorPath);
        }
        else if (scenario == L"failure")
        {
            const auto expected{ static_cast<HRESULT>(std::wcstoul(argv[3], nullptr, 16)) };
            explicitStatics.GetForUnpackaged(c_apiPublisher, c_apiProduct);
            ExpectFailure(expected, [&] { contextStatics.GetForUnpackaged(); });
            contextStatics.SetContextForUnpackaged(c_apiPublisher, c_apiProduct);
            CheckContext(explicitStatics, contextStatics, c_apiPublisher, c_apiProduct);
        }
        else if (scenario == L"concurrent")
        {
            CheckConcurrency(explicitStatics, contextStatics);
        }
        else if (scenario == L"lifetime")
        {
            contextStatics.SetContextForUnpackaged(c_apiPublisher, c_apiProduct);
            contextStatics = nullptr;
            explicitStatics = nullptr;
            factory = nullptr;
            winrt::clear_factory_cache();
            using CanUnload = HRESULT(__stdcall*)();
            const auto canUnload{ reinterpret_cast<CanUnload>(::GetProcAddress(module.get(), "DllCanUnloadNow")) };
            THROW_LAST_ERROR_IF(!canUnload);
            THROW_HR_IF_MSG(E_FAIL, canUnload() != S_FALSE, "Context must retain the runtime module");
            winrt::check_hresult(getFactory(static_cast<HSTRING>(winrt::get_abi(className)), winrt::put_abi(factory)));
            CheckContext(factory.as<Storage::IApplicationDataStatics2>(), factory.as<Storage::IApplicationDataStatics3>(),
                         c_apiPublisher, c_apiProduct);
        }
        else
        {
            THROW_HR(E_INVALIDARG);
        }
        return 0;
    }
    catch (...)
    {
        const auto error{ winrt::to_hresult() };
        std::fwprintf(stderr, L"ApplicationData context scenario failed: 0x%08X\n", static_cast<unsigned int>(error));
        return static_cast<int>(error);
    }
}
