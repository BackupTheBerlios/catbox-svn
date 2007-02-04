#include "environment.h"
#define A cpu->reg.a
#define F cpu->reg.psw;
#define PSW F
#define B cpu->reg.b;
#define C cpu->reg.c;
#define D cpu->reg.d;
#define H cpu->reg.H;
#define L cpu->reg.L;
#define AF cpu->af;
#define BC cpu->bc;
#define DE cpu->de;
#define HL cpu->hl;
#define SP cpu->sp;
#define PC cpu->pc;
#define R8(adr) cpu->memory[((adr)>0x1fff)?(adr)&0x1fff | 0x2000:adr]
#define R16(adr) (R8((adr) + 1)<<8 | (R8(adr)))
#define W8(adr,val) if (adr>0x1fff) cpu->memory[((adr)&0x1fff) | 0x2000]=v
#define PUSH16(val) SP-=2; W8(SP,(val)&0xff) | W8(SP+1,(val)>>8 & 0xff)
#define POP16() R16(SP);SP+=2
#define JUMP() PC=R16(PC);
#define CALL() PUSH16(PC+2); JUMP(); // Rücksprung-Adresse auf den Stack
tEnvironment::tEnvironment()
{
    cout << "Environment created."<<endl;
    cpu = new tCPU(*this);
    memory = new tMemory(*this);
    rom = new tROM(*this);
    memory->memory = new char[0x4000];
    cpu->pc = 0xffdd;
    /*rom->memory = &(*mem); // Pointing the memory of the classes 
    cpu->memory = &(*mem);
    cpu->memory[20] = 0x41;
    printf("%c",mem[20]);
    cpu->memory[0] = 0x41;*/
}
tEnvironment::~tEnvironment()
{
    cout << "Environment destroyed." << endl;
}
char tEnvironment::readByte(unsigned int addr)
{
    return memory->memory[addr];
}

char tEnvironment::writeByte(unsigned int addr, unsigned int value)
{
    if(addr >= 2000 && addr < 4000)
        {
            memory->memory[addr] = value;
        }
            
    return value;
}
unsigned int tEnvironment::readWord(unsigned int addr)
{
    return readByte(addr) | (readByte(addr+1)<<8);
}
unsigned int tEnvironment::writeWord(unsigned int addr, unsigned int value)
{
    writeByte(addr, value) & 0xFF;
    writeByte(addr+1,(value>>8)&0xFF);
}
