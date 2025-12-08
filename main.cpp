#include "main.h"
#include "functions.h"
#include <iostream>

void client_main(HMODULE hModule) {
    while (true) {
        player_jump(env);

        if (GetAsyncKeyState(VK_F10)) {
            break;
        }

        Sleep(50);
    }

    std::cout << "Exiting..." << std::endl;
    if (vm) vm->DetachCurrentThread();
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
    return;
}