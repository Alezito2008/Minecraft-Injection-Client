#include "main.h"

#include <iostream>
#include "utils/jni_utils.h"
#include "modules/modules.h"
#include "functions.h"
#include "hooks/opengl_hook.h"

void client_main(HMODULE hModule) {
    HookOpenGL();

    while (true) {
        for (const auto mod : modules) {
            mod->Tick();
        }

        if (GetAsyncKeyState(VK_F9)) {
            std::cout << "Toggling all" << std::endl;
            for (const auto mod : modules) {
                mod->Toggle();
            }
        }

        if (GetAsyncKeyState(VK_F10)) {
            break;
        }

        Sleep(50);
    }

    std::cout << "[CLIENT] Starting cleanup" << std::endl;
    UnhookOpenGL();
    std::cout << "[CLIENT] Exiting... (you can close this window now)" << std::endl;
    
    if (vm) vm->DetachCurrentThread();
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
}