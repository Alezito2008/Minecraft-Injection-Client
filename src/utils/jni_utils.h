#pragma once

#include <jni/jni.h>
#include <iostream>

extern JNIEnv* env;
extern JavaVM* vm;

namespace JNI {
    struct LocalFrame {
        bool active;

        LocalFrame(jint capacity = 8) : active(false) {
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

    jclass FindClass(const char* name);
    jmethodID GetMethod(jclass clazz, const char* name, const char* sig);
    jmethodID GetStaticMethod(jclass clazz, const char* name, const char* sig);
    jfieldID GetField(jclass clazz, const char* name, const char* sig);
}
