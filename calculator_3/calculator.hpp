//
//  calculator.hpp
//  calculator_3
//
//  Created by Paruir on 27.08.17.
//  Copyright © 2017 Paruir. All rights reserved.
//

#ifndef calculator_hpp
#define calculator_hpp

#include <string>

struct iCalculator
{
    virtual void setOperation(const std::string& op, double value) = 0;
    virtual bool isOperationActive() const = 0;
    virtual void resetOperation() = 0;
    virtual double getResult(double lastvalue) = 0;
    virtual void reset() = 0;
};

#endif /* calculator_hpp */
