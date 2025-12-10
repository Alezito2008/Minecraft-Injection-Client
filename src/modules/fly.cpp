#include <iostream>

#include "mc/Minecraft.h"
#include "modules.h"
#include "utils/jni_utils.h"
#include "functions.h"

class FlyModule : public Module {
public:
    FlyModule() : Module("Fly") {}

    void onTick() override {
        if (enabled) {
            Minecraft& mc = Minecraft::get();
            Player* p = mc.getPlayer();

            if (!p) {
                std::cout << "Player not found, not jumping" << std::endl;
                return;
            }
            
            p->jumpFromGround();
        }
    }

    void onEnable() override {
        std::cout << "Enabled flight" << std::endl;
    }
    void onDisable() override {}
};

FlyModule flyModule;
