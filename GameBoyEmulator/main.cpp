

#include "CPU.h"


int main(int argc, char* args[])
{

    //CPU* processor = new CPU("Pokemon - Red Version.gb");
    CPU* processor = new CPU;

    // MBC1
    //processor->SetRom("Tamagotchi.gb"); // Lots of scrolling backgrounds, fails.
    //processor->SetRom("Garfield Labyrinth.gb"); // Halts and doesnt recover
    //processor->SetRom("Duck Tales.gb");
	//processor->SetRom("Super Mario Land.gb");


	// ROM only
	processor->SetRom("tetris.gb");
	//processor->SetRom("Dr. Mario.gb");
	
    //processor->SetRom("Test//01.gb"); // 01-special.gb
    //processor->SetRom("Test//02.gb"); // 02-interupts.gb
    //processor->SetRom("Test//03.gb"); // 03-op sp,hl.gb
    //processor->SetRom("Test//04.gb"); // 04-op r,imm.gb
    //processor->SetRom("Test//05.gb"); // 05-op rp.gb
    //processor->SetRom("Test//06.gb"); // 06-ld r,r.gb
	//processor->SetRom("Test//07.gb"); // 07-jr,jp,call,ret,rst.gb
    //processor->SetRom("Test//08.gb"); // 08-misc instrs.gb
	//processor->SetRom("Test//09.gb"); // 09-op r,r.gb
    //processor->SetRom("Test//10.gb"); // 10-bit ops.gb
    //processor->SetRom("Test//11.gb"); // 11-op a,(hl).gb

	processor->SetBios("bios.bin");
    
    processor->Start();

    while (processor->IsRunning())
    {
        processor->Loop();
    }
    
    delete processor;

	//system("PAUSE");

    return 0;
}