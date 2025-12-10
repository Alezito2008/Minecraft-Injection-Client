#pragma once

#include <jni/jni.h>

class Player {
public:
    Player(jobject playerObj);
    ~Player();

    void jumpFromGround();
private:
    jobject m_instance = nullptr;
    jclass m_class = nullptr;
};