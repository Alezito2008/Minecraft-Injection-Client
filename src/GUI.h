#pragma once

#include <windows.h>

namespace GUI {
    void Init(HWND hWindow, HDC hdc, HGLRC originalContext);
    void Shutdown();

    void Draw();

    void Show();
    void Hide();
    bool IsVisible();

    HGLRC GetContext();
}
