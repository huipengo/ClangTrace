//
//  WBViewController.m
//  ClangTrace
//
//  Created by huipeng on 04/28/2020.
//  Copyright (c) 2020 huipeng. All rights reserved.
//

#import "WBViewController.h"
#import "WBClangTrace.h"

@interface WBViewController ()

@end

@implementation WBViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    [WBClangTrace wb_generateBinitOrderFile];
}


@end
