//
//  calculator.cpp
//  calculator_3
//
//  Created by Paruir on 27.08.17.
//  Copyright © 2017 Paruir. All rights reserved.
//

#include "calculator.hpp"
#include <limits>
#include <stack>
#include <string>
#include <iostream>
#include <cassert>

class SimpleCalculator : public iCalculator
{
    double _buff = std::numeric_limits<double>::lowest();
    std::string _lastOperation = "";
   
    double _lastValue = 0;
public:
    
    
    virtual bool setOperation(const std::string& op, double value)
    {
        _lastOperation = op;
        applyBuff(op, value);
        
        return false;
    }
    
    virtual void resetOperation()
    {
        
    }
    virtual double getResult(double lastValue)
    {
        applyBuff(_lastOperation, _lastValue);
        _lastValue=lastValue;
        
        
        return _buff;
    }
    virtual void reset()
    {
        _buff = std::numeric_limits<double>::lowest();
        _lastOperation = "";
        
    }

private:
    
    void applyBuff(const std::string op, double value)
    {
        if (_buff == std::numeric_limits<double>::lowest())
        {
            _buff = value;
        }
        else
        {
            if(op == "+")
            {
                _buff += value;
            }
            if(op == "-")
            {
                _buff -= value;
            }
            if(op == "*")
            {
                _buff *= value;
            }
            if(op == "/")
            {
                _buff /= value;
            }
        }
    }
};

iCalculator* createSimpleCalculator()
{
    return new SimpleCalculator;
}



class AdvancedCalculator : public iCalculator
{
    std::stack<double> numbersStack;
    std::string _op = "";
    
    double numberPop()
    {
       double n = numbersStack.top();
        numbersStack.pop();
        return n;
    }
    
public:
    
    virtual bool setOperation(const std::string& op, double value) override
    {
        if(numbersStack.empty())
        {
            numbersStack.push(value);
            _op = op;
            return false;
        }
        
        if(_op == "*")
        {
            double n = numberPop();
            numbersStack.push(n*value);
        }
        else if(_op == "/")
        {
            double n = numberPop();
            numbersStack.push(n/value);
        }
        else if(_op =="-")
        {
            numbersStack.push(-value);
        }
        else if (_op == "+")
        {
            numbersStack.push(value);
        }
        else
        {
            assert(false);
        }
        if(op != "=")
            _op = op;
        
        return true;
    }
    
    virtual  void reset() override
    {
        _op = "";
        
        while(!numbersStack.empty())
        {
            numbersStack.pop();
        }
    }
    
    virtual double getResult(double x) override
    {
        
        while(numbersStack.size() != 1)
        {
            const double v1 = numberPop();
            const double v2 = numberPop();
            
            numbersStack.push(v1 + v2);
        }
        
        const auto value = numbersStack.top();
        numbersStack.pop();
        return value;
    }
};

iCalculator* createAdvancedCalculator()
{
    return new AdvancedCalculator;
}
