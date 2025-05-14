#include "pch.h"
#include "StoragePickersImpl.h"
//#include <windows.h>

namespace StoragePickersImpl {
    int test_add(int a, int b)
    {
        return a + b;
    }

    std::wstring test_hello(const std::wstring& a)
    {
        return L"Hello " + a;
    }
}
