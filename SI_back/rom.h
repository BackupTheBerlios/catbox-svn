// 
// File:   rom.h
// Author: pixman
//
// Created on 27. Januar 2007, 02:49
//

#ifndef _rom_H
#define	_rom_H
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class tROM
{
    public:
        unsigned char *memory;
        char *loadTemp;
        char *filenames[];
        bool loadROM();
        tROM();
        ~tROM();
         
    private:
};


#endif	/* _rom_H */

