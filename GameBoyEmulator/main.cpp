

#include "CPU.h"


int main(int argc, char* args[])
{

    //CPU* processor = new CPU("Pokemon - Red Version.gb");
    CPU* processor = new CPU("tetris.gb");
    //CPU* processor = new CPU("Test7.gb");

    while (processor->IsRunning())
    {
        processor->Loop();
    }
    
    delete processor;

	//system("PAUSE");

    return 0;
}