#include "rom.h"

tROM::tROM(tEnvironment &envExtern):env(envExtern)
{
    cout << "ROM-object created." << endl;
}
tROM::~tROM()
{
    cout << "ROM-Object deleted." << endl;
}
bool tROM::loadROM()
{
    /* memory has to be set on variable mem[0x4000] in main.cpp ! */
    ifstream romFile("invaders.h",ios::binary|ios::in);
    int byteCount = 0x00;
    if (!romFile)
    {
            cout << "ROM file opened." <<endl;
    }
    else
    {
            cout << "Error while opening ROM file." << endl;
            exit(1);
    }
    
    while (!romFile.eof())
    {
        romFile.read((char*)memory,0x800);
    }
    cout << "Finished.";
    return false;
}
/*int LoadAt (const char *filename)
{
    ifstream omg("invaders.e",ios::binary);
    int length,cnt=0;
    omg.seekg(0,ios::end);
    length = omg.tellg();
    omg.seekg(0,ios::beg);
    omg.read(*mem[0x1800],length);

    omg.close();
    return(0);
}*/