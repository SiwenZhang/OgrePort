//
//  OgreBaseApp.cpp
//  ogresdk
//
//  Created by liu enbao on 12/24/16.
//  Copyright © 2016 liu enbao. All rights reserved.
//

#include "OgreBaseApp.h"
#include "IAppInterface.h"
#include "OgreMultiTouch.h"

#import <UIKit/UIApplication.h>

void OgreBaseApp::InitGameWindow() {
    Ogre::NameValuePairList opt;
    opt["colourDepth"] = "32";
    opt["contentScalingFactor"] = "2.0";
    opt["FSAA"] = "16";
    opt["externalWindowHandle"] = Ogre::StringConverter::toString((unsigned long)[UIApplication sharedApplication].keyWindow);
    opt["externalViewHandle"] = Ogre::StringConverter::toString((unsigned long)mOgrePlayer);
    opt["contentScalingFactor"] = Ogre::StringConverter::toString(1);
    
    gRenderWnd = gRoot->createRenderWindow("OgreWindow", 0, 0, true, &opt);
    
    mOgreMultiTouch = new OgreMultiTouch();
    mOgreMultiTouch->setEventCallback(this);
    
    InitStartScene();
    
    //        AConfiguration* config = AConfiguration_new();
    //        // AConfiguration_fromAssetManager(config, gAssetMgr);
    //        //        AConfiguration_setOrientation(config, 2);
    //
    //        if(!gRenderWnd)
    //        {
    //            Ogre::ArchiveManager::getSingleton().addArchiveFactory( new Ogre::APKFileSystemArchiveFactory(gAssetMgr) );
    //            Ogre::ArchiveManager::getSingleton().addArchiveFactory( new Ogre::APKZipArchiveFactory(gAssetMgr) );
    //
    //            Ogre::NameValuePairList opt;
    //            opt["externalWindowHandle"] = Ogre::StringConverter::toString((int)mAppInterface->GetWindow());
    //            // opt["androidConfig"] = Ogre::StringConverter::toString((int)config);
    //
    //            gRenderWnd = gRoot->createRenderWindow("OgreWindow", 1920, 1080, true, &opt);
    //
    //            Ogre::WindowEventUtilities::addWindowEventListener(gRenderWnd, this);
    //
    //            InitStartScene();
    //        }
    //        else
    //        {
    //            static_cast<Ogre::AndroidEGLWindow*>(gRenderWnd)->_createInternalResources(mAppInterface->GetWindow(), NULL);
    //        }
    //        AConfiguration_delete(config);
}

void OgreBaseApp::OnTouch( int iPointerID, float fPosX, float fPosY, int iAction ) {
    printf("fPosX : %f fPosY: %f\n", fPosX, fPosY);
    mOgreMultiTouch->injectTouchEvent(iPointerID, iAction, fPosX, fPosY, gRenderWnd->getWidth(), gRenderWnd->getHeight());
}

void OgreBaseApp::go(IAppInterface* appInterface) {
    appInterface->SetEventHandler(this);
    
    mResourcesRoot = appInterface->getResourcesPath();
    mOgrePlayer = appInterface->getOgrePlayer();
    
    while (true) {
        appInterface->PollEvents();
        
        renderOneFrame();
        
        usleep(10 * 1000);
    }
}
