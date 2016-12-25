//
//  OgrePlayerViewController.m
//  ogresdk
//
//  Created by liu enbao on 12/22/16.
//  Copyright © 2016 liu enbao. All rights reserved.
//

#import "OgrePlayerViewController.h"
#import "OgrePlayer.h"
#include "Logger.h"

@interface OgrePlayerViewController ()

@end

@implementation OgrePlayerViewController

- (instancetype)init {
    if (self = [super init]) {
         [self globalInit];
    }
    return self;
}

- (instancetype)initWithCoder:(NSCoder *)aDecoder {
    if (self = [super initWithCoder:aDecoder]) {
        [self globalInit];
    }
    return self;
}

- (instancetype)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if (self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil]) {
        [self globalInit];
    }
    return self;
}

- (void)globalInit {
//    LOGGER_GLOBAL_INIT();
}

- (void)viewDidLoad {
    [super viewDidLoad];
    mOgrePlayer = [[OgrePlayer alloc] initWithFrame:self.view.bounds resourceRoot:mResourcesRoot];
    [self.view addSubview:mOgrePlayer];
    [mOgrePlayer ogreViewDidLoad];
}

- (void)viewDidUnload {
    [mOgrePlayer ogreViewDidUnload];
    [mOgrePlayer removeFromSuperview];
    [super viewDidUnload];
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    [mOgrePlayer ogreViewDidAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    [mOgrePlayer ogreViewWillDisappear:animated];
}

- (void)didReceiveMemoryWarning {
    [mOgrePlayer ogreDidReceiveMemoryWarning];
    [super didReceiveMemoryWarning];
}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    [mOgrePlayer ogreTouchesBegan:touches withEvent:event];
}

- (void)touchesMoved:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    [mOgrePlayer ogreTouchesMoved:touches withEvent:event];
}

- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    [mOgrePlayer ogreTouchesEnded:touches withEvent:event];
}

- (void)touchesCancelled:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    [mOgrePlayer ogreTouchesCancelled:touches withEvent:event];
}

@end
