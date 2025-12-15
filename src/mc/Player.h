#pragma once

#include <jni/jni.h>

class Player {
public:
    Player(jobject playerObj);
    ~Player();

    bool IsSurvival(JNIEnv* env);
    void JumpFromGround(JNIEnv* env);
    void SetFlying(JNIEnv* env, bool flying);
private:
    jobject m_instance = nullptr;
};