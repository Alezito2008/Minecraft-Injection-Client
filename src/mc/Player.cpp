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

bool Player::IsSurvival()
{
    JNI::LocalFrame frame(8);
    jclass playerClass = env->GetObjectClass(m_instance);
    jfieldID minecraftField = JNI::GetField(playerClass, "minecraft", "Lnet/minecraft/client/Minecraft;");
    jobject minecraftObj = env->GetObjectField(m_instance, minecraftField);
    jclass minecraftClass = env->GetObjectClass(minecraftObj);
    jfieldID gamemodeField = JNI::GetField(minecraftClass, "gameMode", "Lnet/minecraft/client/multiplayer/MultiPlayerGameMode;");
    jobject gamemodeObj = env->GetObjectField(minecraftObj, gamemodeField);
    jclass gamemodeClass = env->GetObjectClass(gamemodeObj);
    jmethodID isSurvivalMethod = JNI::GetMethod(gamemodeClass, "canHurtPlayer", "()Z");
    jboolean result = env->CallBooleanMethod(gamemodeObj, isSurvivalMethod);
    std::cout << "Is survival: " << (bool)result << std::endl;
    return static_cast<bool>(result);
}

void Player::JumpFromGround()
{
    jclass playerClassLocal = env->GetObjectClass(m_instance);
    jmethodID jumpMethod = JNI::GetMethod(playerClassLocal, "jumpFromGround", "()V");
    env->CallVoidMethod(m_instance, jumpMethod);

    env->DeleteLocalRef(playerClassLocal);
}

void Player::SetFlying(bool flying)
{
    jclass playerClassLocal = env->GetObjectClass(m_instance);
    jfieldID abilitiesField = JNI::GetField(playerClassLocal, "abilities", "Lnet/minecraft/world/entity/player/Abilities;");
    jobject abilitiesObj = env->GetObjectField(m_instance, abilitiesField);
    jclass abilitiesClass = env->GetObjectClass(abilitiesObj);
    jfieldID mayflyField = JNI::GetField(abilitiesClass, "mayfly", "Z");
    jfieldID flyingField = JNI::GetField(abilitiesClass, "flying", "Z");
    env->SetBooleanField(
        abilitiesObj,
        mayflyField,
        (flying ? JNI_TRUE : !IsSurvival()) // Set mayfly value
    );
    env->SetBooleanField(
        abilitiesObj,
        flyingField,
        (flying ? JNI_TRUE : JNI_FALSE) // Set flying value
    );
    if (flying) JumpFromGround();

    // Free memory
    env->DeleteLocalRef(abilitiesObj);
    env->DeleteLocalRef(abilitiesClass);
    env->DeleteLocalRef(playerClassLocal);
}
