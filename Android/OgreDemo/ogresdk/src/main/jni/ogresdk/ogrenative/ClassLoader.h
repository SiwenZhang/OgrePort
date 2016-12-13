#ifndef OGRE_CLASSLOADER_H
#define OGRE_CLASSLOADER_H

#include <jni.h>

namespace OgreNative
{
	class ClassLoader
	{
	public:
		ClassLoader();
		~ClassLoader();

		jclass FindClass( const char* pClassName );

		void InitJNI( JNIEnv* pEnv, jclass hActivityClass, jobject pActivityObject );

	private:
		JNIEnv* m_pEnv;
		jclass 	m_hClass;
		jobject m_pObject;

		jmethodID	m_hFindClassMethod;

	};

} /* namespace OgreNative */
#endif /* OGRE_CLASSLOADER_H */
