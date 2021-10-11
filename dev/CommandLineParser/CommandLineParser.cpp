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
}
