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
std::string _op = "";
double _lastValue;
iCalculator* _calc;
bool _canSend = false;
bool _isNeedClear = false;


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
    if (_canSend)
    {
        _calc->setOperation(_op, _lastValue);
        //_op = "";
        _canSend = false;
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
    if (_isNeedClear)
    {
        _result.text=@"";
        _isNeedClear = false;
    }
    
    myNewString = [NSString stringWithFormat:@"%@%ld", _result.text, sender.tag-1];
    _result.text = myNewString;
}

- (IBAction)equal:(UIButton *)sender
{
    if(_op.empty())
        return;
    _op = "=";
    
    if ([_result.text  isEqual: @""]) return;
    bool res = _calc->setOperation(_op, [_result.text doubleValue]);
    if (!res)
    {
        return;
        //_calc->setOperation("=", [_result.text doubleValue]);
    }
    
    double value = _calc->getResult([_result.text doubleValue]);
    
    _result.numberOfLines                =   2;
    _result.adjustsFontSizeToFitWidth    =   true;
    _result.minimumScaleFactor           =   0.4;
    
    std::stringstream ss;
    ss << std::setprecision(8);
    ss << value;            //ss-double
    
    _result.text = [NSString stringWithFormat:@"%s", ss.str().c_str()];
}


-(void) operation: (NSString*) op
{
    _canSend = true;
    _isNeedClear = true;
    
    _op = [op UTF8String];
    _lastValue = [_result.text doubleValue];
}

- (IBAction)plus:(UIButton *)sender
{
    [self operation:@"+"];
}

- (IBAction)minus:(UIButton *)sender
{
    [self operation:@"-"];
}

- (IBAction)multiple:(UIButton *)sender
{
    [self operation:@"*"];
}

- (IBAction)divide:(UIButton *)sender
{
    [self operation:@"/"];
}

- (IBAction)restore:(UIButton *)sender
{
    _calc->reset();
    _result.text = @"0";
    _op = "";
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
   
    int x = [_result.text intValue];
    x=-x;
     _result.text = [NSString stringWithFormat:@"%d", x];
}


@end
