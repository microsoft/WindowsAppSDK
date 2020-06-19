<!--
    Before submitting, delete all <!-- TEMPLATE marked comments in this file,
    and the following quote banner:
-->
> See comments in Markdown for how to use this spec template

<!-- TEMPLATE
    The purpose of this spec is to describe a new feature and
    its APIs that make up a new feature in Project Reunion. 

    There are two audiences for the spec. The first are people
    that want to evaluate and give feedback on the API, as part of
    the submission process.  When it's complete
    it will be incorporated into the documentation for Project Reunion.
    Hopefully we'll be able to copy it mostly verbatim.
    So the second audience is everyone that reads there to learn how
    and why to use this API. 
-->

# Background

<!-- TEMPLATE
    Use this section to provide background context for the new API(s)
    in this spec. 

    This section and the appendix are the only sections that likely
    do not get copied into any official documentation, they're just an aid
    to reading this spec. 
    
    If you're modifying an existing API, included a link here to the
    existing page(s) or spec documentation.

    For example, this section is a place to explain why you're adding this
    API rather than modifying an existing API.

    If you're writing a "converged" API add links into docs.microsoft.com
    for the existing Win32 or WinRT APIs that are being converged.
-->

<!-- TEMPLATE
    For example, this is a place to provide a brief explanation of some dependent
    area, just explanation enough to understand this new API, rather than telling
    the reader "go read 100 pages of background information posted at ...". 
-->

# Description

<!-- TEMPLATE
    Use this section to provide a brief description of the feature.
    For an example, see the introduction to the PasswordBox control
    (http://docs.microsoft.com/windows/uwp/design/controls-and-patterns/password-box).
-->

# Examples

<!-- TEMPLATE

    Use this section to explain the features of the API, showing
    example code with each description. The general format is:

    ## FirstFeatureName

    Feature explanation text goes here, including why an app would use it, how it
    replaces or supplements existing functionality.

    ```c#
    void SampleMethod() {
        var show = new AnExampleOf();
        show.SomeMembers = AndWhyItMight(be, interesting)
    }
    ```

    ## SecondFeatureName

    Feature explanation text goes here, including why an app would use it, how it
    replaces or supplements existing functionality.

    ```c#
    void SampleMethod() {
        var show = new AnExampleOf();
        show.SomeMembers = AndWhyItMight(be, interesting)
    }
    ```

    Code samples should be in C# and/or C++/WinRT.

    As an example of this section, see the Examples section for the PasswordBox
    control (https://docs.microsoft.com/windows/uwp/design/controls-and-patterns/password-box#examples). 
-->

# Remarks

<!-- TEMPLATE

    Explanation and guidance that doesn't fit into the Examples section.

    APIs should only throw exceptions in exceptional conditions; basically,
    only when there's a bug in the caller, such as argument exception.  But if for some
    reason it's necessary for a caller to catch an exception from an API, call that
    out with an explanation either here or in the Examples
-->

# API Notes

<!-- TEMPLATE

    Option 1: Give a one or two line description of each API (type and member),
        or at least the ones that aren't obvious from their name. These
        descriptions are what show up in IntelliSense. For properties, specify
        the default value of the property if it isn't the type's default (for
        example an int-typed property that doesn't default to zero.) 
        
    Option 2: Put these descriptions in the below API Details section,
        with a "///" comment above the member or type. 
-->

# API Details

<!-- TEMPLATE

    The exact API, in MIDL3 format (https://docs.microsoft.com/en-us/uwp/midl-3/)
    when possible, or in C# if starting with an API sketch.  GitHub's markdown
    syntax formatter does not (yet) know about MIDL3, so use ```c# instead even
    when writing MIDL3.

    Example:

    ```c# (but really MIDL3)
    namespace Microsoft.AppModel
    {
        /// Represents a package on the host system. See Windows.ApplicationModel.Package for more details
        runtimeclass Package
        {
            /// Returns the current package, or null if the current process is not packaged
            static Package Current { get; };

            /// Returns the package from the system store with this full name or null if not found
            static Package GetFromFullName(String fullName);

            /// Returns packages in the given family, by name
            static Package[] FindByFamilyName(String familyName);
        }
    }
    ```
-->

# Appendix

<!-- TEMPLATE

    Anything else that you want to write down for posterity, but
    that isn't necessary to understand the purpose and usage of the API.
    For example, implementation details.
    
-->
