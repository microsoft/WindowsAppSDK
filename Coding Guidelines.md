Project Reunion implementations prefer C++ and C++/WinRT implementations.   New code must adhere to the [cppcoreguidelines](https://github.com/isocpp/CppCoreGuidelines) 
and be /W4 clean (for Visual C++.)

Prefer existing std:: and gsl:: types, but use [wil](https://github.com/Microsoft/wil) types for Windows-specific helpers and lifecycle management rather than creating your own.

If new languages become common, we will describe the coding guidelines for such languages here.  
