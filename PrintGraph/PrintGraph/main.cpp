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
#include <set>
#include <fstream>
#include <tuple>

using namespace std;

enum class Color {WHITE, GREY, BLACk};


class NotUniqueException
{
    string _message;
public:
    
    NotUniqueException(const string& message)
        : _message(message)
    {}
    string what() const
    {
        return _message;
    }
};

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
    virtual iNode* getParent() const = 0;
    virtual void setParent(iNode* p) = 0;
};

// Composite
class Node : public iNode
{
    int value = 0;
    iNode* parent = nullptr;
    vector<iNode* > children;
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

// Client
class graph
{
    iNode* _root = nullptr;
    std::set<int> ids;
    std::string _path = "output"; // output file path
    
public:
    
    graph(int value = 0)
    {
        _root = new Node(value);
        ids.insert(value);
    }
    
    void print(const std::string& path)
    {
        _path = path;
        ofstream f(_path);
        f.close();
        
        BFSiterative();
        DFSRecursive();
    }
    
    void print()
    {
        print(_path);
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
        
        stack<iNode*> s;
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
    
private:     ///
    
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
        ofstream f(_path, ios::app);
        for (int i = 0; i < count; ++i)
            f << "| ";
        f << value << "\n";
        f.close();
    }
};

int main()
{
    try
    {
        graph g(1);
        for (int i = 1 ; i < 10; ++i)
        {
            g.insert(i, i + 1);

        }
        
        g.print();
        g.insert(8, 7);
        //g.remove(8);
        g.print();
    }
    catch (NotUniqueException& e)
    {
        cout << e.what() << endl;
    }
    return 0;
}

