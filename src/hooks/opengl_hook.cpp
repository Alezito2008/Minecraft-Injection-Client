#include "opengl_hook.h"

#include <iostream>
#include <minhook/MinHook.h>

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_win32.h>

#include <gl/GL.h>

using SwapBuffers_t = BOOL(WINAPI*)(HDC);

// Can't use ImGui_ImplWin32_WndProcHandler without this
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam); 

static SwapBuffers_t oSwapBuffers = nullptr;
static void* pSwapBuffers = nullptr;

static bool ImGuiInitialized = false;
static HWND hWindow = nullptr;
static WNDPROC oWndProc = nullptr;
static HGLRC imguiContext = nullptr;

LRESULT CALLBACK HookedWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{   
    if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam))
        return TRUE;

    ImGuiIO& io = ImGui::GetIO();
    if (io.WantCaptureMouse || io.WantCaptureKeyboard) return TRUE; // Let ImGui capture mouse and keyboard

    return CallWindowProc(oWndProc, hwnd, msg, wParam, lParam);
}

BOOL WINAPI HookSwapBuffers(HDC hdc) {
    HGLRC originalContext = wglGetCurrentContext();
    if (!originalContext) return oSwapBuffers(hdc);

    if (!ImGuiInitialized) {
        ImGuiInitialized = true;
        std::cout << "[IMGUI] Initializing ImGui" << std::endl;

        imguiContext = wglCreateContext(hdc);

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        // Redirect windows events to ImGui
        hWindow = WindowFromDC(hdc);
        oWndProc = (WNDPROC)SetWindowLongPtr(hWindow, GWLP_WNDPROC, (LONG_PTR)HookedWndProc);
        
        ImGui_ImplWin32_Init(hWindow);
        ImGui_ImplOpenGL3_Init();
    }
    // std::cout << "[HOOK] SwapBuffers called" << std::endl;

    wglMakeCurrent(hdc, imguiContext);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Test");
    ImGui::Text("This is a test");
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    wglMakeCurrent(hdc, originalContext);

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

    std::cout << "[IMGUI] Shutting down" << std::endl;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}
