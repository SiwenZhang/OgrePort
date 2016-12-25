#include "common/OgreBaseApp.h"
#include "utils/ReflexCpp.h"
#include "utils/Any.h"

#include "OgreAndroidEGLWindow.h"
#include "OgreAPKFileSystemArchive.h"
#include "OgreAPKZipArchive.h"

#include <android/log.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "OgreSample", __VA_ARGS__))
#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, "OgreSample", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "OgreSample", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "OgreSample", __VA_ARGS__))

static Ogre::DataStreamPtr openAPKFile(AAssetManager* gAssetMgr, const Ogre::String& fileName)
{
     if(gAssetMgr == NULL)
     {
         LOGE("openAPKFile error gAssetMgr == NULL [%s]", fileName.c_str());
     }

     LOGD("get asset start");
     Ogre::DataStreamPtr stream;
     LOGD("get asset start 2 : %s", fileName.c_str());
     AAsset* asset = AAssetManager_open(gAssetMgr, fileName.c_str(), AASSET_MODE_BUFFER);
     if(asset)
     {
         LOGD("asset ok");
         off_t length = AAsset_getLength(asset);
         void* membuf = OGRE_MALLOC(length, Ogre::MEMCATEGORY_GENERAL);
         memcpy(membuf, AAsset_getBuffer(asset), length);
         AAsset_close(asset);

         stream = Ogre::DataStreamPtr(new Ogre::MemoryDataStream(membuf, length, true, true));
         LOGI("openAPKFile ok %s", fileName.c_str());
     }
     else
     {
         LOGE("openAPKFile error %s", fileName.c_str());
     }
     return stream;
}

void OgreBaseApp::loadResources(const char *name)
{
    LOGD("The loadResources gAssetMgr is : %p", gAssetMgr);

    cf.load(openAPKFile(gAssetMgr, name));

    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
     while (seci.hasMoreElements())
     {
         Ogre::String sec, type, arch;
         sec = seci.peekNextKey();
         Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();
         Ogre::ConfigFile::SettingsMultiMap::iterator i;

         for (i = settings->begin(); i != settings->end(); i++)
         {
             type = i->first;
             arch = i->second;
             Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
         }
     }
}

void OgreBaseApp::InitGameWindow() {
    AConfiguration* config = AConfiguration_new();
    // AConfiguration_fromAssetManager(config, gAssetMgr);
//        AConfiguration_setOrientation(config, 2);

    LOGD("The gAssetMgr is : %p", gAssetMgr);

    if(!gRenderWnd)
    {
        Ogre::APKFileSystemArchiveFactory* apkFileSystem = new Ogre::APKFileSystemArchiveFactory(gAssetMgr);
        Ogre::APKZipArchiveFactory* apkZip = new Ogre::APKZipArchiveFactory(gAssetMgr);

        LOGD("apkFileSystem is : %p factory->getType() : %s", apkFileSystem, apkFileSystem->getType().c_str());
        LOGD("apkZip is : %p", apkZip);

        Ogre::ArchiveManager::getSingleton().addArchiveFactory( apkFileSystem );
        Ogre::ArchiveManager::getSingleton().addArchiveFactory( apkZip );

        LOGD("mWindow is : %p", mWindow);

        Ogre::NameValuePairList opt;
        opt["externalWindowHandle"] = Ogre::StringConverter::toString((int)mAppInterface->GetWindow());
        // opt["androidConfig"] = Ogre::StringConverter::toString((int)config);

        gRenderWnd = gRoot->createRenderWindow("OgreWindow", 1920, 1080, true, &opt);

        Ogre::WindowEventUtilities::addWindowEventListener(gRenderWnd, this);

        InitStartScene();
    }
    else
    {
        static_cast<Ogre::AndroidEGLWindow*>(gRenderWnd)->_createInternalResources(mAppInterface->GetWindow(), NULL);
    }
    AConfiguration_delete(config);
}

void OgreApplicationMain(const char* appName, IAppInterface* appInterface) {
    Any appInstance = CreateObject(appName);
    OgreBaseApp* baseApp = any_cast<OgreBaseApp*>(appInstance);
    baseApp->go(appInterface);
    delete baseApp;
}