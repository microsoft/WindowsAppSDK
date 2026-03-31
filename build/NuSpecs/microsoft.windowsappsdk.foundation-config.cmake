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


find_package(Microsoft.WindowsAppSDK.InteractiveExperiences CONFIG REQUIRED)

block(SCOPE_FOR VARIABLES)
    wasdk_detect_platform()

    # NuGet package root: this file lives at build/cmake/PACKAGE_NAME_LOWER-config.cmake
    set(PACKAGE_LOCATION "${CMAKE_CURRENT_LIST_DIR}/../..")

    #[[====================================================================================================================
        Target: Microsoft.WindowsAppSDK.Foundation
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

endblock()
