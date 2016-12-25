#include "Android.h"

void init_native_activity(JNIEnv* pEnv, jobject pObj, NativeActivity** pInterface) {
    NativeActivity *s_NativeActivity = new NativeActivity();

    s_NativeActivity->SetJNI(pEnv, pObj);

    *pInterface = s_NativeActivity;
}

void uninit_native_activity(JNIEnv* pEnv, jobject pObj, NativeActivity** pInterface) {
    delete *pInterface;
    *pInterface = NULL;
}
