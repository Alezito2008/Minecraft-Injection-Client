#include "functions.h"

void player_jump(JNIEnv* env) {
    jclass minecraftClass = env->FindClass("fzz");
    jmethodID getInstance = env->GetStaticMethodID(minecraftClass, "W", "()Lfzz;");
    jobject mc_instance = env->CallStaticObjectMethod(minecraftClass, getInstance);

    jfieldID playerField = env->GetFieldID(minecraftClass, "s", "Lhep;");
    jobject player = env->GetObjectField(mc_instance, playerField);

    jclass player_class = env->GetObjectClass(player);

    // call player.jump()
    jmethodID jumpMethod = env->GetMethodID(player_class, "u", "()V");
    env->CallVoidMethod(player, jumpMethod);
}