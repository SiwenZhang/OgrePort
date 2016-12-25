#include "NativeActivity.h"

#include <string.h>
#include <assert.h>

NativeActivity::NativeActivity() {
    // Call-backs
    m_pEventHandler = NULL;
    // m_pMessageCallback = NULL;

    // Member variables
    m_pAppDir        = NULL;
    m_pWindow         = NULL;
    m_bIsVisible     = false;

    // JNI Environment
    m_pEnv = NULL;

    // NativeActivity class and reference
    m_pObj = NULL;
    m_pJavaClass = NULL;

    // NativeActivity's methods
    m_hPeekMessageMethod     = NULL;
    m_hPollMessagesMethod     = NULL;

    m_hShowKeyboardMethod     = NULL;
    m_hHideKeyboardMethod     = NULL;

    m_hGetAppDirMethod        = NULL;

    // Message class
    m_hMessageClass = NULL;

    // Message methods
    m_hMessageIDField = NULL;

    // Methods
    m_hGetSystemServiceMethod    = NULL;

    // Context
    m_hGetContextMethod     = NULL;
    m_pContext                 = NULL;
}

NativeActivity::~NativeActivity() {
    m_pEnv->DeleteGlobalRef(m_pObj);
    m_pEnv->DeleteGlobalRef(m_pContext);

    if (m_pAppDir) {
        delete [] m_pAppDir;
    }
}

JNIEnv* NativeActivity::GetJNI() {
    return m_pEnv;
}

jobject NativeActivity::GetObject() {
    return m_pObj;
}

jobject NativeActivity::GetContext() {
    return m_pContext;
}

jclass NativeActivity::GetClass() {
    return m_pJavaClass;
}

void NativeActivity::PollEvents() {
    // Call Java's poll method
    m_pEnv->CallVoidMethod(m_pObj, m_hPollMessagesMethod);

    AndroidMessage message;
    while (PeekEvent(message)) {
        // Send the message to callback
        DispatchMessage(message);
    }
}

void NativeActivity::SetEventHandler(IAppLifeCycle* pHandler) {
    m_pEventHandler = pHandler;
}

bool NativeActivity::PeekEvent(AndroidMessage& message) {
    jobject pObject = m_pEnv->CallObjectMethod(m_pObj, m_hPeekMessageMethod);
    if (pObject) {
        message.iMessageID = m_pEnv->GetIntField(pObject, m_hMessageIDField);
        return true;
    }

    return false;
}

void NativeActivity::DispatchMessage(const AndroidMessage& message) {

}

void NativeActivity::SetJNI(JNIEnv* pEnv, jobject pObj) {
    mAppInterface = new AppInterface(this);

    m_pEnv = pEnv;
    m_pObj = pEnv->NewGlobalRef(pObj);

    m_pJavaClass = pEnv->GetObjectClass(pObj);

    // Retrieve Java methods
    m_hPeekMessageMethod     = pEnv->GetMethodID(m_pJavaClass, "peekMessage", "()Lcom/ccsu/ogresdk/OgreMessage;");
    m_hPollMessagesMethod     = pEnv->GetMethodID(m_pJavaClass, "pollMessages", "()V");

    m_hShowKeyboardMethod     = pEnv->GetMethodID(m_pJavaClass, "showKeyboard", "()V");
    m_hHideKeyboardMethod     = pEnv->GetMethodID(m_pJavaClass, "hideKeyboard", "()V");

    m_hGetAppDirMethod        = pEnv->GetMethodID(m_pJavaClass, "getAppDir", "()Ljava/lang/String;");

    // Message class
    m_hMessageClass     = pEnv->FindClass("com/ccsu/ogresdk/OgreMessage");
    m_hMessageIDField     = pEnv->GetFieldID(m_hMessageClass, "mID", "I");

    // Init member variables
    InitAppDir();

    // Context
    m_hGetContextMethod    = pEnv->GetMethodID(m_pJavaClass, "getContext", "()Landroid/content/Context;");
    m_pContext            = pEnv->NewGlobalRef(pEnv->CallObjectMethod( m_pObj, m_hGetContextMethod));

    jclass hContextClass = pEnv->GetObjectClass(m_pContext );
    m_hGetSystemServiceMethod = pEnv->GetMethodID(hContextClass, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");
}

jobject NativeActivity::GetSystemService(const char* pServiceName) {
    jstring string = m_pEnv->NewStringUTF(pServiceName );
    jobject result = m_pEnv->CallObjectMethod(m_pContext, m_hGetSystemServiceMethod, string);
    m_pEnv->DeleteLocalRef(string);
    return result;
}

void NativeActivity::SetSurface(jobject pSurface) {
    if (pSurface) {
        m_pWindow = ANativeWindow_fromSurface(m_pEnv, pSurface);

        if (m_pEventHandler) {
            m_pEventHandler->OnSurfaceCreated();
        }
    } else {
        if (m_pWindow) {
            ANativeWindow_release(m_pWindow);
            m_pWindow = NULL;

            if (m_pEventHandler) {
                m_pEventHandler->OnSurfaceDestroyed();
            }
        }
    }
}

void NativeActivity::setAssetManager(jobject pAssetManager) {
    if (pAssetManager != NULL) {
        m_pAssetManager = AAssetManager_fromJava(m_pEnv, pAssetManager);
    }
}

ANativeWindow* NativeActivity::GetWindow() {
    return m_pWindow;
}

AAssetManager* NativeActivity::GetAssetManager() {
    return m_pAssetManager;
}

bool NativeActivity::IsVisible() const {
    return m_bIsVisible;
}

void NativeActivity::SetVisible(bool bVisible) {
    m_bIsVisible = bVisible;
}

void NativeActivity::ShowKeyboard() {
    m_pEnv->CallVoidMethod(m_pObj, m_hShowKeyboardMethod);
}

void NativeActivity::HideKeyboard() {
    m_pEnv->CallVoidMethod(m_pObj, m_hHideKeyboardMethod);
}

void NativeActivity::OnSurfaceCreated(jobject pSurface) {
    SetSurface(pSurface);
}

void NativeActivity::OnSurfaceChanged(int iFormat, int iWidth, int iHeight) {
    if (m_pEventHandler) {
        m_pEventHandler->OnSurfaceChanged(iFormat, iWidth, iHeight);
    }
}

void NativeActivity::OnSurfaceDestroyed() {
    SetSurface(NULL);
}

void NativeActivity::OnApplicationPaused() {
    if (m_pEventHandler) {
        m_pEventHandler->OnPause();
    }
}

void NativeActivity::OnApplicationShutdown() {
    if (m_pEventHandler) {
        m_pEventHandler->OnShutdown();
    }
}

void NativeActivity::OnLowMemory() {
    if (m_pEventHandler) {
        m_pEventHandler->OnLowMemory();
    }
}

void NativeActivity::OnApplicationResumed() {
    if (m_pEventHandler) {
        m_pEventHandler->OnResume();
    }
}

void NativeActivity::OnWindowHidden() {
    SetVisible(false);

    if (m_pEventHandler) {
        m_pEventHandler->OnHidden();
    }
}

void NativeActivity::OnWindowShown() {
    SetVisible(true);

    if (m_pEventHandler) {
        m_pEventHandler->OnVisible();
    }
}

void NativeActivity::OnTouch(int iPointerID, float fPosX, float fPosY, int iAction) {
    if (m_pEventHandler) {
        m_pEventHandler->OnTouch(iPointerID, fPosX, fPosY, iAction);
    }
}

void NativeActivity::OnKeyUp(int iKeyCode, int iUnicodeChar) {
    if (m_pEventHandler) {
        m_pEventHandler->OnKey(iKeyCode, iUnicodeChar);
    }
}

void NativeActivity::InitAppDir() {
    // Get the application's directory
    jstring strAppDir = (jstring)m_pEnv->CallObjectMethod(m_pObj, m_hGetAppDirMethod);
    jsize iStringLength = m_pEnv->GetStringLength(strAppDir);
    const char* pString = m_pEnv->GetStringUTFChars(strAppDir, NULL);

    // Copy the string
    m_pAppDir = new char[iStringLength + 2];
    memcpy(m_pAppDir, pString, iStringLength);
    m_pAppDir[iStringLength] = '/';
    m_pAppDir[iStringLength + 1] = 0;

    // Release the java string
    m_pEnv->ReleaseStringUTFChars(strAppDir, pString);
}

const char* NativeActivity::GetAppDir() const {
    return m_pAppDir;
}

/**********************************************************************************/
/*                             App interface begin                                */
/**********************************************************************************/
NativeActivity::AppInterface::AppInterface(NativeActivity* pActivity)
:s_NativeActivity(pActivity) {

}

NativeActivity::AppInterface::~AppInterface() {
    
}

JNIEnv* NativeActivity::AppInterface::GetJNIEnv() {
    return s_NativeActivity->GetJNI();
}

jobject NativeActivity::AppInterface::GetJNIActivity() {
    return s_NativeActivity->GetContext();
}

void NativeActivity::AppInterface::PollEvents() {
    s_NativeActivity->PollEvents();
}

void NativeActivity::AppInterface::SetEventHandler(IAppLifeCycle* pHandler) {
    s_NativeActivity->SetEventHandler(pHandler);
}

ANativeWindow* NativeActivity::AppInterface::GetWindow() {
    return s_NativeActivity->GetWindow();
}

AAssetManager* NativeActivity::AppInterface::GetAssetManager() {
    return s_NativeActivity->GetAssetManager();
}

bool NativeActivity::AppInterface::IsWindowVisible() {
    return s_NativeActivity->IsVisible();
}

void NativeActivity::AppInterface::ShowKeyboard() {
    s_NativeActivity->ShowKeyboard();
}

void NativeActivity::AppInterface::HideKeyboard() {
    s_NativeActivity->HideKeyboard();
}

const char* NativeActivity::AppInterface::GetAppDir() {
    return s_NativeActivity->GetAppDir();
}

/**********************************************************************************/
/*                             App interface end                                  */
/**********************************************************************************/
