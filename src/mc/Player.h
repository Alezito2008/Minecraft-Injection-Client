#pragma once

#include <jni/jni.h>

class Player {
public:
    Player(jobject playerObj);
    ~Player();

    bool IsSurvival();
    void JumpFromGround();
    void SetFlying(bool flying);
private:
    jobject m_instance = nullptr;
};