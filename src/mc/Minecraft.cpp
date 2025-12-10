#include "Minecraft.h"

Minecraft &Minecraft::get()
{
    static Minecraft inst;
    return inst;
}

Player *Minecraft::getPlayer()
{
    jfieldID playerField = JNI::GetField(m_class, "player", "Lnet/minecraft/client/player/LocalPlayer;");
    jobject playerObj = env->GetObjectField(m_instance, playerField);

    if (!playerObj)
        return nullptr;

    return new Player(playerObj);
}

Minecraft::Minecraft()
{
    m_class = JNI::FindClass("net/minecraft/client/Minecraft");
    jmethodID getInstance = JNI::GetStaticMethod(
        m_class,
        "getInstance",
        "()Lnet/minecraft/client/Minecraft;"
    );
    jobject mc_instance = env->CallStaticObjectMethod(m_class, getInstance);
    m_instance = env->NewGlobalRef(mc_instance);
}

Minecraft::~Minecraft()
{
    if (m_instance) {
        env->DeleteGlobalRef(m_instance);
        m_instance = nullptr;
    }
}
