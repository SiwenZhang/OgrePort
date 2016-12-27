//
//  OgreBaseApp.hpp
//  ogresdk
//
//  Created by liu enbao on 12/24/16.
//  Copyright © 2016 liu enbao. All rights reserved.
//

#ifndef OGRE_BASEAPP_H
#define OGRE_BASEAPP_H

#include "Ogre.h"

#define OGRE_STATIC_LIB
#define OGRE_STATIC_GLES2
#define OGRE_STATIC_ParticleFX
#define OGRE_STATIC_OctreeSceneManager

#include "interface/IAppLifeCycle.h"

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

#include "interface/IAppInterface.h"

#include "OgreMultiTouch.h"

#include "utils/Logger.h"

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
    virtual void OnSurfaceCreated();
    
    virtual void OnSurfaceChanged(int iPixelFormat, int iWidth, int iHeight);
    
    virtual void OnSurfaceDestroyed();
    
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
    
    virtual void OnTouch(int iPointerID, float fPosX, float fPosY, int iAction) {
        mOgreMultiTouch->injectTouchEvent(iPointerID, iAction, fPosX, fPosY, mRenderWindow->getWidth(), mRenderWindow->getHeight());
    }
    
private:
    void InitGameWindow();
    
    void InitStartScene() {
        mSceneManager = mRoot->createSceneManager(Ogre::ST_GENERIC);
        
        Ogre::RTShader::ShaderGenerator::initialize();
        Ogre::RTShader::ShaderGenerator::getSingletonPtr()->setTargetLanguage("glsles");
        mMatListener = new Ogre::ShaderGeneratorTechniqueResolverListener(Ogre::RTShader::ShaderGenerator::getSingletonPtr());
        Ogre::MaterialManager::getSingleton().addListener(mMatListener);
        
        Ogre::RTShader::ShaderGenerator::getSingletonPtr()->addSceneManager(mSceneManager);
        
        camera = mSceneManager->createCamera("MyCam");
        camera->setNearClipDistance(0.1f);
        camera->setFarClipDistance(1000.0f);
        camera->setPosition(0,0,50.0f);
        camera->lookAt(0,0,0);
        camera->setAutoAspectRatio(true);
        
        vp = mRenderWindow->addViewport(camera);
        
        mOgreMultiTouch = new OgreMultiTouch();
        mOgreMultiTouch->setEventCallback(this);
        
        loadResources("resources.cfg");
    }
    
    void InitGameScene() {
        if (mSceneInited == true) {
            return ;
        }
        
        Ogre::RTShader::ShaderGenerator::getSingletonPtr()->invalidateScheme(Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME);
        Ogre::ResourceGroupManager::getSingletonPtr()->initialiseAllResourceGroups();
        
        mSceneManager->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
        
        Ogre::Entity* pEntity = mSceneManager->createEntity("Sinbad", "Sinbad.mesh");
        pNode = mSceneManager->getRootSceneNode()->createChildSceneNode("Sinbad");
        pNode->attachObject(pEntity);

        Ogre::TexturePtr rttTexture =
        Ogre::TextureManager::getSingleton().createManual(
                                                          "RttTex",
                                                          Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                                                          Ogre::TEX_TYPE_2D,
                                                          mRenderWindow->getWidth(),
                                                          mRenderWindow->getHeight(),
                                                          0,
                                                          Ogre::PF_R8G8B8,
                                                          Ogre::TU_RENDERTARGET);
        
        mRenderTexture = rttTexture->getBuffer()->getRenderTarget();
        
        mRTTLeftCamera = mSceneManager->createCamera("RTTLeftCamera");
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
        
        mRTTRightCamera = mSceneManager->createCamera("RTTRightCamera");
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
        mSceneManager->getRootSceneNode()->createChildSceneNode();
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
        mPlatform->initialise(mRenderTexture, mSceneManager);
        mGUI = new MyGUI::Gui();
        
        mGUI->initialise();
        mButton = mGUI->createWidget<MyGUI::Button>("Button",10,10,200,100,MyGUI::Align::Stretch,"Main");
        mButton->setCaption("中文");
        mButton->setFontHeight(40);
        
        mSceneInited = true;
    }

    void loadResources(const char *name);
    
public:
    OgreBaseApp() {
        mRoot = new Ogre::Root();
        
#ifdef OGRE_STATIC_LIB
        mStaticPluginLoader = new Ogre::StaticPluginLoader();
        mStaticPluginLoader->load();
#endif
        mRoot->setRenderSystem(mRoot->getAvailableRenderers().at(0));
        mRoot->initialise(false, "");
        
        mRenderWindow = NULL;
        
        mSceneInited = false;
    }
    
    virtual ~OgreBaseApp() {
        Ogre::WindowEventUtilities::removeWindowEventListener(mRenderWindow, this);
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
    Ogre::RenderWindow* mRenderWindow;
    Ogre::Root* mRoot;
    Ogre::SceneManager* mSceneManager;
    Ogre::ShaderGeneratorTechniqueResolverListener* mMatListener;
    Ogre::StaticPluginLoader* mStaticPluginLoader;

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
    
    Ogre::ConfigFile cf;
    
    MyGUI::Gui* mGUI;
    MyGUI::OgrePlatform* mPlatform;
    MyGUI::ButtonPtr mButton;
    
    bool mSceneInited;
            
    OgreMultiTouch* mOgreMultiTouch;
    
private:
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& fe) {
        return true;
    }
    
    virtual void preRenderTargetUpdate(const Ogre::RenderTargetEvent& rte) {
        mMiniscreen->setVisible(false);
    }
    
    virtual void postRenderTargetUpdate(const Ogre::RenderTargetEvent& rte) {
        mMiniscreen->setVisible(true);
    }
    
    virtual void preViewportUpdate(const Ogre::RenderTargetViewportEvent& evt) {
        if (evt.source == mRTTLeftViewport) {
            mPlatform->getRenderManagerPtr()->setActiveViewport(0);
        } else if (evt.source == mRTTRightViewport) {
            mPlatform->getRenderManagerPtr()->setActiveViewport(1);
        } else {
            
        }
    }
    
    virtual void postViewportUpdate(const Ogre::RenderTargetViewportEvent& evt) {
        
    }
    
private:
    Ogre::Rectangle2D* mMiniscreen;
    
protected:
    IAppInterface* mAppInterface;

    virtual void go(IAppInterface* appInterface) {
        appInterface->SetEventHandler(this);

        mAppInterface = appInterface;
        
        while (true) {
            appInterface->PollEvents();
            
            renderOneFrame();
            
            usleep(10 * 1000);
        }
    }
            
    virtual void renderOneFrame() {
        if(mRenderWindow != NULL && mRenderWindow->isActive()) {
            mRoot->renderOneFrame();
        }
    }

private:
    friend void OgreApplicationMain(const char* appName, IAppInterface* appInterface);

private:
    LOGGER_DECLARE(OgreBaseApp);
};

#endif /* OgreBaseApp_hpp */
