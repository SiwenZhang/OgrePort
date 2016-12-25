#include <dlfcn.h>
#include <unistd.h>
#include <stdio.h>

#include "Android.h"

#ifdef __cplusplus
extern "C" {
#endif
    JNIEXPORT void JNICALL nativeMain(JNIEnv* pEnv, jobject pObj, jstring strApplicationName);

    JNIEXPORT void JNICALL nativeOnShutdown(JNIEnv* pEnv, jobject pObj);
    JNIEXPORT void JNICALL nativeOnLowMemory(JNIEnv* pEnv, jobject pObj);
    JNIEXPORT void JNICALL nativeOnTouch(JNIEnv* pEnv, jobject pObj, int iPointerID, float fPosX, float fPosY, int iAction);
    JNIEXPORT void JNICALL nativeOnKeyUp(JNIEnv* pEnv, jobject pObj, int iKeyCode, int iUnicodeChar);
    JNIEXPORT void JNICALL nativeOnSurfaceChanged(JNIEnv* pEnv, jobject pObj, int iFormat, int iWidth, int iHeight);
    JNIEXPORT void JNICALL nativeOnSurfaceCreated(JNIEnv* pEnv, jobject pObj, jobject pSurface);
    JNIEXPORT void JNICALL nativeOnSurfaceDestroyed(JNIEnv* pEnv, jobject pObj);
    JNIEXPORT void JNICALL nativeApplicationPaused(JNIEnv* pEnv, jobject pObj);
    JNIEXPORT void JNICALL nativeApplicationResumed(JNIEnv* pEnv, jobject pObj);
    JNIEXPORT void JNICALL nativeWindowShown(JNIEnv* pEnv, jobject pObj);
    JNIEXPORT void JNICALL nativeWindowHidden(JNIEnv* pEnv, jobject pObj);

    JNIEXPORT void JNICALL nativeInit(JNIEnv* pEnv, jobject pObj, jobject pSurface);
    JNIEXPORT void JNICALL nativeUninit(JNIEnv* pEnv, jobject pObj);
#ifdef __cplusplus
};
#endif

static const JNINativeMethod g_NativActivityeMethods[] = {
    {"nativeMain", "(Ljava/lang/String;)V", (void*)nativeMain},

    {"nativeOnShutdown", "()V", (void*)nativeOnShutdown},
    {"nativeOnLowMemory", "()V", (void*)nativeOnLowMemory},
    {"nativeOnTouch", "(IFFI)V", (void*)nativeOnTouch},
    {"nativeOnKeyUp", "(II)V", (void*)nativeOnKeyUp},
    {"nativeOnSurfaceChanged", "(III)V", (void*)nativeOnSurfaceChanged},
    {"nativeOnSurfaceCreated", "(Landroid/view/Surface;)V", (void*)nativeOnSurfaceCreated},
    {"nativeOnSurfaceDestroyed", "()V", (void*)nativeOnSurfaceDestroyed},
    {"nativeApplicationPaused", "()V", (void*)nativeApplicationPaused},
    {"nativeApplicationResumed", "()V", (void*)nativeApplicationResumed},
    {"nativeWindowShown", "()V", (void*)nativeWindowShown},
    {"nativeWindowHidden", "()V", (void*)nativeWindowHidden},

    {"nativeInit", "(Landroid/content/res/AssetManager;)V", (void*)nativeInit},
    {"nativeUninit", "()V", (void*)nativeUninit},
};

#define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* pJavaVM, void* reserved) {
    JNIEnv* pEnv;
    if (pJavaVM->GetEnv(reinterpret_cast<void**>(&pEnv), JNI_VERSION_1_6) != JNI_OK){
        return -1;
    }

    // Get jclass with pEnv->FindClass.
    // Register methods with pEnv->RegisterNatives.
    jclass jNativeSurfaceViewClass = pEnv->FindClass("com/ccsu/ogresdk/OgreSurfaceView");
    pEnv->RegisterNatives(jNativeSurfaceViewClass, g_NativActivityeMethods, NELEM(g_NativActivityeMethods));

    return JNI_VERSION_1_6;
}

NativeActivity* s_pNativeActivity = NULL;

JNIEXPORT void JNICALL nativeMain(JNIEnv* pEnv, jobject pObj, jstring strApplicationName) {
    // Application Name
    const char* pApplicationName = pEnv->GetStringUTFChars(strApplicationName, NULL);
    char strLibName[128];
    sprintf(strLibName, "lib%s.so", pApplicationName);

    pEnv->ReleaseStringUTFChars(strApplicationName, pApplicationName);

    // Error message
    const char* pErrorString = NULL;

    // Library functions
    void (*ogreapp_main)(IAppInterface* appInterface);

    // Load library
    void* pLibraryHandle = dlopen(strLibName, RTLD_NOW | RTLD_GLOBAL);
    if (!pLibraryHandle) {
        throw "Error";
    }

    // Clear existing errors
    dlerror();

    // Retrieve android_main
    *(void **) (&ogreapp_main) = dlsym(pLibraryHandle, "OgreMain");
    if ((pErrorString = dlerror()) != NULL) {
        throw "Error";
    }

    // Call user defined main
    (*ogreapp_main)(s_pNativeActivity->GetAppInterface());

    dlclose(pLibraryHandle);
}

/**********************************************************************************/
/*                                     OnTouch                                    */
/**********************************************************************************/
JNIEXPORT void JNICALL nativeOnTouch(JNIEnv* env, jobject obj, int iPointerID, float fPosX, float fPosY, int iAction) {
    if (s_pNativeActivity) {
        s_pNativeActivity->OnTouch(iPointerID, fPosX, fPosY, iAction);
    }
}

JNIEXPORT void JNICALL nativeOnKeyUp(JNIEnv* env, jobject obj, int iKeyCode, int iUnicodeChar) {
    if (s_pNativeActivity) {
        s_pNativeActivity->OnKeyUp(iKeyCode, iUnicodeChar);
    }
}

JNIEXPORT void JNICALL nativeOnSurfaceChanged(JNIEnv* env, jobject obj, int iFormat, int iWidth, int iHeight) {
    if (s_pNativeActivity) {
        s_pNativeActivity->OnSurfaceChanged(iFormat, iWidth, iHeight);
    }
}

JNIEXPORT void JNICALL nativeOnSurfaceCreated(JNIEnv* pEnv, jobject pObj, jobject pSurface) {
    if (s_pNativeActivity) {
        s_pNativeActivity->OnSurfaceCreated(pSurface);
    }
}

JNIEXPORT void JNICALL nativeOnSurfaceDestroyed(JNIEnv* pEnv, jobject pObj) {
    if (s_pNativeActivity) {
        s_pNativeActivity->OnSurfaceDestroyed();
    }
}

JNIEXPORT void JNICALL nativeApplicationPaused(JNIEnv* pEnv, jobject pObj) {
    if (s_pNativeActivity) {
        s_pNativeActivity->OnApplicationPaused();
    }
}

JNIEXPORT void JNICALL nativeApplicationResumed(JNIEnv* pEnv, jobject pObj) {
    if (s_pNativeActivity) {
        s_pNativeActivity->OnApplicationResumed();
    }
}

JNIEXPORT void JNICALL nativeWindowShown( JNIEnv* pEnv, jobject pObj ) {
    if (s_pNativeActivity) {
        s_pNativeActivity->OnWindowShown();
    }
}

JNIEXPORT void JNICALL nativeWindowHidden(JNIEnv* pEnv, jobject pObj) {
    if (s_pNativeActivity) {
        s_pNativeActivity->OnWindowHidden();
    }
}

JNIEXPORT void JNICALL nativeOnShutdown(JNIEnv* pEnv, jobject pObj) {
    if (s_pNativeActivity) {
        s_pNativeActivity->OnApplicationShutdown();
    }
}

JNIEXPORT void JNICALL nativeOnLowMemory(JNIEnv* pEnv, jobject pObj) {
    if (s_pNativeActivity) {
        s_pNativeActivity->OnLowMemory();
    }
}

JNIEXPORT void JNICALL nativeInit(JNIEnv* pEnv, jobject pObj, jobject pAssetManager) {
    // Init native activity
    init_native_activity(pEnv, pObj, &s_pNativeActivity);

    if (s_pNativeActivity) {
        s_pNativeActivity->setAssetManager(pAssetManager);
    }
}

JNIEXPORT void JNICALL nativeUninit(JNIEnv* pEnv, jobject pObj) {
    uninit_native_activity(pEnv, pObj, &s_pNativeActivity);
}
