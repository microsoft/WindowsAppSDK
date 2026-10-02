// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
// Helpers using the cryptographic APIs
#pragma once

#include <string>

// This function is for encoding binary data into a format that can be safely included in URLs and other web contexts
inline std::wstring base64urlencode(const streams::IBuffer& buffer)
{
    using namespace winrt::Windows::Security::Cryptography;

    std::wstring result = CryptographicBuffer::EncodeToBase64String(buffer).c_str();
    std::replace(result.begin(), result.end(), '+', '-');
    std::replace(result.begin(), result.end(), '/', '_');
    result.erase(std::remove(result.begin(), result.end(), '='), result.end());

    return result;
}

inline std::wstring random_base64urlencoded_string(std::uint32_t octets)
{
    using namespace winrt::Windows::Security::Cryptography;
    auto buffer = CryptographicBuffer::GenerateRandom(octets);
    return base64urlencode(buffer);
}

// This function computes the SHA-256 hash of a given text string
inline streams::IBuffer sha256(const winrt::hstring& text,
    crypto::BinaryStringEncoding encoding = crypto::BinaryStringEncoding::Utf8)
{
    using namespace winrt::Windows::Security::Cryptography;
    using namespace winrt::Windows::Security::Cryptography::Core;

    auto algo = HashAlgorithmProvider::OpenAlgorithm(HashAlgorithmNames::Sha256());
    return algo.HashData(CryptographicBuffer::ConvertStringToBinary(text, encoding));
}

// This function computes the SHA-256 hash of a given text string and then encodes the result as a base64 string
inline winrt::hstring sha256_base64encoded(const winrt::hstring& text)
{
    auto buffer = sha256(text);
    return crypto::CryptographicBuffer::EncodeToBase64String(buffer);
}

inline std::wstring request_pipe_name(const winrt::hstring& state)
{
    // In order to try and protect the state and auth code, we use a hash of the state value for the pipe name
    std::wstring result = LR"^-^(\\.\pipe\oauth\)^-^";
    result += sha256_base64encoded(state);
    return result;
}

// The create_key function generates a symmetric cryptographic key from a given string.This key is used for both encryption and decryption.
inline crypto::Core::CryptographicKey create_key(const winrt::hstring& keyString)
{
    using namespace winrt::Windows::Security::Cryptography;
    using namespace winrt::Windows::Security::Cryptography::Core;
    using namespace winrt::Windows::Storage::Streams;

    WINRT_ASSERT(!keyString.empty());

    // AES key must be 128, 192, or 256 bits (16, 24, or 32 bytes). Note that the key doesn't have to make a valid
    // string. If we end up slicing a UTF-8 character, that's okay
    auto keyBuffer = CryptographicBuffer::ConvertStringToBinary(keyString, BinaryStringEncoding::Utf8);
    auto keyBufferBegin = keyBuffer.data();
    auto keyBufferEnd = keyBufferBegin + keyBuffer.Length();

    // Repeat the key string as necessary to achieve the desired length
    std::vector<std::uint8_t> buffer(keyBufferBegin, keyBufferEnd);
    auto desiredSize = (buffer.size() <= 16) ? 16 : (buffer.size() <= 24) ? 24 : 32;
    while (buffer.size() < desiredSize)
    {
        buffer.insert(buffer.end(), keyBufferBegin, keyBufferEnd);
    }
    buffer.resize(desiredSize);

    auto algo = SymmetricKeyAlgorithmProvider::OpenAlgorithm(SymmetricAlgorithmNames::AesEcbPkcs7());
    return algo.CreateSymmetricKey(CryptographicBuffer::CreateFromByteArray(buffer));
}

// The encrypt function encrypts a given message using a specified key string.
inline streams::IBuffer encrypt(const winrt::hstring& message, const winrt::hstring& keyString)
{
    using namespace winrt::Windows::Security::Cryptography;
    using namespace winrt::Windows::Security::Cryptography::Core;

    auto msgBuffer = CryptographicBuffer::ConvertStringToBinary(message, BinaryStringEncoding::Utf8);
    auto key = create_key(keyString);
    return CryptographicEngine::Encrypt(key, msgBuffer, nullptr);
}

// The decrypt function decrypts a given encrypted buffer using a specified key string.
inline winrt::hstring decrypt(const streams::IBuffer& encryptedBuffer, const winrt::hstring& keyString)
{
    using namespace winrt::Windows::Security::Cryptography;
    using namespace winrt::Windows::Security::Cryptography::Core;

    auto key = create_key(keyString);
    auto decryptedBuffer = CryptographicEngine::Decrypt(key, encryptedBuffer, nullptr);
    return CryptographicBuffer::ConvertBinaryToString(BinaryStringEncoding::Utf8, decryptedBuffer);
}
