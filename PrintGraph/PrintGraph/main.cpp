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
#include <queue>
#include <stack>

using namespace std;

enum class Color {WHITE, GREY, BLACk};

// Component
struct iNode
{
    virtual iNode* add(int value) = 0;
    virtual size_t getChildrenCount() const = 0;
    virtual iNode* getChild(int index) = 0;
    virtual int getValue() const = 0;
    virtual void setColor(Color color) = 0;
    virtual Color getColor() const = 0;
    virtual void setLevel(int) = 0;
    virtual int getLevel() const = 0;
    
};

// Composite
class Node : public iNode
{
    int value = 0;
    vector<iNode* > children;
    Color _color = Color::WHITE;
    int _level = 0;
    
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
    
    graph(int value = 0)
    {
        _root = new Node(value);
    }
    
    iNode* root()
    {
        return _root;
    }
    
    void print()
    {
        BFSiterative();
        DFSIterative();
    }
    
private:
    
    void DFS()
    {
        printLevel(_root->getValue(), _root->getLevel());
        DFSPrivate(_root);
    }
    
    void DFSPrivate(iNode* node)
    {
        if (node->getChildrenCount() == 0)
            return;
        
        for (int i = 0; i < node->getChildrenCount(); ++i)
        {
            auto c = node->getChild(i);
            
            printLevel(c->getValue(), c->getLevel());
            DFSPrivate(c);
        }
    }
    
    void BFS()
    {
        BFSPrivate(_root);
    }
    
    void BFSPrivate(iNode* n)
    {
        for(int i = 0; i < n->getChildrenCount(); ++i)
        {
            auto child = n->getChild(i);
            child->setLevel(n->getLevel() + 1);
            BFSPrivate(child);
        }
    }
    
    void BFSiterative()
    {
        auto colors = color();
        
        queue<iNode *> q;
        
        q.push(_root);
        while(!q.empty())
        {
            auto node = q.front();
            
            if(node->getColor() == colors.start)
            {
                for(int i=0; i<node->getChildrenCount(); ++i)
                {
                    auto c = node->getChild(i);
                    c->setLevel(node->getLevel() + 1);
                    q.push(c);
                }
            }
            node->setColor(colors.end);
            q.pop();
        }
    }
    
    void DFSIterative()
    {
        auto colors = color();
        
        stack<iNode*> s;
        s.push(_root);
        
        while(!s.empty())
        {
            auto node = s.top();
            if(node->getColor() == Color::GREY)
            {
                node->setColor(colors.end);
                s.pop();
            }
            if(node->getColor() == colors.start)
            {
                for(int i=0;i<node->getChildrenCount();++i)
                {
                    auto c = node->getChild(i);
                    s.push(c);
                }
                node->setColor(Color::GREY);
                printLevel(node->getValue(), node->getLevel());
            }
        }
    }
    
    
    struct Colors
    {
        Color start,end;
    };
    
    Colors color()
    {
        Colors colors;
        Color c = _root->getColor();
        if (c == Color::WHITE)
        {
            colors.start = Color::WHITE;
            colors.end = Color::BLACk;
        }
        else
        {
            colors.start = Color::BLACk;
            colors.end = Color::WHITE;
        }
        
        return colors;
    }
    
    void printLevel(int value, int count)
    {
        for (int i = 0; i < count; ++i)
            cout << "_";
        cout << value << endl;
    }
};

int main()
{
    graph g;
    
    iNode* p = g.root();
    auto p4 = p->add(4);
    p4->add(12);
    p4->add(13)->add(14);
    p->add(5);
    p->add(6);
    iNode* p2 = p->add(7);
    p2->add(8);
    p2->add(9);
    auto p3 = p2->add(10);
    p3->add(11);
    
    g.print();
    
    return 0;
}

