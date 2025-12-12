#pragma once

#include <windows.h>

namespace GUI {
    void Init(HWND hWindow, HDC hdc, HGLRC originalContext);
    void Shutdown();

    void Draw();

    void Enable();
    void Disable();
    bool IsEnabled();

    HGLRC GetContext();
}
