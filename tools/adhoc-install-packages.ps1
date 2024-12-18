cd Packages   # for instance, C:\ado\WindowsAppSDK\Packages

#  Define the source and destination paths for all versions
$sourcePaths = @(
   "Microsoft.FrameworkUdk.1.8.0-CI-26107.1720.241003-1631.3",
   "Microsoft.FrameworkUdk.1.8.0-CI-26107.1728.241202-0947.0",
   "Microsoft.FrameworkUdk.1.8.0-CI-26107.1730.241212-1315.0",
   "Microsoft.ProjectReunion.InteractiveExperiences.TransportPackage.1.8.0-CI-26107.1720.241003-1631.3",
   "Microsoft.ProjectReunion.InteractiveExperiences.TransportPackage.1.8.0-CI-26107.1728.241202-0947.0",
   "Microsoft.ProjectReunion.InteractiveExperiences.TransportPackage.1.8.0-CI-26107.1730.241212-1315.0"
)

#  Loop through each source path and copy the content to the corresponding destination path

foreach ($sourcePath in $sourcePaths) {
   # Extract the root directory and version from the source path
   $rootDir = $sourcePath -replace "\.\d.*", ""
   $version = $sourcePath -replace "$rootDir\.", ""
   $destinationPath = "$rootDir/$version"

   # Create the root directory if it doesn't exist
   if (-Not (Test-Path -Path $rootDir)) {
       New-Item -ItemType Directory -Path $rootDir
   }

   # Create the versioned directory inside the destination directory if it doesn't exist
   if (-Not (Test-Path -Path $destinationPath)) {
       New-Item -ItemType Directory -Path $destinationPath
   }

   # Copy the content from the source directory to the destination directory
   Copy-Item -Path "$sourcePath\*" -Destination $destinationPath -Recurse -Force

   Write-Output "Content copied from $sourcePath to $destinationPath successfully."

}