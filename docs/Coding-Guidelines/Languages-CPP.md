# C++

**DO** implement types using C++ and [C++/WinRT](https://github.com/microsoft/cppwinrt)

**DO** follow the [CppCoreGudelines](https://github.com/isocpp/CppCoreGuidelines) for all new code.

**DO** enable `/W4 /Wx` for all new code.

**CONSIDER** using the [Windows Implementation Library](https://github.com/Microsoft/wil) for
Windows-specific helpers rather than creating your own.

**DO** use 4-space indentation instead of tab characters.

## Catching C++/WinRT Exceptions and HRESULT

Exceptions should not be used for standard flow control.

When a catch clause is required, note that `winrt::hresult_error` does not also catch
`std::bad_alloc` or any of the other C++ standard exceptions. In cases where a single catch handler
desires to pull out an HRESULT, use the following:

```c++
// For code using C++/WinRT
catch (...)
{
    auto e{ winrt::hresult_error(winrt::to_hresult(), winrt::take_ownership_from_abi) };
    auto hr{ e.code() };
    auto message { e.message() };
    // hr contains the WinRT exception or best-guess conversion from a C++ exception,
    // message contains the best-guess textual format of that exception
}

// For code using WIL
catch (...)
{
    auto hr{ wil::ResultFromCaughtException() };
    // hr contains the WinRT exception, WIL exception, or best-guess conversion from a C++ exception
}
```

C++/WinRT's ABI layer automatically catches and converts exceptions generated during a method call
and uses a similar mechanism to map a C++ exception to an `HRESULT` that can be delivered across the
ABI.
