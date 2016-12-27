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
    
}

void OgreApplication::destroyScene(void) {
    
}

IMPLEMENT_CLASS(OgreApplication)

void OgreMain(IAppInterface* appInterface) {
    OgreApplicationMain("OgreApplication", appInterface);
}
