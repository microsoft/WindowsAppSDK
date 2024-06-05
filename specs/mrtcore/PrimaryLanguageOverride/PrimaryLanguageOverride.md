# ApplicationLanguages.PrimaryLanguageOverride

This feature provides the ability to change the application language for WindowsAppSDK applications,
comparable to the one in
[Windows.Globalization.ApplicationLanguages.PrimaryLanguageOverride](https://learn.microsoft.com/uwp/api/windows.globalization.applicationlanguages).
The benefit of this addition is that it applies to both packaged and un-packaged WindowsAppSDK
applications, whereas the existing one is not supported for un-packaged.

# Background

Changing the application language using
[PrimaryLanguageOverride](https://learn.microsoft.com/uwp/api/windows.globalization.applicationlanguages.primarylanguageoverride)
property from `Windows.Globalization.ApplicationLanguages` namespace is not supported for
WindowsAppSDK un-packaged apps, only for packaged. To support the same behavior for un-packaged
applications `PrimaryLanguageOverride` property is introduced in
`Microsoft.Windows.ApplicationModel.Resources` MRTCore namespace. This property
(`Microsoft.Windows.ApplicationModel.Resources.PrimaryLanguageOverride`) overrides the behavior of
the existing one (`Windows.Globalization.ApplicationLanguages.PrimaryLanguageOverride`).

# API Pages

## ApplicationLanguages class

Specifies the language-related preferences that the app can use and maintain.

# Remarks

The languages referenced in this class are represented by
[BCP-47](https://tools.ietf.org/html/bcp47) language tags.

_Spec note: Should there be more details about language format, like in Remarks section from
https://learn.microsoft.com/uwp/api/windows.globalization.applicationlanguages?_

Example:

```c#
Microsoft.Windows.ApplicationModel.Resources.ApplicationLanguages.PrimaryLanguageOverride = "en-US";
```

## ApplicationLanguages.PrimaryLanguageOverride property

Specifies the language-related preferences that the app can use and maintain.

Gets or sets an override for the app's preferred language, expressed as a
[BCP-47 language tag](https://tools.ietf.org/html/bcp47).

Example:

```c#
Microsoft.Windows.ApplicationModel.Resources.ApplicationLanguages.PrimaryLanguageOverride = "en-US";
```

# Remarks

This property overrides the behavior of
[PrimaryLanguageOverride](https://learn.microsoft.com/uwp/api/windows.globalization.applicationlanguages.primarylanguageoverride)
property from Windows.Globalization.ApplicationLanguages namespace property.

# API Details

```c# (but really MIDL3)
namespace Microsoft.Windows.ApplicationModel.Resources
{
  // ...
  [contract(MrtCoreContract, 1)]
  runtimeclass ApplicationLanguages
  {
      static String PrimaryLanguageOverride;
  }
}
```
