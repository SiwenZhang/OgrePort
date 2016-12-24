//
//  OgreBaseApp.hpp
//  ogresdk
//
//  Created by liu enbao on 12/24/16.
//  Copyright © 2016 liu enbao. All rights reserved.
//

#ifndef OGRE_BASEAPP_H
#define OGRE_BASEAPP_H

#import "Ogre.h"

#define OGRE_STATIC_LIB
#define OGRE_STATIC_GLES2
#define OGRE_STATIC_ParticleFX
#define OGRE_STATIC_OctreeSceneManager
//#define RTSHADER_SYSTEM_BUILD_CORE_SHADERS

#include "IAppLifeCycle.h"

#include "Ogre.h"
#include "OgreRenderWindow.h"
#include "OgreStringConverter.h"
#include "RTShaderHelper.h"

#include "OgreOverlayManager.h"
#include "OgreOverlayContainer.h"
#include "OgreTextAreaOverlayElement.h"
#include "OgreOverlaySystem.h"

#include "OgreStaticPluginLoader.h"

#include "MyGUI.h"
#include "MyGUI_OgrePlatform.h"

#include "OIS.h"

class IAppInterface;
class OgreMultiTouch;

class OgreBaseApp
        :public IAppLifeCycle,
        public Ogre::WindowEventListener,
        public Ogre::FrameListener,
        public Ogre::RenderTargetListener,
        public OIS::MultiTouchListener {

public:
    // Application
    virtual void OnShutdown() {
        
    }
    
    // Surface
    virtual void OnSurfaceCreated() {
        InitGameWindow();
    }
    
    virtual void OnSurfaceChanged( int iPixelFormat, int iWidth, int iHeight ) {
        // camera->setAspectRatio((float)iWidth / (float)iHeight);
        
        // if (gRoot && gRenderWnd) {
        //     AConfiguration* config = AConfiguration_new();
        //           AConfiguration_fromAssetManager(config, gAssetMgr);
        //     static_cast<Ogre::AndroidEGLWindow*>(gRenderWnd)->_destroyInternalResources();
        //     static_cast<Ogre::AndroidEGLWindow*>(gRenderWnd)->_createInternalResources(mAppInterface->GetWindow(), config);
        //     AConfiguration_delete(config);
        // }
        
        mWidth = iWidth;
        mHeight = iHeight;
        
        // InitStartScene();
        InitGameScene();
        
        //        Ogre::Matrix4 mat = camera->getProjectionMatrix();
        //        mat = mat * Ogre::Quaternion(Ogre::Degree(90.0f), Ogre::Vector3::UNIT_Z);
        //        camera->setCustomProjectionMatrix(true, mat);
        
        gRenderWnd->resize(iWidth, iHeight);
        
        // After rotation the aspect ratio of the viewport has changed, update that as well.
        if(gRenderWnd->getNumViewports() > 0) {
            Ogre::Viewport *viewPort = gRenderWnd->getViewport(0);
            //            viewPort->getCamera()->setAspectRatio((Real) iWidth / (Real) iHeight);
        }
        
        //        gRenderWnd->windowMovedOrResized();
        
        // camera->setAspectRatio((float)gRenderWnd->getWidth() / (float)gRenderWnd->getHeight());
    }
    
    virtual void OnSurfaceDestroyed() {
        //        if(gRoot && gRenderWnd)
        //            static_cast<Ogre::AndroidEGLWindow*>(gRenderWnd)->_destroyInternalResources();
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
    
    virtual void OnTouch( int iPointerID, float fPosX, float fPosY, int iAction );
    
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
    void InitGameWindow();
    
    void InitStartScene()
    {
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
        //    vp->setMaterialScheme(Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME);
        
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
        pNode = gSceneMgr->getRootSceneNode()->createChildSceneNode("Sinbad");
        pNode->attachObject(pEntity);
        //pNode->setPosition(0, 0, 0);
        
        //Ogre::Light* pDirLight = gSceneMgr->createLight();
        //pDirLight->setDirection(Ogre::Vector3(0,-1,0));
        //pDirLight->setType(Ogre::Light::LT_DIRECTIONAL);
        //pNode->attachObject(pDirLight);
        
        // Create a light
        //       Ogre::Light* pointLight = gSceneMgr->createLight("pointLight");
        //       pointLight->setType(Ogre::Light::LT_POINT);
        //       pointLight->setPosition(Ogre::Vector3(250, 150, 250));
        //       pointLight->setDiffuseColour(Ogre::ColourValue::Red);
        //       pointLight->setSpecularColour(Ogre::ColourValue::Red);
        
        //    mRayScnQuery = gSceneMgr->createRayQuery(Ogre::Ray());
        
        Ogre::TexturePtr rttTexture =
        Ogre::TextureManager::getSingleton().createManual(
                                                          "RttTex",
                                                          Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                                                          Ogre::TEX_TYPE_2D,
                                                          mWidth,
                                                          mHeight,
                                                          0,
                                                          Ogre::PF_R8G8B8,
                                                          Ogre::TU_RENDERTARGET);
        
        mRenderTexture = rttTexture->getBuffer()->getRenderTarget();
        
        mRTTLeftCamera = gSceneMgr->createCamera("RTTLeftCamera");
        mRTTLeftCamera->setNearClipDistance(0.1f);
        mRTTLeftCamera->setFarClipDistance(1000.0f);
        mRTTLeftCamera->setPosition(0, 0, 50);
        mRTTLeftCamera->lookAt(0,0,0);
        mRTTLeftCamera->setAutoAspectRatio(true);
        
        mRTTLeftViewport = mRenderTexture->addViewport(mRTTLeftCamera, 0, 0.0f, 0.0f, 0.5f, 1.0f);
        mRenderTexture->setAutoUpdated(true);
        mRTTLeftViewport->setClearEveryFrame(true);
        mRTTLeftViewport->setBackgroundColour(Ogre::ColourValue::Green);
        mRTTLeftViewport->setOverlaysEnabled(true);
        
        mRTTRightCamera = gSceneMgr->createCamera("RTTRightCamera");
        mRTTRightCamera->setNearClipDistance(0.1f);
        mRTTRightCamera->setFarClipDistance(1000.0f);
        mRTTRightCamera->setPosition(0, 0, 50);
        mRTTRightCamera->lookAt(0,0,0);
        mRTTRightCamera->setAutoAspectRatio(true);
        
        mRTTRightViewport = mRenderTexture->addViewport(mRTTRightCamera, 1, 0.5f, 0.0f, 0.5f, 1.0f);
        mRenderTexture->setAutoUpdated(true);
        mRTTRightViewport->setClearEveryFrame(true);
        mRTTRightViewport->setBackgroundColour(Ogre::ColourValue::Blue);
        mRTTRightViewport->setOverlaysEnabled(true);
        
        mMiniscreen = new Ogre::Rectangle2D(true);
        mMiniscreen->setCorners(-1.0, 1.0, 1.0, -1.0);
        mMiniscreen->setBoundingBox(Ogre::AxisAlignedBox::BOX_INFINITE);
        
        Ogre::SceneNode* miniscreenNode =
        gSceneMgr->getRootSceneNode()->createChildSceneNode();
        miniscreenNode->attachObject(mMiniscreen);
        
        Ogre::MaterialPtr renderMat =
        Ogre::MaterialManager::getSingleton().create(
                                                     "RttMat",
                                                     Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        renderMat->getTechnique(0)->getPass(0)->setLightingEnabled(false);
        renderMat->getTechnique(0)->getPass(0)->createTextureUnitState("RttTex");
        
        mMiniscreen->setMaterial("RttMat");
        
        mRenderTexture->addListener(this);
        
        mPlatform = new MyGUI::OgrePlatform();
        mPlatform->initialise(mRenderTexture, gSceneMgr);
        mGUI = new MyGUI::Gui();
        
        mGUI->initialise();
        mButton = mGUI->createWidget<MyGUI::Button>("Button",10,10,200,100,MyGUI::Align::Stretch,"Main");
        mButton->setCaption("中文");
        mButton->setFontHeight(40);
        
        mSceneInited = true;
    }
    
    Ogre::DataStreamPtr openAPKFile(const Ogre::String& fileName)
    {
        //        if(gAssetMgr == NULL)
        //        {
        //
        //        }
        
        Ogre::DataStreamPtr stream;
        //        AAsset* asset = AAssetManager_open(gAssetMgr, fileName.c_str(), AASSET_MODE_BUFFER);
        //        if(asset)
        //        {
        //            LOGD("asset ok");
        //            off_t length = AAsset_getLength(asset);
        //            void* membuf = OGRE_MALLOC(length, Ogre::MEMCATEGORY_GENERAL);
        //            memcpy(membuf, AAsset_getBuffer(asset), length);
        //            AAsset_close(asset);
        //
        //            stream = Ogre::DataStreamPtr(new Ogre::MemoryDataStream(membuf, length, true, true));
        //            LOGI("openAPKFile ok %s", fileName.c_str());
        //        }
        //        else
        //        {
        //            LOGE("openAPKFile error %s", fileName.c_str());
        //        }
        return stream;
    }
    
    void loadResources(const char *name)
    {
        cf.load(mResourcesRoot + "/" + name);
        
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
                
                // OS X does not set the working directory relative to the app,
                // In order to make things portable on OS X we need to provide
                // the loading with it's own bundle path location
                if (!Ogre::StringUtil::startsWith(arch, "/", false)) // only adjust relative dirs
                    arch = Ogre::String(mResourcesRoot + arch);
                
                Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
            }
        }
    }
    
public:
//    OgreBaseApp(void* ogrePlayer, const Ogre::String& resourcesRoot) {
    OgreBaseApp() {
        //        mAppInterface = appInterface;
        
        gRoot = new Ogre::Root();
        
#ifdef OGRE_STATIC_LIB
        gStaticPluginLoader = new Ogre::StaticPluginLoader();
        gStaticPluginLoader->load();
#endif
        
        gRoot->setRenderSystem(gRoot->getAvailableRenderers().at(0));
        gRoot->initialise(false, "");
        
        //        gAssetMgr = mAppInterface->GetAssetManager();
        
        gRenderWnd = NULL;
        
//        mOgrePlayer = ogrePlayer;
//        mResourcesRoot = resourcesRoot;
        
        mSceneInited = false;
    }
    
    virtual ~OgreBaseApp() {
        //        Ogre::WindowEventUtilities::removeWindowEventListener(gRenderWnd, this);
    }
            
    virtual bool touchMoved( const OIS::MultiTouchEvent &arg ) {
        return true;
    }
    
    virtual bool touchPressed( const OIS::MultiTouchEvent &arg ) {
        return true;
    }
            
    virtual bool touchReleased( const OIS::MultiTouchEvent &arg ) {
        return true;
    }
    
    virtual bool touchCancelled( const OIS::MultiTouchEvent &arg ) {
        return true;
    }
            
protected:
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
    
    Ogre::Viewport* mRTTLeftViewport;
    Ogre::Viewport* mRTTRightViewport;
    Ogre::RenderTexture* mRenderTexture;
    Ogre::Camera* mRTTLeftCamera;
    Ogre::Camera* mRTTRightCamera;
    
    Ogre::Viewport* mSaveViewport;
    
    //    AAssetManager* gAssetMgr;
    
    Ogre::ConfigFile cf;
    
    //My GUI implement
    MyGUI::Gui* mGUI;
    MyGUI::OgrePlatform* mPlatform;
    MyGUI::ButtonPtr mButton;
    
    bool mSceneInited;
    int mWidth;
    int mHeight;
            
    OgreMultiTouch* mOgreMultiTouch;
    
private:
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& fe) {
        //Do nothing at all
        return true;
    }
    
    //////////////////////
    // Tutorial Section //
    //////////////////////
    virtual void preRenderTargetUpdate(const Ogre::RenderTargetEvent& rte) {
        // LOGD("preRenderTargetUpdate");
        // Ogre::RenderSystem* system = Ogre::Root::getSingleton().getRenderSystem();
        // mSaveViewport = system->_getViewport();
        // system->_setViewport(mRTTViewPort);
        mMiniscreen->setVisible(false);
        //    system->clearFrameBuffer(Ogre::FBT_COLOUR, Ogre::ColourValue::ZERO);
    }
    
    virtual void postRenderTargetUpdate(const Ogre::RenderTargetEvent& rte) {
        // LOGD("postRenderTargetUpdate");
        //       Ogre::RenderSystem* system = Ogre::Root::getSingleton().getRenderSystem();
        // // system->_setViewport(mSaveViewport);
        mMiniscreen->setVisible(true);
        
        // LOGD("The renderTexture native texture id : %d", renderTexture->getNativeTextureId());
    }
    
    /* Called just before a Viewport on a RenderTarget is to be updated.
     @remarks
     This method is called before each viewport on the RenderTarget is
     rendered to. You can use this to perform per-viewport settings changes,
     such as showing / hiding particular overlays.
     */
    virtual void preViewportUpdate(const Ogre::RenderTargetViewportEvent& evt) {
        if (evt.source == mRTTLeftViewport) {
            // LOGD("preViewportUpdate mRTTLeftViewport");
            mPlatform->getRenderManagerPtr()->setActiveViewport(0);
        } else if (evt.source == mRTTRightViewport) {
            // LOGD("preViewportUpdate mRTTRightViewport");
            mPlatform->getRenderManagerPtr()->setActiveViewport(1);
        } else {
            
        }
    }
    
    /* Called just after a Viewport on a RenderTarget is to be updated.
     @remarks
     This method is called after each viewport on the RenderTarget is
     rendered to.
     */
    virtual void postViewportUpdate(const Ogre::RenderTargetViewportEvent& evt) {
        
    }
    
private:
    Ogre::Rectangle2D* mMiniscreen;
    
private:
    friend void OgreApplicationMain(const char* appName, IAppInterface* appInterface);
            
    void* mOgrePlayer;
    Ogre::String mResourcesRoot;
    void go(IAppInterface* appInterface);
};

#endif /* OgreBaseApp_hpp */
