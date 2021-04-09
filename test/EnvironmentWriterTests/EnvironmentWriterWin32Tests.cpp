// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "EnvironmentWriterWin32Tests.h"
#include "EnvironmentVariableHelper.h"

using namespace winrt::Microsoft::ProjectReunion;

namespace ProjectReunionEnvironmentWriterTests
{
    void EnvironmentWriterWin32Tests::TestGetForProcess()
    {
        EnvironmentWriter environmentWriter{ EnvironmentWriter::GetForProcess() };
        VERIFY_IS_NOT_NULL(environmentWriter);
    }

    void EnvironmentWriterWin32Tests::TestGetForUser()
    {
        EnvironmentWriter environmentWriter{ EnvironmentWriter::GetForUser() };
        VERIFY_IS_NOT_NULL(environmentWriter);
    }

    void EnvironmentWriterWin32Tests::TestGetForMachine()
    {
        EnvironmentWriter environmentWriter{ EnvironmentWriter::GetForMachine() };
        VERIFY_IS_NOT_NULL(environmentWriter);
    }

    void EnvironmentWriterWin32Tests::TestSetEnvironmentVariableForProcess()
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
    }

    void EnvironmentWriterWin32Tests::TestSetEnvironmentVariableForUser()
    {
        EnvironmentWriter environmentWriter = EnvironmentWriter::GetForUser();
        VERIFY_NO_THROW(environmentWriter.SetEnvironmentVariable(c_evKeyName, c_evValueName));

        std::wstring writtenEV = GetEnvironmentVariableForUser(c_evKeyName);
        VERIFY_ARE_EQUAL(std::wstring(c_evValueName), writtenEV);

        // Update the environment variable
        VERIFY_NO_THROW(environmentWriter.SetEnvironmentVariable(c_evKeyName, c_evValueName2));
        writtenEV = GetEnvironmentVariableForUser(c_evKeyName);
        VERIFY_ARE_EQUAL(std::wstring(c_evValueName2), writtenEV);


        // Remove the value
        // setting the value to empty is the same as deleting the variable
        VERIFY_NO_THROW(environmentWriter.SetEnvironmentVariable(c_evKeyName, L""));
        VERIFY_ARE_EQUAL(L"", GetEnvironmentVariableForUser(c_evKeyName));
    }

    void EnvironmentWriterWin32Tests::TestSetEnvironmentVariableForMachine()
    {
        EnvironmentWriter environmentWriter = EnvironmentWriter::GetForMachine();

        if (!IsElevated())
        {
            VERIFY_THROWS(environmentWriter.SetEnvironmentVariable(c_evKeyName, c_evValueName), winrt::hresult_access_denied);
            return;
        }

        VERIFY_NO_THROW(environmentWriter.SetEnvironmentVariable(c_evKeyName, c_evValueName));

        std::wstring writtenEV = GetEnvironmentVariableForMachine(c_evKeyName);
        VERIFY_ARE_EQUAL(std::wstring(c_evValueName), writtenEV);

        // Update the environment variable
        VERIFY_NO_THROW(environmentWriter.SetEnvironmentVariable(c_evKeyName, c_evValueName2));
        writtenEV = GetEnvironmentVariableForMachine(c_evKeyName);
        VERIFY_ARE_EQUAL(std::wstring(c_evValueName2), writtenEV);


        // Remove the value
        // setting the value to empty is the same as deleting the variable
        VERIFY_NO_THROW(environmentWriter.SetEnvironmentVariable(c_evKeyName, L""));
        VERIFY_ARE_EQUAL(L"", GetEnvironmentVariableForMachine(c_evKeyName));
    }

    void EnvironmentWriterWin32Tests::TestAppendToPathForProcess()
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

    void EnvironmentWriterWin32Tests::TestAppendToPathForUser()
    {
        std::wstring pathToRestore = GetEnvironmentVariableForUser(c_pathName);
        std::wstring pathToManipulate(pathToRestore);
        EnvironmentWriter environmentWriter = EnvironmentWriter::GetForUser();

        VERIFY_NO_THROW(environmentWriter.AppendToPath(c_evValueName));

        // Current path should have the semi-colon
        std::wstring currentPath = GetEnvironmentVariableForUser(c_pathName);
        if (pathToManipulate.back() != L';')
        {
            pathToManipulate += L";";
        }

        pathToManipulate += c_evValueName;
        pathToManipulate += L";";

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        RestoreUserPath(pathToRestore);
    }

    void EnvironmentWriterWin32Tests::TestAppendToPathForMachine()
    {
        std::wstring pathToRestore = GetEnvironmentVariableForMachine(c_pathName);
        std::wstring pathToManipulate(pathToRestore);
        EnvironmentWriter environmentWriter = EnvironmentWriter::GetForMachine();

        if (!IsElevated())
        {
            VERIFY_THROWS(environmentWriter.AppendToPath(c_evValueName), winrt::hresult_access_denied);
            return;
        }

        VERIFY_NO_THROW(environmentWriter.AppendToPath(c_evValueName));

        // Current path should have the semi-colon
        std::wstring currentPath = GetEnvironmentVariableForMachine(c_pathName);
        if (pathToManipulate.back() != L';')
        {
            pathToManipulate += L";";
        }

        pathToManipulate += c_evValueName;
        pathToManipulate += L";";;

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        RestoreMachinePath(pathToRestore);
    }

    void EnvironmentWriterWin32Tests::TestRemoveFromPathForProcess()
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

    void EnvironmentWriterWin32Tests::TestRemoveFromPathForUser()
    {
        // Get the PATH for Process.  Don't append any semi-colon
        std::wstring originalPath = GetEnvironmentVariableForUser(c_pathName);
        std::wstring pathToRestore(originalPath);
        std::wstring pathToManipulate(originalPath);
        EnvironmentWriter environmentWriter = EnvironmentWriter::GetForUser();

        // This will append c_evValueName to the path with a semi-colon.
        VERIFY_NO_THROW(environmentWriter.AppendToPath(c_evValueName));
        if (pathToManipulate.back() != L';')
        {
            pathToManipulate += L';';
        }

        pathToManipulate += c_evValueName;
        pathToManipulate += L";";

        originalPath = GetEnvironmentVariableForUser(c_pathName);

        VERIFY_ARE_EQUAL(originalPath, pathToManipulate);

        std::wstring pathPart(originalPath, 0, originalPath.find(L';') + 1);
        environmentWriter.RemoveFromPath(pathPart);
        originalPath = GetEnvironmentVariableForUser(c_pathName);

        pathToManipulate.erase(pathToManipulate.rfind(pathPart), pathPart.length());

        VERIFY_ARE_EQUAL(originalPath, pathToManipulate);

        VERIFY_NO_THROW(environmentWriter.RemoveFromPath(L"I do not exist"));

        VERIFY_ARE_EQUAL(originalPath, pathToManipulate);

        RestoreUserPath(pathToRestore);
    }

    void EnvironmentWriterWin32Tests::TestRemoveFromPathForMachine()
    {
        // Get the PATH for Process.  Don't append any semi-colon
        std::wstring originalPath = GetEnvironmentVariableForMachine(c_pathName);
        std::wstring pathToRestore(originalPath);
        std::wstring pathToManipulate(originalPath);
        EnvironmentWriter environmentWriter = EnvironmentWriter::GetForMachine();

        if (!IsElevated())
        {
            VERIFY_THROWS(environmentWriter.AppendToPath(c_evValueName), winrt::hresult_access_denied);
            return;
        }


        // This will append c_evValueName to the path with a semi-colon.
        VERIFY_NO_THROW(environmentWriter.AppendToPath(c_evValueName));
        if (pathToManipulate.back() != L';')
        {
            pathToManipulate += L';';
        }

        pathToManipulate += c_evValueName;
        pathToManipulate += L";";

        originalPath = GetEnvironmentVariableForMachine(c_pathName);

        VERIFY_ARE_EQUAL(originalPath, pathToManipulate);

        std::wstring pathPart(originalPath, 0, originalPath.find(L';') + 1);
        environmentWriter.RemoveFromPath(pathPart);
        originalPath = GetEnvironmentVariableForMachine(c_pathName);

        pathToManipulate.erase(pathToManipulate.rfind(pathPart), pathPart.length());

        VERIFY_ARE_EQUAL(originalPath, pathToManipulate);

        VERIFY_NO_THROW(environmentWriter.RemoveFromPath(L"I do not exist"));

        VERIFY_ARE_EQUAL(originalPath, pathToManipulate);

        RestoreMachinePath(pathToRestore);
    }
}
