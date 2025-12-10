#pragma once
#include "utils/jni_utils.h"
#include "Player.h"

class Minecraft {
public:
    static Minecraft& get();

    inline jobject getJavaInstance() const { return m_instance; }

    Player* getPlayer();
private:
    Minecraft();
    ~Minecraft();

    jobject m_instance = nullptr;
    jclass m_class = nullptr;
};
