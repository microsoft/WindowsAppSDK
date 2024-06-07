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
[BCP-47](https://tools.ietf.org/html/bcp47) language tags. Each of these is a language identifier
and not a locale name, although the two structurally can be the same. As a language tag, "en-US"
means American English (or the dialect of English spoken in the United States). It makes no claims
about the actual location of the speakers (though many of them do reside in the US) and no other
claims about conventions that are used in the US such as the measurement system or currency.

Example:

```c#
Microsoft.Windows.ApplicationModel.Resources.ApplicationLanguages.PrimaryLanguageOverride = "en-US";
```

Language tags support the Unicode extensions "ca-" and "nu-". (See Unicode Key/Type Definitions.)
Note that these extensions can affect the numeral system or calendar used by globalization objects.

## ApplicationLanguages.PrimaryLanguageOverride property

Gets or sets an override for the app's preferred language, expressed as a
[BCP-47 language tag](https://tools.ietf.org/html/bcp47). This setting is global for the running
process and is not persisted.

```c#
public static string PrimaryLanguageOverride { get; set; }
```

# Property Value

[String](https://learn.microsoft.com/dotnet/api/system.string)

A [BCP-47 language tag](https://tools.ietf.org/html/bcp47). The app can set it to override the
language. It must be a single language tag; a delimited list of language tags will result in default
language being used.

The PrimaryLanguageOverride property should only be set to languages available for the app.

When your app gets the value, PrimaryLanguageOverride returns either a single language tag (if your
app has previously set the property) or an empty string.

# Remarks

Apps normally run with language settings determined by the system by comparing the languages
supported by the app with the language preferences of the user. The PrimaryLanguageOverride property
is used to override that behavior by setting a single specific language.

The PrimaryLanguageOverride setting is not persisted between sessions. It should be set each time
the app is loaded. You should set PrimaryLanguageOverride setting in early stage of app loading,
before any resource is loaded. It should only be set based on user input presented in settings UI.
The property can be read at any time. If the property has never been set, it returns an empty
string.

When you set the PrimaryLanguageOverride, this will be immediately reflected in resources loaded
afterwards, both resources loaded from the code and the resources loaded by XAML. However, this
change may not take effect immediately on resources already loaded in the app UI. To make sure the
app responds to such changes, actions may be needed to reload resources. Those requirements may vary
depending on the UI framework used by the app, and it may be necessary to restart the app.

This property overrides the behavior of
[PrimaryLanguageOverride](https://learn.microsoft.com/uwp/api/windows.globalization.applicationlanguages.primarylanguageoverride)
property from Windows.Globalization.ApplicationLanguages namespace property.

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
        Microsoft.Windows.ApplicationModel.Resources.ApplicationLanguages.PrimaryLanguageOverride = "de-DE";

        this.InitializeComponent();
    }
    // ...
}
```

# API Details

```c# (but really MIDL3)
namespace Microsoft.Windows.ApplicationModel.Resources
{
  // ...
  [contract(MrtCoreContract, 2)]
  runtimeclass ApplicationLanguages
  {
      static String PrimaryLanguageOverride;
  }
}
```
