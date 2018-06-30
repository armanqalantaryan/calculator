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
    std::vector< iNode* > children;
    Color _color = Color::WHITE;
    int _level = 0;
    
public:
    
    Node(int n) : value(n)
    {
        
    }
    
    ~Node()
    {
        children.clear();
    }
    
    void setColor(Color color) override
    {
        _color = color;
    }
    
    Color getColor() const override
    {
        return _color;
    }
    
    void setLevel(int level) override
    {
        _level = level;
    }
    
    int getLevel() const override
    {
        return _level;
    }
    
    iNode* add(int val) override
    {
        iNode* x = new Node(val);
        x->setParent(this);
        children.push_back(x);
        return children.back();
    }
    
    void add(iNode* n) override
    {
        n->setParent(this);
        children.push_back(n);
    }
    
    bool remove(iNode* node) override
    {
        auto it = std::find(children.begin(), children.end(), node);       /////////
        if (it == children.end())
            return false;
        
        children.erase(it);
        return true;
    }
    
    size_t getChildrenCount() const override
    {
        return children.size();
    }
    
    iNode* getChild(int index) override
    {
        assert(index >=0 && index < children.size());
        return children[index];
    }
    
    int getValue() const override
    {
        return value;
    }
    
    iNode* getParent() const override
    {
        return parent;
    }
    
    void setParent(iNode* p) override
    {
        parent = p;
    }
};

iNode* createNode(int value)
{
    return new Node(value);
}
