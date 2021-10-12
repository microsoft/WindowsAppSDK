#pragma once
#include "Microsoft.Windows.System.CommandLineParser.g.h"
#include <string>
#include <map>

using namespace winrt::Windows::Foundation::Collections;

namespace winrt::Microsoft::Windows::System::implementation
{
    struct CommandLineParser : CommandLineParserT<CommandLineParser>
    {
        CommandLineParser() = default;

        CommandLineParser(hstring const& arguments);
        void AddArguments(hstring const& arguments);

        IMapView<hstring, hstring> GetParsedArguments();
        IMapView<hstring, hstring> Parse();
        void Reset();

    private:
        std::wstring m_Arguments{};
        std::Map<hstring, hstring> m_ParsedArguments{};

    };
}
namespace winrt::Microsoft::Windows::System::factory_implementation
{
    struct CommandLineParser : CommandLineParserT<CommandLineParser, implementation::CommandLineParser>
    {
    };
}
