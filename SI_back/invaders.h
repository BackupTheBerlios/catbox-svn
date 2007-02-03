// 
// File:   invaders.h
// Author: pixman
//
// Created on 3. Februar 2007, 17:04
//

#ifndef _invaders_H
#define	_invaders_H
#include <iostream>
#include "environment.h"
#include "cpu.h"

class tInvaders : tEnvironment
{
    public:
        tInvaders();
        ~tInvaders();
        tCPU *cpu;
    private:
    
};

#endif	/* _invaders_H */

