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
    bool _isOperationActive = false;
    double _lastValue = 0;
public:
    
    
    virtual bool setOperation(const std::string& op, double value)
    {
        _isOperationActive = true;
        _lastOperation = op;
        applyBuff(op, value);
        
        return false;
    }
    
    virtual bool isOperationActive() const
    {
        return _isOperationActive;
    }
    virtual void resetOperation()
    {
        _isOperationActive = false;
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
        _isOperationActive = false;
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
    bool _isOperationActive = false;

    std::stack<double> numbersStack;
    std::stack<std::string> operationStack;
    double numberPop()
    {
       double n = numbersStack.top();
        numbersStack.pop();
        return n;
    }
    
    std::string operationPop()
    {
        const std::string& op = operationStack.top();
        operationStack.pop();
        return op;
    }

public:
    
    virtual bool setOperation(const std::string& op, double value) override
    {
        _isOperationActive = true;

        if(numbersStack.empty())
        {
            numbersStack.push(value);
            operationStack.push(op);
            return false;
        }
        
        if(operationStack.top() == "*")
        {
            double n = numberPop();
            numbersStack.push(n*value);
            operationStack.pop();
            if (op != "=")
                operationStack.push(op);
        }
        else if(operationStack.top()== "/")
        {
            double n = numberPop();
            numbersStack.push(n/value);
            operationStack.pop();
            if (op != "=")
                operationStack.push(op);
        }
        else
        {
            numbersStack.push(value);
            if (op != "=")
                operationStack.push(op);
        }
        
        if(operationStack.size() == 1)
            return false;
        
        return true;
    }
    
   virtual bool isOperationActive() const override
    {
        return _isOperationActive;
    }
    
    virtual  void reset() override
    {
        _isOperationActive = false;

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
            
            if (operationPop() == "+")
            {
                numbersStack.push(v1 + v2);
            }
            else
            {
                numbersStack.push(v2 - v1);
            }
        }

       return numbersStack.top();
    }
    
    virtual void resetOperation() override
    {
        
    }
};

iCalculator* createAdvancedCalculator()
{
    return new AdvancedCalculator;
}
