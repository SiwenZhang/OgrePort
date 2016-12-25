#ifndef OGRE_NOTIFICATIONMANAGER_H
#define OGRE_NOTIFICATIONMANAGER_H

#include "Notification.h"
#include <jni.h>

#include "IAppInterface.h"

// namespace OgreNative
// {
    class NotificationManager
    {
    public:
        NotificationManager();
        ~NotificationManager();

        void Cancel( int iNotificationID );
        void Cancel( const char* pTag, int iNotificationID );
        void CancelAll();

        void Notify( int iNotificationID, const Notification& notification );
        void Notify( const char* pTag, int iNotificationID, const Notification& notification );

        void Init(IAppInterface* appInterface);

    private:
        JNIEnv* m_pEnv;

        jmethodID m_hCancelMethod;
        jmethodID m_hCancelTagMethod;
        jmethodID m_hCancelAllMethod;
        jmethodID m_hNotifyMethod;
        jmethodID m_hNotifyTagMethod;

        inline jobject GetObject();
    };

//} /* namespace OgreNative */
#endif /* OGRE_NOTIFICATIONMANAGER_H */
