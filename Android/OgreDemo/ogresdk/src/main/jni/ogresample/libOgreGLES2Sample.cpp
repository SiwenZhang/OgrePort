#define OGRE_STATIC_LIB
#define OGRE_STATIC_GLES2
#define OGRE_STATIC_ParticleFX
#define OGRE_STATIC_OctreeSceneManager
#define RTSHADER_SYSTEM_BUILD_CORE_SHADERS

#include <jni.h>
#include <errno.h>

#include <EGL/egl.h>
#include <android/log.h>
#include <android_native_app_glue.h>

#include <android/input.h>
#include <android/sensor.h>

#include "Ogre.h"
#include "OgreRenderWindow.h"
#include "OgreStringConverter.h"
#include "RTShaderHelper.h"
#include "OgreAndroidEGLWindow.h"
#include "OgreAPKFileSystemArchive.h"
#include "OgreAPKZipArchive.h"

#include "OgreOverlayManager.h"
#include "OgreOverlayContainer.h"
#include "OgreTextAreaOverlayElement.h"
#include "OgreOverlaySystem.h"

#include "OgreStaticPluginLoader.h"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "OgreSample", __VA_ARGS__))
#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, "OgreSample", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "OgreSample", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "OgreSample", __VA_ARGS__))

static Ogre::RenderWindow* gRenderWnd = NULL;
static Ogre::Root* gRoot = NULL;
static AAssetManager* gAssetMgr = NULL;
static Ogre::SceneManager* gSceneMgr = NULL;
static Ogre::ShaderGeneratorTechniqueResolverListener* gMatListener = NULL;
static Ogre::StaticPluginLoader* gStaticPluginLoader = NULL;



class AppState{
	public:
	int CurentState;
};

class NativeApp{

	public:
		struct android_app* app;

		ASensorManager* sensorManager;
		ASensorEventQueue* sensorEventQueue;

		AppState state;
};

NativeApp app;

Ogre::DataStreamPtr openAPKFile(const Ogre::String& fileName)
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

Ogre::Camera* camera = NULL;
Ogre::SceneNode* pNode = NULL;
Ogre::RaySceneQuery* mRayScnQuery = NULL;
Ogre::TextAreaOverlayElement* textArea = NULL;
Ogre::Viewport* vp = NULL;

/**
 * Загрузка ресурсов
 */
Ogre::ConfigFile cf;
static void loadResources(const char *name)
{
	cf.load(openAPKFile(name));

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


static void InitGameScene()
{
	if(app.state.CurentState != 1)
	{
		return;
	}

	Ogre::RTShader::ShaderGenerator::getSingletonPtr()->invalidateScheme(Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME);
	Ogre::ResourceGroupManager::getSingletonPtr()->initialiseAllResourceGroups();

	gSceneMgr->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));

	Ogre::Entity* pEntity = gSceneMgr->createEntity("Sinbad", "Sinbad.mesh");
	Ogre::SceneNode* pNode = gSceneMgr->getRootSceneNode()->createChildSceneNode("Sinbad");
	pNode->attachObject(pEntity);
	//pNode->setPosition(0, 0, 0);

	//Ogre::Light* pDirLight = gSceneMgr->createLight();
	//pDirLight->setDirection(Ogre::Vector3(0,-1,0));
	//pDirLight->setType(Ogre::Light::LT_DIRECTIONAL);
	//pNode->attachObject(pDirLight);

	// Create a light
 //   	Ogre::Light* pointLight = gSceneMgr->createLight("pointLight");
 //   	pointLight->setType(Ogre::Light::LT_POINT);
 //   	pointLight->setPosition(Ogre::Vector3(250, 150, 250));
 //   	pointLight->setDiffuseColour(Ogre::ColourValue::Red);
 //   	pointLight->setSpecularColour(Ogre::ColourValue::Red);

//	mRayScnQuery = gSceneMgr->createRayQuery(Ogre::Ray());

	app.state.CurentState = 2;
}

static void InitStartScene()
{
	if(app.state.CurentState > 0)
	{
		return;
	}

	LOGW("Create SceneManager");
    gSceneMgr = gRoot->createSceneManager(Ogre::ST_GENERIC);

	Ogre::RTShader::ShaderGenerator::initialize();
	Ogre::RTShader::ShaderGenerator::getSingletonPtr()->setTargetLanguage("glsles");
	gMatListener = new Ogre::ShaderGeneratorTechniqueResolverListener(Ogre::RTShader::ShaderGenerator::getSingletonPtr());
	Ogre::MaterialManager::getSingleton().addListener(gMatListener);

	Ogre::RTShader::ShaderGenerator::getSingletonPtr()->addSceneManager(gSceneMgr);

	camera = gSceneMgr->createCamera("MyCam");
	camera->setNearClipDistance(0.1f);
	camera->setFarClipDistance(1000.0f);
	camera->setPosition(0,0,50.0f);
	camera->lookAt(0,0,0);
	camera->setAutoAspectRatio(true);

	vp = gRenderWnd->addViewport(camera);
	vp->setBackgroundColour(Ogre::ColourValue(1.0f, 0.0f, 0.0f));
//	vp->setMaterialScheme(Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME);

	loadResources("resources.cfg");

	app.state.CurentState = 1;
}

Ogre::Vector3 CameraRot;
Ogre::Vector3 lastPos;
static int32_t handleInput(struct android_app* app, AInputEvent* event)
{
	    if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION)
	    {
	        float x = AMotionEvent_getX(event, 0);
	        float y = AMotionEvent_getY(event, 0);

	        LOGW("MOTION: x=%d y=%d", (int)x, (int)y);

	        if( abs(x - lastPos.x) < 25)
	        {
	        	CameraRot.x += (x - lastPos.x) * 0.01;
	        }

	        if( abs(y - lastPos.y)< 25)
	        {
	        	CameraRot.y += (y - lastPos.y) * 0.01;
	        }

	        camera->setPosition( cos( CameraRot.x) * 20,  sin( CameraRot.y) * 20 , -sin( CameraRot.x) * 20 );
	    	camera->lookAt(0,0,0);

	        lastPos.x = x;
	        lastPos.y = y;


	        if(textArea != NULL)
	        {
				char text[300];
				sprintf(text, "X:%d Y:%d", (int)x, (int)y);
				textArea->setCaption( text );
	        }

	            /*
	        	This next big chunk basically sends a raycast straight down from the camera's position
	        	It then checks to see if it is under world geometry and if it is we move the camera back up
	        	*/
	        	//Ogre::Vector3 camPos = camera->getPosition();
	        	//Ogre::Ray cameraRay(Ogre::Vector3(camPos.x, 5000.0f, camPos.z), Ogre::Vector3::NEGATIVE_UNIT_Y);
        	    //mRayScnQuery->setRay(cameraRay);

	        	//create a raycast straight out from the camera at the mouse's location
				//Ogre::Ray mouseRay = camera->getCameraToViewportRay( x/float(vp->getActualWidth()),  y/float(vp->getActualHeight()));
				//mRayScnQuery->setRay(mouseRay);

	        	//Ogre::RaySceneQueryResult& result = mRayScnQuery->execute();
	        	//Ogre::RaySceneQueryResult::iterator iter = result.begin();
//
//	        	if(iter != result.end() && iter->movable)
//	        	{
//	        		LOGW("SELECT: %s", iter->movable->getName().c_str());
//	        	}
	        	return true;


	        return 1;
	    }
	return 0;
}

static void handleCmd(struct android_app* app, int32_t cmd)
{
    switch (cmd)
    {
        case APP_CMD_SAVE_STATE:
        	// http://developer.android.com/reference/android/app/NativeActivity.html
            break;
        case APP_CMD_INIT_WINDOW:
            if(app->window && gRoot)
            {
                AConfiguration* config = AConfiguration_new();
                AConfiguration_fromAssetManager(config, app->activity->assetManager);
                gAssetMgr = app->activity->assetManager;

                if(!gRenderWnd)
                {
				    Ogre::ArchiveManager::getSingleton().addArchiveFactory( new Ogre::APKFileSystemArchiveFactory(app->activity->assetManager) );
					Ogre::ArchiveManager::getSingleton().addArchiveFactory( new Ogre::APKZipArchiveFactory(app->activity->assetManager) );

                    Ogre::NameValuePairList opt;
                    opt["externalWindowHandle"] = Ogre::StringConverter::toString((int)app->window);
                    opt["androidConfig"] = Ogre::StringConverter::toString((int)config);

					gRenderWnd = gRoot->createRenderWindow("OgreWindow", 0, 0, false, &opt);

					InitStartScene();
                }
                else
                {
					static_cast<Ogre::AndroidEGLWindow*>(gRenderWnd)->_createInternalResources(app->window, config);
                }
                AConfiguration_delete(config);
            }
            break;
        case APP_CMD_TERM_WINDOW:
            if(gRoot && gRenderWnd)
				static_cast<Ogre::AndroidEGLWindow*>(gRenderWnd)->_destroyInternalResources();
            break;
        case APP_CMD_GAINED_FOCUS:
        	// When our app gains focus, we start monitoring the accelerometer.

            break;
        case APP_CMD_LOST_FOCUS:
			// Also stop animating.
            break;
    }
}

void android_main(struct android_app* state)
{
    LOGI("android_main start");
    app_dummy();
	state->userData = &app;

    LOGI("android_main userData");

	// Prepare to monitor accelerometer
	app.sensorManager = ASensorManager_getInstance();
	app.sensorEventQueue = ASensorManager_createEventQueue(app.sensorManager, state->looper, LOOPER_ID_USER, NULL, NULL);

	if (state->savedState != NULL)
	{
		// We are starting with a previous saved state; restore from it.
		app.state = *(AppState*)state->savedState;
	}

   LOGI("android_main create root");

	if(gRoot == NULL)
	{
		gRoot = new Ogre::Root();
		LOGI("android_main create root end");
		#ifdef OGRE_STATIC_LIB
		   LOGI("android_main load static plugin");
			gStaticPluginLoader = new Ogre::StaticPluginLoader();
			gStaticPluginLoader->load();
            LOGI("android_main load static plugin");
		#endif
	    LOGI("android_main getAvailableRenderers size : %d", gRoot->getAvailableRenderers().size());

        gRoot->setRenderSystem(gRoot->getAvailableRenderers().at(0));
        gRoot->initialise(false);
	}

   LOGI("android_main create root end");

    state->onAppCmd = &handleCmd;
    state->onInputEvent = &handleInput;

    int ident, events;
    struct android_poll_source* source;

    while (true)
    {
        while ((ident = ALooper_pollAll(0, NULL, &events, (void**)&source)) >= 0)
        {
            if (source != NULL)
            {
            	source->process(state, source);
            }

            if (state->destroyRequested != 0)
            {
            	return;
            }
        }

		if(gRenderWnd != NULL && gRenderWnd->isActive())
		{
			gRenderWnd->windowMovedOrResized();

			gRoot->renderOneFrame();

			InitGameScene();

		}
    }
}
