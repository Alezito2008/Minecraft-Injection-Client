#pragma once

#include <functional>
#include <unordered_map>

class InputManager {
public:
    struct KeyData {
        bool pressed;
        std::function<void()> onPress;
    };

    static void RegisterKey(int vk, std::function<void()> onPress);
    static void Update();

private:
    static std::unordered_map<int,KeyData> keyMap;
};