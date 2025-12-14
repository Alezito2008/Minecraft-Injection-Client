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

    ImGui::Begin("Test");
    ImGui::Text("This is a test");
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    wglMakeCurrent(s_hdc, s_originalContext);
}

void GUI::Show()
{
    std::cout << "Called GUI::Show()" << std::endl;
    isVisible = true;
}

void GUI::Hide()
{
    isVisible = false;
}

void GUI::Toggle()
{
    isVisible ? Hide() : Show();
    std::cout << "Visible: " << isVisible << std::endl;
}

bool GUI::IsVisible()
{
    return isVisible;
}

HGLRC GUI::GetContext()
{
    return s_imguiContext;
}
