//
//  OgreApplication.cpp
//  OgreDemo
//
//  Created by liu enbao on 12/24/16.
//  Copyright © 2016 liu enbao. All rights reserved.
//

#include "OgreApplication.h"
#include "IAppInterface.h"
#include "OgreApplicationMain.h"

OgreApplication::OgreApplication() {

}

OgreApplication::~OgreApplication() {
    
}

IMPLEMENT_CLASS(OgreApplication)

void OgreMain(IAppInterface* appInterface) {
    OgreApplicationMain("OgreApplication", appInterface);
}
