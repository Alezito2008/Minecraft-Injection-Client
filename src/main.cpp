#include "main.h"

#include <iostream>
#include "utils/jni_utils.h"
#include "modules/modules.h"
#include "hooks/opengl_hook.h"
#include "managers/InputManager.h"
#include "GUI.h"

void client_main(HMODULE hModule) {
    HookOpenGL();

    InputManager::RegisterKey(VK_RSHIFT, GUI::Toggle);

    while (true) {
        for (const auto mod : modules) {
            mod->Tick();
        }

        // Toggle all
        if (GetAsyncKeyState(VK_F9)) {
            std::cout << "Toggling all" << std::endl;
            for (const auto mod : modules) {
                mod->Toggle();
            }
        }

        // Exit
        if (GetAsyncKeyState(VK_F10)) {
            break;
        }

        InputManager::Update();
        Sleep(50);
    }

    std::cout << "[CLIENT] Starting cleanup" << std::endl;
    UnhookOpenGL();
    std::cout << "[CLIENT] Exiting..." << std::endl;
    
    if (vm) vm->DetachCurrentThread();

    // Give some time to shut down
    // FIXME
    Sleep(500);
    std::cout << "You can now close this window" << std::endl;

    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
}