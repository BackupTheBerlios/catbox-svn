// 
// File:   environment.h
// Author: pixman
//
// Created on 1. Februar 2007, 22:54
//

#ifndef _environment_H
#define	_environment_H
#include <iostream>
#include "cpu.h"
#include "memory.h"
#include "rom.h"
using namespace std;
class tCPU;
class tROM;
class tMemory;
class tEnvironment
{
    public:
        tEnvironment();
        ~tEnvironment();
         tCPU *cpu;
         tMemory *memory;
         tROM *rom;
    private:
        
};


#endif	/* _environment_H */

