#include <iostream>
#include <string>
#include <Windows.h>
#include <Urlmon.h>

int main() {
    CoInitialize(NULL);  // Initialize COM library

    std::wstring url;
    std::wcout << L"Please enter the URL to check: ";
    std::wcin >> url;

    IInternetSecurityManager* pISM = NULL;
    HRESULT hr = CoCreateInstance(CLSID_InternetSecurityManager, NULL, CLSCTX_ALL, IID_IInternetSecurityManager, (void**)&pISM);

    if (SUCCEEDED(hr) && pISM != NULL) {
        DWORD zone = 0;
        hr = pISM->MapUrlToZone(url.c_str(), &zone, 0);
        if (SUCCEEDED(hr)) {
            std::wcout << L"The zone for this URL is: " << zone << std::endl;
        }
        else {
            std::wcout << L"Failed to call MapUrlToZone, HRESULT: " << hr << std::endl;
        }
        pISM->Release();  // Release the interface
    }
    else {
        std::wcout << L"Failed to create IInternetSecurityManager instance, HRESULT: " << hr << std::endl;
    }

    CoUninitialize();  // Uninitialize COM library

    std::wcout << L"Press any key to exit..." << std::endl;
    std::wcin.ignore();  // Ignore the previous newline character
    std::wcin.get();  // Wait for user input

    return 0;
}
