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
        public Ogre::FrameListener,
        public Ogre::WindowEventListener,
        public OIS::MultiTouchListener {
public:
    OgreBaseApp()
        :mRoot(NULL),
        mCamera(NULL),
        mSceneMgr(NULL),
        mWindow(NULL)
//        mOverlaySystem(NULL),
            {
        
    }
            
protected:
    Ogre::Root*                 mRoot;
    Ogre::Camera*               mCamera;
    Ogre::SceneManager*         mSceneMgr;
    Ogre::RenderWindow*         mWindow;
    Ogre::Viewport*             mViewport;
//    Ogre::OverlaySystem*        mOverlaySystem;
    
    Ogre::ShaderGeneratorTechniqueResolverListener* mMatListener;
    Ogre::StaticPluginLoader* mStaticPluginLoader;
    
    OgreMultiTouch* mOgreMultiTouch;
    
    Ogre::ConfigFile cf;

protected:
    IAppInterface* mAppInterface;

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
        mOgreMultiTouch->injectTouchEvent(iPointerID, iAction, fPosX, fPosY, mWindow->getWidth(), mWindow->getHeight());
    }

protected:
    virtual bool setup() {
        mRoot = new Ogre::Root();
        
#ifdef OGRE_STATIC_LIB
        mStaticPluginLoader = new Ogre::StaticPluginLoader();
        mStaticPluginLoader->load();
#endif
        mRoot->setRenderSystem(mRoot->getAvailableRenderers().at(0));
        mRoot->initialise(false, "");
        
        setupResources("resources.cfg");
        
//        setupRTShader();
        
//        if (!configure()) {
//            return false;
//        }
//        
//        chooseSceneManager();
        
        return true;
    }
            
    virtual void unsetup() {
        
    }

    virtual void createGameWindow();
    
    virtual void destroyGameWindow();
            
//    virtual bool configure(void) {
//        
//        return true;
//    }
            
    virtual void chooseSceneManager(void) {
        // Get the SceneManager, in this case a generic one
        mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
        
//        // Initialize the OverlaySystem (changed for Ogre 1.9)
//        mOverlaySystem = new Ogre::OverlaySystem();
//        mSceneMgr->addRenderQueueListener(mOverlaySystem);
    }
    
    virtual void createCamera(void) {
        mCamera = mSceneMgr->createCamera("MyCam");
        mCamera->setNearClipDistance(0.1f);
        mCamera->setFarClipDistance(1000.0f);
        mCamera->setPosition(0,0,50.0f);
        mCamera->lookAt(0,0,0);
        mCamera->setAutoAspectRatio(true);
    }

    virtual void setupResources(const char* resoureCfg);

    virtual void loadResources() {
        Ogre::RTShader::ShaderGenerator::initialize();
        Ogre::RTShader::ShaderGenerator::getSingletonPtr()->setTargetLanguage("glsles");
        mMatListener = new Ogre::ShaderGeneratorTechniqueResolverListener(Ogre::RTShader::ShaderGenerator::getSingletonPtr());
        Ogre::MaterialManager::getSingleton().addListener(mMatListener);
        
        Ogre::RTShader::ShaderGenerator::getSingletonPtr()->addSceneManager(mSceneMgr);
        
        Ogre::RTShader::ShaderGenerator::getSingletonPtr()->invalidateScheme(Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME);
        
        Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    }
            
    virtual void createScene(void) = 0; // Override me!
    virtual void destroyScene(void) = 0; // Override me!
    
    virtual void createViewports(void) {
        // Create one viewport, entire window
        mViewport = mWindow->addViewport(mCamera);
        mViewport->setBackgroundColour(Ogre::ColourValue(0.3, 0.3, 0.3));
        
//        // Alter the camera aspect ratio to match the viewport
//        mCamera->setAspectRatio(Ogre::Real(mViewport->getActualWidth()) / Ogre::Real(mViewport->getActualHeight()));
    }
    
    virtual void createResourceListener(void) {
    
    }
            
    virtual void createFrameListener(void) {
        
        mOgreMultiTouch = new OgreMultiTouch();
        mOgreMultiTouch->setEventCallback(this);

        //Add some event looper
        mRoot->addFrameListener(this);
    }

    virtual void go(IAppInterface* appInterface) {
        appInterface->SetEventHandler(this);

        mAppInterface = appInterface;
        
        setup();
        
        while (true) {
            appInterface->PollEvents();
            
            renderOneFrame();
            
            usleep(10 * 1000);
        }
        
        unsetup();
    }

    virtual void renderOneFrame() {
        if(mWindow != NULL && mWindow->isActive()) {
            mRoot->renderOneFrame();
        }
    }

private:
    friend void OgreApplicationMain(const char* appName, IAppInterface* appInterface);

private:
    LOGGER_DECLARE(OgreBaseApp);
};

#endif /* OgreBaseApp_hpp */
