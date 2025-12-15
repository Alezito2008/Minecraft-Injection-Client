#include "GUI.h"

#include <iostream>

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_win32.h>

static HGLRC s_originalContext = nullptr;
static HGLRC s_imguiContext = nullptr;
static HDC s_hdc = nullptr;

static bool isVisible = false;

void GUI::Init(HWND hWindow, HDC hdc, HGLRC originalContext)
{
    std::cout << "[GUI] Initializing ImGui" << std::endl;

    s_hdc = hdc;
    s_originalContext = originalContext;
    s_imguiContext = wglCreateContext(hdc);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(hWindow);
    ImGui_ImplOpenGL3_Init();

    std::cout << "[GUI] ImGui initialized" << std::endl;
}

void GUI::Shutdown()
{
    std::cout << "[GUI] Shutting down" << std::endl;
    Hide();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void GUI::Draw()
{
    if (!s_originalContext || !isVisible) return;

    wglMakeCurrent(s_hdc, s_imguiContext);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    // Overlay

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
    ImGui::SetNextWindowBgAlpha(0.5);
    ImGui::Begin("Overlay", nullptr, 
          ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar
        | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs
    );
    ImGui::End();

    ImGui::Begin("Test");
    ImGui::Text("This is a test");
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    wglMakeCurrent(s_hdc, s_originalContext);
}

void GUI::Show()
{
    isVisible = true;
}

void GUI::Hide()
{
    isVisible = false;
}

void GUI::Toggle()
{
    isVisible ? Hide() : Show();
}

bool GUI::IsVisible()
{
    return isVisible;
}

HGLRC GUI::GetContext()
{
    return s_imguiContext;
}
