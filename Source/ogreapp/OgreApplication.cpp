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

IMPLEMENT_CLASS(OgreApplication)

#ifdef __cplusplus
extern "C" {
#endif
void OgreMain(IAppInterface* appInterface) {
    OgreApplicationMain("OgreApplication", appInterface);
}
#ifdef __cplusplus
}
#endif