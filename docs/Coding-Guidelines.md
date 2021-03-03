#### General

Project Reunion prefers using industry-standard coding styles, guidelines, and patterns for any languages used in implementation or testing.

#### C++

Project Reunion implementations prefer C++ and C++/WinRT implementations.   New code must adhere to the **cppcoreguidelines** at
https://github.com/isocpp/CppCoreGuidelines and be /W4 clean (for Visual C++.)

Prefer existing std:: and gsl:: types, but use **wil** (https://github.com/Microsoft/wil) types for Windows-specific helpers and lifecycle management
rather than creating your own.

##### Catching Exceptions and HRESULT

Don't just catch winrt::hresult_error or other variations as that doesn't catch std::bad_alloc.

Use the following snippet to catch exceptions and retrieve their HRESULT:

```
catch (...)
{
    auto e{ hresult_error(to_hresult(), take_ownership_from_abi) };
    ...e.code() contains the HRESULT...
}
```

#### Markdown

**GUIDELINE:** The preferred line length limit is ~100 characters. GitHub formats lines regardless of individual length but GitHub diff is line oriented.
Keeping lines within the preferred limit makes changes easier to review.

#### Other Languages

If new languages become common, we will describe the coding guidelines for such languages here.
