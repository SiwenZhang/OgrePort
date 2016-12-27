//
//  OgreApplication.cpp
//  OgreDemo
//
//  Created by liu enbao on 12/24/16.
//  Copyright © 2016 liu enbao. All rights reserved.
//

#include "OgreApplication.h"
#include "interface/IAppInterface.h"
#include "common/OgreApplicationMain.h"

OgreApplication::OgreApplication() {

}

OgreApplication::~OgreApplication() {
    
}

void OgreApplication::createScene(void) {
    mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
    
    mSinbadEntity = mSceneMgr->createEntity("Sinbad", "Sinbad.mesh");
    mSinbadNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("Sinbad");
    mSinbadNode->attachObject(mSinbadEntity);
    
    mRTTTexture = Ogre::TextureManager::getSingleton().createManual(
                                                                "RttTex",
                                                                Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,                                                   Ogre::TEX_TYPE_2D,
                                                                mWindow->getWidth(),
                                                                mWindow->getHeight(),
                                                                0,
                                                                Ogre::PF_R8G8B8,
                                                                Ogre::TU_RENDERTARGET);

    mRenderTexture = mRTTTexture->getBuffer()->getRenderTarget();

    mRTTLeftCamera = mSceneMgr->createCamera("RTTLeftCamera");
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
    
    mRTTRightCamera = mSceneMgr->createCamera("RTTRightCamera");
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
    
    mMiniscreenNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    mMiniscreenNode->attachObject(mMiniscreen);

    mRTTMaterial = Ogre::MaterialManager::getSingleton().create(
                                                            "RttMat",
                                                            Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    mRTTMaterial->getTechnique(0)->getPass(0)->setLightingEnabled(false);
    mRTTMaterial->getTechnique(0)->getPass(0)->createTextureUnitState("RttTex");

    mMiniscreen->setMaterial("RttMat");

    mRenderTexture->addListener(this);
    mWindow->addListener(this);
}

void OgreApplication::destroyScene(void) {
    
}

void OgreApplication::preRenderTargetUpdate(const Ogre::RenderTargetEvent& rte) {
    if (rte.source == mRenderTexture) {
        mMiniscreen->setVisible(false);
    } else if (rte.source == mWindow) {
        mSinbadEntity->setVisible(false);
    }
}

void OgreApplication::postRenderTargetUpdate(const Ogre::RenderTargetEvent& rte) {
    if (rte.source == mRenderTexture) {
        mMiniscreen->setVisible(true);
    } else if (rte.source == mWindow) {
        mSinbadEntity->setVisible(true);
    }
}

bool OgreApplication::touchMoved( const OIS::MultiTouchEvent &arg ) {
    mSinbadNode->yaw(Ogre::Radian(Ogre::Degree(arg.state.X.rel)));
    return true;
}

IMPLEMENT_CLASS(OgreApplication)

void OgreMain(IAppInterface* appInterface) {
    OgreApplicationMain("OgreApplication", appInterface);
}