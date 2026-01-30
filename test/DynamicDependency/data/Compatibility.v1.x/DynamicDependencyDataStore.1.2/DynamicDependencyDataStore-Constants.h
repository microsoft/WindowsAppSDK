// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

// Rely on _STRINGIZE(x) in yvals_core.h
#ifndef _STRINGIZE
#define _STRINGIZEX(x)  #x
#define _STRINGIZE(x)   _STRINGIZEX(x)
#endif

#define PR_DYNDEP_1X_LIBID_UUID             419D01EE-8167-4d62-B722-5C671D5F0B03

#define PR_DYNDEP_DATASTORE_1X_CLSID_UUID   89EC5F0D-882E-4363-B057-752E8D57E67C
#define PR_DYNDEP_DATASTORE_1X_CLSID_STRING _STRINGIZE(PR_DYNDEP_DATASTORE_CLSID_UUID)
