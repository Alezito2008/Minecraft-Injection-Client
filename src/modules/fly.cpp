#include <iostream>

#include "modules.h"
#include "utils/jni_utils.h"
#include "functions.h"

class FlyModule : public Module {
public:
    FlyModule() : Module("Fly") {}

    void onTick() override {
        if (enabled) {
            player_jump(env);
        }
    }

    void onEnable() override {
        std::cout << "Enabled flight" << std::endl;
    }
    void onDisable() override {}
};

FlyModule flyModule;
