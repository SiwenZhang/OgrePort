#ifndef OGRE_IAPPSTATEINTERFACE_H
#define OGRE_IAPPSTATEINTERFACE_H

#include <JNI.h>

namespace OgreNative
{
	class IAppStateInterface
	{
	public:
		virtual void OnStateLoaded( const jobject pListener, const int iStatusCode, const int iStateKey, const jbyteArray data ) = 0;
		virtual void OnStateConflict( const jobject pListener, const int iStateKey, const jstring resolvedVersion, const jbyteArray localData, const jbyteArray serverData ) = 0;

		virtual ~IAppStateInterface() { }
	};

} /* namespace OgreNative */
#endif /* OGRE_IAPPSTATEINTERFACE_H */
