#include "pch.h"

using namespace winrt;
using namespace Windows::Foundation;

int APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
    init_apartment();
    Uri uri(L"http://aka.ms/cppwinrt");
    printf("Hello, %ls!\n", uri.AbsoluteUri().c_str());
}
