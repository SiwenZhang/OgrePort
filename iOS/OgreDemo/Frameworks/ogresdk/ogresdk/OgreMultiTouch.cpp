//
//  OgreMultiTouch.cpp
//  ogresdk
//
//  Created by liu enbao on 12/24/16.
//  Copyright © 2016 liu enbao. All rights reserved.
//

#include "OgreMultiTouch.h"

void OgreMultiTouch::injectTouchEvent(int pointerId, int action, float x, float y, int width, int height) {
    OIS::MultiTouchState &state = getMultiTouchState(pointerId, x, y);
    switch (action) {
        case 0:
            state.touchType = OIS::MT_Pressed;
            state.X.abs = (int)x;
            state.Y.abs = (int)y;
            break;
        case 1: {
            state.touchType = OIS::MT_Moved;
            
            int lastX = state.X.abs;
            state.X.abs = (int)x;
            state.X.rel = state.X.abs - lastX;
            
            int lastY = state.Y.abs;
            state.Y.abs = (int)y;
            state.Y.rel = state.Y.abs - lastY;
        }
            break;
        case 2:
            state.touchType = OIS::MT_Released;
            state.X.abs = (int)x;
            state.Y.abs = (int)y;
            break;
        case 3:
            state.touchType = OIS::MT_Cancelled;
            state.X.abs = (int)x;
            state.Y.abs = (int)y;
            break;
        default:
            state.touchType = OIS::MT_None;
            break;
    }
    
    state.Z.abs = 0;
    state.Z.rel = 0;
    
    if(state.touchType != OIS::MT_None && mBuffered) {
        OIS::MultiTouchEvent evt(this, state);
        
        switch(state.touchType){
            case OIS::MT_Pressed:
                mListener->touchPressed(evt);
                break;
            case OIS::MT_Released:
                mListener->touchReleased(evt);
                break;
            case OIS::MT_Moved:
                mListener->touchMoved(evt);
                break;
            case OIS::MT_Cancelled:
                mListener->touchCancelled(evt);
                break;
        }
    }
}
