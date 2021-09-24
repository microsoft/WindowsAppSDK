#include <windows.h>
#include <iostream>
#include <MddBootstrap.h>
#include <WindowsAppSDK-VersionInfo.h>

static struct MddInitializer
{
    MddInitializer(){ 
        MddBootstrapInitializer(); 
    }

    ~MddInitializer() {
        MddBootstrapShutdown();
    }

    void MddBootstrapInitializer()
    {
       const UINT32 c_majorMinorVersion{ WINDOWSAPPSDK_RELEASE_MAJORMINOR};
       PCWSTR c_versionTag{WINDOWSAPPSDK_RELEASE_VERSION_TAG_W};
       const PACKAGE_VERSION c_minVersion{WINDOWSAPPSDK_RELEASE_VERSION_UINT64};
     
       HRESULT hr{MddBootstrapInitialize(c_majorMinorVersion, c_versionTag, c_minVersion)};
       if (FAILED(hr))
       {
           exit(hr);
       }
    }
    
}
_MddInitializer;