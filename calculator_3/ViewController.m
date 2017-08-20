//
//  ViewController.m
//  calculator_3
//
//  Created by Paruir on 20.08.17.
//  Copyright © 2017 Paruir. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


- (IBAction)numbers:(UIButton *)sender
{
    NSString* myNewString = [NSString stringWithFormat:@"%@%ld", _result.text, sender.tag-1];
    
    _result.text = myNewString;
}

- (IBAction)equal:(UIButton *)sender {
}

- (IBAction)plus:(UIButton *)sender {
}

- (IBAction)minus:(UIButton *)sender {
}

- (IBAction)multiple:(UIButton *)sender {
}

- (IBAction)divide:(UIButton *)sender {
}

- (IBAction)restore:(UIButton *)sender {
}



@end
