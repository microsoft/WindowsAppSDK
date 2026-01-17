# Windows Dynamic Dependency APIs Analysis

## Overview
This document lists all Windows Dynamic Dependency APIs (from Windows SDK's appmodel.h) and identifies which ones do NOT have a matching `Mdd*` API in `msixdynamicdependency.h`.

## Windows Dynamic Dependency APIs (Windows SDK)

The following APIs are part of the Windows SDK's Dynamic Dependency support in `appmodel.h`:

1. **TryCreatePackageDependency**
   - Creates a package dependency reference
   - Available in Windows 11 and later

2. **TryCreatePackageDependency2**
   - Extended version of TryCreatePackageDependency with additional parameters
   - Available in Windows 11 24H1 (version 23H2) and later
   - Includes `PackageDependencyLifetimeArtifactType` parameter for finer control

3. **DeletePackageDependency**
   - Deletes a package dependency reference

4. **AddPackageDependency**
   - Adds a package dependency to the process's package graph

5. **AddPackageDependency2**
   - Extended version of AddPackageDependency with additional options
   - Available in Windows 11 23H2 and later

6. **RemovePackageDependency**
   - Removes a package dependency from the process's package graph

7. **GetResolvedPackageFullNameForPackageDependency**
   - Returns the resolved package full name for a package dependency

8. **GetResolvedPackageFullNameForPackageDependency2**
   - Extended version with different error handling (returns ERROR_NOT_FOUND for unknown IDs)
   - Available in Windows 11 and later

9. **GetIdForPackageDependencyContext**
   - Returns the package dependency ID for a given context

10. **GetPackageGraphRevisionId**
    - Returns the current package graph revision ID

## Mdd* APIs in MsixDynamicDependency.h

The following `Mdd*` APIs are available in `MsixDynamicDependency.h` (Windows App SDK):

1. **MddTryCreatePackageDependency** ✓
   - Matches: `TryCreatePackageDependency`

2. **MddDeletePackageDependency** ✓
   - Matches: `DeletePackageDependency`

3. **MddAddPackageDependency** ✓
   - Matches: `AddPackageDependency`

4. **MddRemovePackageDependency** ✓
   - Matches: `RemovePackageDependency`

5. **MddGetResolvedPackageFullNameForPackageDependency** ✓
   - Matches: `GetResolvedPackageFullNameForPackageDependency`

6. **MddGetResolvedPackageFullNameForPackageDependency2** ✓
   - Matches: `GetResolvedPackageFullNameForPackageDependency2`

7. **MddGetIdForPackageDependencyContext** ✓
   - Matches: `GetIdForPackageDependencyContext`

8. **MddGetPackageGraphRevisionId** ✓
   - Matches: `GetPackageGraphRevisionId`

9. **MddGetGenerationId** ✓
   - Deprecated API (superseded by MddGetPackageGraphRevisionId)
   - No direct Windows API equivalent (internal implementation)

## Windows APIs WITHOUT Matching Mdd* APIs

The following Windows Dynamic Dependency APIs do **NOT** have a matching `Mdd*` API in `msixdynamicdependency.h`:

### 1. TryCreatePackageDependency2
- **Windows API**: `TryCreatePackageDependency2`
- **Expected Mdd* API**: `MddTryCreatePackageDependency2` (DOES NOT EXIST)
- **Reason**: This is a newer API added in Windows 11 24H1 with an additional parameter (`PackageDependencyLifetimeArtifactType`) that provides more fine-grained control over lifetime artifact types
- **Status**: Not yet implemented in Windows App SDK
- **Reference**: Mentioned in `dev/Common/IsWindowsVersion.h` line 57-58

### 2. AddPackageDependency2
- **Windows API**: `AddPackageDependency2`
- **Expected Mdd* API**: `MddAddPackageDependency2` (DOES NOT EXIST)
- **Reason**: This is a newer API added in Windows 11 23H2 with extended options for more control over the dependency add operation
- **Status**: Not yet implemented in Windows App SDK
- **Reference**: No references found in the codebase yet

## Summary

**Total Windows Dynamic Dependency APIs**: 10
**Matching Mdd* APIs**: 8
**Missing Mdd* APIs**: 2

### APIs Requiring Implementation

1. `MddTryCreatePackageDependency2` - to match `TryCreatePackageDependency2`
2. `MddAddPackageDependency2` - to match `AddPackageDependency2`

## Additional Notes

- The Windows App SDK (`MsixDynamicDependency.h`) provides compatibility wrappers for the Windows Dynamic Dependency APIs
- These Mdd* APIs allow applications to work on older Windows versions where native APIs are not available
- The missing APIs (`TryCreatePackageDependency2` and `AddPackageDependency2`) are newer additions to Windows 11 and may be added to future versions of Windows App SDK
- `MddGetResolvedPackageFullNameForPackageDependency2` exists in the header but is currently not fully implemented (see TODO comments in `MddWin11.h`)

## References

- **MsixDynamicDependency.h**: `/home/runner/work/WindowsAppSDK/WindowsAppSDK/dev/DynamicDependency/API/MsixDynamicDependency.h`
- **MddWin11.h**: `/home/runner/work/WindowsAppSDK/WindowsAppSDK/dev/DynamicDependency/API/MddWin11.h`
- **IsWindowsVersion.h**: `/home/runner/work/WindowsAppSDK/WindowsAppSDK/dev/Common/IsWindowsVersion.h`
- **Windows SDK Documentation**: [Dynamic Dependency API Reference](https://learn.microsoft.com/en-us/windows/win32/api/appmodel/)
