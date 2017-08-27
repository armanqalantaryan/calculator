//
//  ViewController.m
//  calculator_3
//
//  Created by Paruir on 20.08.17.
//  Copyright © 2017 Paruir. All rights reserved.
//

#import "ViewController.h"
#include <string>


@interface ViewController ()

@end
int numberonscreen=0;
std::string ns_to_std(NSString *foo)
{
    
    std::string numberonthescreen = std::string([foo UTF8String]);
    return numberonthescreen;
}

int std_to_int(std::string& numberonscreen_)
{
    
    
     numberonscreen = atoi(numberonscreen_.c_str());
    return numberonscreen;
}
@implementation ViewController


bool isOperationPress = false;
double plusBuffer = 0;


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
    NSString* myNewString;
    if (!isOperationPress)
    {
         myNewString = [NSString stringWithFormat:@"%@%ld", _result.text, sender.tag-1];
         _result.text = myNewString;
    }

    else
    {
     // _result.text=@"";
      myNewString = [NSString stringWithFormat:@"%@%ld", _result.text, sender.tag-1];
         _result.text = myNewString;
        
    }
   // _result.text = myNewString;      //???
}

- (IBAction)equal:(UIButton *)sender
{
    
}

- (IBAction)plus:(UIButton *)sender
{
    isOperationPress = true;
}

- (IBAction)minus:(UIButton *)sender
{
    
}

- (IBAction)multiple:(UIButton *)sender
{
    
}

- (IBAction)divide:(UIButton *)sender
{
    
}

- (IBAction)restore:(UIButton *)sender
{
    
}



@end
