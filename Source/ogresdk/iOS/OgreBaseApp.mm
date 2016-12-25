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

#import <UIKit/UIApplication.h>

void OgreBaseApp::loadResources(const char *name)
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

void OgreBaseApp::InitGameWindow() {
    Ogre::NameValuePairList opt;
    opt["colourDepth"] = "32";
    opt["contentScalingFactor"] = "2.0";
    opt["FSAA"] = "16";
    opt["externalWindowHandle"] = Ogre::StringConverter::toString((unsigned long)[UIApplication sharedApplication].keyWindow);
    opt["externalViewHandle"] = Ogre::StringConverter::toString((unsigned long)mOgrePlayer);
    opt["contentScalingFactor"] = Ogre::StringConverter::toString(1);
    
    gRenderWnd = gRoot->createRenderWindow("OgreWindow", 0, 0, true, &opt);
    
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

void OgreApplicationMain(const char* appName, IAppInterface* appInterface) {
    Any appInstance = CreateObject(appName);
    OgreBaseApp* baseApp = any_cast<OgreBaseApp*>(appInstance);
    baseApp->go(appInterface);
    delete baseApp;
}
