#include <iostream>

#include "modules/modules.h"
#include "utils/jni_utils.h"
#include "mc/Minecraft.h"

class FlyModule : public Module {
public:
    FlyModule() : Module("Fly", Categories::MOVEMENT) {}

    void onTick() override {
        
    }

    void onEnable() override {
        Minecraft& mc = Minecraft::get();
        Player* p = mc.getPlayer();
        p->SetFlying(true);
        delete p;
    }
    void onDisable() override {
        Minecraft& mc = Minecraft::get();
        Player* p = mc.getPlayer();
        p->SetFlying(false);
        delete p;
    }
};

FlyModule flyModule;
