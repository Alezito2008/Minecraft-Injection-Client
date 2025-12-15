#include "Minecraft.h"

Minecraft &Minecraft::get(JNIEnv *env)
{
    static Minecraft inst(env);
    return inst;
}

Player *Minecraft::getPlayer()
{
    if (!m_class || !m_instance) return nullptr;
    JNIEnv* env = JNI::GetJNIEnv();

    jfieldID playerField = JNI::GetField(env, m_class, "player", "Lnet/minecraft/client/player/LocalPlayer;");
    jobject playerObj = env->GetObjectField(m_instance, playerField);

    if (!playerObj) return nullptr;

    jobject globalPlayerObj = env->NewGlobalRef(playerObj);

    return new Player(globalPlayerObj);
}

Minecraft::Minecraft(JNIEnv *env)
{
    JNI::LocalFrame frame(env);

    jclass mc_class = JNI::FindClass(env, "net/minecraft/client/Minecraft");

    jmethodID getInstance = JNI::GetStaticMethod(
        env,
        mc_class,
        "getInstance",
        "()Lnet/minecraft/client/Minecraft;"
    );

    if (!getInstance) {
        env->ExceptionDescribe();
        return;
    }

    jobject mc_instance = env->CallStaticObjectMethod(mc_class, getInstance);

    if (!mc_instance) {
        std::cout << "mc_instance is NULL" << std::endl;
        return;
    }

    m_class = (jclass) env->NewGlobalRef(mc_class);
    m_instance = env->NewGlobalRef(mc_instance);
}

Minecraft::~Minecraft()
{
    JNIEnv* env = JNI::GetJNIEnv();

    if (m_class) {
        env->DeleteGlobalRef(m_class);
        m_class = nullptr;
    }

    if (m_instance) {
        env->DeleteGlobalRef(m_instance);
        m_instance = nullptr;
    }
}
