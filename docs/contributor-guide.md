## Contributing

_We want to hear from you!_

File a [new issue!](https://github.com/microsoft/ProjectReunion/issues/new/choose) Tell us what problem you're
trying to solve, how you've tried to solve it so far, and what would be the ideal solution for your app.  Bonus
points if there's a gist or existing repo we can look at with you.


1. **[Ask a question](https://github.com/microsoft/ProjectReunion/issues/new?assignees=&labels=question&template=question.md&title=Question%3A+%5Byour+question+here%5D)**<br>
    Also, have a look at our [frequently asked questions](faq.md) page which we will update often.

2. **[Start a discussion](https://github.com/microsoft/ProjectReunion/discussions)**<br>
   Discussions can be about any topics or ideas related to Project Reunion.For example,
   you might start a Discussion issue to see if others are interested in a cool new idea
   you've been thinking about that isn't quite ready to be filed as a more formal Feature Proposal.

3. **[Make a feature proposal](https://github.com/microsoft/ProjectReunion/issues/new?assignees=&labels=feature+proposal&template=feature-proposal.md&title=)**<br>
   What components do you want to see in Project Reunion? For example you can propose a new API on an existing type, or an idea for a new API.
   It's fine if you don't have all the details: you can start with a summary and rationale.


**Over time, we will add Project Reunion code and samples into this repo and provide code contribution/developer guidelines.**


Most contributions require you to agree to a
Contributor License Agreement (CLA) declaring that you have the right to, and actually do, grant us
the rights to use your contribution. For details, visit https://cla.opensource.microsoft.com.

When you submit a pull request, a CLA bot will automatically determine whether you need to provide
a CLA and decorate the PR appropriately (e.g., status check, comment). Simply follow the instructions
provided by the bot. You will only need to do this once across all repos using our CLA.

This project has adopted the [Microsoft Open Source Code of Conduct](https://opensource.microsoft.com/codeofconduct/).
For more information see the [Code of Conduct FAQ](https://opensource.microsoft.com/codeofconduct/faq/) or
contact [opencode@microsoft.com](mailto:opencode@microsoft.com) with any additional questions or comments.

## Getting Started

You'll need Visual Studio 2019 installed to do work in a GUI, or at least the MSBuild and SDK toolchains to build from the command line.  From Visual Studio, open the ProjectReunion.sln and hit build!

Or start a Developer Command Prompt or Developer Powershell for VS 2019, and use ```msbuild /p:configuration=release,platform=x86 projectreunion.sln``` to build.

If you don't have Visual Studio 2019 or Visual Studio Code installed you can download them [here](https://visualstudio.microsoft.com/downloads/).

### Coding Style Guide

The Project Reunion Coding Style Guide aims to help contributors produce the best code possible by providing specific guidance on best practices, techniques and technologies. We strive to keep the rules as natural and unobtrusive as practical while promiting qualify, productivity and fun.

#### C++

Please follow the industry driven [C++ Code Guidelines](https://isocpp.github.io/CppCoreGuidelines/) when writing C++ code. Exceptions and additions to these guidelines are noted below:

* No exceptions or additions yet :-)

#### Markdown

**GUIDELINE:** The preferred line length limit is ~100 characters. GitHub formats lines regardless of individual length but GitHub diff is line oriented. Keeping lines within the preferred limit makes changes easier to review.
