

#include "CPU.h"


int main(int argc, char* args[])
{
    
    CPU* processor = new CPU;

    //processor->SetBios("bios.bin");


    //Overwrites whatever choice has been compiled
    if (argc == 2)
    {
        std::cout << args[1] << std::endl;
        processor->SetRom(args[1]);
    }
    else
    { 
		processor->SetRom("Aaron.gb");  
        processor->SetRom("Blaargs_instruction_test.gb");  // All instructions requires MBC1 Support
	    processor->SetRom("Screen_test.gb");  
      
    }
	

    processor->Start();

    while (processor->IsRunning())
    {
        processor->Loop();
    }
    
    delete processor;

	//system("PAUSE");

    return 0;
}