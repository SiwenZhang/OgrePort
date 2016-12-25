//
//  OgrePlayerViewController.h
//  ogresdk
//
//  Created by liu enbao on 12/22/16.
//  Copyright © 2016 liu enbao. All rights reserved.
//

#import <UIKit/UIKit.h>

@class OgrePlayer;

@interface OgrePlayerViewController : UIViewController {
@protected
    OgrePlayer* mOgrePlayer;
    
    NSString* mResourcesRoot;
}

@end
