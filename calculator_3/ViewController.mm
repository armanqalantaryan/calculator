//
//  ViewController.m
//  calculator_3
//
//  Created by Paruir on 20.08.17.
//  Copyright © 2017 Paruir. All rights reserved.
//

#import "ViewController.h"
#include "calculator.hpp"
#include <string>
#include <sstream>
#include <iomanip>

iCalculator* createAdvancedCalculator();

@interface ViewController ()
@end


@implementation ViewController
bool equalIsActive = false;
iCalculator* _calc;


- (void)viewDidLoad {
    [super viewDidLoad];
    
    _calc = createAdvancedCalculator();
    _result.text = @"0";
    // Do any additional setup after loading the view, typically from a nib.
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


- (IBAction)numbers:(UIButton *)sender
{
    if(equalIsActive == true)
    {
        _result.text = @"";
        equalIsActive = false;
    }
    
    if([_result.text  isEqual: @"0"])
    {
        if(sender.tag-1 == 0)
        {
            return;
        }
        else
        {
            _result.text = @"";
        }
    }
    
    NSString* myNewString;
    if (!_calc->isOperationActive())
    {
        
         myNewString = [NSString stringWithFormat:@"%@%d", _result.text, sender.tag-1];
         _result.text = myNewString;
    }
    else
    {
        _result.text=@"";
        myNewString = [NSString stringWithFormat:@"%@%d", _result.text, sender.tag-1];
         _result.text = myNewString;
        _calc->resetOperation();
    }
}

- (IBAction)equal:(UIButton *)sender
{
    equalIsActive = true;
    
    if ([_result.text  isEqual: @""]) return;
    _calc->setOperation("=", [_result.text doubleValue]);
    double value = _calc->getResult([_result.text doubleValue]);
    
    _result.numberOfLines                =   2;
    _result.adjustsFontSizeToFitWidth    =   true;
    _result.minimumScaleFactor           =   0.4;
    
    std::stringstream ss;
    ss << std::setprecision(8);
    ss << value;            //ss-double
    
    _result.text = [NSString stringWithFormat:@"%s", ss.str().c_str()];
    
}

- (IBAction)plus:(UIButton *)sender
{
    if ([_result.text  isEqual: @""]) return;   // chpiti @"0" lini

    double currentValue = [_result.text doubleValue];
    
    _calc->setOperation("+", currentValue);
    
}

- (IBAction)minus:(UIButton *)sender
{
    if ([_result.text  isEqual: @""]) return;
    
    double currentValue = [_result.text doubleValue];
    
    _calc->setOperation("-", currentValue);
}

- (IBAction)multiple:(UIButton *)sender
{
    if ([_result.text  isEqual: @""]) return;

    double currentValue = [_result.text doubleValue];
    
    _calc->setOperation("*", currentValue);
}

- (IBAction)divide:(UIButton *)sender
{
    if ([_result.text  isEqual: @""]) return;

    double currentValue = [_result.text doubleValue];
    
    _calc->setOperation("/", currentValue);
}

- (IBAction)restore:(UIButton *)sender
{
    _calc->reset();
    _result.text = @"0";
}

- (IBAction)dot:(UIButton *)sender
{
    if ([_result.text rangeOfString:@"."].location != NSNotFound)
    {
        return;
    }
    _result.text = [NSString stringWithFormat:@"%@%@", _result.text, @"."];
}


@end
