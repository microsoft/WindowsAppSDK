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

        * Microsoft.WindowsAppSDK.Foundation_Framework - A target representing the Windows App SDK Foundation APIs for
            framework-dependent deployment scenarios. Auto-initialization behavior is controlled by target properties
            on the _consuming_ target:

                * `WindowsPackageType` - "MSIX" (default) for packaged apps, "None" for unpackaged apps.
                    Drives which auto-initializers are enabled by default.
                * `WindowsAppSdkBootstrapInitialize` - Automatically initializes the Framework Package via
                    the Dynamic Dependency bootstrap logic. Required for unpackaged framework-dependent apps.
                    Defaults to TRUE when WindowsPackageType is "None".
                * `WindowsAppSdkDeploymentManagerInitialize` - Automatically initializes the Deployment Manager
                    for Main/Singleton functionality (e.g., Push Notifications). Required for packaged
                    framework-dependent apps. Defaults to TRUE when WindowsPackageType is "MSIX".
                * `WindowsAppSdkCompatibilityInitialize` - Enables A/B Containment facilities for controlling
                    servicing release behavior. Opt-in only (default FALSE). Applies to both framework-dependent
                    and self-contained scenarios.

        * Microsoft.WindowsAppSDK.Foundation_SelfContained - An interface target that represents the Windows App SDK
            Foundation APIs for self-contained deployment scenarios. Auto-initialization behavior is controlled by:

                * `WindowsAppSdkUndockedRegFreeWinRTInitialize` - Enables manifest-based WinRT activation for
                    downlevel (< 19H1) devices. Defaults to TRUE when target platform < 10.0.18362.0,
                    FALSE otherwise. Can be explicitly set TRUE/FALSE to override.
                * `WindowsAppSdkCompatibilityInitialize` - Enables A/B Containment facilities for controlling
                    servicing release behavior. Opt-in only (default FALSE). Applies to both framework-dependent
                    and self-contained scenarios.

    License:
        See the LICENSE file in the package root for more information.
====================================================================================================================]]#
include_guard()

# Check for minimum CMake version. Avoid using `cmake_minimum_required`, which will reset policies if this file is
# included by a project that has already specified a minimum CMake version.
if(CMAKE_VERSION VERSION_LESS 3.31)
    message(FATAL_ERROR "Microsoft.WindowsAppSDK.Foundation requires at least CMake 3.31, but CMake ${CMAKE_VERSION} is in use.")
endif()


find_package(Microsoft.WindowsAppSDK.InteractiveExperiences CONFIG REQUIRED)

block(SCOPE_FOR VARIABLES)
    wasdk_detect_platform()

    # NuGet package root: this file lives at build/cmake/PACKAGE_NAME_LOWER-config.cmake
    set(PACKAGE_LOCATION "${CMAKE_CURRENT_LIST_DIR}/../..")

    #[[====================================================================================================================
        Target: Microsoft.WindowsAppSDK.Foundation

        Base target: CppWinRT projection + headers. No runtime components.
    ====================================================================================================================]]#
    file(GLOB _WINMD_FILES "${PACKAGE_LOCATION}/metadata/*.winmd")
    add_cppwinrt_projection(Microsoft.WindowsAppSDK.Foundation
        INPUTS ${_WINMD_FILES}
        OPTIMIZE
        DEPS
            Microsoft.WindowsAppSDK.InteractiveExperiences
    )

    target_include_directories(Microsoft.WindowsAppSDK.Foundation
        INTERFACE
            ${PACKAGE_LOCATION}/include
    )

    #[[====================================================================================================================
        Target: Microsoft.WindowsAppSDK.Foundation_DynamicDependencyBootstrap

        Auto-initializer for unpackaged framework-dependent apps. Provides the Bootstrap DLL
        (Microsoft.WindowsAppRuntime.Bootstrap.lib/.dll) and adds MddBootstrapAutoInitializer.cpp.
        All bootstrap files are in the Foundation NuGet — does NOT depend on the Runtime NuGet package.
    ====================================================================================================================]]#
    # Internal target for the Bootstrap binary — not a public API surface.
    # Linked via _DynamicDependencyBootstrap so TARGET_RUNTIME_DLLS propagates automatically.
    add_library(Microsoft.WindowsAppSDK.Foundation._BootstrapBinary SHARED IMPORTED)
    set_target_properties(Microsoft.WindowsAppSDK.Foundation._BootstrapBinary
        PROPERTIES
            IMPORTED_IMPLIB "${PACKAGE_LOCATION}/lib/native/${PLATFORM_IDENTIFIER}/Microsoft.WindowsAppRuntime.Bootstrap.lib"
            IMPORTED_LOCATION "${PACKAGE_LOCATION}/runtimes/win-${PLATFORM_IDENTIFIER}/native/Microsoft.WindowsAppRuntime.Bootstrap.dll"
    )

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
            Microsoft.WindowsAppSDK.Foundation._BootstrapBinary
    )

    #[[====================================================================================================================
        Target: Microsoft.WindowsAppSDK.Foundation_DeploymentManager

        Auto-initializer for packaged framework-dependent apps that use Main/Singleton functionality
        (e.g., Push Notifications). Adds DeploymentManagerAutoInitializer.cpp.
        DeploymentManager calls WinRT APIs (not Bootstrap APIs) — no Bootstrap.lib linkage needed.
    ====================================================================================================================]]#
    add_library(Microsoft.WindowsAppSDK.Foundation_DeploymentManager INTERFACE)

    target_sources(Microsoft.WindowsAppSDK.Foundation_DeploymentManager
        INTERFACE
            "${PACKAGE_LOCATION}/include/DeploymentManagerAutoInitializer.cpp"
    )

    target_compile_definitions(Microsoft.WindowsAppSDK.Foundation_DeploymentManager
        INTERFACE
            MICROSOFT_WINDOWSAPPSDK_AUTOINITIALIZE_DEPLOYMENTMANAGER
    )

    #[[====================================================================================================================
        Target: Microsoft.WindowsAppSDK.Foundation_UndockedRegFreeWinRT

        Auto-initializer for self-contained apps running on downlevel (< 19H1) devices. Enables
        manifest-based WinRT activation. Not required for framework-dependent apps or self-contained
        apps targeting >= 19H1 (opt out via WindowsAppSdkUndockedRegFreeWinRTInitialize=FALSE).
    ====================================================================================================================]]#
    add_library(Microsoft.WindowsAppSDK.Foundation_UndockedRegFreeWinRT INTERFACE)

    target_sources(Microsoft.WindowsAppSDK.Foundation_UndockedRegFreeWinRT
        INTERFACE
            "${PACKAGE_LOCATION}/include/UndockedRegFreeWinRT-AutoInitializer.cpp"
    )

    target_compile_definitions(Microsoft.WindowsAppSDK.Foundation_UndockedRegFreeWinRT
        INTERFACE
            MICROSOFT_WINDOWSAPPSDK_AUTOINITIALIZE_UNDOCKEDREGFREEWINRT
    )

    #[[====================================================================================================================
        Target: Microsoft.WindowsAppSDK.Foundation_Compatibility

        Auto-initializer for A/B Containment facilities to control servicing release behavior.
        Opt-in only — requires setting WindowsAppSdkCompatibilityInitialize=TRUE on the consuming target.
    ====================================================================================================================]]#
    add_library(Microsoft.WindowsAppSDK.Foundation_Compatibility INTERFACE)

    target_compile_definitions(Microsoft.WindowsAppSDK.Foundation_Compatibility
        INTERFACE
            MICROSOFT_WINDOWSAPPSDK_AUTOINITIALIZE_COMPATIBILITY
    )

    #[[====================================================================================================================
        Runtime Package Detection (not a target — configure-time setup)

        The Runtime NuGet (Microsoft.WindowsAppSDK.Runtime) is NOT a build dependency of Foundation.
        It is probed here to perform two optional setup tasks:

        1. Version info: The Runtime NuGet ships WindowsAppSDK-VersionInfo.h and .json containing
           the framework package identity (name, version, publisher). If present, these are extracted
           and stored as cache variables (WINDOWSAPPSDK_FRAMEWORK_PACKAGE_NAME, etc.) for use by
           wasdk_generate_appx_manifest() when generating AppxManifest.xml for packaged apps.

        2. Bootstrap linkage: If Runtime is found, the _DynamicDependencyBootstrap target is linked
           to the Runtime target so that version info headers are available to MddBootstrapAutoInitializer.

        The Runtime_FOUND result also controls _Framework target behavior downstream:
            - Runtime FOUND:     _Framework provides full auto-init (Bootstrap/DeploymentManager genexes).
            - Runtime NOT FOUND: _Framework gracefully falls back to _SelfContained behavior.
    ====================================================================================================================]]#
    find_package(Microsoft.WindowsAppSDK.Runtime CONFIG QUIET)
    if(Microsoft.WindowsAppSDK.Runtime_FOUND)
        # Wire version info headers from Runtime into the bootstrap target
        target_link_libraries(Microsoft.WindowsAppSDK.Foundation_DynamicDependencyBootstrap
            INTERFACE
                Microsoft.WindowsAppSDK.Runtime
        )

        # Extract framework package identity for AppxManifest generation
        get_property(_RUNTIME_LOCATION GLOBAL PROPERTY NUGET_LOCATION-MICROSOFT_WINDOWSAPPSDK_RUNTIME)
        set(_VERSION_JSON "${_RUNTIME_LOCATION}/WindowsAppSDK-VersionInfo.json")
        if(EXISTS "${_VERSION_JSON}")
            file(READ "${_VERSION_JSON}" _VERSION_JSON_CONTENT)

            string(JSON _FRAMEWORK_PFN GET "${_VERSION_JSON_CONTENT}" "Runtime" "Packages" "Framework" "PackageFamilyName")
            string(REGEX REPLACE "_[^_]+$" "" _FRAMEWORK_PACKAGE_NAME "${_FRAMEWORK_PFN}")
            string(JSON _RUNTIME_VERSION GET "${_VERSION_JSON_CONTENT}" "Runtime" "Version" "DotQuadNumber")
            string(JSON _RUNTIME_PUBLISHER GET "${_VERSION_JSON_CONTENT}" "Runtime" "Identity" "Publisher")

            set(WINDOWSAPPSDK_FRAMEWORK_PACKAGE_NAME "${_FRAMEWORK_PACKAGE_NAME}" CACHE INTERNAL "")
            set(WINDOWSAPPSDK_FRAMEWORK_MIN_VERSION "${_RUNTIME_VERSION}" CACHE INTERNAL "")
            set(WINDOWSAPPSDK_FRAMEWORK_PUBLISHER "${_RUNTIME_PUBLISHER}" CACHE INTERNAL "")
        endif()

        message(STATUS "WindowsAppSDK: Runtime package found — framework-dependent deployment available.")
        message(STATUS "WindowsAppSDK: For packaged apps, call wasdk_generate_appx_manifest() to generate "
            "AppxManifest.xml with framework PackageDependency.")
    else()
        message(STATUS "WindowsAppSDK: Runtime package not found — only self-contained deployment is available. "
            "If Foundation_Framework is linked, it will automatically fall back to self-contained behavior.")
    endif()

    #[[====================================================================================================================
        Target: Microsoft.WindowsAppSDK.Foundation_SelfContainedRuntime
        Target: Microsoft.WindowsAppSDK.Foundation_SelfContained

        Self-contained deployment target. Bundles runtime DLLs and SxS manifest. Auto-initialization:

            WindowsAppSdkUndockedRegFreeWinRTInitialize
                Defaults to TRUE when target platform < 10.0.18362.0 (19H1), FALSE otherwise.
                Enables manifest-based WinRT activation for downlevel devices.
                Can be explicitly set TRUE/FALSE to override.

            WindowsAppSdkCompatibilityInitialize (default: FALSE)
                Opt-in for A/B Containment.
    ====================================================================================================================]]#
    add_library(Microsoft.WindowsAppSDK.Foundation_SelfContainedRuntime SHARED IMPORTED)

    set(FRAMEWORK_PATH "${PACKAGE_LOCATION}/runtimes-framework/win-${PLATFORM_IDENTIFIER}/native")
    file(GLOB FRAMEWORK_DLLS "${FRAMEWORK_PATH}/*.dll")

    set_target_properties(Microsoft.WindowsAppSDK.Foundation_SelfContainedRuntime
        PROPERTIES
            IMPORTED_IMPLIB "${PACKAGE_LOCATION}/lib/native/${PLATFORM_IDENTIFIER}/Microsoft.WindowsAppRuntime.lib"
            IMPORTED_LOCATION "${FRAMEWORK_DLLS}"
    )

    add_library(Microsoft.WindowsAppSDK.Foundation_SelfContained INTERFACE)

    wasdk_transform_appxfragment(
        Microsoft.WindowsAppSDK.Foundation_SelfContained
        "${PACKAGE_LOCATION}/runtimes-framework/package.appxfragment"
        "${CMAKE_BINARY_DIR}/__manifests/Microsoft.WindowsAppSDK.Foundation.manifest"
    )

    target_link_libraries(Microsoft.WindowsAppSDK.Foundation_SelfContained
        INTERFACE
            Microsoft.WindowsAppSDK.Foundation
            Microsoft.WindowsAppSDK.Foundation_SelfContainedRuntime
    )

    # UndockedRegFreeWinRT — required for self-contained apps on downlevel (< 19H1) devices.
    # Default: TRUE when target platform < 10.0.18362.0 (19H1), FALSE otherwise.
    # Developer can override by explicitly setting WindowsAppSdkUndockedRegFreeWinRTInitialize TRUE/FALSE.
    set(_FOUNDATION_REGFREE_DEFAULT FALSE)
    if(NOT "${CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION}" STREQUAL "")
        set(_FOUNDATION_PLATFORM_VERSION "${CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION}")
    elseif(DEFINED ENV{WindowsSDKVersion})
        string(REGEX REPLACE "^([0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+).*" "\\1"
            _FOUNDATION_PLATFORM_VERSION "$ENV{WindowsSDKVersion}")
    endif()
    if(DEFINED _FOUNDATION_PLATFORM_VERSION AND _FOUNDATION_PLATFORM_VERSION VERSION_LESS "10.0.18362.0")
        set(_FOUNDATION_REGFREE_DEFAULT TRUE)
    endif()

    if(_FOUNDATION_REGFREE_DEFAULT)
        set(_REGFREE_ENABLED "$<NOT:$<STREQUAL:$<TARGET_PROPERTY:WindowsAppSdkUndockedRegFreeWinRTInitialize>,FALSE>>")
    else()
        set(_REGFREE_ENABLED "$<STREQUAL:$<TARGET_PROPERTY:WindowsAppSdkUndockedRegFreeWinRTInitialize>,TRUE>")
    endif()
    # _REGFREE_ENABLED is used in the orchestrator section below for linkage + compile definitions

    #[[====================================================================================================================
        Target: Microsoft.WindowsAppSDK.Foundation_Framework

        Framework-dependent deployment target. Auto-initialization behavior is driven by target properties
        on the consuming target:

            WindowsPackageType (default: "MSIX")
                "MSIX"  -> DeploymentManager auto-init enabled by default
                "None"  -> Bootstrap (DynDep) auto-init enabled by default

            WindowsAppSdkBootstrapInitialize         -> opt-in/out for bootstrap
            WindowsAppSdkDeploymentManagerInitialize  -> opt-in/out for deployment manager
            WindowsAppSdkCompatibilityInitialize      -> opt-in for A/B Containment

        The WindowsAppRuntimeAutoInitializer.cpp orchestrator is always compiled as a source; it
        conditionally calls each initializer based on the preprocessor defines set by the linked targets.

        If the Runtime package is not found, _Framework falls back to self-contained behavior.
    ====================================================================================================================]]#
    add_library(Microsoft.WindowsAppSDK.Foundation_Framework INTERFACE)

    target_link_libraries(Microsoft.WindowsAppSDK.Foundation_Framework
        INTERFACE
            Microsoft.WindowsAppSDK.Foundation
    )

    # In Windows App SDK CMake consumption, deployment mode is expressed through target choice:
    #   _Framework     = framework-dependent (not self-contained)
    #   _SelfContained = self-contained
    # For MSBuild parity, WindowsAppSdkSelfContained is set as a local variable that reflects
    # the target's deployment intent. This makes the if() conditions read naturally and explicitly
    # show the self-contained check, matching MSBuild's property-based flow.
    set(WindowsAppSdkSelfContained FALSE)  # _Framework = not self-contained

    if(NOT Microsoft.WindowsAppSDK.Runtime_FOUND OR WindowsAppSdkSelfContained)
        # Fallback: Runtime package not found — framework-dependent deployment is not viable.
        # Wire _Framework to delegate entirely to _SelfContained so the developer gets a working
        # build with self-contained behavior. All self-contained logic (runtime DLLs, SxS manifest,
        # UndockedRegFreeWinRT, Compatibility) comes from _SelfContained — no duplication here.
        target_link_libraries(Microsoft.WindowsAppSDK.Foundation_Framework
            INTERFACE
                Microsoft.WindowsAppSDK.Foundation_SelfContained
        )
    endif()

    #[[====================================================================================================================
        Orchestrator: WindowsAppRuntimeAutoInitializer.cpp

        The orchestrator is compiled as a source on both _Framework and _SelfContained deployment targets.
        It uses preprocessor defines (MICROSOFT_WINDOWSAPPSDK_AUTOINITIALIZE_*) to conditionally call
        each auto-initializer at startup via #pragma init_seg(lib).

        This mirrors MSBuild's flow: property → define → orchestrator call.
        Genex enable variables are calculated here alongside the defines they control.
        The same genexes used for target_link_libraries (above) drive the defines here.
    ====================================================================================================================]]#

    # --- Genex enable variables ---
    # Bootstrap: enabled when PackageType is "None" (unpackaged) or explicitly TRUE
    set(_BOOTSTRAP_EXPLICIT_TRUE  "$<STREQUAL:$<TARGET_PROPERTY:WindowsAppSdkBootstrapInitialize>,TRUE>")
    set(_BOOTSTRAP_NOT_SET        "$<STREQUAL:$<TARGET_PROPERTY:WindowsAppSdkBootstrapInitialize>,>")
    set(_PACKAGE_TYPE_IS_NONE     "$<STREQUAL:$<TARGET_PROPERTY:WindowsPackageType>,None>")
    set(_BOOTSTRAP_DEFAULT_ON     "$<AND:${_BOOTSTRAP_NOT_SET},${_PACKAGE_TYPE_IS_NONE}>")
    set(_BOOTSTRAP_ENABLED        "$<OR:${_BOOTSTRAP_EXPLICIT_TRUE},${_BOOTSTRAP_DEFAULT_ON}>")

    # DeploymentManager: enabled when PackageType is not "None" (default MSIX) or explicitly TRUE
    set(_DEPLOYMGR_EXPLICIT_TRUE  "$<STREQUAL:$<TARGET_PROPERTY:WindowsAppSdkDeploymentManagerInitialize>,TRUE>")
    set(_DEPLOYMGR_NOT_SET        "$<STREQUAL:$<TARGET_PROPERTY:WindowsAppSdkDeploymentManagerInitialize>,>")
    set(_DEPLOYMGR_DEFAULT_ON     "$<AND:${_DEPLOYMGR_NOT_SET},$<NOT:${_PACKAGE_TYPE_IS_NONE}>>")
    set(_DEPLOYMGR_ENABLED        "$<OR:${_DEPLOYMGR_EXPLICIT_TRUE},${_DEPLOYMGR_DEFAULT_ON}>")

    # Compatibility: opt-in only
    set(_COMPAT_ENABLED "$<BOOL:$<TARGET_PROPERTY:WindowsAppSdkCompatibilityInitialize>>")

    # --- _SelfContained: helper target linkage + orchestrator source + defines ---
    target_link_libraries(Microsoft.WindowsAppSDK.Foundation_SelfContained
        INTERFACE
            $<${_REGFREE_ENABLED}:Microsoft.WindowsAppSDK.Foundation_UndockedRegFreeWinRT>
            $<${_COMPAT_ENABLED}:Microsoft.WindowsAppSDK.Foundation_Compatibility>
    )
    target_sources(Microsoft.WindowsAppSDK.Foundation_SelfContained
        INTERFACE
            "${PACKAGE_LOCATION}/include/WindowsAppRuntimeAutoInitializer.cpp"
    )
    target_compile_definitions(Microsoft.WindowsAppSDK.Foundation_SelfContained
        INTERFACE
            $<${_REGFREE_ENABLED}:MICROSOFT_WINDOWSAPPSDK_AUTOINITIALIZE_UNDOCKEDREGFREEWINRT>
            $<${_COMPAT_ENABLED}:MICROSOFT_WINDOWSAPPSDK_AUTOINITIALIZE_COMPATIBILITY>
    )

    # --- _Framework: helper target linkage + orchestrator source + defines ---
    if(Microsoft.WindowsAppSDK.Runtime_FOUND AND NOT WindowsAppSdkSelfContained)
        target_link_libraries(Microsoft.WindowsAppSDK.Foundation_Framework
            INTERFACE
                $<${_BOOTSTRAP_ENABLED}:Microsoft.WindowsAppSDK.Foundation_DynamicDependencyBootstrap>
                $<${_DEPLOYMGR_ENABLED}:Microsoft.WindowsAppSDK.Foundation_DeploymentManager>
                $<${_COMPAT_ENABLED}:Microsoft.WindowsAppSDK.Foundation_Compatibility>
        )
    endif()
    target_sources(Microsoft.WindowsAppSDK.Foundation_Framework
        INTERFACE
            "${PACKAGE_LOCATION}/include/WindowsAppRuntimeAutoInitializer.cpp"
    )
    target_compile_definitions(Microsoft.WindowsAppSDK.Foundation_Framework
        INTERFACE
            $<${_BOOTSTRAP_ENABLED}:MICROSOFT_WINDOWSAPPSDK_AUTOINITIALIZE_BOOTSTRAP>
            $<${_DEPLOYMGR_ENABLED}:MICROSOFT_WINDOWSAPPSDK_AUTOINITIALIZE_DEPLOYMENTMANAGER>
            $<${_COMPAT_ENABLED}:MICROSOFT_WINDOWSAPPSDK_AUTOINITIALIZE_COMPATIBILITY>
    )

    #[[====================================================================================================================
        wasdk_generate_appx_manifest()

        Generates an AppxManifest.xml for packaged apps. For framework-dependent apps, automatically
        includes the <PackageDependency> entry for the Windows App Runtime Framework package.

            wasdk_generate_appx_manifest(
                TARGET <target>
                OUTPUT <output-path>
                IDENTITY_NAME <name>
                IDENTITY_PUBLISHER <publisher>
                IDENTITY_VERSION <version>
                [DISPLAY_NAME <name>]
                [DESCRIPTION <description>]
                [LOGO <path>]
            )

        The TARGET must already be defined via add_executable(). If the target links
        Microsoft.WindowsAppSDK.Foundation_Framework, a <PackageDependency> for the Windows App Runtime
        Framework package is automatically included. If the target links _SelfContained, no
        PackageDependency is added.
    ====================================================================================================================]]#
    function(wasdk_generate_appx_manifest)
        set(ONE_VALUE_KEYWORDS TARGET OUTPUT IDENTITY_NAME IDENTITY_PUBLISHER IDENTITY_VERSION DISPLAY_NAME DESCRIPTION LOGO)
        cmake_parse_arguments(PARSE_ARGV 0 APPX "" "${ONE_VALUE_KEYWORDS}" "")

        if(NOT APPX_TARGET)
            message(FATAL_ERROR "wasdk_generate_appx_manifest: TARGET is required")
        endif()
        if(NOT APPX_OUTPUT)
            set(APPX_OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/AppxManifest.xml")
        endif()
        if(NOT APPX_IDENTITY_NAME OR NOT APPX_IDENTITY_PUBLISHER OR NOT APPX_IDENTITY_VERSION)
            message(FATAL_ERROR "wasdk_generate_appx_manifest: IDENTITY_NAME, IDENTITY_PUBLISHER, and IDENTITY_VERSION are required")
        endif()
        if(NOT APPX_DISPLAY_NAME)
            set(APPX_DISPLAY_NAME "${APPX_IDENTITY_NAME}")
        endif()
        if(NOT APPX_DESCRIPTION)
            set(APPX_DESCRIPTION "${APPX_DISPLAY_NAME}")
        endif()
        if(NOT APPX_LOGO)
            set(APPX_LOGO "Logo.png")
        endif()

        # Determine architecture
        wasdk_detect_platform()
        if(PLATFORM_IDENTIFIER STREQUAL "x64")
            set(_PROC_ARCH "x64")
        elseif(PLATFORM_IDENTIFIER STREQUAL "arm64")
            set(_PROC_ARCH "arm64")
        else()
            set(_PROC_ARCH "x64")
        endif()

        # Build the PackageDependency section if framework info is available
        set(_PACKAGE_DEPENDENCY "")
        if(DEFINED WINDOWSAPPSDK_FRAMEWORK_PACKAGE_NAME)
            set(_PACKAGE_DEPENDENCY "    <PackageDependency Name=\"${WINDOWSAPPSDK_FRAMEWORK_PACKAGE_NAME}\" MinVersion=\"${WINDOWSAPPSDK_FRAMEWORK_MIN_VERSION}\" Publisher=\"${WINDOWSAPPSDK_FRAMEWORK_PUBLISHER}\" />\n")
        endif()

        # Generate the manifest
        file(WRITE "${APPX_OUTPUT}"
"<?xml version=\"1.0\" encoding=\"utf-8\"?>
<Package xmlns=\"http://schemas.microsoft.com/appx/manifest/foundation/windows10\"
         xmlns:uap=\"http://schemas.microsoft.com/appx/manifest/uap/windows10\"
         xmlns:rescap=\"http://schemas.microsoft.com/appx/manifest/foundation/windows10/restrictedcapabilities\"
         IgnorableNamespaces=\"uap rescap\">
  <Identity Name=\"${APPX_IDENTITY_NAME}\"
            Version=\"${APPX_IDENTITY_VERSION}\"
            Publisher=\"${APPX_IDENTITY_PUBLISHER}\"
            ProcessorArchitecture=\"${_PROC_ARCH}\" />
  <Properties>
    <DisplayName>${APPX_DISPLAY_NAME}</DisplayName>
    <PublisherDisplayName>${APPX_IDENTITY_PUBLISHER}</PublisherDisplayName>
    <Description>${APPX_DESCRIPTION}</Description>
    <Logo>${APPX_LOGO}</Logo>
  </Properties>
  <Dependencies>
    <TargetDeviceFamily Name=\"Windows.Desktop\" MinVersion=\"10.0.17763.0\" MaxVersionTested=\"10.0.26100.0\" />
${_PACKAGE_DEPENDENCY}  </Dependencies>
  <Resources>
    <Resource Language=\"en-us\" />
  </Resources>
  <Applications>
    <Application Id=\"App\" Executable=\"${APPX_TARGET}.exe\" EntryPoint=\"Windows.FullTrustApplication\">
      <uap:VisualElements DisplayName=\"${APPX_DISPLAY_NAME}\" Description=\"${APPX_DESCRIPTION}\"
                          BackgroundColor=\"transparent\" Square150x150Logo=\"${APPX_LOGO}\" Square44x44Logo=\"${APPX_LOGO}\">
        <uap:DefaultTile Wide310x150Logo=\"${APPX_LOGO}\" />
      </uap:VisualElements>
    </Application>
  </Applications>
  <Capabilities>
    <rescap:Capability Name=\"runFullTrust\" />
  </Capabilities>
</Package>
")

        # Copy manifest + logo to output directory post-build
        add_custom_command(TARGET ${APPX_TARGET} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different "${APPX_OUTPUT}" $<TARGET_FILE_DIR:${APPX_TARGET}>
        )
    endfunction()

endblock()
