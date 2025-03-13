$workingDirectory = get-location
$BasePath = "BuildOutput/FullNuget"
$manifestPath = "$BasePath\manifests"
$xslt = New-Object System.Xml.Xsl.XslCompiledTransform
$xslt.Load("$workingDirectory\build\TransformAppxManifest.xslt")
$xslt.Transform("$workingDirectory\$BasePath\AppxManifest.xml", "$workingDirectory\$manifestPath\Microsoft.WindowsAppSdk.Foundation.manifest")
