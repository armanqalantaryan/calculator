//
//  Graph.cpp
//  PrintGraph
//
//  Created by Paruir on 25.03.18.
//  Copyright © 2018 Paruir. All rights reserved.
//

#include "iNode.h"
#include "iGraph.hpp"
#include "iGraphTest.h"

#include <set>
#include <fstream>
#include <algorithm>
#include <cassert>
#include <queue>
#include <stack>

iNode* createNode(int);

class NotUniqueException
{
    std::string _message;
public:
    
    NotUniqueException(const std::string& message)
    : _message(message)
    {}
    std::string what() const
    {
        return _message;
    }
};


class Graph : public iGraph
{
    iNode* _root = nullptr;
    std::set<int> ids;
    std::string _path = "output"; // output file path
    
public:
    
    Graph(int value = 0)
    {
        _root = createNode(value);
        ids.insert(value);
    }
    
    void print(const std::string& path)
    {
        _path = path;
        std::ofstream f(_path);
        f.close();
        
        BFSRecursive();
        DFSRecursive();
    }
    
    void print()
    {
        print(_path);
    }
    
    bool remove (int value)
    {
        auto node = find(value);
        
        if(!node)
            return false;
        
        auto parent = node->getParent();
        for(int i = 0;i<node->getChildrenCount();i++)
        {
            auto child = node->getChild(i);
            parent->add(child);
        }
        
        delete node;
        return true;
    }
    
    void insert (int i, int j)
    {
        auto node = find(i);
        if (node)
        {
            if (ids.count(j) == 0)
            {
                node->add(j);
                ids.insert(j);
            }
            else
            {
                throw NotUniqueException("Child id is not unique!");
            }
        }
        else
        {
            throw NotUniqueException("Parent does not exist!");
        }
    }
    
private:
    
    iNode* find(int i)
    {
        auto colors = color();
        
        std::stack<iNode*> s;
        s.push(_root);
        
        while(!s.empty())
        {
            auto node = s.top();
            if (node->getValue() == i)
            {
                while(!s.empty())
                {
                    auto n = s.top();
                    n->setColor(colors.end);
                    s.pop();
                }
                return node;
            }
            
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
            }
        }
        
        return nullptr;
    }
    
protected:     ///
    
    void DFSRecursive()
    {
        printLevel(_root->getValue(), _root->getLevel());
        DFSRecursivePrivate(_root);
    }
    
    void DFSRecursivePrivate(iNode* node)
    {
        for (int i = 0; i < node->getChildrenCount(); ++i)
        {
            auto c = node->getChild(i);
            printLevel(c->getValue(), c->getLevel());
            DFSRecursivePrivate(c);
        }
    }
    
    void BFSRecursive()
    {
        BFSRecursivePrivate(_root);
    }
    
    void BFSRecursivePrivate(iNode* n)
    {
        
        for(int i = 0; i < n->getChildrenCount(); ++i)
        {
            auto child = n->getChild(i);
            child->setLevel(n->getLevel() + 1);
        }
        
        for(int i = 0; i < n->getChildrenCount(); ++i)
        {
            auto child = n->getChild(i);
            BFSRecursivePrivate(child);
        }
        
    }
    
    void BFSiterative()
    {
        auto colors = color();
        
        std::queue<iNode *> q;
        
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
        
        std::stack<iNode*> s;
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
        std::ofstream f(_path, std::ios::app);
        for (int i = 0; i < count; ++i)
            f << "| ";
        f << value << "\n";
        f.close();
    }
};

class GraphTest : public iGraphTest, public Graph
{
public:
    
    void run() override
    {
        DFSIterativeTest();
    }
    
    GraphTest(int n = 0) : Graph(n)
    {
        
    }
    
    void DFSIterativeTest()
    {
        DFSIterative();
    }
};

iGraphTest* createGraphTest()
{
    return new GraphTest;
}
