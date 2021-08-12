# General

The Windows App SDK prefers using industry-standard coding styles, guidelines, and patterns for any
languages used in implementation or testing.

## Languages

This list is non-exhaustive; new guidelines for languages will be added over time.

### C++

**DO** implement types using C++ and [C++/WinRT](https://github.com/microsoft/cppwinrt)

**DO** follow the [CppCoreGudelines](https://github.com/isocpp/CppCoreGuidelines) for all new code.

**DO** enable `/W4 /Wx` for all new code.

**CONSIDER** using the [Windows Implementation Library](https://github.com/Microsoft/wil) for
Windows-specific helpers rather than creating your own.

**DO** use 4-space indentation instead of tab characters.

##### Catching C++/WinRT Exceptions and HRESULT

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

### Markdown

**DO** wrap lines at ~100 characters. GitHub formats lines regardless of individual length but
GitHub diff is line oriented. Keeping lines within the preferred limit makes changes easier to
review. Use a tool like Prettier to bulk-reformat files, or configure your editor's "rulers." If new
languages become common, we will describe the coding guidelines for such languages here.

## Git Checkin-to-main Policy

The main branch needs to be kept 'healthy' and ready to ship near daily (daily, or within a day or
two). An unhealthy main branch negatively impacts day-to-day development and jeopardizes release
schedules. We have policies to ensure a high quality bar in main. The details differ depending if a
code change is Experimental vs Preview or Stable.

See [Final Decision: Release channels and cadences #637](https://github.com/microsoft/WindowsAppSDK/discussions/637)
for the expectations of the various release channels.

### Policy: Preview and Stable (aka non-Experimental)

The following requirements must be met to checkin non-Experimental changes to main:

1. API Review approval
2. Tests
3. Prepared to accept bug reports from the world

Changes of a non-Experimental nature must meet these policies to be committed to the main branch.

### Policy: Experimental

The policies for Experimental content differ from non-Experimental content because of the reasons for Experimental content:

1. **Selfhost** – a change is good but you're interested in community usage and feedback to verify
   it's ready for Preview/Stable.
2. **Skeleton** – API Review has approved and you've made an initial 'skeletal' implementation to
   get the interface and infrastructure building but isn't functionally complete e.g. skeletal code
   compiles but everything returns E_NOTIMPL/false/null/etc). Having the API surface building in
   main can unblock documentation, test and sample writers.
3. **Feedback** – your API shape isn't locked (or even clear) but you want and/or need feedback from
   the community, partners and/or others before deciding the API is ready to consider for
   non-Experimental releases. The API is not yet ready to go through API Review.

Reasons NOT to make Experimental content:

1. **Prototype** – prototypes, ideas and wild experimentation should be done on a 'feature branch'
   and not checked into main. To make a 'feature branch' checkout a new branch off main (or a child
   of main) with no intention to checkin to main any time soon (or maybe ever). Make a feature
   branch and don't check into main

Changes of an Experimental nature follow a modified form of the policies for non-Experimental content:

1. CONSIDER: Review API with your local-representative
2. Tests
3. Prepared to accept feedback from the world
4. Experimental APIs are marked experimental

Experimental APIs don't go through full API Review but should be discussed with your local API
Review representative. This ensures your API is aligned with API practices and policies and avoids
the risk of significant changes required to pass API Review.

Experimental content requires appropriate test coverage. This is no different than non-Experimental
content, except meaning of 'appropriate' may vary. For instance, 'skeletal' Experimental APIs don't
need the same breadth of test coverage as non-Experimental APIs.

Experimenal content is broadly shipped via Experimental releases. You should be prepared to receive
feedback on Experimental content.

Experimental content must be tagged to indicate it's Experimental. The mechanisms to do so may vary
(WinRT APIs, Flat-C APIs, non-API content (e.g. data files), etc) but the policy is the same -
Experimental content must be marked to indicate it's Experimental.
