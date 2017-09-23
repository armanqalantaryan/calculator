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
bool _isoperation = false;
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
    if (!_isoperation)
    {
        
         myNewString = [NSString stringWithFormat:@"%@%d", _result.text, sender.tag-1];
         _result.text = myNewString;
    }
    else
    {
        _result.text=@"";
        myNewString = [NSString stringWithFormat:@"%@%d", _result.text, sender.tag-1];
         _result.text = myNewString;
    }
    _isoperation = false;
}

- (IBAction)equal:(UIButton *)sender
{
    if(_isoperation == true) return;
    _isoperation = true;
    
    
    
    
    if ([_result.text  isEqual: @""]) return;
    bool res = _calc->setOperation("=", [_result.text doubleValue]);
    if (!res)
        return;
    
    double value = _calc->getResult([_result.text doubleValue]);
    
    _result.numberOfLines                =   2;
    _result.adjustsFontSizeToFitWidth    =   true;
    _result.minimumScaleFactor           =   0.4;
    
    std::stringstream ss;
    ss << std::setprecision(8);
    ss << value;            //ss-double
    
    _result.text = [NSString stringWithFormat:@"%s", ss.str().c_str()];

}

- (void)setOperation:(NSString*) op;
{
    if(_isoperation == true) return;
    if ([_result.text  isEqual: @""]) return;   // chpiti @"0" lini
    
    double currentValue = [_result.text doubleValue];
    
    _calc->setOperation([op UTF8String], currentValue);
    
    _isoperation = true;
}

- (IBAction)plus:(UIButton *)sender
{
    [self setOperation:@"+"];
}

- (IBAction)minus:(UIButton *)sender
{
    [self setOperation:@"-"];
}

- (IBAction)multiple:(UIButton *)sender
{
    [self setOperation:@"*"];
}

- (IBAction)divide:(UIButton *)sender
{
    [self setOperation:@"/"];
}

- (IBAction)restore:(UIButton *)sender
{
    _calc->reset();
    _result.text = @"0";
    _isoperation = false;
}

- (IBAction)dot:(UIButton *)sender
{
    if ([_result.text rangeOfString:@"."].location != NSNotFound)
    {
        return;
    }
    _result.text = [NSString stringWithFormat:@"%@%@", _result.text, @"."];
}

- (IBAction)plusminus:(UIButton *)sender
{
    _result.text
}


@end
