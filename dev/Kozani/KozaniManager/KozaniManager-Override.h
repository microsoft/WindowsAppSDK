// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#ifdef PR_KOZANIMANAGER_LIBID_UUID
#undef PR_KOZANIMANAGER_LIBID_UUID
#define PR_KOZANIMANAGER_LIBID_UUID        fb7410ad-2b1b-4b38-a714-c6b4cee0877d
#endif

#ifdef PR_KOZANIMANAGER_CLSID_UUID
#undef PR_KOZANIMANAGER_CLSID_UUID
#define PR_KOZANIMANAGER_CLSID_UUID        5d15855d-c951-411e-b3fb-dd5ba8c94cbf
#endif

#ifdef PR_KOZANIMANAGER_CLSID_STRING
#undef PR_KOZANIMANAGER_CLSID_STRING
#define PR_KOZANIMANAGER_CLSID_STRING      _STRINGIZE(PR_KOZANIMANAGER_CLSID_UUID)
#endif

#ifdef PR_KOZANIMANAGER_CLSID_GUID
#undef PR_KOZANIMANAGER_CLSID_GUID
#define PR_KOZANIMANAGER_CLSID_GUID        0x5d15855d, 0xc951, 0x411e, { 0xb3, 0xfb, 0xdd, 0x5b, 0xa8, 0xc9, 0x4c, 0xbf }
#endif
