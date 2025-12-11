#include "opengl_hook.h"
#include <iostream>
#include <minhook/MinHook.h>

using SwapBuffers_t = BOOL(WINAPI*)(HDC);

SwapBuffers_t originalSwapBuffers = nullptr;
void* pSwapBuffers                = nullptr;

BOOL WINAPI HookSwapBuffers(HDC hdc) {
    std::cout << "[HOOK] SwapBuffers called" << std::endl;
    return originalSwapBuffers(hdc);
}

void HookOpenGL()
{
    if (MH_Initialize() != MH_OK) {
        std::cout << "[HOOK] Error al inicializar minhook" << std::endl;
        return;
    }

    HMODULE hGDI = GetModuleHandleA("gdi32.dll");

    pSwapBuffers = GetProcAddress(hGDI, "SwapBuffers");

    if (!pSwapBuffers) {
        std::cout << "[HOOK] SwapBuffers not found!" << std::endl;
    }

    if (MH_CreateHook(pSwapBuffers, &HookSwapBuffers,
        reinterpret_cast<LPVOID*>(&originalSwapBuffers)) != MH_OK) {
        std::cout << "[HOOK] Error hooking SwapBuffers" << std::endl;
        return;
    }

    MH_EnableHook(pSwapBuffers);
}

void UnhookOpenGL()
{
    if (pSwapBuffers)
        MH_DisableHook(pSwapBuffers);

    MH_Uninitialize();
}
