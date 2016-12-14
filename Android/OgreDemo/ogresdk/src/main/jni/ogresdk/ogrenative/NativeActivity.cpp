#include "NativeActivity.h"
#include "AndroidLog.h"

#include <string.h>
#include <assert.h>

namespace OgreNative
{
	NativeActivity::NativeActivity()
	{
		// Call-backs
		m_pEventHandler = NULL;
		m_pMessageCallback = NULL;

		// Member variables
		m_pAppDir		= NULL;
		m_pWindow 		= NULL;
		m_bIsVisible 	= false;

		// JNI Environment
		m_pEnv = NULL;

		// NativeActivity class and reference
		m_pObj = NULL;
		m_pJavaClass = NULL;

		// NativeActivity's methods
		m_hPeekMessageMethod 	= NULL;
		m_hPollMessagesMethod 	= NULL;

		m_hShowKeyboardMethod 	= NULL;
		m_hHideKeyboardMethod 	= NULL;

		m_hGetAppDirMethod		= NULL;

		// Message class
		m_hMessageClass = NULL;

		// Message methods
		m_hMessageIDField = NULL;

		// Methods
		m_hGetSystemServiceMethod	= NULL;

		// Context
		m_hGetContextMethod 	= NULL;
		m_pContext 				= NULL;
	}

	NativeActivity::~NativeActivity()
	{
		//GooglePlayServices::Shutdown();

		m_pEnv->DeleteGlobalRef( m_pObj );
		m_pEnv->DeleteGlobalRef( m_pContext );

		if ( m_pAppDir )
		{
			delete [] m_pAppDir;
		}
	}

	JNIEnv* NativeActivity::GetJNI()
	{
		return m_pEnv;
	}

	jobject	NativeActivity::GetObject()
	{
		return m_pObj;
	}

	jobject	NativeActivity::GetContext()
	{
		return m_pContext;
	}

	jclass NativeActivity::GetClass()
	{
		return m_pJavaClass;
	}

	void NativeActivity::PollEvents()
	{
		// Call Java's poll method
		m_pEnv->CallVoidMethod( m_pObj, m_hPollMessagesMethod );

		AndroidMessage message;
		while ( PeekEvent( message ) )
		{
			// Send the message to callback
			DispatchMessage( message );
		}
	}

	void NativeActivity::SetEventCallback( MessageCallbackFunction pCallback )
	{
		m_pMessageCallback = pCallback;
	}

	void NativeActivity::SetEventHandler( IAndroidHandler* pHandler )
	{
		m_pEventHandler = pHandler;
	}

	bool NativeActivity::PeekEvent( AndroidMessage& message )
	{
		jobject pObject = m_pEnv->CallObjectMethod( m_pObj, m_hPeekMessageMethod );
		if ( pObject )
		{
			message.iMessageID = m_pEnv->GetIntField( pObject, m_hMessageIDField );

			return true;
		}

		return false;
	}

	void NativeActivity::DispatchMessage( const AndroidMessage& message )
	{
		if ( m_pMessageCallback != NULL )
		{
			// Send message
			m_pMessageCallback( message );
		}
	}

	// void NativeActivity::DispatchMessage( AndroidMessageType eMessage )
	// {
	// 	if ( m_pMessageCallback != NULL )
	// 	{
	// 		AndroidMessage message;
	// 		message.iMessageID = eMessage;

	// 		// Send message
	// 		m_pMessageCallback( message );
	// 	}
	// }

	void NativeActivity::SetJNI( JNIEnv* pEnv, jobject pObj )
	{
	    mAppInterface = new AppInterface(this);

		m_pEnv = pEnv;
		m_pObj = pEnv->NewGlobalRef( pObj );

		m_pJavaClass = pEnv->GetObjectClass( pObj );

		// Retrieve Java methods
		m_hPeekMessageMethod 	= pEnv->GetMethodID( m_pJavaClass, "peekMessage", "()Lcom/ccsu/ogresdk/OgreNativeMessage;" );
		m_hPollMessagesMethod 	= pEnv->GetMethodID( m_pJavaClass, "pollMessages", "()V" );

		m_hShowKeyboardMethod 	= pEnv->GetMethodID( m_pJavaClass, "showKeyboard", "()V" );
		m_hHideKeyboardMethod 	= pEnv->GetMethodID( m_pJavaClass, "hideKeyboard", "()V" );

		m_hGetAppDirMethod		= pEnv->GetMethodID( m_pJavaClass, "getAppDir", "()Ljava/lang/String;" );

		// Message class
		m_hMessageClass 	= pEnv->FindClass( "com/ccsu/ogresdk/OgreNativeMessage" );
		m_hMessageIDField 	= pEnv->GetFieldID( m_hMessageClass, "mID", "I" );

		// Init member variables
		InitAppDir();

		// Context
		m_hGetContextMethod	= pEnv->GetMethodID( m_pJavaClass, "getContext", "()Landroid/content/Context;" );
		m_pContext			= pEnv->NewGlobalRef( pEnv->CallObjectMethod( m_pObj, m_hGetContextMethod ) );

		jclass hContextClass = pEnv->GetObjectClass( m_pContext );
		m_hGetSystemServiceMethod = pEnv->GetMethodID( hContextClass, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;" );

		m_ClassLoader.InitJNI( pEnv, hContextClass, m_pContext );
		m_NotificationManager.Init(mAppInterface);

		//GooglePlayServices::Init( pEnv, m_pContext );

		// *pInterface = new NativeInterface( this );
	}

	jobject NativeActivity::GetSystemService( const char* pServiceName )
	{
		jstring string = m_pEnv->NewStringUTF( pServiceName );
		jobject result = m_pEnv->CallObjectMethod( m_pContext, m_hGetSystemServiceMethod, string );
		m_pEnv->DeleteLocalRef( string );

		return result;
	}

	void NativeActivity::SetSurface( jobject pSurface )
	{
		if ( pSurface )
		{
			m_pWindow = ANativeWindow_fromSurface( m_pEnv, pSurface );

			if ( m_pEventHandler )
			{
				m_pEventHandler->OnSurfaceCreated();
			}

			// DispatchMessage( AndroidMessage_SurfaceCreated );
		}

		else
		{
			if ( m_pWindow )
			{
				ANativeWindow_release( m_pWindow );
				m_pWindow = NULL;

				if ( m_pEventHandler )
				{
					m_pEventHandler->OnSurfaceDestroyed();
				}

				// DispatchMessage( AndroidMessage_SurfaceDestroyed );
			}
		}
	}

	void NativeActivity::setAssetManager(jobject pAssetManager) {
		if (pAssetManager != NULL) {
			m_pAssetManager = AAssetManager_fromJava(m_pEnv, pAssetManager);
		}
	}

	ANativeWindow* NativeActivity::GetWindow()
	{
		return m_pWindow;
	}

	AAssetManager* NativeActivity::GetAssetManager() {
		return m_pAssetManager;
	}

	bool NativeActivity::IsVisible() const
	{
		return m_bIsVisible;
	}

	void NativeActivity::SetVisible( bool bVisible )
	{
		m_bIsVisible = bVisible;
	}

	void NativeActivity::ShowKeyboard()
	{
		m_pEnv->CallVoidMethod( m_pObj, m_hShowKeyboardMethod );
	}

	void NativeActivity::HideKeyboard()
	{
		m_pEnv->CallVoidMethod( m_pObj, m_hHideKeyboardMethod );
	}

	/**********************************************************************************/
	/*                                 NativeInterface                                */
	/**********************************************************************************/
	// NativeActivity::NativeInterface::NativeInterface( NativeActivity* pActivity )
	// {
	// 	m_pActivity = pActivity;
	// }

	// NativeActivity::NativeInterface::~NativeInterface()
	// {

	// }

	void NativeActivity::OnSurfaceCreated( jobject pSurface )
	{
		SetSurface( pSurface );
	}

	void NativeActivity::OnSurfaceChanged( int iFormat, int iWidth, int iHeight )
	{
		//LOGV( "[Native] OnSurfaceChanged: Width: %i, Height: %i, Format: %i.", iWidth, iHeight, iFormat );

		if ( m_pEventHandler )
		{
			m_pEventHandler->OnSurfaceChanged( iFormat, iWidth, iHeight );
		}

		// // Create surface data
		// AndroidSurfaceChanged surfaceChanged;
		// surfaceChanged.iFormat 	= iFormat;
		// surfaceChanged.iWidth	= iWidth;
		// surfaceChanged.iHeight	= iHeight;

		// // Create message
		// AndroidMessage message;
		// message.iMessageID = AndroidMessage_SurfaceChanged;
		// message.pData = &surfaceChanged;

		// // Send message
		// m_pActivity->DispatchMessage( message );
	}

	void NativeActivity::OnSurfaceDestroyed()
	{
		SetSurface( NULL );
	}

	void NativeActivity::OnApplicationPaused()
	{
		if (m_pEventHandler )
		{
			m_pEventHandler->OnPause();
		}

		// m_pActivity->DispatchMessage( AndroidMessage_ApplicationPaused );
	}

	void NativeActivity::OnApplicationShutdown()
	{
		if ( m_pEventHandler )
		{
			m_pEventHandler->OnShutdown();
		}

		// m_pActivity->DispatchMessage( AndroidMessage_ApplicationShutdown );
	}

	void NativeActivity::OnLowMemory()
	{
		if ( m_pEventHandler )
		{
			m_pEventHandler->OnLowMemory();
		}

		// m_pActivity->DispatchMessage( AndroidMessage_LowMemory );
	}

	void NativeActivity::OnApplicationResumed()
	{
		if ( m_pEventHandler )
		{
			m_pEventHandler->OnResume();
		}

		// m_pActivity->DispatchMessage( AndroidMessage_ApplicationResumed );
	}

	void NativeActivity::OnWindowHidden()
	{
		SetVisible( false );

		if ( m_pEventHandler )
		{
			m_pEventHandler->OnHidden();
		}

		// m_pActivity->DispatchMessage( AndroidMessage_WindowHidden );
	}

	void NativeActivity::OnWindowShown()
	{
		SetVisible( true );

		if ( m_pEventHandler )
		{
			m_pEventHandler->OnVisible();
		}

		// m_pActivity->DispatchMessage( AndroidMessage_WindowVisible );
	}

	void NativeActivity::OnTouch( int iPointerID, float fPosX, float fPosY, int iAction )
	{
		if ( m_pEventHandler )
		{
			m_pEventHandler->OnTouch( iPointerID, fPosX, fPosY, iAction );
		}

		// // Create touch data
		// AndroidTouch touch;
		// touch.iPointerID = iPointerID;
		// touch.fPosX = fPosX;
		// touch.fPosY	= fPosY;
		// touch.iAction = iAction;

		// // Create message
		// AndroidMessage message;
		// message.iMessageID = AndroidMessage_OnTouch;
		// message.pData = &touch;

		// // Send message
		// m_pActivity->DispatchMessage( message );
	}

	void NativeActivity::OnKeyUp( int iKeyCode, int iUnicodeChar )
	{
		if ( m_pEventHandler )
		{
			m_pEventHandler->OnKey( iKeyCode, iUnicodeChar );
		}

		// // Create key data
		// AndroidKey keyMessage;
		// keyMessage.iKeyCode = iKeyCode;
		// keyMessage.iUnicodeChar = (wchar_t)iUnicodeChar;

		// // Create message
		// AndroidMessage message;
		// message.iMessageID = AndroidMessage_OnKey;
		// message.pData = &keyMessage;

		// // Send message
		// m_pActivity->DispatchMessage( message );
	}

//	void NativeActivity::NativeInterface::OnSignInSucceeded( char* pAccountName )
//	{
//		GooglePlayServices::OnSignInSucceeded( pAccountName );
//	}
//
//	void NativeActivity::NativeInterface::OnSignInFailed()
//	{
//		GooglePlayServices::OnSignInFailed();
//	}
//
//	void NativeActivity::setAssetManager(jobject pAssetManager) {
//		setAssetManager( pAssetManager );
//	}
//
//	IAppStateInterface* NativeActivity::NativeInterface::GetAppStateInterface()
//	{
//		return &m_AppState;
//	}

	ClassLoader& NativeActivity::GetClassLoader()
	{
		return m_ClassLoader;
	}

	NotificationManager& NativeActivity::GetNotificationManager()
	{
		return m_NotificationManager;
	}

	void NativeActivity::InitAppDir()
	{
		// Get the application's directory
		jstring strAppDir = (jstring)m_pEnv->CallObjectMethod( m_pObj, m_hGetAppDirMethod );
		jsize iStringLength = m_pEnv->GetStringLength( strAppDir );
		const char* pString = m_pEnv->GetStringUTFChars( strAppDir, NULL );

		// Copy the string
		m_pAppDir = new char[ iStringLength + 2 ];
		memcpy( m_pAppDir, pString, iStringLength );
		m_pAppDir[ iStringLength ] = '/';
		m_pAppDir[ iStringLength + 1 ] = 0;

		// Release the java string
		m_pEnv->ReleaseStringUTFChars( strAppDir, pString );
	}

	const char* NativeActivity::GetAppDir() const
	{
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

//	NativeActivity& NativeActivity::AppInterface::GetNativeActivity()
//	{
//		return *s_NativeActivity;
//	}

	JNIEnv* NativeActivity::AppInterface::GetJNIEnv()
	{
		return s_NativeActivity->GetJNI();
	}

	jobject NativeActivity::AppInterface::GetJNIActivity()
	{
		return s_NativeActivity->GetContext();
	}

	void NativeActivity::AppInterface::PollEvents()
	{
		s_NativeActivity->PollEvents();
	}

	void NativeActivity::AppInterface::SetEventCallback( MessageCallbackFunction pCallback )
	{
        s_NativeActivity->SetEventCallback( pCallback );
    }

	void NativeActivity::AppInterface::SetEventHandler( IAndroidHandler* pHandler )
	{
		s_NativeActivity->SetEventHandler( pHandler );
	}

	ANativeWindow* NativeActivity::AppInterface::GetWindow()
	{
		return s_NativeActivity->GetWindow();
	}

	AAssetManager* NativeActivity::AppInterface::GetAssetManager()
	{
		return s_NativeActivity->GetAssetManager();
	}

	bool NativeActivity::AppInterface::IsWindowVisible()
	{
		return s_NativeActivity->IsVisible();
	}

	void NativeActivity::AppInterface::ShowKeyboard()
	{
		s_NativeActivity->ShowKeyboard();
	}

	void NativeActivity::AppInterface::HideKeyboard()
	{
		s_NativeActivity->HideKeyboard();
	}

	const char* NativeActivity::AppInterface::GetAppDir()
	{
		return s_NativeActivity->GetAppDir();
	}

	ClassLoader* NativeActivity::AppInterface::GetClassLoader()
	{
		return &s_NativeActivity->GetClassLoader();
	}

	NotificationManager* NativeActivity::AppInterface::GetNotificationManager()
	{
		return &s_NativeActivity->GetNotificationManager();
	}
	/**********************************************************************************/
	/*                             App interface end                                  */
	/**********************************************************************************/

}
