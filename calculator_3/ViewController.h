//
//  ViewController.h
//  calculator_3
//
//  Created by Paruir on 20.08.17.
//  Copyright © 2017 Paruir. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController

- (IBAction)numbers:(UIButton *)sender;
- (IBAction)equal:(UIButton *)sender;
- (IBAction)plus:(UIButton *)sender;
- (IBAction)minus:(UIButton *)sender;
- (IBAction)multiple:(UIButton *)sender;
- (IBAction)divide:(UIButton *)sender;
- (IBAction)restore:(UIButton *)sender;

@property (strong, nonatomic) IBOutlet UILabel *result;

@end

