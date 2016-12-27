//
//  OgreApplication.hpp
//  OgreDemo
//
//  Created by liu enbao on 12/24/16.
//  Copyright © 2016 liu enbao. All rights reserved.
//

#ifndef OGRE_APPLICATION_H
#define OGRE_APPLICATION_H

#include "common/OgreBaseApp.h"
#include "utils/ReflexCpp.h"

class OgreApplication:
                public OgreBaseApp,
                public Ogre::RenderTargetListener {
    DECLARE_CLASS(OgreApplication)

public:
    OgreApplication();
    virtual ~OgreApplication();
    
protected:
    virtual void createScene(void); // Override me!
    virtual void destroyScene(void); // Override me!
    
protected:
    virtual bool touchMoved( const OIS::MultiTouchEvent &arg );
    
    virtual bool touchPressed( const OIS::MultiTouchEvent &arg ) {
        return true;
    }
    
    virtual bool touchReleased( const OIS::MultiTouchEvent &arg ) {
        return true;
    }
    
    virtual bool touchCancelled( const OIS::MultiTouchEvent &arg ) {
        return true;
    }
                    
    virtual void preRenderTargetUpdate(const Ogre::RenderTargetEvent& rte);
    virtual void postRenderTargetUpdate(const Ogre::RenderTargetEvent& rte);
    
private:
    Ogre::Entity* mSinbadEntity;
    Ogre::SceneNode* mSinbadNode;

private:
    Ogre::Viewport* mRTTLeftViewport;
    Ogre::Viewport* mRTTRightViewport;
    Ogre::Camera* mRTTLeftCamera;
    Ogre::Camera* mRTTRightCamera;
    
    Ogre::Rectangle2D* mMiniscreen;
    Ogre::SceneNode* mMiniscreenNode;

    Ogre::RenderTexture* mRenderTexture;
    Ogre::TexturePtr mRTTTexture;
    Ogre::MaterialPtr mRTTMaterial;
};

#endif /* OGRE_APPLICATION_H */
