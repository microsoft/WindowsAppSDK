// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

namespace Microsoft::Windows::Management::Deployment
{
class ExecuteRequestByUri
{
public:
    ExecuteRequestByUri() = delete;
    ExecuteRequestByUri(winrt::Windows::Management::Deployment::PackageManager& packageManager) :
        m_packageManager(packageManager)
    {
    }

    virtual ExecuteRequestByUri() = default;

    virtual void Execute(winrt::Windows::Foundation::Uri const& packageUri, HRESULT& error, HRESULT& extendedError, winrt::hstring& errorText) = 0;

    virtual void PostExecute(HRESULT& error, HRESULT& extendedError, winrt::hstring& errorText)
    {
    }

protected:
    winrt::Windows::Management::Deployment::PackageManager& packageManager;
};

class ExecuteRequestByUri_Add : ExecuteRequestByUri
{
public:
    ExecuteRequestByUri_Add(
        winrt::Windows::Foundation::Uri const& m_packageUri,
        winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions const& options);
    virtual ExecuteRequestByUri_Add() = default;

    virtual void Execute(winrt::Windows::Foundation::Uri const& packageUri, HRESULT& error, HRESULT& extendedError, winrt::hstring& errorText);

    virtual void PostExecute(HRESULT& error, HRESULT& extendedError, winrt::hstring& errorText);

private:
    winrt::Windows::Foundation::Uri const& m_packageUri;
    winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions const& m_options;
    winrt::hstring m_packageUriAsString;
};
}
