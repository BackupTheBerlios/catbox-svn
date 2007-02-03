// 
// File:   memory.h
// Author: pixman
//
// Created on 23. Januar 2007, 21:22
//

#ifndef _memory_H
#define	_memory_H
#include <iostream>
#include <string>
using namespace std;
class tMemory
{
    public:
        unsigned char *screen;
        unsigned char *memory;
        tMemory();
        ~tMemory();
    private:
        
};


#endif	/* _memory_H */

