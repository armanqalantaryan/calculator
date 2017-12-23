//
//  main.cpp
//  find_same
//
//  Created by Paruir on 12.02.17.
//  Copyright © 2017 Paruir. All rights reserved.
//

#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

// Component
struct iNode
{
    virtual iNode* add(int value) = 0;
    virtual size_t getChildrenCount() const = 0;
    virtual iNode* getChild(int index) = 0;
    virtual int getValue() const = 0;
};

// Composite
class Node : public iNode
{
    int value = 0;
    vector<iNode* > children;
    
public:
    
    Node(int n) : value(n)
    {
        
    }
    
    virtual iNode* add(int val)
    {
        children.push_back(new Node(val));
        return children.back();
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
};

// Client
class graph
{
    iNode* _root = nullptr;
public:
    
    graph(int value)
    {
        _root = new Node(value);
    }
    
    iNode* root()
    {
        return _root;
    }
    
    void BFS()
    {
        cout << _root->getValue() << endl;
        BFSPrivate(_root, 1);
    }

    void printLevel(int value, int count)
    {
        for (int i = 0; i < count; ++i)
            cout << "__";
        cout << value << endl;
    }
    
    void BFSPrivate(iNode* n, int spaceCount)
    {
        for(int i = 0;i<n->getChildrenCount();++i )
        {
            auto child = n->getChild(i);
            printLevel(child->getValue(), spaceCount);
        }

        spaceCount++;

        for(int i = 0;i<n->getChildrenCount();++i )
        {
            auto child = n->getChild(i);
            BFSPrivate(child, spaceCount);
        }
    }
};

int main()
{
    graph g(3);
    iNode* p = g.root();
    p->add(4);
    p->add(5);
    p->add(6);
    iNode* p2 = p->add(7);
    p2->add(8);
    p2->add(9);
    auto p3 = p2->add(10);
    p3->add(11);
    g.BFS();

    return 0;
}
