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
    [mOgrePlayer viewDidLoad];
}

- (void)viewDidUnload {
    [mOgrePlayer viewDidUnload];
    [mOgrePlayer removeFromSuperview];
    [super viewDidUnload];
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    [mOgrePlayer viewDidAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    [mOgrePlayer viewWillDisappear:animated];
}

- (void)didReceiveMemoryWarning {
    [mOgrePlayer didReceiveMemoryWarning];
    [super didReceiveMemoryWarning];
}

@end
