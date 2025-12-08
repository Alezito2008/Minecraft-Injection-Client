#pragma once

#include <windows.h>
#include "jni/jni.h"

extern JavaVM* vm;
extern JNIEnv* env;

extern void client_main(HMODULE hModule);
