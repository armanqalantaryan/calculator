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
    std::stack<std::string> operationStack;
    double numberPop()
    {
       double n = numbersStack.top();
        numbersStack.pop();
        return n;
    }
    void reverse(std::stack<double>& stk)
    {
        std::stack<double> temp;
    
        while(! stk.empty())
        {
            temp.push(stk.top());
            stk.pop();
        }
    
        stk = temp;
    }

public:
    
    virtual bool setOperation(const std::string& op, double value) override
    {
        if(numbersStack.empty())
        {
            if (op == "=")
                return false;
            numbersStack.push(value);
            operationStack.push(op);
            return false;
        }
        
        auto top = operationStack.top();
        
        if(top == "*")
        {
            double n = numberPop();
            numbersStack.push(n*value);
            operationStack.pop();
            if (op != "=")
                operationStack.push(op);
        }
        else if(top == "/")
        {
            double n = numberPop();
            numbersStack.push(n/value);
            operationStack.pop();
            if (op != "=")
                operationStack.push(op);
        }
        else if(top =="-")
        {
            numbersStack.push(-value);
            operationStack.pop();
            operationStack.push("+");
            
            if (op != "=")
                operationStack.push(op);
        }
        else if (top == "+")
        {
            numbersStack.push(value);
            if (op != "=")
                operationStack.push(op);
        }
        else
        {
            assert(false);
        }

                
        return true;
    }
    
    virtual  void reset() override
    {
        while(!operationStack.empty())
        {
            operationStack.pop();
        }
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
            
            if (operationStack.top() == "+")
            {
                numbersStack.push(v1 + v2);
            }
            else
            {
                assert(operationStack.top() == "-");
                numbersStack.push(v2 - v1);
            }
            operationStack.pop();
        }

       return numbersStack.top();
    }
};

iCalculator* createAdvancedCalculator()
{
    return new AdvancedCalculator;
}
