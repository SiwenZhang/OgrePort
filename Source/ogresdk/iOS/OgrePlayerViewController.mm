//
//  OgrePlayerViewController.m
//  ogresdk
//
//  Created by liu enbao on 12/22/16.
//  Copyright © 2016 liu enbao. All rights reserved.
//

#import "OgrePlayerViewController.h"
#import "OgrePlayer.h"

@interface OgrePlayerViewController ()

@end

@implementation OgrePlayerViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    NSLog(@"the view frame is : %@", NSStringFromCGRect(self.view.frame));
    
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
