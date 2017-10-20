

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
    {   // MBC1
	    //processor->SetRom("Mercenary Force.gb");      // needs 16x8 pixel sprites
		//processor->SetRom("Tamagotchi.gb");           // Need to implement window support.
        //processor->SetRom("Garfield Labyrinth.gb");   // Seems relatively playable apart from scroll juttering and no window support
		//processor->SetRom("Duck Tales.gb");           // maybe needs other LCD interrupt conditions to be implemented, ma
	    //processor->SetRom("Super Mario Land.gb");     // Playable apart from scroll juttering
        //processor->SetRom("Legend of Zelda, The - Link's Awakening.gb");
	    //processor->SetRom("Game Boy Gallery.gb");

        //MBC3
	    //CPU* processor = new CPU("Pokemon - Red Version.gb");

	    // ROM only
	    //processor->SetRom("tetris.gb");
	    processor->SetRom("Dr. Mario.gb"); // This game uses Timer, sprite issues could be down to that

		
	    //processor->SetRom("Test//all.gb");  // All instructions requires MBC1 Support
        //processor->SetRom("Test//01.gb"); // 01-special.gb
        //processor->SetRom("Test//02.gb"); // 02-interrupts.gb
        //processor->SetRom("Test//03.gb"); // 03-op sp,hl.gb
        //processor->SetRom("Test//04.gb"); // 04-op r,imm.gb
        //processor->SetRom("Test//05.gb"); // 05-op rp.gb
        //processor->SetRom("Test//06.gb"); // 06-ld r,r.gb
	    //processor->SetRom("Test//07.gb"); // 07-jr,jp,call,ret,rst.gb
        //processor->SetRom("Test//08.gb"); // 08-misc instrs.gb
	    //processor->SetRom("Test//09.gb"); // 09-op r,r.gb
        //processor->SetRom("Test//10.gb"); // 10-bit ops.gb
        //processor->SetRom("Test//11.gb"); // 11-op a,(hl).gb


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