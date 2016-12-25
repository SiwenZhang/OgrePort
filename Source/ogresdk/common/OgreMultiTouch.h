//
//  OgreMultiTouch.h
//  ogresdk
//
//  Created by liu enbao on 12/24/16.
//  Copyright © 2016 liu enbao. All rights reserved.
//

#ifndef OGRE_MULTITOUCH_H
#define OGRE_MULTITOUCH_H

#include <OIS.h>

class OgreMultiTouch : public OIS::MultiTouch {
public:
    OgreMultiTouch():OIS::MultiTouch("DWM", true, 0, NULL) {
    
    }
    
    /** @copydoc Object::setBuffered */
    virtual void setBuffered(bool buffered) {
    
    }
    
    /** @copydoc Object::capture */
    virtual void capture() {
    
    }
    
    /** @copydoc Object::queryInterface */
    virtual OIS::Interface* queryInterface(OIS::Interface::IType type) {
        return 0;
    }
    
    /** @copydoc Object::_initialize */
    virtual void _initialize() {
    
    }
    
    OIS::MultiTouchState &getMultiTouchState(int i, int width, int height) {
        while(i >= mStates.size()) {
            OIS::MultiTouchState state;
            state.width = width;
            state.height = height;
            mStates.push_back(state);
        }
        return mStates[i];
    }
    
    void injectTouchEvent(int pointerId, int action, float x, float y, int width, int height);
};

#endif /* OGRE_MULTITOUCH_H */
