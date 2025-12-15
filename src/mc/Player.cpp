#include "Player.h"
#include "utils/jni_utils.h"

Player::Player(jobject playerObj)
{
    m_instance = playerObj;
}

Player::~Player() {
    JNIEnv* env = JNI::GetJNIEnv();

    if (m_instance) {
        env->DeleteGlobalRef(m_instance);
        m_instance = nullptr;
    }
}

bool Player::IsSurvival(JNIEnv* env)
{
    JNI::LocalFrame frame(env, 8);
    jclass playerClass = env->GetObjectClass(m_instance);
    jfieldID minecraftField = JNI::GetField(env, playerClass, "minecraft", "Lnet/minecraft/client/Minecraft;");
    jobject minecraftObj = env->GetObjectField(m_instance, minecraftField);
    jclass minecraftClass = env->GetObjectClass(minecraftObj);
    jfieldID gamemodeField = JNI::GetField(env, minecraftClass, "gameMode", "Lnet/minecraft/client/multiplayer/MultiPlayerGameMode;");
    jobject gamemodeObj = env->GetObjectField(minecraftObj, gamemodeField);
    jclass gamemodeClass = env->GetObjectClass(gamemodeObj);
    jmethodID isSurvivalMethod = JNI::GetMethod(env, gamemodeClass, "canHurtPlayer", "()Z");
    jboolean result = env->CallBooleanMethod(gamemodeObj, isSurvivalMethod);
    std::cout << "Is survival: " << (bool)result << std::endl;
    return result == JNI_TRUE;
}

void Player::JumpFromGround(JNIEnv* env)
{
    jclass playerClassLocal = env->GetObjectClass(m_instance);
    jmethodID jumpMethod = JNI::GetMethod(env, playerClassLocal, "jumpFromGround", "()V");
    env->CallVoidMethod(m_instance, jumpMethod);

    env->DeleteLocalRef(playerClassLocal);
}

void Player::SetFlying(JNIEnv* env, bool flying)
{
    bool gamemodeCanFly = !IsSurvival(env);

    jclass playerClassLocal = env->GetObjectClass(m_instance);
    jfieldID abilitiesField = JNI::GetField(env, playerClassLocal, "abilities", "Lnet/minecraft/world/entity/player/Abilities;");
    jobject abilitiesObj = env->GetObjectField(m_instance, abilitiesField);
    jclass abilitiesClass = env->GetObjectClass(abilitiesObj);
    jfieldID mayflyField = JNI::GetField(env, abilitiesClass, "mayfly", "Z");
    jfieldID flyingField = JNI::GetField(env, abilitiesClass, "flying", "Z");
    env->SetBooleanField(
        abilitiesObj,
        mayflyField,
        (flying ? JNI_TRUE : (gamemodeCanFly ? JNI_TRUE : JNI_FALSE)) // Set mayfly value
    );
    env->SetBooleanField(
        abilitiesObj,
        flyingField,
        (flying ? JNI_TRUE : JNI_FALSE) // Set flying value
    );
    if (flying) JumpFromGround(env);

    // Free memory
    env->DeleteLocalRef(abilitiesObj);
    env->DeleteLocalRef(abilitiesClass);
    env->DeleteLocalRef(playerClassLocal);
}
