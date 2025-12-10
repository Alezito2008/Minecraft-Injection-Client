#include "main.h"

#include <iostream>
#include "utils/jni_utils.h"
#include "modules/modules.h"
#include "functions.h"

void client_main(HMODULE hModule) {
    while (true) {
        for (const auto mod : modules) {
            mod->onTick();
        }

        if (GetAsyncKeyState(VK_F9)) {
            std::cout << "Enabling all" << std::endl;
            for (const auto mod : modules) {
                std::cout << "Enabled: " << mod->getName() << std::endl;
                mod->Enable();
            }
        }

        if (GetAsyncKeyState(VK_F10)) {
            break;
        }

        Sleep(50);
    }

    std::cout << "Exiting..." << std::endl;
    if (vm) vm->DetachCurrentThread();
    FreeConsole();

    FreeLibraryAndExitThread(hModule, 0);
}