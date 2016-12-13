#ifndef OGRE_APPSTATEIMPL_H
#define OGRE_APPSTATEIMPL_H

#include "IAppStateInterface.h"
#include <jni.h>

namespace OgreNative
{
	class AppStateImpl : public IAppStateInterface
	{
	public:
		AppStateImpl( JNIEnv* pEnv );
		virtual ~AppStateImpl();

		void OnStateLoaded( const jobject pListener, const int iStatusCode, const int iStateKey, const jbyteArray data );
		void OnStateConflict( const jobject pListener, const int iStateKey, const jstring resolvedVersion, const jbyteArray localData, const jbyteArray serverData );

	private:
		JNIEnv* m_pEnv;
	};

} /* namespace OgreNative */
#endif /* OGRE_APPSTATEIMPL_H */
