//
//  CMasterViewController.h
//  vLogging
//
//  Created by Virendra Shakya on 4/23/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#import <UIKit/UIKit.h>

@class CDetailViewController;

@interface CMasterViewController : UITableViewController

@property (strong, nonatomic) CDetailViewController *detailViewController;

@end
