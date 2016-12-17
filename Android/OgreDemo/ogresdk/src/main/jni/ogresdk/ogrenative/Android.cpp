#include "Android.h"
#include "AndroidLog.h"

namespace OgreNative
{
    // OgreNative::NativeActivity* s_NativeActivity = NULL;
    //static JNIEnv* s_pEnv = NULL;
    //static jobject s_pActivity = NULL;

    // NativeActivity& GetNativeActivity()
    // {
    //     return *s_NativeActivity;
    // }

    // JNIEnv* GetJNIEnv()
    // {
    //     return s_NativeActivity->GetJNI();
    // }

    // jobject GetJNIActivity()
    // {
    //     return s_NativeActivity->GetContext();
    // }

    // void PollEvents()
    // {
    //     s_NativeActivity->PollEvents();
    // }

    // void SetEventCallback( MessageCallbackFunction pCallback )
    // {
 //        s_NativeActivity->SetEventCallback( pCallback );
 //    }

    // void SetEventHandler( IAndroidHandler* pHandler )
    // {
    //     s_NativeActivity->SetEventHandler( pHandler );
    // }

    // ANativeWindow* GetWindow()
    // {
    //     return s_NativeActivity->GetWindow();
    // }

    // AAssetManager* GetAssetManager()
    // {
    //     return s_NativeActivity->GetAssetManager();
    // }

    // bool IsWindowVisible()
    // {
    //     return s_NativeActivity->IsVisible();
    // }

    // void ShowKeyboard()
    // {
    //     s_NativeActivity->ShowKeyboard();
    // }

    // void HideKeyboard()
    // {
    //     s_NativeActivity->HideKeyboard();
    // }

    // const char* GetAppDir()
    // {
    //     return s_NativeActivity->GetAppDir();
    // }

    // ClassLoader& GetClassLoader()
    // {
    //     return s_NativeActivity->GetClassLoader();
    // }

    // NotificationManager& GetNotificationManager()
    // {
    //     return s_NativeActivity->GetNotificationManager();
    // }
}

extern "C"
{
    void init_native_activity( JNIEnv* pEnv, jobject pObj, OgreNative::NativeActivity** pInterface )
    {
        LOGV( "[Android]: Setting JNI Environment." );
        //s_pEnv = pEnv;

        OgreNative::NativeActivity *s_NativeActivity = new OgreNative::NativeActivity();

        s_NativeActivity->SetJNI( pEnv, pObj );
        //s_pActivity = s_NativeActivity->GetContext();

        *pInterface = s_NativeActivity;
    }

    void uninit_native_activity( JNIEnv* pEnv, jobject pObj, OgreNative::NativeActivity** pInterface )
    {
        delete *pInterface;
        *pInterface = NULL;
    }
}
