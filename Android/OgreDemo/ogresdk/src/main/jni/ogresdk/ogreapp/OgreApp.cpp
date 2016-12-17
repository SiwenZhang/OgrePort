#define OGRE_STATIC_LIB
#define OGRE_STATIC_GLES2
#define OGRE_STATIC_ParticleFX
#define OGRE_STATIC_OctreeSceneManager
//#define RTSHADER_SYSTEM_BUILD_CORE_SHADERS

#include <jni.h>
#include <errno.h>

#include <EGL/egl.h>
#include <android/log.h>
//#include <android_native_app_glue.h>

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

#include "MyGUI.h"
#include "MyGUI_OgrePlatform.h"

#include "../ogrenative/IAppInterface.h"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "OgreSample", __VA_ARGS__))
#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, "OgreSample", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "OgreSample", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "OgreSample", __VA_ARGS__))

class OgreMainApp
        : public IAndroidHandler,
         public Ogre::WindowEventListener,
         public Ogre::FrameListener,
         public Ogre::RenderTargetListener {

public:
	public:
	// Application
	virtual void OnShutdown() {

	}

	// Surface
	virtual void OnSurfaceCreated() {
		LOGD("OnSurfaceCreated");
	    InitGameWindow();
	}

	virtual void OnSurfaceChanged( int iPixelFormat, int iWidth, int iHeight ) {
		LOGD("OnSurfaceChanged iWidth : %d iHeight : %d gRoot : %p gRenderWnd : %p", iWidth, iHeight, gRoot, gRenderWnd);
		// camera->setAspectRatio((float)iWidth / (float)iHeight);

		// if (gRoot && gRenderWnd) {
		// 	AConfiguration* config = AConfiguration_new();
  //       	AConfiguration_fromAssetManager(config, gAssetMgr);
		// 	static_cast<Ogre::AndroidEGLWindow*>(gRenderWnd)->_destroyInternalResources();
		// 	static_cast<Ogre::AndroidEGLWindow*>(gRenderWnd)->_createInternalResources(mAppInterface->GetWindow(), config);
		// 	AConfiguration_delete(config);
		// }

		// InitStartScene();
		InitGameScene();

		LOGD("OnSurfaceChanged vp width : %d height : %d", vp->getWidth(), vp->getHeight());

//		Ogre::Matrix4 mat = camera->getProjectionMatrix();
//        mat = mat * Ogre::Quaternion(Ogre::Degree(90.0f), Ogre::Vector3::UNIT_Z);
//        camera->setCustomProjectionMatrix(true, mat);
		
		gRenderWnd->windowMovedOrResized();

		// camera->setAspectRatio((float)gRenderWnd->getWidth() / (float)gRenderWnd->getHeight());
	}

	virtual void OnSurfaceDestroyed() {
		LOGD("OnSurfaceDestroyed");
        if(gRoot && gRenderWnd)
			static_cast<Ogre::AndroidEGLWindow*>(gRenderWnd)->_destroyInternalResources();
	}

	// States
	virtual void OnPause() {

	}

	virtual void OnResume() {

	}

	virtual void OnVisible() {

	}

	virtual void OnHidden() {

	}

	virtual void OnLowMemory() {

	}

	// Input
	virtual void OnKey( int iKeyCode, wchar_t iUnicodeChar ) {

	}

	virtual void OnTouch( int iPointerID, float fPosX, float fPosY, int iAction ) {

	}

public:
	void renderOneFrame() {
		if(gRenderWnd != NULL && gRenderWnd->isActive())
		{
			// gRenderWnd->windowMovedOrResized();

			// renderTexture->update();

			gRoot->renderOneFrame();
		}
	}

private:
	void InitGameWindow() {
        AConfiguration* config = AConfiguration_new();
        // AConfiguration_fromAssetManager(config, gAssetMgr);
//        AConfiguration_setOrientation(config, 2);

        if(!gRenderWnd)
        {
		    Ogre::ArchiveManager::getSingleton().addArchiveFactory( new Ogre::APKFileSystemArchiveFactory(gAssetMgr) );
			Ogre::ArchiveManager::getSingleton().addArchiveFactory( new Ogre::APKZipArchiveFactory(gAssetMgr) );

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

	void InitStartScene()
	{
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
		// vp->setBackgroundColour(Ogre::ColourValue(1.0f, 0.0f, 0.0f));
	//	vp->setMaterialScheme(Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME);

		loadResources("resources.cfg");
	}

	void InitGameScene()
	{
	    if (mSceneInited == true) {
	        return ;
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

			// mRTTCamera = gSceneMgr->createCamera("RTTCamera");
			// mRTTCamera->setNearClipDistance(0.1f);
			// mRTTCamera->setFarClipDistance(1000.0f);
			// mRTTCamera->setPosition(50,0, 0);
			// mRTTCamera->lookAt(0,0,0);
			// mRTTCamera->setAutoAspectRatio(true);

			// LOGD("rttTexture width : %d height : %d", gRenderWnd->getWidth(), gRenderWnd->getHeight());

//	      Ogre::TexturePtr rttTexture =
//            Ogre::TextureManager::getSingleton().createManual(
//              "RttTex",
          //     Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
          //     Ogre::TEX_TYPE_2D,
          //     gRenderWnd->getWidth(), gRenderWnd->getHeight(),
          //     0,
          //     Ogre::PF_R8G8B8,
          //     Ogre::TU_RENDERTARGET);

          // renderTexture = rttTexture->getBuffer()->getRenderTarget();
          // mRTTViewPort = renderTexture->addViewport(mRTTCamera);
          // renderTexture->setAutoUpdated(true);
          // mRTTViewPort->setClearEveryFrame(true);
          // mRTTViewPort->setBackgroundColour(Ogre::ColourValue::Green);
          // mRTTViewPort->setOverlaysEnabled(true);

//          renderTexture->update();
//          renderTexture->writeContentsToFile("start.png");

          // mMiniscreen = new Ogre::Rectangle2D(true);
          // mMiniscreen->setCorners(-1.0, 1.0, 1.0, -1.0);
          // mMiniscreen->setBoundingBox(Ogre::AxisAlignedBox::BOX_INFINITE);

          // Ogre::SceneNode* miniscreenNode =
          //   gSceneMgr->getRootSceneNode()->createChildSceneNode();
          // miniscreenNode->attachObject(mMiniscreen);

          // Ogre::MaterialPtr renderMat =
          //   Ogre::MaterialManager::getSingleton().create(
          //     "RttMat",
          //     Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
          // renderMat->getTechnique(0)->getPass(0)->setLightingEnabled(false);
          // renderMat->getTechnique(0)->getPass(0)->createTextureUnitState("RttTex");

          // mMiniscreen->setMaterial("RttMat");

          // renderTexture->addListener(this);

			// mPlatform = new MyGUI::OgrePlatform();
			// mPlatform->initialise(renderTexture, gSceneMgr);
			// mGUI = new MyGUI::Gui();

			// mGUI->initialise();
			// mButton = mGUI->createWidget<MyGUI::Button>("Button",10,10,800,600,MyGUI::Align::Default,"Main");
			// mButton->setCaption("HelloWorld");

			mSceneInited = true;
	}

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

	void loadResources(const char *name)
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

public:
	OgreMainApp(OgreNative::IAppInterface* appInterface) {
	    mAppInterface = appInterface;

		gRoot = new Ogre::Root();
		LOGI("android_main create root end");
		#ifdef OGRE_STATIC_LIB
		   LOGI("android_main load static plugin");
			gStaticPluginLoader = new Ogre::StaticPluginLoader();
			gStaticPluginLoader->load();
		#endif
	    LOGI("android_main getAvailableRenderers size : %d", gRoot->getAvailableRenderers().size());

        gRoot->setRenderSystem(gRoot->getAvailableRenderers().at(0));
        gRoot->initialise(false);

        gAssetMgr = mAppInterface->GetAssetManager();

        gRenderWnd = NULL;

        mSceneInited = false;
	}

	virtual ~OgreMainApp() {
	    Ogre::WindowEventUtilities::removeWindowEventListener(gRenderWnd, this);
	}

private:
	Ogre::RenderWindow* gRenderWnd;
	Ogre::Root* gRoot;
	Ogre::SceneManager* gSceneMgr;
	Ogre::ShaderGeneratorTechniqueResolverListener* gMatListener;
	Ogre::StaticPluginLoader* gStaticPluginLoader;
	Ogre::Camera* camera;
	Ogre::SceneNode* pNode;
	Ogre::RaySceneQuery* mRayScnQuery;
	Ogre::TextAreaOverlayElement* textArea;
	Ogre::Viewport* vp;

	Ogre::Viewport* mRTTViewPort;
	Ogre::RenderTexture* renderTexture;
	Ogre::Camera* mRTTCamera;

	Ogre::Viewport* mSaveViewport;

	AAssetManager* gAssetMgr;

	Ogre::ConfigFile cf;

	//My GUI implement
	MyGUI::Gui* mGUI;
	MyGUI::OgrePlatform* mPlatform;
	MyGUI::ButtonPtr mButton;

	bool mSceneInited;

private:
    OgreNative::IAppInterface* mAppInterface;

private:
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& fe) {
        //Do nothing at all
    }

    //////////////////////
    // Tutorial Section //
    //////////////////////
    virtual void preRenderTargetUpdate(const Ogre::RenderTargetEvent& rte) {
    	// LOGD("preRenderTargetUpdate");
    	// Ogre::RenderSystem* system = Ogre::Root::getSingleton().getRenderSystem();
    	// mSaveViewport = system->_getViewport();
    	// system->_setViewport(mRTTViewPort);
     //    mMiniscreen->setVisible(false);
     //    system->clearFrameBuffer(Ogre::FBT_COLOUR, Ogre::ColourValue::ZERO);
    }

    virtual void postRenderTargetUpdate(const Ogre::RenderTargetEvent& rte) {
    	// LOGD("postRenderTargetUpdate");
  //   	Ogre::RenderSystem* system = Ogre::Root::getSingleton().getRenderSystem();
		// // system->_setViewport(mSaveViewport);
  //       mMiniscreen->setVisible(true);
    }

private:
    Ogre::Rectangle2D* mMiniscreen;
};

#ifdef __cplusplus
extern "C" {
#endif

void ogreapp_main(OgreNative::IAppInterface* appInterface) {
    LOGI("ogreapp_main start");
    OgreMainApp* mainApp = new OgreMainApp(appInterface);

    appInterface->SetEventHandler(mainApp);

    while (true) {
    	appInterface->PollEvents();
    	
    	mainApp->renderOneFrame();

    	usleep(10 * 1000);
    }

    delete mainApp;
    mainApp = NULL;
}

#ifdef __cplusplus
}
#endif
