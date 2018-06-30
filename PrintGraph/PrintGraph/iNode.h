//
//  Header.h
//  PrintGraph
//
//  Created by Paruir on 25.03.18.
//  Copyright © 2018 Paruir. All rights reserved.
//

#ifndef INODE_H
#define INODE_H

#include <stddef.h>

enum class Color {WHITE, GREY, BLACk};

struct iNode
{
    virtual iNode* add(int) = 0;
    virtual void add(iNode*) = 0;
    virtual bool remove(iNode*) = 0;
    virtual size_t getChildrenCount() const = 0;
    virtual iNode* getChild(int ) = 0;
    virtual int getValue() const = 0;
    virtual void setColor(Color) = 0;
    virtual Color getColor() const = 0;
    virtual void setLevel(int) = 0;
    virtual int getLevel() const = 0;
    virtual iNode* getParent() const = 0;
    virtual void setParent(iNode*) = 0;
    
    virtual ~iNode() {}
};

#endif /* INODE_H */
