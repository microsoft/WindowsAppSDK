#[[====================================================================================================================

    Microsoft.WindowsAppSDK.Foundation

    CMake configuration file for Microsoft.WindowsAppSDK.Foundation package. Use `find_package(Microsoft.WindowsAppSDK.Foundation CONFIG...)`
    to load this package and its dependencies:

        find_package(Microsoft.WindowsAppSDK.Foundation CONFIG REQUIRED)

    This package defines the following CMake targets:

        * Microsoft.WindowsAppSDK.Foundation - A target representing the Cpp/WinRT projection, headers and libraries of
            the Windows App SDK Foundation APIs. This does not include the necessary runtime components to use the
            Windows App SDK, and is intended to be used by library authors who want to consume the Windows App SDK
            Foundation APIs.

        * Microsoft.WindowsAppSDK.Foundation_Framework - A target representing the Windows App SDK Foundation APIs that
            also takes a dependency on the 'Framework Package' of the Windows App SDK. Target properties can be set on
            _consuming_ target to control:
                * `WindowsAppSdkBootstrapInitialize` - Whether to automatically initialize the Framework Package via
                    the 'dynamic dependency' bootstrap logic.
                * `WindowsAppSdkDeploymentManagerInitialize` - Whether to automatically initialize the Deployment
                    Manager bootstrap logic.

        * Microsoft.WindowsAppSDK.Foundation_SelfContained - An interface target that represents the Windows App SDK
            Foundation APIs for self-contained deployment scenarios. Projects should normally link against this target,
            which in turn depends on `Microsoft.WindowsAppSDK.Foundation_SelfContainedRuntime` to provide the required
            implementation dependencies of the Windows App SDK.

    License:
        See the LICENSE file in the package root for more information.
====================================================================================================================]]#
include_guard()

# Check for minimum CMake version. Avoid using `cmake_minimum_required`, which will reset policies if this file is
# included by a project that has already specified a minimum CMake version.
if(CMAKE_VERSION VERSION_LESS 3.31)
    message(FATAL_ERROR "Microsoft.WindowsAppSDK.Foundation requires at least CMake 3.31, but CMake ${CMAKE_VERSION} is in use.")
endif()

find_package(Microsoft.Windows.CppWinRT CONFIG REQUIRED)
find_package(Microsoft.WindowsAppSDK.InteractiveExperiences CONFIG REQUIRED)

if(NOT (TARGET Microsoft.Windows.CppWinRT))
    message(FATAL_ERROR "Microsoft.Windows.CppWinRT target not found. A CMake package definition for CppWinRT is required. An existing package definition is available from the NuGetCMakePackage repository: https://github.com/mschofie/NuGetCMakePackage")
endif()

block(SCOPE_FOR VARIABLES)
    # Set the 'PLATFORM_IDENTIFIER' - mapping CMake constructs to the identifiers that the NuGet package layout uses.
    if(CMAKE_GENERATOR MATCHES "^Visual Studio")
        set(PLATFORM_IDENTIFIER ${CMAKE_GENERATOR_PLATFORM})
    else()
        set(PLATFORM_PROCESSOR ${CMAKE_SYSTEM_PROCESSOR})
        if(PLATFORM_PROCESSOR STREQUAL "")
            set(PLATFORM_PROCESSOR ${CMAKE_HOST_PROCESSOR})
        endif()
        if(PLATFORM_PROCESSOR STREQUAL "AMD64")
            set(PLATFORM_IDENTIFIER "x64")
        elseif(PLATFORM_PROCESSOR STREQUAL "ARM64")
            set(PLATFORM_IDENTIFIER "arm64")
        endif()
    endif()

    if(PLATFORM_IDENTIFIER STREQUAL "")
        message(FATAL_ERROR "Unable to determine the platform identifier.")
    endif()

    get_property(PACKAGE_LOCATION GLOBAL PROPERTY NUGET_LOCATION-MICROSOFT_WINDOWSAPPSDK_FOUNDATION)
    get_property(PACKAGE_VERSION  GLOBAL PROPERTY NUGET_VERSION-MICROSOFT_WINDOWSAPPSDK_FOUNDATION)

    #[[====================================================================================================================
        Target: Microsoft.WindowsAppSDK.Foundation
    ====================================================================================================================]]#
    add_cppwinrt_projection(Microsoft.WindowsAppSDK.Foundation
        INPUTS
            ${PACKAGE_LOCATION}/metadata/Microsoft.Windows.ApplicationModel.Background.UniversalBGTask.winmd
            ${PACKAGE_LOCATION}/metadata/Microsoft.Windows.ApplicationModel.Background.winmd
            ${PACKAGE_LOCATION}/metadata/Microsoft.Windows.ApplicationModel.DynamicDependency.winmd
            ${PACKAGE_LOCATION}/metadata/Microsoft.Windows.ApplicationModel.Resources.winmd
            ${PACKAGE_LOCATION}/metadata/Microsoft.Windows.ApplicationModel.WindowsAppRuntime.winmd
            ${PACKAGE_LOCATION}/metadata/Microsoft.Windows.AppLifecycle.winmd
            ${PACKAGE_LOCATION}/metadata/Microsoft.Windows.AppNotifications.Builder.winmd
            ${PACKAGE_LOCATION}/metadata/Microsoft.Windows.AppNotifications.winmd
            ${PACKAGE_LOCATION}/metadata/Microsoft.Windows.BadgeNotifications.winmd
            ${PACKAGE_LOCATION}/metadata/Microsoft.Windows.Foundation.winmd
            ${PACKAGE_LOCATION}/metadata/Microsoft.Windows.Globalization.winmd
            ${PACKAGE_LOCATION}/metadata/Microsoft.Windows.Management.Deployment.winmd
            ${PACKAGE_LOCATION}/metadata/Microsoft.Windows.Media.Capture.winmd
            ${PACKAGE_LOCATION}/metadata/Microsoft.Windows.PushNotifications.winmd
            ${PACKAGE_LOCATION}/metadata/Microsoft.Windows.Security.AccessControl.winmd
            ${PACKAGE_LOCATION}/metadata/Microsoft.Windows.Storage.Pickers.winmd
            ${PACKAGE_LOCATION}/metadata/Microsoft.Windows.Storage.winmd
            ${PACKAGE_LOCATION}/metadata/Microsoft.Windows.System.Power.winmd
            ${PACKAGE_LOCATION}/metadata/Microsoft.Windows.System.winmd
        OPTIMIZE
        DEPS
            Microsoft.WindowsAppSDK.InteractiveExperiences
    )

    target_include_directories(Microsoft.WindowsAppSDK.Foundation
        INTERFACE
            ${PACKAGE_LOCATION}/include
    )

    #[[====================================================================================================================
        Target: Microsoft.WindowsAppSDK.Foundation_Framework
    ====================================================================================================================]]#
    add_library(Microsoft.WindowsAppSDK.Foundation_Framework INTERFACE)

    target_link_libraries(Microsoft.WindowsAppSDK.Foundation_Framework
        INTERFACE
            Microsoft.WindowsAppSDK.Foundation
    )

    #[[====================================================================================================================
        Targets:
            Microsoft.WindowsAppSDK.Foundation_Bootstrap
            Microsoft.WindowsAppSDK.Foundation_DynamicDependencyBootstrap
            Microsoft.WindowsAppSDK.Foundation_DeploymentManagerBootstrap

        Note: Consumers should not consume these targets directly. Instead, consume 'Microsoft.WindowsAppSDK.Foundation_Framework'
        and set target properties on the _consuming_ target.

        These targets need the Microsoft.WindowsAppSDK.Runtime package to be present. If the package cannot be found,
        these targets will not be created, and the end-user will need to bootstrap the Framework manually.
    ====================================================================================================================]]#
    find_package(Microsoft.WindowsAppSDK.Runtime CONFIG QUIET)
    if(NOT Microsoft.WindowsAppSDK.Runtime_FOUND)
        message(VERBOSE "Microsoft.WindowsAppSDK.Runtime *not* found. The 'bootstrap' logic will *not* be available, and the Framework will need to be bootstrapped manually.")
    else()
        add_library(Microsoft.WindowsAppSDK.Foundation_Bootstrap SHARED IMPORTED GLOBAL)

        target_sources(Microsoft.WindowsAppSDK.Foundation_Bootstrap
            INTERFACE
                "${PACKAGE_LOCATION}/include/WindowsAppRuntimeAutoInitializer.cpp"
        )

        set_target_properties(Microsoft.WindowsAppSDK.Foundation_Bootstrap
            PROPERTIES
                IMPORTED_IMPLIB "${PACKAGE_LOCATION}/lib/native/${PLATFORM_IDENTIFIER}/Microsoft.WindowsAppRuntime.Bootstrap.lib"
                IMPORTED_LOCATION "${PACKAGE_LOCATION}/runtimes/win-${PLATFORM_IDENTIFIER}/native/Microsoft.WindowsAppRuntime.Bootstrap.dll"
        )

        target_link_libraries(Microsoft.WindowsAppSDK.Foundation_Bootstrap
            INTERFACE
                Microsoft.WindowsAppSDK.Runtime
        )

        # The 'Microsoft.WindowsAppSDK.Foundation_DynamicDependencyBootstrap' target adds the
        # 'MddBootstrapAutoInitializer.cpp' source, and the MICROSOFT_WINDOWSAPPSDK_AUTOINITIALIZE_BOOTSTRAP
        # preprocessor definition.
        add_library(Microsoft.WindowsAppSDK.Foundation_DynamicDependencyBootstrap INTERFACE)

        target_sources(Microsoft.WindowsAppSDK.Foundation_DynamicDependencyBootstrap
            INTERFACE
                "${PACKAGE_LOCATION}/include/MddBootstrapAutoInitializer.cpp"
        )

        target_compile_definitions(Microsoft.WindowsAppSDK.Foundation_DynamicDependencyBootstrap
            INTERFACE
                MICROSOFT_WINDOWSAPPSDK_AUTOINITIALIZE_BOOTSTRAP
        )

        target_link_libraries(Microsoft.WindowsAppSDK.Foundation_DynamicDependencyBootstrap
            INTERFACE
                Microsoft.WindowsAppSDK.Foundation_Bootstrap
        )

        # The 'Microsoft.WindowsAppSDK.Foundation_DeploymentManagerBootstrap' target adds the
        # 'DeploymentManagerAutoInitializer.cpp' source, and the MICROSOFT_WINDOWSAPPSDK_AUTOINITIALIZE_DEPLOYMENTMANAGER
        # preprocessor definition.
        add_library(Microsoft.WindowsAppSDK.Foundation_DeploymentManagerBootstrap INTERFACE)

        target_sources(Microsoft.WindowsAppSDK.Foundation_DeploymentManagerBootstrap
            INTERFACE
                "${PACKAGE_LOCATION}/include/DeploymentManagerAutoInitializer.cpp"
        )

        target_compile_definitions(Microsoft.WindowsAppSDK.Foundation_DeploymentManagerBootstrap
            INTERFACE
                MICROSOFT_WINDOWSAPPSDK_AUTOINITIALIZE_DEPLOYMENTMANAGER
        )

        target_link_libraries(Microsoft.WindowsAppSDK.Foundation_DeploymentManagerBootstrap
            INTERFACE
                Microsoft.WindowsAppSDK.Foundation_Bootstrap
        )

        # 'Microsoft.WindowsAppSDK.Foundation_Framework' should now depend on the individual bootstrap targets,
        # conditional on properties of the consuming target.
        target_link_libraries(Microsoft.WindowsAppSDK.Foundation_Framework
            INTERFACE
                $<$<BOOL:$<TARGET_PROPERTY:WindowsAppSdkBootstrapInitialize>>:Microsoft.WindowsAppSDK.Foundation_DynamicDependencyBootstrap>
                $<$<BOOL:$<TARGET_PROPERTY:WindowsAppSdkDeploymentManagerInitialize>>:Microsoft.WindowsAppSDK.Foundation_DeploymentManagerBootstrap>
        )
    endif()

    #[[====================================================================================================================
        Target: Microsoft.WindowsAppSDK.Foundation_SelfContained
    ====================================================================================================================]]#
    add_library(Microsoft.WindowsAppSDK.Foundation_SelfContainedRuntime SHARED IMPORTED GLOBAL)

    set(FRAMEWORK_PATH "${PACKAGE_LOCATION}/runtimes-framework/win-${PLATFORM_IDENTIFIER}/native")
    set(FRAMEWORK_DLLS
        "${FRAMEWORK_PATH}/Microsoft.Windows.ApplicationModel.Resources.dll"
        "${FRAMEWORK_PATH}/Microsoft.WindowsAppRuntime.dll"
    )

    set_target_properties(Microsoft.WindowsAppSDK.Foundation_SelfContainedRuntime
        PROPERTIES
            IMPORTED_IMPLIB "${PACKAGE_LOCATION}/lib/native/${PLATFORM_IDENTIFIER}/Microsoft.WindowsAppRuntime.lib"
            IMPORTED_LOCATION "${FRAMEWORK_DLLS}"
    )

    add_library(Microsoft.WindowsAppSDK.Foundation_SelfContained INTERFACE)

    # Transform appxfragment into SxS activation manifest via XSLT
    set(_XSLT_FILE "${CMAKE_BINARY_DIR}/__xslt/TransformAppxFragment.xslt")
    set(_PS_FILE "${CMAKE_BINARY_DIR}/__xslt/Invoke-XsltTransform.ps1")
    set(_FOUNDATION_MANIFEST_FILE "${CMAKE_BINARY_DIR}/__manifests/Microsoft.WindowsAppSDK.Foundation.manifest")
    set(_FOUNDATION_FRAGMENT "${PACKAGE_LOCATION}/runtimes-framework/package.appxfragment")

    if(NOT EXISTS "${_XSLT_FILE}")
        file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/__xslt")
        file(WRITE "${_XSLT_FILE}" [=[<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:appx="http://schemas.microsoft.com/appx/manifest/foundation/windows10" exclude-result-prefixes="appx">
<xsl:output method="xml" indent="yes" encoding="UTF-8" standalone="yes"/>
<xsl:strip-space elements="*"/>
<xsl:template match="/"><assembly manifestVersion="1.0" xmlns:asmv3="urn:schemas-microsoft-com:asm.v3" xmlns:winrtv1="urn:schemas-microsoft-com:winrt.v1" xmlns="urn:schemas-microsoft-com:asm.v1"><xsl:apply-templates select="//appx:InProcessServer"/></assembly></xsl:template>
<xsl:template match="appx:InProcessServer"><asmv3:file name="{appx:Path}" xmlns:asmv3="urn:schemas-microsoft-com:asm.v3"><xsl:apply-templates select="appx:ActivatableClass"/></asmv3:file></xsl:template>
<xsl:template match="appx:ActivatableClass"><winrtv1:activatableClass name="{@ActivatableClassId}" threadingModel="both" xmlns:winrtv1="urn:schemas-microsoft-com:winrt.v1"/></xsl:template>
</xsl:stylesheet>
]=])
        file(WRITE "${_PS_FILE}" [=[param([string]$XsltPath,[string]$InputPath,[string]$OutputPath)
$xslt = New-Object System.Xml.Xsl.XslCompiledTransform
$xslt.Load($XsltPath)
$dir = Split-Path $OutputPath -Parent
if (-not (Test-Path $dir)) { New-Item -Path $dir -ItemType Directory -Force | Out-Null }
$w = [System.Xml.XmlWriter]::Create($OutputPath, $xslt.OutputSettings)
try { $xslt.Transform($InputPath, $w) } finally { $w.Close() }
$t = [System.IO.File]::ReadAllText($OutputPath)
$t = $t -replace 'encoding="utf-8"','encoding="UTF-8"'
$t = $t -replace '<assembly manifestVersion="1.0" xmlns="urn:schemas-microsoft-com:asm.v1" xmlns:asmv3="urn:schemas-microsoft-com:asm.v3" xmlns:winrtv1="urn:schemas-microsoft-com:winrt.v1">',("<assembly manifestVersion=""1.0""
    xmlns:asmv3=""urn:schemas-microsoft-com:asm.v3""
    xmlns:winrtv1=""urn:schemas-microsoft-com:winrt.v1""
    xmlns=""urn:schemas-microsoft-com:asm.v1"">")
[System.IO.File]::WriteAllText($OutputPath, $t, [System.Text.UTF8Encoding]::new($false))
]=])
    endif()

    if(EXISTS "${_FOUNDATION_FRAGMENT}")
        file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/__manifests")
        execute_process(
            COMMAND powershell -ExecutionPolicy Bypass -File "${_PS_FILE}"
                -XsltPath "${_XSLT_FILE}" -InputPath "${_FOUNDATION_FRAGMENT}" -OutputPath "${_FOUNDATION_MANIFEST_FILE}"
            RESULT_VARIABLE _XFORM_RESULT
        )
        if(_XFORM_RESULT STREQUAL 0)
            target_sources(Microsoft.WindowsAppSDK.Foundation_SelfContained INTERFACE "${_FOUNDATION_MANIFEST_FILE}")
            target_link_options(Microsoft.WindowsAppSDK.Foundation_SelfContained INTERFACE /MANIFEST)
        endif()
    endif()

    target_link_libraries(Microsoft.WindowsAppSDK.Foundation_SelfContained
        INTERFACE
            Microsoft.WindowsAppSDK.Foundation
            Microsoft.WindowsAppSDK.Foundation_SelfContainedRuntime
    )

endblock()
