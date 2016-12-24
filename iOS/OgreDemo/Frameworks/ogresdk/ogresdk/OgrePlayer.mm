//
//  OgrePlayer.m
//  ogresdk
//
//  Created by liu enbao on 12/22/16.
//  Copyright © 2016 liu enbao. All rights reserved.
//

#import "OgrePlayer.h"
#include "IAppLifeCycle.h"
#include "IAppInterface.h"
#include "OgreBaseApp.h"
#include "ReflexCpp.h"
#include "Any.h"

#include <string>

const int kMultiTouchMaxEntries = 10;

typedef struct TouchSlot {
    void * uiTouchPtr;
} TouchSlot;

@interface OgrePlayer () {
    IAppLifeCycle* mAppLifeCycle;
    
    std::string mResourcesRoot;
    
    NSThread* mOgreMainLoop;
    
    NSMutableArray* mEventQueue;
    
    TouchSlot mTouchesSlot[kMultiTouchMaxEntries];
}

- (void)PollEvents;

- (void)setAppLifeCycle:(IAppLifeCycle*)appLifeCycle;
- (std::string)getResourcesPath;

@end

@implementation OgrePlayer

//Use opengl es layer
+ (Class) layerClass {
    return [CAEAGLLayer class];
}

- (instancetype)initWithFrame:(CGRect)frame resourceRoot:(NSString*)resourceRoot {
    if (self = [super initWithFrame:frame]) {
        mResourcesRoot = [resourceRoot UTF8String];
        
        mOgreMainLoop = [[NSThread alloc] initWithTarget:self selector:@selector(run) object:nil];
        [mOgreMainLoop setName:@"OgreMainLoop"];
        [mOgreMainLoop start];
        
        mEventQueue = [[NSMutableArray alloc] init];
        
        memset(mTouchesSlot, 0, sizeof(mTouchesSlot));
    }
    return self;
}

- (void)ogreViewDidLoad {
    NSBlockOperation* op = [NSBlockOperation blockOperationWithBlock:^{
        mAppLifeCycle->OnSurfaceCreated();
    }];
    [self ogreQueueEvent:op];
}

- (void)ogreViewDidUnload {
    
}

- (void)ogreViewDidAppear:(BOOL)animated {
    
}

- (void)ogreViewWillDisappear:(BOOL)animated {
    
}

- (void)ogreDidReceiveMemoryWarning {
    
}

- (void)ogreQueueEvent:(NSOperation*)op {
    @synchronized(mEventQueue) {
        [mEventQueue addObject:op];
    }
}

- (void)PollEvents {
    @synchronized (mEventQueue) {
        NSEnumerator *enumerator = [mEventQueue objectEnumerator];
        
        NSOperation* op = nil;
        while ((op = [enumerator nextObject]) != nil) {
            [op start];
        }
    }
}

- (void)setAppLifeCycle:(IAppLifeCycle*)appLifeCycle {
    mAppLifeCycle = appLifeCycle;
}

- (std::string)getResourcesPath {
    return mResourcesRoot;
}

class OgreAppInterface: public IAppInterface {
public:
    OgreAppInterface(void* priv) {
        mPriv = priv;
    }
    
    virtual ~OgreAppInterface() {
        
    }
    
    virtual void PollEvents() {
        [(__bridge OgrePlayer*)mPriv PollEvents];
    }
    
    virtual void SetEventHandler(IAppLifeCycle* pHandler) {
        [(__bridge OgrePlayer*)mPriv setAppLifeCycle:pHandler];
    }
    
    void* getOgrePlayer() {
        return mPriv;
    }
    
    std::string getResourcesPath() {
        return [(__bridge OgrePlayer*)mPriv getResourcesPath];
    }
    
private:
    void* mPriv;
};

extern void OgreMain(IAppInterface* appInterface);

- (void)run {
    IAppInterface* appInterface = new OgreAppInterface((__bridge void*)self);
    OgreMain(appInterface);
    delete appInterface;
}

void OgreApplicationMain(const char* appName, IAppInterface* appInterface) {
    Any appInstance = CreateObject(appName);
    OgreBaseApp* baseApp = any_cast<OgreBaseApp*>(appInstance);
    baseApp->go(appInterface);
    delete baseApp;
}

- (void)layoutSubviews {
    unsigned int width = (uint)self.bounds.size.width;
    unsigned int height = (uint)self.bounds.size.height;

    NSBlockOperation* op = [NSBlockOperation blockOperationWithBlock:^{
        mAppLifeCycle->OnSurfaceChanged(0, width, height);
    }];
    [self ogreQueueEvent:op];
}

- (void)ogreTouchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    for (UITouch* touch in touches) {
        int pointer = [self getTouchPointer:(__bridge void*)touch];
        CGPoint location = [touch locationInView:self];
        NSBlockOperation* op = [NSBlockOperation blockOperationWithBlock:^{
            mAppLifeCycle->OnTouch(pointer, location.x, location.y, 0);
        }];
        [self ogreQueueEvent:op];
    }
}

- (void)ogreTouchesMoved:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    for (UITouch* touch in touches) {
        int pointer = [self getTouchPointer:(__bridge void*)touch];
        CGPoint location = [touch locationInView:self];
        NSBlockOperation* op = [NSBlockOperation blockOperationWithBlock:^{
            mAppLifeCycle->OnTouch(pointer, location.x, location.y, 1);
        }];
        [self ogreQueueEvent:op];
    }
}

- (void)ogreTouchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    for (UITouch* touch in touches) {
        int pointer = [self getTouchPointer:(__bridge void*)touch];
        CGPoint location = [touch locationInView:self];
        NSBlockOperation* op = [NSBlockOperation blockOperationWithBlock:^{
            mAppLifeCycle->OnTouch(pointer, location.x, location.y, 2);
        }];
        [self ogreQueueEvent:op];
        [self unsetTouchPointer:pointer];
    }
}

- (void)ogreTouchesCancelled:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    for (UITouch* touch in touches) {
        int pointer = [self getTouchPointer:(__bridge void*)touch];
        CGPoint location = [touch locationInView:self];
        NSBlockOperation* op = [NSBlockOperation blockOperationWithBlock:^{
            mAppLifeCycle->OnTouch(pointer, location.x, location.y, 3);
        }];
        [self ogreQueueEvent:op];
        [self unsetTouchPointer:pointer];
    }
}

- (int)getTouchPointer:(void*)touchPtr {
    int pos = - 1;
    
    // Find an existing slot for this touch value.
    for (int i = 0; i < kMultiTouchMaxEntries; ++i) {
        if (mTouchesSlot[i].uiTouchPtr == touchPtr) {
            pos = i;
            break;
        }
    }
    
    // No exiting slot found. Find first empty slot.
    if (pos == -1) {
        for (int i = 0; i < kMultiTouchMaxEntries; ++i) {
            if (mTouchesSlot[i].uiTouchPtr == NULL) {
                pos = i;
                mTouchesSlot[pos].uiTouchPtr = touchPtr;
                break;
            }
        }
    }
    
    return pos;
}

- (void)unsetTouchPointer:(int)pos {
    mTouchesSlot[pos].uiTouchPtr = NULL;
}

@end
