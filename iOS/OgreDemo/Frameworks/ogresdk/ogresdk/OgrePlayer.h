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

- (void)viewDidLoad;

- (void)viewDidUnload;

- (void)viewDidAppear:(BOOL)animated;

- (void)viewWillDisappear:(BOOL)animated;

- (void)didReceiveMemoryWarning;

@end
