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
};

#endif /* OGRE_APPLICATION_H */
