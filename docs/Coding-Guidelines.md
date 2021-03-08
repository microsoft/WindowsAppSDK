# General

Project Reunion prefers using industry-standard coding styles, guidelines, and patterns for any
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

### Markdown

**DO** wrap lines at ~100 characters. GitHub formats lines regardless of individual length but
GitHub diff is line oriented. Keeping lines within the preferred limit makes changes easier to
review. Use a tool like Prettier to bulk-reformat files, or configure your editor's "rulers."
