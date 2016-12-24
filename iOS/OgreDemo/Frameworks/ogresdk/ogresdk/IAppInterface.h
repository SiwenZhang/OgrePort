//
//  IAppInterface.h
//  ogresdk
//
//  Created by liu enbao on 12/24/16.
//  Copyright © 2016 liu enbao. All rights reserved.
//

#ifndef I_APPINTERFACE_H
#define I_APPINTERFACE_H

class IAppLifeCycle;

#include <string>

class IAppInterface {
public:
    virtual void PollEvents() = 0;
    virtual void SetEventHandler( IAppLifeCycle* pHandler ) = 0;
    
    virtual void* getOgrePlayer() = 0;
    virtual std::string getResourcesPath() = 0;
    
    virtual ~IAppInterface() {
    
    }
};

#endif /* I_APPINTERFACE_H */
