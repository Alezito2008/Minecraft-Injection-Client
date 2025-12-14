#include "Player.h"
#include "utils/jni_utils.h"

Player::Player(jobject playerObj)
{
    m_instance = playerObj;
}

Player::~Player() {
    if (m_instance) {
        env->DeleteGlobalRef(m_instance);
        m_instance = nullptr;
    }
}

void Player::JumpFromGround()
{
    jclass playerClassLocal = env->GetObjectClass(m_instance);
    jmethodID jumpMethod = JNI::GetMethod(playerClassLocal, "jumpFromGround", "()V");
    env->CallVoidMethod(m_instance, jumpMethod);
}

void Player::SetCanFly(bool canFly)
{
    jclass playerClassLocal = env->GetObjectClass(m_instance);
    jfieldID abilitiesField = JNI::GetField(playerClassLocal, "abilities", "Lnet/minecraft/world/entity/player/Abilities;");
    jobject abilitiesObj = env->GetObjectField(m_instance, abilitiesField);
    jclass abilitiesClass = env->GetObjectClass(abilitiesObj);
    jfieldID mayflyField = JNI::GetField(abilitiesClass, "mayfly", "Z");
    env->SetBooleanField(
        abilitiesObj,
        mayflyField,
        (canFly ? JNI_TRUE : JNI_FALSE) // Set mayFly value
    );
    // Free memory
    env->DeleteLocalRef(abilitiesObj);
    env->DeleteLocalRef(abilitiesClass);
    env->DeleteLocalRef(playerClassLocal);
}
