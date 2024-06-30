# ApplicationLanguages

This new type (`Microsoft.Windows.Globalization.ApplicationLanguages`) is a wrapper for the OS
`Windows.Globalization.ApplicationLanguages` type with the updated behavior for the
`PrimaryLanguageOverride` property to be supported for unpackaged apps.

# Background

Changing the application language using
[PrimaryLanguageOverride](https://learn.microsoft.com/uwp/api/windows.globalization.applicationlanguages.primarylanguageoverride)
property from `Windows.Globalization.ApplicationLanguages` namespace is not supported for
WindowsAppSDK unpackaged apps, only for packaged. To support language change for unpackaged
applications, `Microsoft.Windows.Globalization.ApplicationLanguages` type is introduced in
MRTCore.`Microsoft.Windows.Globalization.ApplicationLanguages.PrimaryLanguageOverride` property is
supported both for packaged and unpackaged WindowsAppSDK apps.

This new type (`Microsoft.Windows.Globalization.ApplicationLanguages`) is a wrapper for the OS type
with the updated behavior for the `PrimaryLanguageOverride` to support unpackaged apps.
`Microsoft.Windows.Globalization.ApplicationLanguages` should serve as a replacement for the
existing OS type (`Windows.Globalization.ApplicationLanguages.PrimaryLanguageOverride`).

`GetLanguagesForUser(User)` method from `Windows.Globalization.ApplicationLanguages` is being
intentionally left off due to not being relevant for WinAppSDK.

# API Pages

## ApplicationLanguages class

Specifies the language-related preferences that the app can use and maintain. This class is based on
OS
[Windows.Globalization.ApplicationLanguages](https://learn.microsoft.com/uwp/api/windows.globalization.applicationlanguages)
class. You should prefer this type for WinAppSDK apps over the OS one.

# Remarks

The languages referenced in this class are represented by
[BCP-47](https://tools.ietf.org/html/bcp47) language tags. Each of these is a language identifier
and not a locale name, although the two structurally can be the same. As a language tag, "en-US"
means American English (or the dialect of English spoken in the United States). It makes no claims
about the actual location of the speakers (though many of them do reside in the US) and no other
claims about conventions that are used in the US such as the measurement system or currency.

Example:

```c#
Microsoft.Windows.Globalization.ApplicationLanguages.PrimaryLanguageOverride = "en-US";
```

Language tags support the Unicode extensions "ca-" and "nu-" (See Unicode Key/Type Definitions.).
Note that these extensions can affect the numeral system or calendar used by globalization objects.

## ApplicationLanguages.Languages property

Gets a ranked list of current runtime language values preferred by the user.

# Property Value

[IReadOnlyList](https://learn.microsoft.com/dotnet/api/system.collections.generic.ireadonlylist-1)<[String](https://learn.microsoft.com/dotnet/api/system.string)>

A computed list of languages that merges the app's declared supported languages
(ApplicationLanguages.ManifestLanguages) with the user's ranked list of preferred languages.

Note: This property returns the same values as the language list exposed by
[Windows.Globalization.ApplicationLanguages.Languages](https://learn.microsoft.com/uwp/api/windows.globalization.applicationlanguages.languages)
property.

# Remarks

At runtime, the list of languages for which your app has declared support (the app manifest language
list) is compared with the list of languages for which the user has declared a preference (the user
profile language list). The app runtime language list is set to this intersection (if the
intersection is not empty), or to just the app's default language (if the intersection is empty).
For more detail, see the
[App runtime language list](https://learn.microsoft.com/windows/apps/design/globalizing/manage-language-and-region#app-runtime-language-list)
section in
[Understand user profile languages and app manifest languages](https://learn.microsoft.com/windows/apps/design/globalizing/manage-language-and-region).

## ApplicationLanguages.ManifestLanguages property

Gets the declared list of supported languages in the app's manifest, or empty list for unpackaged
applications.

# Property Value

[IReadOnlyList](https://learn.microsoft.com/dotnet/api/system.collections.generic.ireadonlylist-1)<[String](https://learn.microsoft.com/dotnet/api/system.string)>

For packaged applications, the list of supported languages declared in the app's manifest, same as
the language list exposed by
[Windows.Globalization.ApplicationLanguages.ManifestLanguages](https://learn.microsoft.com/uwp/api/windows.globalization.applicationlanguages.manifestlanguages)
property. For unpackaged applications, empty list.

# Remarks

When language resource packages are used, the packages that are installed and registered for a given
user are determined by the languages in the user's language profile. The set of languages returned
by the ManifestLanguages property is limited to the languages currently available on the system for
the user. Languages included in the main app package manifest will always be returned; languages
from resource packages will be returned only if the language is applicable for the user (that is, is
in the user's preferences) and the resource package has been installed and registered for the user
at the time the property is accessed.

## ApplicationLanguages.PrimaryLanguageOverride property

Gets or sets an override for the app's preferred language, expressed as a
[BCP-47 language tag](https://tools.ietf.org/html/bcp47). For packaged apps, this property is a
wrapper for
[Windows.Globalization.ApplicationLanguages.PrimaryLanguageOverride](https://learn.microsoft.com/uwp/api/windows.globalization.applicationlanguages.primarylanguageoverride)
property and behaves the same. This setting is global for the running process. Unlike for packaged
apps, for unpackaged apps, this setting is not persisted between app sessions.

```c#
public static string PrimaryLanguageOverride { get; set; }
```

# Property Value

[String](https://learn.microsoft.com/dotnet/api/system.string)

A [BCP-47 language tag](https://tools.ietf.org/html/bcp47). The app can set it to override the
language. It must be a single language tag; if delimited list of language tags or any value not
representing a language tag is used, exception is thrown.

The PrimaryLanguageOverride property should only be set to languages available for the app. For
packaged apps, languages available for the app to use are limited to those languages included in the
main app package manifest. The ApplicationLanguages.ManifestLanguages property reflects language
resource packages that are available for the user, and returns an appropriate set of languages that
can be used for setting the PrimaryLanguageOverride property. For unpackaged apps, languages
available for the app to use are limited to languages for which your app has explicitely declared
support.

When your app gets the value, PrimaryLanguageOverride returns either a single language tag (if your
app has previously set the property) or an empty string.

# Remarks

Apps normally run with language settings determined by the system by comparing the languages
supported by the app with the language preferences of the user. The PrimaryLanguageOverride property
is used to override that behavior by setting a single specific language.

For packaged apps, `PrimaryLanguageOverride` setting is a wrapper for
[Windows.Globalization.ApplicationLanguages.PrimaryLanguageOverride](https://learn.microsoft.com/uwp/api/windows.globalization.applicationlanguages.primarylanguageoverride)
property and behaves the same. It is persisted between app sessions. The property should only be set
based on user input presented in settings UI.

For unpackaged apps, `PrimaryLanguageOverride` setting is not persisted between sessions. It should
be set each time the app is loaded. You should set PrimaryLanguageOverride setting in early stage of
app loading, before any resource is loaded.

The property can be read at any time. If the property has never been set, it returns an empty
string.

When you set the PrimaryLanguageOverride, this will be immediately reflected in resources loaded
afterwards, both resources loaded from the code and the resources loaded by XAML. However, this
change may not take effect immediately on resources already loaded in the app UI. To make sure the
app responds to such changes, actions may be needed to reload resources. Those requirements may vary
depending on the UI framework used by the app, and it may be necessary to restart the app.

Example:

```c#
public partial class App : Application
{
    // ...
    public App()
    {
        // Set the primary language override to German (Germany)
        // This will cause the app to use the German (Germany) resources
        // Both resources loaded manually with ResourceLoader and XAML resources fetched with x:Uid
        // will be German (Germany)
        Microsoft.Windows.Globalization.ApplicationLanguages.PrimaryLanguageOverride = "de-DE";

        var resourceLoader = new Microsoft.Windows.ApplicationModel.Resources.ResourceLoader();
        var resourceString = resourceLoader.GetString("SampleString");

        this.InitializeComponent();
    }
    // ...
}
```

# API Details

```c# (but really MIDL3)
namespace Microsoft.Windows.Globalization
{
  // ...
  [contract(MrtCoreContract, 2)]
  runtimeclass ApplicationLanguages
  {
      static IVectorView<String> Languages { get; };
      static IVectorView<String> ManifestLanguages { get; };
      static String PrimaryLanguageOverride;
  }
}
```
