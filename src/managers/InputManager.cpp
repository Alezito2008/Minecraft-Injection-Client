#include "InputManager.h"

#include <windows.h>

std::unordered_map<int,InputManager::KeyData> InputManager::keyMap;

void InputManager::RegisterKey(int vk, std::function<void()> onPress)
{
    keyMap[vk] = { false, onPress };
}

void InputManager::Update()
{
    for (auto& [vk, data] : keyMap) {
        bool pressed = GetAsyncKeyState(vk);
        if (pressed && !data.pressed) {
            data.onPress();
        }
        data.pressed = pressed;
    }
}
