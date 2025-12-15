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
        JNIEnv* env = JNI::GetJNIEnv();

        Minecraft& mc = Minecraft::get(env);
        Player* p = mc.getPlayer();
        p->SetFlying(env, true);
        delete p;
    }
    void onDisable() override {
        JNIEnv* env = JNI::GetJNIEnv();

        Minecraft& mc = Minecraft::get(env);
        Player* p = mc.getPlayer();
        p->SetFlying(env, false);
        delete p;
    }
};

FlyModule flyModule;
