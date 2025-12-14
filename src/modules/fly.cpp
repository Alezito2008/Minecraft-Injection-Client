#include <iostream>

#include "mc/Minecraft.h"
#include "modules.h"
#include "utils/jni_utils.h"
#include "functions.h"

class FlyModule : public Module {
public:
    FlyModule() : Module("Fly") {}

    void onTick() override {
        
    }

    void onEnable() override {
        Minecraft& mc = Minecraft::get();
        Player* p = mc.getPlayer();
        p->SetCanFly(true);
        delete p;
    }
    void onDisable() override {
        Minecraft& mc = Minecraft::get();
        Player* p = mc.getPlayer();
        p->SetCanFly(false);
        delete p;
    }
};

FlyModule flyModule;
