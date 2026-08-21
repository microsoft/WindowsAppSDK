# LocalDev VS Template Title Poke

## Problem and approach

Visual Studio template manifests under `dev\Templates\Source` do not contain title text directly. Each `<Name>` points to a localized string in the C# or C++ extension package through `Package` and `ID` attributes. During VSIX packaging, `dev\Templates\VSIX\Extension\Directory.Build.targets` already applies an unconditional XSL transform to every archived `.vstemplate`, followed by an optional experimental transform that advances the title resource ID to its `[Experimental]` partner.

Add a LocalDev-only XSL transform in that existing rewrite pipeline. The transform will remap each template `Name/@ID` into a reserved, non-conflicting LocalDev resource-ID range. Populate that range in the C# and C++ invariant and satellite `.resx` files with titles whose existing localized text is preserved and whose suffix is ` (LocalDev)`. Keep a paired LocalDev experimental entry so a build with both `Deployment=LocalDev` and `EnableExperimentalVSIXFeatures=true` resolves to `[Experimental] {localized title} (LocalDev)`.

The transform must be conditioned only on `$(Deployment) == 'LocalDev'`; Standalone and Component archives must retain their current IDs and titles.

## Todos

1. **Define the LocalDev title-resource mapping**
   - Inventory every `Name/@ID` used by C# and C++ project, item, and linked subtemplates that can be packed into either VSIX.
   - Reserve and document a collision-free LocalDev ID range or fixed offset.
   - Preserve the existing normal/experimental pairing so the LocalDev transform and experimental transform compose predictably, including currently hidden linked subtemplates.

2. **Add localized LocalDev title resources**
   - Update `dev\Templates\VSIX\Extension\Cs\Common\VSPackage.resx` and `dev\Templates\VSIX\Extension\Cpp\Common\VSPackage.resx` with LocalDev normal and experimental title entries.
   - Add the corresponding entries to every C# and C++ satellite `VSPackage.<locale>.resx`, copying each locale's existing translated base and experimental title and appending ` (LocalDev)`.
   - Do not alter descriptions or existing resource IDs, and do not require generated `VSPackage.Designer.cs` accessors unless the repository's resource-generation step updates them as part of the normal build.

3. **Add the LocalDev XSL poke**
   - In `dev\Templates\VSIX\Extension\Directory.Build.targets`, define a dedicated `_LocalDevVsTemplateXslt` alongside the unconditional and experimental stylesheets.
   - Match `/ns:VSTemplate/ns:TemplateData/ns:Name/@ID` and remap it to the LocalDev title resource ID.
   - Run and move the generated `.vstemplate` files only when `$(Deployment) == 'LocalDev'`.
   - Order the transforms so LocalDev plus experimental resolves to the paired `[Experimental] ... (LocalDev)` resource, while the existing package-GUID, custom-parameter, and `TemplateID.Experimental` rewrites remain intact.

4. **Validate all deployment combinations**
   - Build targeted C# and C++ LocalDev VSIXes without experimental features and inspect the rewritten template archives/resource payloads; confirm representative project and item titles resolve as `{localized title} (LocalDev)`, including `WinUI Blank App (Packaged) (LocalDev)`.
   - Build LocalDev with experimental features and confirm the corresponding result is `[Experimental] {localized title} (LocalDev)` and experimental template IDs remain suffixed.
   - Build at least one non-LocalDev flavor and confirm its `.vstemplate` name IDs and resolved titles are unchanged.
   - Check a non-English satellite resource to confirm the base title stays localized while the literal `LocalDev` marker is appended, and verify every rewritten LocalDev ID exists in the appropriate invariant and satellite resource sets.

## Localization decision and alternative

**Recommended policy:** keep `LocalDev` literal in every locale. It is the exact MSBuild deployment value, script option, VSIX identity marker, and artifact flavor name, so leaving it untranslated makes diagnostics and artifact identification consistent while still preserving the localized template title.

**Alternative:** localize the marker itself in each satellite resource, producing `{localized title} ({localized LocalDev label})`. The XSL and ID-mapping design would not change, but every locale would need an approved translation and ongoing localization ownership. This can make the displayed suffix diverge from the `Deployment=LocalDev` value used in commands, logs, filenames, and support guidance. If this alternative is chosen later, only the LocalDev resource values should need to change.

Adding LocalDev keys only to the invariant resource is not suitable: localized Visual Studio instances would fall back to the entire invariant English title rather than preserving the translated base title.

## Notes

- The existing XSL operates on every `.vstemplate` inside each collected template ZIP, so the change should remain centralized rather than editing source manifests individually.
- The existing experimental transform advances `Name/@ID` and appends `.Experimental` to `TemplateID`; the LocalDev design must compose with it rather than replace it.
- No existing focused tests for the VSIX XSL rewrite were found, so verification should use the established local VSIX build plus archive/resource inspection.
- Repository-level `AGENTS.md` and Git status were unavailable under the active sandbox policy; implementation should recheck both after the sandbox policy is adjusted with `/sandbox`.
