#include "cpu.h"
#define R8 
#define R16
#define PUSH16
#define POP16
#define PC
#define SP
tCPU::tCPU(tEnvironment &envExtern):env(envExtern)
//tCPU::tCPU()
{
    
    cout << "New Intel 8080 CPU created." << endl;
    tCPU::pc = 0x100;
    tCPU::sp =0x25;
    running=1;
    cycles=20;
static const unsigned char opcodeCycles[0x100]={
	4, 10,7, 5, 5, 5, 7, 4, 0, 10,7, 5, 5, 5, 7, 4,
	0, 10,7, 5, 5, 5, 7, 4, 0, 10,7, 5, 5, 5, 7, 4,
	0, 10,16,5, 5, 5, 7, 4, 0, 10,16,5, 5, 5, 7, 4,
	0, 10,13,5, 10,10,10,4, 0, 10,13,5, 5, 5, 7, 4,
	5, 5, 5, 5, 5, 5, 7, 5, 5, 5, 5, 5, 5, 5, 7, 5,
	5, 5, 5, 5, 5, 5, 7, 5, 5, 5, 5, 5, 5, 5, 7, 5,
	5, 5, 5, 5, 5, 5, 7, 5, 5, 5, 5, 5, 5, 5, 7, 5,
	7, 7, 7, 7, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 7, 5,
	4, 4, 4, 4, 4, 4, 7, 4, 4, 4, 4, 4, 4, 4, 7, 4,
	4, 4, 4, 4, 4, 4, 7, 4, 4, 4, 4, 4, 4, 4, 7, 4,
	4, 4, 4, 4, 4, 4, 7, 4, 4, 4, 4, 4, 4, 4, 7, 4,
	4, 4, 4, 4, 4, 4, 7, 4, 4, 4, 4, 4, 4, 4, 7, 4,
	5, 10,10,10,11,11,7, 11,5, 10,10,0, 11,17,7, 11,
	5, 10,10,10,11,11,7, 11,5, 0, 10,10,11,0, 7, 11,
	5, 10,10,18,11,11,7, 11,5, 5, 10,4, 11,0, 7, 11,
	5, 10,10,4, 11,11,7, 11,5, 5, 10,4, 11,0, 7, 11
};
}
tCPU::~tCPU()
{
    cout << "CPU destroyed." << endl;
    tCPU::pc== 0x100;
    running=0;
}
void tCPU::executeCycles(int cycles)
{
    int opcode;
    tCPU::cycles + cycles;
    while(tCPU::cycles > 0)
    {
        opcode = R8(tCPU::sp);
        tCPU::pc++;
        tCPU::cycles-=opcodeCycles[opcode];
        //(tCPU::sp);
        //cout << "Opcode:" << opcode << endl;
            
    }
}
   
