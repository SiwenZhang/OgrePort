//
//  OgreApplication.hpp
//  OgreDemo
//
//  Created by liu enbao on 12/24/16.
//  Copyright © 2016 liu enbao. All rights reserved.
//

#ifndef OGRE_APPLICATION_H
#define OGRE_APPLICATION_H

#include "OgreBaseApp.h"
#include "ReflexCpp.h"

class OgreApplication: public OgreBaseApp {
    DECLARE_CLASS(OgreApplication)

public:
    OgreApplication();
    virtual ~OgreApplication();
    
protected:
    virtual bool touchMoved( const OIS::MultiTouchEvent &arg ) {
        pNode->yaw(Ogre::Radian(Ogre::Degree(arg.state.X.rel)));
//        mRTTRightCamera->yaw(Ogre::Radian(Ogre::Degree(-arg.state.X.rel)));
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
};

#endif /* OGRE_APPLICATION_H */
