//
//  Graph.hpp
//  PrintGraph
//
//  Created by Paruir on 25.03.18.
//  Copyright © 2018 Paruir. All rights reserved.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <string>

struct iGraph
{
private:
    virtual void print(const std::string&) = 0;
    virtual void print() = 0;
    virtual bool remove (int value) = 0;
    virtual void insert (int i, int j) = 0;
};


#endif /* Graph_hpp */
