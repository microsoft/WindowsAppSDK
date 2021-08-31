// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

namespace wil
{
#if defined(_APISETLIBLOADER_) && !defined(__WIL_APISETLIBLOADER_)
#define __WIL_APISETLIBLOADER_
typedef unique_any<DLL_DIRECTORY_COOKIE, decltype(&::RemoveDllDirectory), ::RemoveDllDirectory> unique_dll_directory_cookie;
#endif // __WIL_APISETLIBLOADER_

#if defined(MSIXDYNAMICDEPENDENCY_H) && !defined(__WIL_MSIXDYNAMICDEPENDENCY_H)
#define __WIL_MSIXDYNAMICDEPENDENCY_H
typedef unique_any<MDD_PACKAGEDEPENDENCY_CONTEXT, decltype(&::MddRemovePackageDependency), ::MddRemovePackageDependency> unique_package_dependency_context;
#endif // __WIL_MSIXDYNAMICDEPENDENCY_H

#if defined(_APPMODEL_H_) && !defined(__WIL_APPMODEL_H_) && WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
#define __WIL_APPMODEL_H_
typedef unique_any<PACKAGE_INFO_REFERENCE, decltype(&::ClosePackageInfo), ::ClosePackageInfo> unique_package_info_reference;
#endif // __WIL_APPMODEL_H_
#if defined(__WIL_APPMODEL_H_) && !defined(__WIL_APPMODEL_H_STL) && defined(WIL_RESOURCE_STL)
#define __WIL_APPMODEL_H_STL
typedef shared_any<unique_package_info_reference> shared_package_info_reference;
typedef weak_any<shared_package_info_reference> weak_package_info_reference;
#endif // __WIL_APPMODEL_H_STL
}
