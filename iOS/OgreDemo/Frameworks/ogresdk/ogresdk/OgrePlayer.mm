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

@interface OgrePlayer () {
    IAppLifeCycle* mAppLifeCycle;
    
    std::string mResourcesRoot;
    
    NSThread* mOgreMainLoop;
    
    NSMutableArray* mEventQueue;
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
    }
    return self;
}

- (void)viewDidLoad {
    NSBlockOperation* op = [NSBlockOperation blockOperationWithBlock:^{
        mAppLifeCycle->OnSurfaceCreated();
    }];
    [self queueEvent:op];
}

- (void)viewDidUnload {
    
}

- (void)viewDidAppear:(BOOL)animated {
    
}

- (void)viewWillDisappear:(BOOL)animated {
    
}

- (void)didReceiveMemoryWarning {
    
}

- (void)queueEvent:(NSOperation*)r {
    @synchronized(mEventQueue) {
        [mEventQueue addObject:r];
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
    [self queueEvent:op];
}

@end
