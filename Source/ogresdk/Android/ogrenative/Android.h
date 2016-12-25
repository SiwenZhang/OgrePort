#ifndef OGRE_ANDROID_H
#define OGRE_ANDROID_H

#include "NativeActivity.h"

void init_native_activity(JNIEnv* pEnv, jobject pObj, NativeActivity** pInterface);

void uninit_native_activity(JNIEnv* pEnv, jobject pObj, NativeActivity** pInterface);

#endif
