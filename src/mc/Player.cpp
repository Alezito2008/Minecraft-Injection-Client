#include "Player.h"
#include "utils/jni_utils.h"

Player::Player(jobject playerObj)
{
    jclass playerClass = env->GetObjectClass(playerObj);

    m_instance = env->NewGlobalRef(playerObj);
    m_class = (jclass) env->NewGlobalRef(playerClass);
}

Player::~Player() {
    if (m_instance) {
        env->DeleteGlobalRef(m_instance);
        m_instance = nullptr;
    }

    if (m_class) {
        env->DeleteGlobalRef(m_class);
        m_class = nullptr;
    }
}

void Player::jumpFromGround()
{
    jmethodID jumpMethod = JNI::GetMethod(m_class, "jumpFromGround", "()V");
    env->CallVoidMethod(m_instance, jumpMethod);
}
