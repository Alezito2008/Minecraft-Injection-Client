#include <iostream>
#include <windows.h>
#include "main.h"
#include "utils/jni_utils.h"

FILE* pFile = nullptr;

DWORD WINAPI init(LPVOID module) {
    HMODULE mod = (HMODULE) module;

    FreeConsole();
    AllocConsole();
    freopen_s(&pFile, "CONOUT$", "w", stdout);

    std::cout << "Client injected" << std::endl;

    jsize vmCount;
    if (JNI_GetCreatedJavaVMs(&vm, 1, &vmCount) != JNI_OK || vmCount == 0) {
        std::cout << "Java vm not found" << std::endl;
        return 0;
    }

    jint res = vm->GetEnv((void**)&env, JNI_VERSION_21);
    if (res == JNI_EDETACHED) {
        res = vm->AttachCurrentThread((void**)&env, nullptr);
    }
    if (res != JNI_OK) {
        std::cout << "Failed setting up JNI" << std::endl;
    }
    if (env != nullptr) {
        std::cout << "JNI attached" << std::endl;
        client_main(mod);
    }

    return 0;
}

BOOL WINAPI DllMain(
    HINSTANCE hModule,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpvReserved )  // reserved
{
    switch( fdwReason ) 
    { 
        case DLL_PROCESS_ATTACH:
            CreateThread(nullptr, 0, init, hModule, 0, 0);
            break;
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}