#[[====================================================================================================================

    Microsoft.WindowsAppSDK.Foundation

    CMake configuration file for Microsoft.WindowsAppSDK.Foundation package. Use `find_package(Microsoft.WindowsAppSDK.Foundation CONFIG...)`
    to load this package and its dependencies:

        find_package(Microsoft.WindowsAppSDK.Foundation CONFIG REQUIRED)

    This package defines the following CMake targets:

        * Microsoft.WindowsAppSDK.Foundation - A target representing the C++/WinRT projection, headers and libraries of
          the Windows App SDK Foundation APIs. This target does not have any deployment-mode-specific behavior, 
          however it does forward-declare two variant targets (Foundation_Framework and Foundation_SelfContained) that the wasdk_link_component_variant() helper populates based on the consumer's WindowsAppSDKSelfContained property.

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

find_package(Microsoft.WindowsAppSDK.Base CONFIG REQUIRED)
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

    # Forward-declare deployment-mode variant targets adjacent to the basic target.
    # Populated further below; this declaration lets wasdk_link_component_variant() enforce
    # the contract that both variants exist at configure time.
    add_library(Microsoft.WindowsAppSDK.Foundation_Framework INTERFACE)
    add_library(Microsoft.WindowsAppSDK.Foundation_SelfContained INTERFACE)

    # Basic target as variant selector
    # Resolves to _Framework or _SelfContained based on the consumer's WindowsAppSDKSelfContained
    # property at generation time.
    wasdk_link_component_variant(Foundation)

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

    #[[====================================================================================================================
        Target: Microsoft.WindowsAppSDK.Foundation_Compatibility

        Auto-initializer for A/B Containment facilities to control servicing release behavior.
        Opt-in only — requires setting WindowsAppSdkCompatibilityInitialize=TRUE on the consuming target.
    ====================================================================================================================]]#
    add_library(Microsoft.WindowsAppSDK.Foundation_Compatibility INTERFACE)

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
    endif()

    # In Windows App SDK CMake consumption, deployment mode is expressed through target choice:
    #   _SelfContained = self-contained     (WindowsAppSdkSelfContained == true)
    #   _Framework     = framework-dependent (WindowsAppSdkSelfContained == false)
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

    # _SelfContained interface target was forward-declared near the basic target above.

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

        If the Runtime package is not found, _Framework is not available.
    ====================================================================================================================]]#
    # _Framework interface target was forward-declared near the basic target above.

    target_link_libraries(Microsoft.WindowsAppSDK.Foundation_Framework
        INTERFACE
            Microsoft.WindowsAppSDK.Foundation
    )

    if(NOT Microsoft.WindowsAppSDK.Runtime_FOUND)
        # Runtime not found — _Framework will not have auto-init wiring (Bootstrap, DeploymentManager).
        # If the developer links _Framework without Runtime, they will get link errors from missing
        # auto-initializer symbols. This warning gives them actionable guidance before that happens.
        message(WARNING "WindowsAppSDK: Runtime package not found. "
            "Foundation_Framework will not be available for framework-dependent deployment. "
            "Add Microsoft.WindowsAppSDK.Runtime to add_nuget_packages() or use Foundation_SelfContained.")
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
    if(Microsoft.WindowsAppSDK.Runtime_FOUND)
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
        Foundation auto-init configuration validation (deferred)

        Runs at end of consumer's directory configure. Walks targets that link
        any Microsoft.WindowsAppSDK* and validates 2 configuration rules:

        Rule A: FW Unpackaged + WindowsAppSdkBootstrapInitialize=FALSE
            → "The Windows App SDK Bootstrapper is required for framework-dependent unpackaged apps"

        Rule B: SelfContained + downlevel SDK (< 19H1) + WindowsAppSdkUndockedRegFreeWinRTInitialize=FALSE
            → "Undocked Reg-Free WinRT activation is required for self-contained apps targeting Windows versions prior to 10.0.18362.0"

        Both produce configure-time FATAL_ERROR. This Foundation-side validator only fires when Foundation
        IS loaded.
    ====================================================================================================================]]#
    function(_wasdk_foundation_validate_target target)
        get_target_property(_type ${target} TYPE)
        if(NOT _type STREQUAL "EXECUTABLE")
            return()
        endif()

        get_target_property(_link_libs ${target} LINK_LIBRARIES)
        if(NOT _link_libs)
            return()
        endif()
        set(_uses_wasdk FALSE)
        foreach(_lib IN LISTS _link_libs)
            if(_lib MATCHES "^Microsoft\\.WindowsAppSDK")
                set(_uses_wasdk TRUE)
                break()
            endif()
        endforeach()
        if(NOT _uses_wasdk)
            return()
        endif()

        get_target_property(_pkg_type ${target} WindowsPackageType)
        get_target_property(_sc       ${target} WindowsAppSDKSelfContained)
        get_target_property(_bootstrap ${target} WindowsAppSdkBootstrapInitialize)
        get_target_property(_urf       ${target} WindowsAppSdkUndockedRegFreeWinRTInitialize)

        # Rule A: FW Unpackaged + BootstrapInit=FALSE → error
        if(_pkg_type STREQUAL "None" AND NOT _sc AND _bootstrap STREQUAL "FALSE")
            message(FATAL_ERROR
                "The Windows App SDK Bootstrapper is required for framework-dependent unpackaged apps. "
                "Target '${target}' has WindowsPackageType=\"None\" and "
                "WindowsAppSdkBootstrapInitialize=FALSE. Either set "
                "WindowsAppSdkBootstrapInitialize=TRUE, change the deployment model, or "
                "make the app self-contained.")
        endif()

        # Rule B: SC + downlevel SDK + URFInit=FALSE → error
        if(_sc AND _urf STREQUAL "FALSE")
            # Detect the target's MINIMUM supported OS version.
            # CMAKE_SYSTEM_VERSION (set via -DCMAKE_SYSTEM_VERSION or by toolchain
            # file) is the canonical CMake variable for the target MIN OS version.
            # CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION is the BUILD SDK that VS
            # selects to compile against (often newer than the target min); not
            # what we want for this check. Falls back to env if neither set.
            set(_tpv "")
            if(NOT "${CMAKE_SYSTEM_VERSION}" STREQUAL "")
                set(_tpv "${CMAKE_SYSTEM_VERSION}")
            elseif(NOT "${CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION}" STREQUAL "")
                set(_tpv "${CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION}")
            elseif(DEFINED ENV{WindowsSDKVersion})
                string(REGEX REPLACE "^([0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+).*" "\\1" _tpv "$ENV{WindowsSDKVersion}")
            endif()
            if(_tpv AND _tpv VERSION_LESS "10.0.18362.0")
                message(FATAL_ERROR
                    "Undocked Reg-Free WinRT activation is required for self-contained apps targeting Windows versions prior to 10.0.18362.0. "
                    "Target '${target}' is self-contained, targets SDK version ${_tpv}, and has "
                    "WindowsAppSdkUndockedRegFreeWinRTInitialize=FALSE. Either remove the "
                    "explicit FALSE override, raise the target SDK version, or switch to "
                    "framework-dependent deployment.")
            endif()
        endif()
    endfunction()

    function(_wasdk_foundation_validate_recursive _dir)
        get_directory_property(_targets DIRECTORY ${_dir} BUILDSYSTEM_TARGETS)
        foreach(_t IN LISTS _targets)
            _wasdk_foundation_validate_target(${_t})
        endforeach()

        get_directory_property(_subdirs DIRECTORY ${_dir} SUBDIRECTORIES)
        foreach(_sub IN LISTS _subdirs)
            _wasdk_foundation_validate_recursive(${_sub})
        endforeach()
    endfunction()

    function(_wasdk_foundation_validate)
        _wasdk_foundation_validate_recursive(${CMAKE_CURRENT_SOURCE_DIR})
    endfunction()

    # Register DEFER hook; idempotent per directory.
    get_directory_property(_already_deferred _WASDK_FOUNDATION_VALIDATE_DEFERRED)
    if(NOT _already_deferred)
        set_property(DIRECTORY PROPERTY _WASDK_FOUNDATION_VALIDATE_DEFERRED TRUE)
        cmake_language(DEFER CALL _wasdk_foundation_validate)
    endif()

endblock()
