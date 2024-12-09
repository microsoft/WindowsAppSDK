# Picker Prototypes Implementation Notes

This folder contains prototype implementations for adding types in `Storage.Pickers` to the Windows App SDK. It is currently under development and **not** ready for review or production use.

NOTE: a develop certificate maybe required to run the demo app, if you encounter deployment issues, please add a new certificate to the PickerUsageApp project.

## Current State

- Basic implementation of most core functionalities was added in `Microsoft.Storage.Pickers/`.
- A basic demo app for testing and comparing purpose was added in `PickerUsageApp/`.

### Next steps
- Additional argument validation needs to be added.
- More detailed error handling and exception code, with proper internationalization (localization), is required.
- Add Unit tests 
- Need to be moved to proper folder and integrate with normal WinAppSDK pipeline

## Questions

- The implementation of `SettingsIdentifier` is based on `IFileDialog`'s `SetClientGuid` method, which requires converting the user-provided `SettingsIdentifier` string into a GUID to pass to `SetClientGuid`. We are using MD5 hashing for this conversion to avoid dependence on external state (static or other persistent states). Is this an acceptable approach?
- The implementation uses Win32 interop APIs, which require linking to `Shell32.lib`. Is this the correct way to implement pickers?
- Should we check for COM initialization?
- How can we obtain resources (i18n) for proper error reporting for hardcoded labels like `"All"` for `*` file type filters?



