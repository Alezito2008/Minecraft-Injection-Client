#include "opengl_hook.h"

#include <iostream>
#include <minhook/MinHook.h>

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_win32.h>

using SwapBuffers_t = BOOL(WINAPI*)(HDC);

// Tengo que hacer esto porque sino no me deja usar ImGui_ImplWin32_WndProcHandler
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam); 

SwapBuffers_t originalSwapBuffers = nullptr;
void* pSwapBuffers                = nullptr;

static HWND hWindow = nullptr;
static bool ImGuiInitialized = false;

static WNDPROC oWndProc = nullptr;

LRESULT CALLBACK HookedWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    // ImGuiIO& io = ImGui::GetIO(); (void)io;
    
    if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam))
        return true;

    return CallWindowProc(oWndProc, hwnd, msg, wParam, lParam);
}

BOOL WINAPI HookSwapBuffers(HDC hdc) {
    if (!ImGuiInitialized) {
        std::cout << "[IMGUI] Initializing ImGui" << std::endl;
        ImGuiInitialized = true;

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGui::StyleColorsDark();

        hWindow = WindowFromDC(hdc);

        // Redirect windows events to ImGui
        oWndProc = (WNDPROC)SetWindowLongPtr(
            hWindow, GWLP_WNDPROC, (LONG_PTR)HookedWndProc
        );
        
        ImGui_ImplWin32_Init(hWindow);
        ImGui_ImplOpenGL3_Init();
    }
    // std::cout << "[HOOK] SwapBuffers called" << std::endl;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Test");
    ImGui::Text("This is a test");
    ImGui::Button("Button");
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    return originalSwapBuffers(hdc);
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
        reinterpret_cast<LPVOID*>(&originalSwapBuffers)) != MH_OK) {
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
