//
//  OgrePlayer.h
//  ogresdk
//
//  Created by liu enbao on 12/22/16.
//  Copyright © 2016 liu enbao. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface OgrePlayer : UIView

- (instancetype)initWithFrame:(CGRect)frame resourceRoot:(NSString*)resourceRoot;

- (void)ogreQueueEvent:(NSOperation*)op;

- (void)ogreViewDidLoad;

- (void)ogreViewDidUnload;

- (void)ogreViewDidAppear:(BOOL)animated;

- (void)ogreViewWillDisappear:(BOOL)animated;

- (void)ogreDidReceiveMemoryWarning;

- (void)ogreTouchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event;

- (void)ogreTouchesMoved:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event;

- (void)ogreTouchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event;

- (void)ogreTouchesCancelled:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event;

@end
