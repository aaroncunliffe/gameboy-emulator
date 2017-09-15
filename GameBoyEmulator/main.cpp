

#include "CPU.h"


int main(int argc, char* args[])
{

    //CPU* processor = new CPU("Pokemon - Red Version.gb");
    CPU* processor = new CPU;

    // MBC1
    //CPU* processor = new CPU("Tamagotchi.gb"); // Lots of scrolling backgrounds, fails.
    //CPU* processor = new CPU("Garfield Labyrinth.gb"); // Halts and doesnt recover
    //CPU* processor = new CPU("Duck Tales.gb");

    //CPU* processor = new CPU("Test//01.gb"); // 01-special.gb
    //CPU* processor = new CPU("Test//02.gb"); // 02-interupts.gb
    //CPU* processor = new CPU("Test//03.gb"); // 03-op sp,hl.gb
    //CPU* processor = new CPU("Test//04.gb"); // 04-op r,imm.gb
    //CPU* processor = new CPU("Test//05.gb"); // 05-op rp.gb
    //CPU* processor = new CPU("Test//06.gb"); // 06-ld r,r.gb
    //CPU* processor = new CPU("Test//07.gb"); // 07-jr,jp,call,ret,rst.gb
    //CPU* processor = new CPU("Test//08.gb"); // 08-misc instrs.gb
    //CPU* processor = new CPU("Test//09.gb"); // 09-op r,r.gb
    //CPU* processor = new CPU("Test//10.gb"); // 10-bit ops.gb
    //CPU* processor = new CPU("Test//11.gb"); // 11-op a,(hl).gb

    //processor->SetBios("bios.gb");
    processor->SetRom("tetris.gb");

    processor->Start();

    while (processor->IsRunning())
    {
        processor->Loop();
    }
    
    delete processor;

	//system("PAUSE");

    return 0;
}