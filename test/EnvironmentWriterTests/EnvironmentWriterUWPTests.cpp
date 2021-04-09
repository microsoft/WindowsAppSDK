// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "EnvironmentWriterUWPTests.h"
#include "EnvironmentVariableHelper.h"
#include "TestSetupAndTeardownHelper.h"

using namespace winrt::Microsoft::ProjectReunion;

namespace ProjectReunionEnvironmentWriterTests
{
    void EnvironmentWriterUWPTests::UWPTestGetForProcess()
    {
        EnvironmentWriter environmentWriter{ EnvironmentWriter::GetForProcess() };
        VERIFY_IS_NOT_NULL(environmentWriter);
    }

    void EnvironmentWriterUWPTests::UWPTestGetForUser()
    {
        EnvironmentWriter environmentWriter{ EnvironmentWriter::GetForUser() };
        VERIFY_IS_NOT_NULL(environmentWriter);
    }

    void EnvironmentWriterUWPTests::UWPTestGetForMachine()
    {
        EnvironmentWriter environmentWriter{ EnvironmentWriter::GetForMachine() };
        VERIFY_IS_NOT_NULL(environmentWriter);
    }

    void EnvironmentWriterUWPTests::UWPTestSetEnvironmentVariableForProcess()
    {
        EnvironmentWriter environmentWriter = EnvironmentWriter::GetForProcess();
        VERIFY_NO_THROW(environmentWriter.SetEnvironmentVariable(c_evKeyName, c_evValueName));

        std::wstring writtenEV = GetEnvironmentVariableForProcess(c_evKeyName);
        VERIFY_ARE_EQUAL(std::wstring(c_evValueName), writtenEV);

        // Update the environment variable
        VERIFY_NO_THROW(environmentWriter.SetEnvironmentVariable(c_evKeyName, c_evValueName2));
        writtenEV = GetEnvironmentVariableForProcess(c_evKeyName);
        VERIFY_ARE_EQUAL(std::wstring(c_evValueName2), writtenEV);


        // Remove the value
        // setting the value to empty is the same as deleting the variable
        VERIFY_NO_THROW(environmentWriter.SetEnvironmentVariable(c_evKeyName, L""));
        VERIFY_ARE_EQUAL(0, ::GetEnvironmentVariable(c_evKeyName, nullptr, 0));
        VERIFY_ARE_EQUAL(ERROR_ENVVAR_NOT_FOUND, GetLastError());
    }

    void EnvironmentWriterUWPTests::UWPTestSetEnvironmentVariableForUser()
    {
        EnvironmentWriter environmentMananger = EnvironmentWriter::GetForUser();
        VERIFY_THROWS(environmentMananger.SetEnvironmentVariable(c_evKeyName, c_evValueName), winrt::hresult_access_denied);
    }

    void EnvironmentWriterUWPTests::UWPTestSetEnvironmentVariableForMachine()
    {
        EnvironmentWriter environmentMananger = EnvironmentWriter::GetForMachine();
        VERIFY_THROWS(environmentMananger.SetEnvironmentVariable(c_evKeyName, c_evValueName), winrt::hresult_access_denied);
    }

    void EnvironmentWriterUWPTests::UWPTestAppendToPathForProcess()
    {
        std::wstring pathToRestore = GetEnvironmentVariableForProcess(c_pathName);
        std::wstring pathToManipulate(pathToRestore);
        EnvironmentWriter environmentWriter = EnvironmentWriter::GetForProcess();

        VERIFY_NO_THROW(environmentWriter.AppendToPath(c_evValueName));

        // Current path should have the semi-colon
        std::wstring currentPath = GetEnvironmentVariableForProcess(c_pathName);
        if (pathToManipulate.back() != L';')
        {
            pathToManipulate += L";";
        }

        pathToManipulate += c_evValueName;
        pathToManipulate += L";";

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        RestoreProcessPath(pathToRestore);
    }

    void EnvironmentWriterUWPTests::UWPTestAppendToPathForUser()
    {
        EnvironmentWriter environmentWriter = EnvironmentWriter::GetForUser();
        VERIFY_THROWS(environmentWriter.AppendToPath(c_evValueName), winrt::hresult_access_denied);
    }

    void EnvironmentWriterUWPTests::UWPTestAppendToPathForMachine()
    {
        EnvironmentWriter environmentWriter = EnvironmentWriter::GetForMachine();
        VERIFY_THROWS(environmentWriter.AppendToPath(c_evValueName), winrt::hresult_access_denied);
    }

    void EnvironmentWriterUWPTests::UWPTestRemoveFromPathForProcess()
    {
        // Get the PATH for Process.  Don't append any semi-colon
        std::wstring originalPath = GetEnvironmentVariableForProcess(c_pathName);
        std::wstring pathToRestore(originalPath);
        std::wstring pathToManipulate(originalPath);
        EnvironmentWriter environmentWriter = EnvironmentWriter::GetForProcess();

        // This will append c_evValueName to the path with a semi-colon.
        VERIFY_NO_THROW(environmentWriter.AppendToPath(c_evValueName));
        if (pathToManipulate.back() != L';')
        {
            pathToManipulate += L';';
        }

        pathToManipulate += c_evValueName;
        pathToManipulate += L";";

        originalPath = GetEnvironmentVariableForProcess(c_pathName);

        VERIFY_ARE_EQUAL(originalPath, pathToManipulate);

        std::wstring pathPart(originalPath, 0, originalPath.find(L';') + 1);
        environmentWriter.RemoveFromPath(pathPart);
        originalPath = GetEnvironmentVariableForProcess(c_pathName);

        pathToManipulate.erase(pathToManipulate.rfind(pathPart), pathPart.length());

        VERIFY_ARE_EQUAL(originalPath, pathToManipulate);

        VERIFY_NO_THROW(environmentWriter.RemoveFromPath(L"I do not exist"));

        VERIFY_ARE_EQUAL(originalPath, pathToManipulate);

        RestoreProcessPath(pathToRestore);
    }

    void EnvironmentWriterUWPTests::UWPTestRemoveFromPathForUser()
    {
        EnvironmentWriter environmentWriter = EnvironmentWriter::GetForUser();
        VERIFY_THROWS(environmentWriter.AppendToPath(c_evValueName), winrt::hresult_access_denied);
    }

    void EnvironmentWriterUWPTests::UWPTestRemoveFromPathForMachine()
    {
        EnvironmentWriter environmentWriter = EnvironmentWriter::GetForMachine();
        VERIFY_THROWS(environmentWriter.AppendToPath(c_evValueName), winrt::hresult_access_denied);        
    }

}
