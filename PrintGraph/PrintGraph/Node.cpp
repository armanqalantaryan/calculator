//
//  Node.cpp
//  PrintGraph
//
//  Created by Paruir on 25.03.18.
//  Copyright © 2018 Paruir. All rights reserved.
//

#include "iNode.h"
#include <vector>
#include <cassert>



class Node : public iNode
{
    int value = 0;
    iNode* parent = nullptr;
    std::vector<iNode* > children;
    Color _color = Color::WHITE;
    int _level = 0;
    int _searchValue = 0;
    
public:
    
    Node(int n) : value(n)
    {
        
    }
    
    virtual void setColor(Color color)
    {
        _color = color;
    }
    
    virtual Color getColor() const
    {
        return _color;
    }
    
    virtual void setLevel(int level)
    {
        _level = level;
    }
    
    virtual int getLevel() const
    {
        return _level;
    }
    
    virtual iNode* add(int val)
    {   iNode* x = new Node(val);
        x->setParent(this);
        children.push_back(x);
        return children.back();
    }
    virtual void add(iNode* n)
    {
        n->setParent(this);
        children.push_back(n);
    }
    size_t getChildrenCount() const
    {
        return children.size();
    }
    
    iNode* getChild(int index)
    {
        assert(index >=0 && index < children.size());
        return children[index];
    }
    
    int getValue() const
    {
        return value;
    }
    
    virtual iNode* getParent() const
    {
        return parent;
    }
    
    virtual void setParent(iNode* p)
    {
        parent = p;
    }
};
iNode* createNode(int value)
{
    return new Node(value);
}
