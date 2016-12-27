//
//  OgreBaseApp.cpp
//  ogresdk
//
//  Created by liu enbao on 12/24/16.
//  Copyright © 2016 liu enbao. All rights reserved.
//

#include "OgreBaseApp.h"
#include "ReflexCpp.h"
#include "Any.h"
#include "IAppInterface.h"

#import <UIKit/UIApplication.h>

LOGGER_IMPLEMENT(OgreBaseApp);

void OgreBaseApp::loadResources(const char *name) {
    cf.load(mAppInterface->getResourcesPath() + "/" + name);
    
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
    while (seci.hasMoreElements()) {
        Ogre::String sec, type, arch;
        sec = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        
        for (i = settings->begin(); i != settings->end(); i++) {
            type = i->first;
            arch = i->second;
            
            // OS X does not set the working directory relative to the app,
            // In order to make things portable on OS X we need to provide
            // the loading with it's own bundle path location
            if (!Ogre::StringUtil::startsWith(arch, "/", false)) // only adjust relative dirs
                arch = Ogre::String(mAppInterface->getResourcesPath() + arch);
            
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
        }
    }
}

// Surface
void OgreBaseApp::OnSurfaceCreated() {
    InitGameWindow();
}

void OgreBaseApp::OnSurfaceChanged(int iPixelFormat, int iWidth, int iHeight) {
    InitGameScene();
}

void OgreBaseApp::OnSurfaceDestroyed() {
    
}

void OgreBaseApp::InitGameWindow() {
    Ogre::NameValuePairList opt;
    opt["colourDepth"] = "32";
    opt["contentScalingFactor"] = "2.0";
    opt["FSAA"] = "16";
    opt["externalWindowHandle"] = Ogre::StringConverter::toString((unsigned long)[UIApplication sharedApplication].keyWindow);
    opt["externalViewHandle"] = Ogre::StringConverter::toString((unsigned long)mAppInterface->getOgrePlayer());
    opt["contentScalingFactor"] = Ogre::StringConverter::toString(1);
    
    mRenderWindow = mRoot->createRenderWindow("OgreWindow", 0, 0, true, &opt);
    
    InitStartScene();
    
    LDEBUG(OgreBaseApp, "InitGameWindow");
}

void OgreApplicationMain(const char* appName, IAppInterface* appInterface) {
    Any appInstance = CreateObject(appName);
    OgreBaseApp* baseApp = any_cast<OgreBaseApp*>(appInstance);
    baseApp->go(appInterface);
    delete baseApp;
}
