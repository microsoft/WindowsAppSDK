#include "pch.h"

inline IID IID_IWpnForegroundSink = winrt::guid("A25F1E10-0EF6-4503-BEA5-F2EB82A956D0");

struct __declspec(uuid("A25F1E10-0EF6-4503-BEA5-F2EB82A956D0")) IWpnForegroundSink : IUnknown
{
    virtual bool AddEvent() = 0;
};

class WpnForegroundSink : IWpnForegroundSink
{
    private:
        mutable Microsoft::WRL::Wrappers::SRWLock m_lock;
        ULONG* m_ref = 0;

    public:
        WpnForegroundSink() = default;
        HRESULT IUnknown::QueryInterface(const IID& iid, void** ptr)
        {
            if (!ptr)
            {
                return E_INVALIDARG;
            }
            *ptr = nullptr;
            if (iid == IID_IUnknown || iid == IID_IWpnForegroundSink)
            {
                *ptr = (void*) this;
                AddRef();
                return NOERROR;
            }
            return E_NOINTERFACE;
        }

        ULONG IUnknown::AddRef()
        {
            InterlockedIncrement(m_ref);
            return *m_ref;
        }

        ULONG IUnknown::Release()
        {
            ULONG ulRefCount = InterlockedDecrement(m_ref);
            if (0 == *m_ref)
            {
                delete this;
            }
            return ulRefCount;
        }

        bool AddEvent();
};
