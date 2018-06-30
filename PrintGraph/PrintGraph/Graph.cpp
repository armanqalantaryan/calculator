//
//  Graph.cpp
//  PrintGraph
//
//  Created by Paruir on 25.03.18.
//  Copyright © 2018 Paruir. All rights reserved.
//

#include "iNode.h"
#include "iGraph.hpp"
#include "iTestGraph.h"

#include <set>
#include <fstream>
#include <algorithm>
#include <cassert>
#include <queue>
#include <stack>
#include <iostream>

iNode* createNode(int);

class BaseExeption            /////
{
    std::string _message;
public:
    
    BaseExeption(const std::string& message)
        : _message(message)
    {}
    std::string what() const
    {
        return _message;
    }
};

struct ChildNotUnique : public BaseExeption
{
    ChildNotUnique(const std::string& message)
        : BaseExeption(message)
    {}
};

struct ParentNotFound : public BaseExeption
{
    ParentNotFound(const std::string& message)
        : BaseExeption(message)
    {}
};

class GraphTest;

class Graph : public iGraph
{
    iNode* _root = nullptr;
    std::set<int> ids;
    std::string _path = "output";                     // output file path
    
    friend class GraphTest;
public:
    
    Graph(int value = 0)
    {
        _root = createNode(value);
        ids.insert(value);
    }
    
    ~Graph()
    {
        
    }
    
    void print(const std::string& path) override
    {
        _path = path;
        std::ofstream f(_path);
        f.close();
        
        BFSiterative();
        DFSRecursive();
    }
    
    void print() override
    {
        print(_path);
    }
    
    bool remove (int value) override
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
        
        int _value = node->getValue();
        ids.erase(_value);
        
        parent->remove(node);
        
        delete node;
        node = nullptr;
        return true;
    }
        
    void insert (int i, int j) override
    {
        auto node = find(i);
        if (node)
        {
            if (ids.count(j) == 0)
            {
                auto node_child = createNode(j);
                node_child->setColor(color().start);
                node->add(node_child);
                ids.insert(j);
            }
            else
            {
                throw ChildNotUnique("Child id is not unique!");
            }
        }
        else
        {
            throw ParentNotFound("Parent does not exist!");
        }
    }
    
private:
    
    iNode* find(int i)
    {
        auto colors = color();
        std::queue<iNode *> q;
        iNode* found = nullptr;

        q.push(_root);
        while(!q.empty())
        {
            auto node = q.front();
            if (node->getValue() == i)
            {
                found = node;
            }
            
            for(int i=0; i<node->getChildrenCount(); ++i)
            {
                auto c = node->getChild(i);
                c->setLevel(node->getLevel() + 1);
                q.push(c);
            }
            node->setColor(colors.end);
            q.pop();
        }

        return found;
    }
    
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
            
            for(int i=0; i<node->getChildrenCount(); ++i)
            {
                auto c = node->getChild(i);
                c->setLevel(node->getLevel() + 1);
                q.push(c);
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
    
    iNode* getRoot()
    {
        return _root;
    }
};

// GRAPH TEST

#define START_TEST \
std::cout << __func__ << " : ";

class GraphTest : public iGraphTest
{
public:
    
    void run() override
    {
        test_find_positive();
        test_find_negative();
        test_insert_positive();
        test_insert_negative1();
        test_insert_negative2();
        test_insert_negative3();
        test_remove_positive1();
        test_remove_positive2();
        test_remove_negative();
    }
    
private:
    
    void test_print()
    {
        auto graph =  create_graph();
        graph->print("arman.txt");
    }
    
    void test_remove_positive1()
    {
        START_TEST
        auto graph = create_graph();
        graph->remove(13);
        auto notFound = graph->find(13);
        isFalse(isValid(notFound));
    }

    void test_remove_positive2()
    {
        START_TEST
        auto graph = create_graph();
        
        auto n6 = graph->find(6);
        
        auto ch10 = n6->getChild(0);
        auto ch9 = n6->getChild(1);

        bool res = ch9->getParent()->getValue() == 6;
        res &= ch10->getParent()->getValue() == 6;
        
        graph->remove(6);
        
        res &= ch9->getParent()->getValue() == 2;
        res &= ch10->getParent()->getValue() == 2;

        auto notFound = graph->find(6);
        
        res &= notFound == nullptr;
        
        isTrue(res);
    }
    
    void test_remove_negative()
    {
        START_TEST
        auto graph = create_graph();
        isFalse(graph->remove(23));
    }
    
    void test_insert_positive()
    {
        START_TEST
        auto graph = create_graph();
        graph->insert(14 , 15);
        auto ret = isValid(graph->find(15));
        isTrue(ret);
    }

    void test_insert_negative1()
    {
        START_TEST
        auto graph = create_graph();
        
        try
        {
            graph->insert(15, 17);
        }
        catch (ParentNotFound e)
        {
            isTrue(true);
            return;
        }
        
        isTrue(false);
    }
    
    void test_insert_negative2()
    {
        START_TEST
        auto graph = create_graph();
        
        try
        {
            graph->insert(14, 11);
        }
        catch (ChildNotUnique e)
        {
            isTrue(true);
            return;
        }
        
        isTrue(false);
    }
    
    void test_insert_negative3()
    {
        START_TEST
        auto graph = create_graph();
        
        try
        {
            graph->insert(7, 11);
        }
        catch (ChildNotUnique e)
        {
            isTrue(true);
            return;
        }
        
        isTrue(false);
    }
    
    void test_find_positive()
    {
        START_TEST
        auto graph =  create_graph();
        
        bool ret = true;
        for(int i = 1; i<14; ++i)
        {
            ret &= isValid(graph->find(i));
        }
        isTrue(ret);
    }
    
    void test_find_negative()
    {
        START_TEST
        auto graph =  create_graph();

        bool ret = false;
        for(int i = 15; i<20; ++i)
        {
            if (isValid(graph->find(i)) == true)
                ret = true;
        }
        
        isFalse(ret);
    }
    
    std::unique_ptr<Graph> create_graph()
    {
        auto g = std::unique_ptr<Graph>(new Graph(1));
        
        g->insert(1,2);
        g->insert(1,3);
        g->insert(1,4);
        
        g->insert(2,5);
        g->insert(2,6);
        
        g->insert(6,9);
        g->insert(6,10);
        
        g->insert(3,7);
        
        g->insert(7,11);
        g->insert(7,12);
        g->insert(7,13);

        g->insert(13,14);
        
        g->insert(4,8);

        return g;
    }
    
    bool isValid(iNode* node)
    {
        return node != nullptr;
    }
    
    void isTrue(bool b)
    {
        b ? std::cout << "PASS\n" : std::cout << "FAIL\n";
    }
    
    void isFalse(bool b)
    {
        !b ? std::cout << "PASS\n" : std::cout << "FAIL\n";
    }
};

iGraphTest* createGraphTest()
{
    return new GraphTest;
}
