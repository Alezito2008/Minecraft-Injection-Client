#include "utils/jni_utils.h"

JavaVM* vm = nullptr;

JNIEnv* JNI::GetJNIEnv() {
    JNIEnv* env = nullptr;
    if (vm->GetEnv((void**)&env, JNI_VERSION_21) != JNI_OK) {
        vm->AttachCurrentThread((void**)&env, nullptr);
    }
    return env;
}

jclass JNI::FindClass(JNIEnv* env, const char *name)
{
    jclass local = env->FindClass(name);
    if (!local) 
        std::cout << "[JNI] Failed to find class: " << name << std::endl;
    jclass global = (jclass) env->NewGlobalRef(local);
    env->DeleteLocalRef(local);
    return global;
}

jmethodID JNI::GetMethod(JNIEnv* env, jclass clazz, const char *name, const char* sig)
{
    jmethodID m = env->GetMethodID(clazz, name, sig);
    if (!m)
        std::cout << "[JNI] Failed to get method: " << name << sig << std::endl;
    return m;
}

jmethodID JNI::GetStaticMethod(JNIEnv* env, jclass clazz, const char *name, const char *sig)
{
    jmethodID m = env->GetStaticMethodID(clazz, name, sig);
    if (!m)
        std::cout << "[JNI] Failed to get static method: " << name << sig << std::endl;
    return m;
}

jfieldID JNI::GetField(JNIEnv* env, jclass clazz, const char* name, const char* sig)
{
    jfieldID f = env->GetFieldID(clazz, name, sig);
    if (!f)
        std::cout << "[JNI] Failed to get field: " << name << sig << std::endl;
    return f;
}
