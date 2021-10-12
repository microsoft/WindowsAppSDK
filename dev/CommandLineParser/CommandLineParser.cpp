#include "pch.h"
#include "CommandLineParser.h"
#include "Microsoft.Windows.System.CommandLineParser.g.cpp"

namespace winrt::Microsoft::Windows::System::implementation
{
    CommandLineParser::CommandLineParser(hstring const& arguments)
        : m_Arguments(arguments)
    {}

    void CommandLineParser::AddArguments(hstring const& arguments)
    {
        if ((m_Arguments.back() != L' ') ||
            (arguments.front() != L' '))
        {
            m_Arguments.append(L" ");
        }

        m_Arguments.append(arguments);
    }

    IMapView<hstring, hstring> CommandLineParser::Parse()
    {
        return m_ParsedArguments;
    }

    IMapView<hstring, hstring> CommandLineParser::Parse()
    {
        if (m_Arguments.empty())
        {
            return {};
        }

        std::unique_ptr<wchar_t> argumentsToParse = new wchar_t[m_Arguments.size() + 1];
        wcscpy(argumentsToParse, m_Arguments.c_str());

        for (auto environmentVariableOffset = argumentsToParse; *environmentVariableOffset; environmentVariableOffset += wcslen(environmentVariableOffset) + 1)
        {
            auto delimiter{ wcschr(environmentVariableOffset, L' ') };
            FAIL_FAST_HR_IF_NULL(E_UNEXPECTED, delimiter);
            std::wstring switchName(environmentVariableOffset, 0, delimiter - environmentVariableOffset);
            auto switchValue{ delimiter + 1 };
            m_ParsedArguments.insert(variableName, variableValue);
        }

        return m_ParsedArguments.GetView();
    }

    void CommandLineParser::Reset()
    {
        m_Arguments.clear();
        m_ParsedArguments.clear();
    }
}
