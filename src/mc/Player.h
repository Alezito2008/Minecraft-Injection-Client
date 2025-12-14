#pragma once

#include <jni/jni.h>

class Player {
public:
    Player(jobject playerObj);
    ~Player();

    void JumpFromGround();
    void SetCanFly(bool canFly);
private:
    jobject m_instance = nullptr;
};