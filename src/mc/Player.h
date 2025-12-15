#pragma once

#include <jni/jni.h>

class Player {
public:
    Player(jobject playerObj);
    ~Player();

    void JumpFromGround();
    void SetFlying(bool flying);
private:
    jobject m_instance = nullptr;
};