//
//  calculator.cpp
//  calculator_3
//
//  Created by Paruir on 27.08.17.
//  Copyright © 2017 Paruir. All rights reserved.
//

#include "calculator.hpp"
#include <limits>

class SimpleCalculator : public iCalculator
{
    double _buff = std::numeric_limits<double>::lowest();
    std::string _lastOperation = "";
    bool _isOperationActive = false;
    
public:
    
    virtual void setOperation(const std::string& op, double value)
    {
        _isOperationActive = true;
        _lastOperation = op;
        applyBuff(op, value);
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
        applyBuff(_lastOperation, lastValue);
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
    return new SimpleCalculator{};
}
