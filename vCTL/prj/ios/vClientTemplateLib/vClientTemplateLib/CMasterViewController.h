//
//  CMasterViewController.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/21/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#import <UIKit/UIKit.h>

@class CDetailViewController;

@interface CMasterViewController : UITableViewController

@property (strong, nonatomic) CDetailViewController *detailViewController;

@end
