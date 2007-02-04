// 
// File:   cpu.h
// Author: pixman
//
// Created on 22. Januar 2007, 19:58
//

#ifndef _cpu_H
#define	_cpu_H
#include <iostream>
#include <string>
#include "environment.h"

using namespace std;
class tEnvironment;
class tCPU
{   
    public:
    tCPU();
    tCPU(tEnvironment &envExtern);
    ~tCPU();
    enum Flags 
    {
        Carry     = 0x01,
        Parity    = 0x04, Overflow = Parity,
        HalfCarry = 0x10, AuxCarry = HalfCarry,
        Zero      = 0x40,
        Sign      = 0x80
    };
    union
    {
        unsigned short pc;
        struct
        {
            unsigned char pchi,pclo;
        };
    
    };
    
    
    union
    {
        unsigned short sp;
        struct
        {
            unsigned char sphi,splo;  
        };
    };
     union
    {   
            unsigned short af,bc,de,hl;    
        struct
      {
            unsigned char flags,a,c,b,e,d,l,h;  
        };
          
    }reg;
    
    int cycles;
    int running;
    unsigned short result;
    unsigned char irq;
    unsigned char irqpending;
    unsigned char aux;
    unsigned char *memory;
    unsigned char opcodeCycles[0x100];
    void executeCycles(int cycles);
    tEnvironment &env;
    typedef void (*OpcodeHandler)();
    typedef struct 
    {
        OpcodeHandler opcodeMethod;
        unsigned int cycles;
    }OpcodeInformation;
    OpcodeInformation OpcodeList[256];
    
    private:
};


#endif	/* _cpu_H */

