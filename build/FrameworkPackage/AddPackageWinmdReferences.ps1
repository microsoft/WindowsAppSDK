[CmdLetBinding()]
Param(
    [Parameter(Position=0,Mandatory=$true)]
    [String[]]$winmdPaths,
    [Parameter(Position=1,Mandatory=$true)]
    [string]$propFilePath
)

$propsXmlDoc = [xml](get-content $propFilePath)
$xmlDocNS = $propsXmlDoc.DocumentElement.NamespaceURI

$winmdPath = $winmdPaths[0]
$winmdFileName = [System.IO.Path]::GetFileName($winmdPath);
$winmdFileNameNoExtension = [System.IO.Path]::GetFileNameWithoutExtension($winmdPath);
$winmdXmlName = $winmdFileNameNoExtension
$winmdXmlName = $winmdXmlName -replace '\.',''
$winmdXmlName = $winmdXmlName + "Winmd"

$itemGroupElement = $propsXmlDoc.createElement("ItemGroup", $xmlDocNS)
$propsXmlDoc.DocumentElement.appendchild($itemGroupElement)

$projectReunionWinmdElement = $propsXmlDoc.createElement($winmdXmlName, $xmlDocNS)
$itemGroupElement.appendchild($projectReunionWinmdElement)
$projectReunionWinmdElement.setattribute("Include", $winmdPath)

$skipHarvestingWinmdRegistrationElement = $propsXmlDoc.createElement("SkipHarvestingWinmdRegistration", $xmlDocNS)
$projectReunionWinmdElement.appendchild($skipHarvestingWinmdRegistrationElement)
$skipHarvestingWinmdRegistrationElement.InnerText = "true"

# TODO: update this to be the winmd name!
$targetPathElement = $propsXmlDoc.createElement("TargetPath", $xmlDocNS)
$projectReunionWinmdElement.appendchild($targetPathElement)
$targetPathElement.InnerText = "`$(WinMetadataDir)\" + $winmdFileName

$outputGroupElement = $propsXmlDoc.createElement("OutputGroup", $xmlDocNS)
$projectReunionWinmdElement.appendchild($outputGroupElement)
$outputGroupElement.InnerText = "CustomOutputGroupForPackaging"

$projectNameElement = $propsXmlDoc.createElement("ProjectName", $xmlDocNS)
$projectReunionWinmdElement.appendchild($projectNameElement)
$projectNameElement.InnerText = "`$(ProjectName)"

$propertyGroupElement = $propsXmlDoc.createElement("PropertyGroup", $xmlDocNS)
$propsXmlDoc.DocumentElement.appendchild($propertyGroupElement)

$winmdNameXmlElementName = "ProjectReunionWinmdName"
$winMdNameElement = $propsXmlDoc.createElement($winmdNameXmlElementName, $xmlDocNS)
$propertyGroupElement.appendchild($winMdNameElement)
$winMdNameElement.InnerText = $winmdFileName

$targetElement = $propsXmlDoc.createElement("Target", $xmlDocNS)
$propsXmlDoc.DocumentElement.appendchild($targetElement)
$targetElement.setattribute("Name", "_FixWinmdCopyLocal")
$targetElement.setattribute("AfterTargets", "ResolveNuGetPackageAssets")

$itemGroup4Element = $propsXmlDoc.createElement("ItemGroup", $xmlDocNS)
$targetElement.appendchild($itemGroup4Element)

$winMdCopyLocalElementName = $winmdXmlName + "CopyLocal"
$projectReunionWinMdCopyLocalElement = $propsXmlDoc.createElement($winMdCopyLocalElementName, $xmlDocNS)
$itemGroup4Element.appendchild($projectReunionWinMdCopyLocalElement)
$projectReunionWinMdCopyLocalElement.setattribute("Include", "@(ReferenceCopyLocalPaths)")
$projectReunionWinMdCopyLocalElement.setattribute("Condition", "'%(ReferenceCopyLocalPaths.Filename)%(ReferenceCopyLocalPaths.Extension)' == '`$($winmdNameXmlElementName)'")

$itemGroup5Element = $propsXmlDoc.createElement("ItemGroup", $xmlDocNS)
$targetElement.appendchild($itemGroup5Element)
$itemGroup5Element.setattribute("Condition", "'@($winMdCopyLocalElementName)' != ''")

$referenceCopyLocalPathsElement = $propsXmlDoc.createElement("ReferenceCopyLocalPaths", $xmlDocNS)
$itemGroup5Element.appendchild($referenceCopyLocalPathsElement)
$referenceCopyLocalPathsElement.setattribute("Remove", "@($winMdCopyLocalElementName)")

$targetElement2 = $propsXmlDoc.createElement("Target", $xmlDocNS)
$propsXmlDoc.DocumentElement.appendchild($targetElement2)
$targetElement2.setattribute("Name", "_FixWinmdPackaging")
$targetElement2.setattribute("BeforeTargets", "_ComputeAppxPackagePayload")

# TODO: fill in values for the below elements!
$itemGroupElement2 = $propsXmlDoc.createElement("ItemGroup", $xmlDocNS)
$targetElement2.appendchild($itemGroupElement2)

$winmdPackagingOutputElementName = $winmdXmlName + "PackagingOutput"
$winmdPackagingOutputElement = $propsXmlDoc.createElement($winmdPackagingOutputElementName, $xmlDocNS)
$itemGroupElement2.appendchild($winmdPackagingOutputElement)
$winmdPackagingOutputElement.setattribute("Include", "@(PackagingOutputs)")
$winmdPackagingOutputElement.setattribute("Condition", "'%(PackagingOutputs.Filename)%(PackagingOutputs.Extension)' == '`$($winmdNameXmlElementName)'")

$itemGroupElement3 = $propsXmlDoc.createElement("ItemGroup", $xmlDocNS)
$targetElement2.appendchild($itemGroupElement3)
$itemGroupElement3.setattribute("Condition", "'@($winmdPackagingOutputElementName)' != ''")

$packagingOutputsElement = $propsXmlDoc.createElement("PackagingOutputs", $xmlDocNS)
$itemGroupElement3.appendchild($packagingOutputsElement)
$packagingOutputsElement.setattribute("Remove", "@($winmdPackagingOutputElementName)")

$itemGroupElement4 = $propsXmlDoc.createElement("ItemGroup", $xmlDocNS)
$targetElement2.appendchild($itemGroupElement4)

$packagingOutputs2Element = $propsXmlDoc.createElement("PackagingOutputs", $xmlDocNS)
$itemGroupElement4.appendchild($packagingOutputs2Element)
$packagingOutputs2Element.setattribute("Include", "@($winmdXmlName)")

# TODO: use correct name and do an override if already existing!
$directory = Split-Path -Parent $propFilePath
$propsXmlDoc.save($directory + "/modified.props")