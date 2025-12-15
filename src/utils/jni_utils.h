#pragma once

#include <jni/jni.h>
#include <iostream>

extern JavaVM* vm;

namespace JNI {
    struct LocalFrame {
        bool active;
        JNIEnv* env;

        LocalFrame(JNIEnv* env, jint capacity = 8) : active(false), env(env) {
            if (env->PushLocalFrame(capacity) == JNI_OK) {
                active = true;
            }
        }

        ~LocalFrame() {
            if (active) {
                env->PopLocalFrame(nullptr);
            }
        }
    };

    JNIEnv* GetJNIEnv();

    jclass FindClass(JNIEnv* env, const char* name);
    jmethodID GetMethod(JNIEnv* env, jclass clazz, const char* name, const char* sig);
    jmethodID GetStaticMethod(JNIEnv* env, jclass clazz, const char* name, const char* sig);
    jfieldID GetField(JNIEnv* env, jclass clazz, const char* name, const char* sig);
}
