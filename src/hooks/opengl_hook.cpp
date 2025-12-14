#include "opengl_hook.h"

#include <iostream>
#include <minhook/MinHook.h>

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_win32.h>

#include "GUI.h"

#include <gl/GL.h>

using SwapBuffers_t = BOOL(WINAPI*)(HDC);

// Can't use ImGui_ImplWin32_WndProcHandler without this
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam); 

static SwapBuffers_t oSwapBuffers = nullptr;
static void* pSwapBuffers = nullptr;

static bool initialized = false;
static HWND hWindow = nullptr;
static WNDPROC oWndProc = nullptr;

LRESULT CALLBACK HookedWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{   
    if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam))
        return TRUE;

    ImGuiIO& io = ImGui::GetIO();
    if (io.WantCaptureMouse || io.WantCaptureKeyboard) return TRUE; // Let ImGui capture mouse and keyboard

    return CallWindowProc(oWndProc, hwnd, msg, wParam, lParam);
}

BOOL WINAPI HookSwapBuffers(HDC hdc) {
    if (!initialized) {
        initialized = true;
        // Redirect windows events to ImGui
        hWindow = WindowFromDC(hdc);
        oWndProc = (WNDPROC)SetWindowLongPtr(hWindow, GWLP_WNDPROC, (LONG_PTR)HookedWndProc);
        
        HGLRC originalContext = wglGetCurrentContext();
        GUI::Init(hWindow, hdc, originalContext);
        GUI::Show(); // DEBUG
    }

    GUI::Draw();

    return oSwapBuffers(hdc);
}

void HookOpenGL()
{
    std::cout << "[HOOK] Hooking SwapBuffers (gdi32.dll)" << std::endl;

    if (MH_Initialize() != MH_OK) {
        std::cout << "[HOOK] Error initializing MinHook" << std::endl;
        return;
    }

    HMODULE hGDI = GetModuleHandleA("gdi32.dll");

    if (!hGDI) {
        std::cout << "[HOOK] Failed to find gdi32.dll" << std::endl;
        return;
    }

    pSwapBuffers = GetProcAddress(hGDI, "SwapBuffers");

    if (!pSwapBuffers) {
        std::cout << "[HOOK] SwapBuffers not found!" << std::endl;
    }

    if (MH_CreateHook(pSwapBuffers, &HookSwapBuffers,
        reinterpret_cast<LPVOID*>(&oSwapBuffers)) != MH_OK) {
        std::cout << "[HOOK] Error hooking SwapBuffers" << std::endl;
        return;
    }

    MH_EnableHook(pSwapBuffers);
}

void UnhookOpenGL()
{
    std::cout << "[HOOK] Removing hooks" << std::endl;
    if (pSwapBuffers)
        MH_DisableHook(pSwapBuffers);
    MH_Uninitialize();

    SetWindowLongPtr(hWindow, GWLP_WNDPROC, (LONG_PTR)oWndProc);
    GUI::Shutdown();
}
