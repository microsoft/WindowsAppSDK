## Writing tests guide

Tests are MSTest classes — any `.cs` file with `[TestClass]` and
`[TestMethod]` attributes is discovered automatically.

```csharp
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace MyApp.Tests;

[TestClass]
public class CalculatorTests
{
    [TestMethod]
    public void Add_TwoPositiveNumbers_ReturnsSum()
    {
        var result = Calculator.Add(2, 3);
        Assert.AreEqual(5, result);
    }
}
```

### Targeting the code under test

Reference the project or package being tested:

```powershell
dotnet add reference ..\MyApp\MyApp.csproj
# or
dotnet add package MyLibrary
```

Types under test must be `public`. If you need to test internals, add
`[assembly: InternalsVisibleTo("MyApp.Tests")]` to the project under
test.

### Patterns worth knowing

- **Async tests**: `[TestMethod] public async Task ...` — MSTest awaits
  the returned `Task`.
- **Data-driven tests**: `[DataRow(...)]` paired with `[DataTestMethod]`
  runs the same body across multiple inputs.
- **Setup / teardown**: `[TestInitialize]` and `[TestCleanup]` run
  before and after every test; `[ClassInitialize]` and
  `[ClassCleanup]` run once per class.
- **Mocking services**: [Moq](https://github.com/devlooped/moq) or
  [NSubstitute](https://nsubstitute.github.io/) for interface-based
  dependencies injected via DI.

For the full reference, see
[Unit testing with MSTest](https://learn.microsoft.com/dotnet/core/testing/unit-testing-mstest-intro).
