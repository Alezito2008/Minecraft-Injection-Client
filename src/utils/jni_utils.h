#pragma once

#include <jni/jni.h>
#include <iostream>

extern JNIEnv* env;
extern JavaVM* vm;

namespace JNI {
    jclass FindClass(const char* name);
    jmethodID GetMethod(jclass clazz, const char* name, const char* sig);
    jmethodID GetStaticMethod(jclass clazz, const char* name, const char* sig);
    jfieldID GetField(jclass clazz, const char* name, const char* sig);
}
