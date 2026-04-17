---
description: 'Unit testing standards, test project setup, naming, build & run commands'
applyTo: '**/*Tests.cs, **/*Test.cs, **/*.Tests.csproj'
---

# Testing — Unit Tests, Build & Run

Every public method and class must have corresponding unit tests. Tests are not optional.

---

## 1. Test Framework & Project Setup

### Recommended Stack

| Component | Package | Purpose |
|---|---|---|
| Test Framework | `MSTest` | Test runner & assertions |
| Mocking | `Moq` | Mock dependencies |
| UI Testing | `Microsoft.Windows.Apps.Test` | WinUI UI automation (optional) |

### Test Project Setup

Create a test project alongside the main project:

```
<SolutionRoot>/
  <ProjectName>/           ← Main app project
  <ProjectName>.Tests/     ← Unit test project
```

Test project `.csproj` should reference the main project:

```xml
<Project Sdk="Microsoft.NET.Sdk">
  <PropertyGroup>
    <!-- Match TargetFramework to the main project's .csproj -->
    <TargetFramework><!-- same as the main project's .csproj TargetFramework --></TargetFramework>
    <UseWinUI>true</UseWinUI>
    <Nullable>enable</Nullable>
    <IsPackable>false</IsPackable>
  </PropertyGroup>

  <ItemGroup>
    <!-- Use latest stable versions; do not hard-code version numbers in instructions -->
    <PackageReference Include="MSTest.TestAdapter" Version="*" />
    <PackageReference Include="MSTest.TestFramework" Version="*" />
    <PackageReference Include="Microsoft.NET.Test.Sdk" Version="*" />
    <PackageReference Include="Moq" Version="*" />
  </ItemGroup>

  <ItemGroup>
    <ProjectReference Include="..\<ProjectName>\<ProjectName>.csproj" />
  </ItemGroup>
</Project>
```

---

## 2. Test Writing Rules

### What to Test
- **All public methods** in ViewModels, Services, Helpers, and Models.
- **Edge cases** — null inputs, empty collections, boundary values.
- **Error paths** — exception handling, invalid state transitions.
- **Business logic** — calculations, transformations, state management.

### What NOT to Test (Directly)
- XAML layout / visual rendering (use UI tests for that).
- Framework internals (e.g., `InitializeComponent()`).
- Private methods — test them indirectly through public methods.

### Test Naming Convention

Use the pattern: `MethodName_Scenario_ExpectedResult`

```csharp
[TestMethod]
public void CalculateTotal_WithEmptyCart_ReturnsZero() { }

[TestMethod]
public void LoadDataAsync_WhenServiceThrows_SetsErrorState() { }

[TestMethod]
public async Task SaveAsync_WithValidInput_ReturnsTrue() { }
```

### Test Structure (AAA Pattern)

Every test follows **Arrange → Act → Assert**:

```csharp
[TestMethod]
public void Add_TwoPositiveNumbers_ReturnsSum()
{
    // Arrange
    var calculator = new Calculator();

    // Act
    int result = calculator.Add(2, 3);

    // Assert
    Assert.AreEqual(5, result);
}
```

### ViewModel Testing Example

```csharp
[TestMethod]
public async Task LoadItemsAsync_OnSuccess_PopulatesItems()
{
    // Arrange
    var mockService = new Mock<IDataService>();
    mockService
        .Setup(s => s.GetItemsAsync())
        .ReturnsAsync(new List<Item> { new("Test") });

    var viewModel = new MainViewModel(mockService.Object);

    // Act
    await viewModel.LoadItemsAsync();

    // Assert
    Assert.AreEqual(1, viewModel.Items.Count);
    Assert.IsFalse(viewModel.IsLoading);
}
```

---

## 3. Test Organization

### File Structure

Mirror the main project's folder structure (defined in [winui-best-practices](winui-best-practices.instructions.md)) in the test project. As the main project grows with subfolders under `ViewModels/`, `Services/`, `Views/`, etc., the test project must grow organically in the same way. This alignment enables on-demand test runs scoped to the area you changed:

```
<ProjectName>/                    <ProjectName>.Tests/
  Models/                           Models/
    User.cs                           UserTests.cs
  ViewModels/                       ViewModels/
    MainViewModelTests.cs             MainViewModelTests.cs
    Settings/                         Settings/
      ThemeViewModel.cs                 ThemeViewModelTests.cs
  Services/                         Services/
    DataService.cs                    DataServiceTests.cs
    Auth/                             Auth/
      AuthService.cs                    AuthServiceTests.cs
  Helpers/                          Helpers/
    StringHelper.cs                   StringHelperTests.cs
  Converters/                       Converters/
    BoolToVisibilityConverter.cs      BoolToVisibilityConverterTests.cs
```

### One Test Class per Class Under Test

```csharp
namespace <RootNamespace>.Tests.ViewModels;

[TestClass]
public class MainViewModelTests
{
    // All tests for MainViewModel go here
}
```

### Running Tests On-Demand

After a change, run only the tests related to the affected area instead of the full suite:

```powershell
# Run from the test project folder
cd <ProjectName>.Tests

# Run tests for a specific class
dotnet test -c Debug -p:Platform=x64 --filter "FullyQualifiedName~MainViewModelTests"

# Run a single test
dotnet test -c Debug -p:Platform=x64 --filter "FullyQualifiedName~MainViewModelTests.LoadItemsAsync_OnSuccess_PopulatesItems"

# Run all tests in a namespace (e.g., all ViewModel tests)
dotnet test -c Debug -p:Platform=x64 --filter "FullyQualifiedName~Tests.ViewModels"

# Run tests in a subfolder namespace (e.g., only Settings ViewModels)
dotnet test -c Debug -p:Platform=x64 --filter "FullyQualifiedName~Tests.ViewModels.Settings"

# Run the full suite (for cross-cutting changes)
dotnet test -c Debug -p:Platform=x64
```
```

---

## 4. Test-Specific Commands

For general build and register commands, see **Build, Run & Deploy** in `.github/agents/Agents.md`.
For on-demand test filtering, see **Running Tests On-Demand** above.

Below are additional test commands:

### Build Only the Test Project

```powershell
cd <ProjectName>.Tests
dotnet build -c Debug -p:Platform=x64
```

### Run Tests with Verbose Output

```powershell
dotnet test -c Debug -p:Platform=x64 --verbosity normal
```

---

## 5. Agent Workflow for Tests

When you write or modify code, follow this sequence:

1. **Implement the feature or fix** in the main project.
2. **Write unit tests** for every new/changed public method.
3. **Build** — see **Build, Run & Deploy** in `.github/agents/Agents.md`. Fix all errors and warnings.
4. **Run tests** — `dotnet test -c Debug -p:Platform=x64` (from the test project folder) and ensure all pass.
5. **Review** — Confirm tests cover the happy path, edge cases, and error cases.

### When Modifying Existing Code

1. **Run existing tests first** to establish a baseline.
2. Make the code change.
3. **Run tests again** — fix any failures.
4. **Add new tests** if the change introduces new behaviour.

### Coverage Goals

- Aim for **80%+ code coverage** on business logic (ViewModels, Services).
- 100% coverage of utility/helper methods.
- UI code-behind is exempt from unit test coverage (tested via integration/UI tests).

---

## 6. Common Test Pitfalls

| Pitfall | Fix |
|---|---|
| Test depends on another test's state | Each test must be fully independent |
| Testing multiple things in one test | One assertion per logical concept |
| Tests pass but don't actually verify anything | Always have meaningful assertions |
| Mocking too much | Mock only external dependencies, not the class under test |
| Testing implementation details | Test behaviour and outcomes, not internal method calls |
| Async tests without `await` | Always `await` async methods and use `async Task` return type |

---

## Validation

- Build & run tests — see **Build, Run & Deploy** in `.github/agents/Agents.md`.
- Verify all tests pass — zero failures, zero skipped without justification.
- Verify naming follows `MethodName_Scenario_ExpectedResult` pattern.
- Verify AAA structure (Arrange/Act/Assert) in every test method.
- Confirm coverage goals: 80%+ on ViewModels/Services, 100% on helpers.

---

## Must Read & Research

> **Agent Rule:** Before writing or modifying tests, you **must** fetch and review the relevant references below using `fetch_webpage`. Apply what you learn — do not skip this step.

| # | Reference | When to consult |
|---|---|---|
| 1 | [Unit testing C# with MSTest](https://learn.microsoft.com/en-us/dotnet/core/testing/unit-testing-with-mstest) | Setting up test project, writing first tests, MSTest attributes |
| 2 | [Unit testing best practices .NET](https://learn.microsoft.com/en-us/dotnet/core/testing/unit-testing-best-practices) | Every time you write tests — naming, structure, AAA pattern |
| 3 | [Moq Quickstart](https://github.com/devlooped/moq/wiki/Quickstart) | Mocking interfaces, setting up `Returns`/`Throws`, verifying calls |
| 4 | [FluentAssertions Documentation](https://fluentassertions.com/introduction) | Writing expressive assertions (`Should().Be()`, collections, exceptions) |
| 5 | [dotnet test CLI](https://learn.microsoft.com/en-us/dotnet/core/tools/dotnet-test) | Running tests from terminal, filtering, verbosity options |
| 6 | [Test Explorer in Visual Studio](https://learn.microsoft.com/en-us/visualstudio/test/run-unit-tests-with-test-explorer) | Debugging tests, viewing coverage, understanding test output |


