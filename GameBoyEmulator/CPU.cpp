

#include "CPU.h"
#include <iomanip>

CPU::CPU()
{
    biosLoaded = false;
	RomLoaded = false;

    regs.pc = 0x0000;
    regs.ime = 0x00;

    display = new Display();
    keyboard = new Joypad(this);
    display->init(4);

    mmu = new MMU(display, keyboard);

    display->SetMMU(mmu);

    InitOpcodeFunctions();
    InitOpcodeFunctionsCB();

    memset(instructionProfiling, (u32)0, 0x100 * sizeof(u32));
    memset(instructionProfilingCB, (u32)0, 0x100 * sizeof(u32));

	//regs.AF.high = 0x01;
	//regs.AF.low = 0xB0;
	//regs.BC.word = 0x0013;
	//regs.DE.word = 0x00D8;
	//regs.HL.word = 0x014D;


}

CPU::CPU(char* romPath) : CPU()
{
	path = romPath;
    SetRom(path);
}

CPU::~CPU()
{
    delete mmu;
    delete display;
    delete keyboard;
}

void CPU::SetBios(char* path)
{
    if (!mmu->LoadBios(path))
    {
        std::cout << "Error loading bios, continuing with default values" << std::endl;
        std::cout << std::endl;
        DefaultValues();
        mmu->SetBiosComplete(true);
    }
    else
    {
        biosLoaded = true;
    }
}

void CPU::SetRom(char* path)
{
	if (!mmu->LoadRom(path))
		assert(false); // Error loading the ROM file
	else
		RomLoaded = true;
}

void CPU::Start()
{
	lastCycleTime = SDL_GetTicks();
    display->clear();
    if (!biosLoaded)
    {
        std::cout << "Bios file not loaded" << std::endl;
        std::cout << std::endl;
        DefaultValues();
        mmu->SetBiosComplete(true);
    }
	if (!RomLoaded)
	{
		assert(false); // No rom loaded
	}
    running = true;
}

void CPU::Stop()
{
    running = false;
}

void CPU::Reset()
{
    //display->clear();
	mmu->WriteByte(0xFF40, 0x00); // Disable LCD before resetting to stop a graphic bug where tile at position 0 is written accross the entire screen
    lastCycleTime = SDL_GetTicks();

    counter = 0;

    regs.ime = 0x00;

    if (biosLoaded)
    {
        regs.pc = 0x00;// PROGRAM_START;
        mmu->SetBiosComplete(false);
    }
    else
    {
        std::cout << "Bios file not loaded" << std::endl;
        std::cout << std::endl;
        DefaultValues();
        mmu->SetBiosComplete(true);
    }
}

void CPU::DefaultValues()
{
    // MANUAL BIOS 
    regs.AF.high = 0x01;
    regs.AF.low = 0xB0;
    regs.BC.word = 0x0013;
    regs.DE.word = 0x00D8;
    regs.HL.word = 0x014D;
    regs.sp = 0xFFFE;
    regs.pc = 0x0100;
    mmu->WriteByte(0xFF05, 0x00);
    mmu->WriteByte(0xFF06, 0x00);
    mmu->WriteByte(0xFF07, 0x00);
    mmu->WriteByte(0xFF10, 0x80);
    mmu->WriteByte(0xFF11, 0xBF);
    mmu->WriteByte(0xFF12, 0xF3);
    mmu->WriteByte(0xFF14, 0xBF);
    mmu->WriteByte(0xFF16, 0x3F);
    mmu->WriteByte(0xFF17, 0x00);
    mmu->WriteByte(0xFF19, 0xBF);
    mmu->WriteByte(0xFF1A, 0x7F);
    mmu->WriteByte(0xFF1B, 0xFF);
    mmu->WriteByte(0xFF1C, 0x9F);
    mmu->WriteByte(0xFF1E, 0xBF);
    mmu->WriteByte(0xFF20, 0xFF);
    mmu->WriteByte(0xFF21, 0x00);
    mmu->WriteByte(0xFF22, 0x00);
    mmu->WriteByte(0xFF23, 0xBF);
    mmu->WriteByte(0xFF24, 0x77);
    mmu->WriteByte(0xFF25, 0xF3);
    mmu->WriteByte(0xFF26, 0xF1); // F1 - GB F0 - SGB
    mmu->WriteByte(0xFF40, 0x91);
    mmu->WriteByte(0xFF42, 0x00);
    mmu->WriteByte(0xFF43, 0x00);
    mmu->WriteByte(0xFF45, 0x00);
    mmu->WriteByte(0xFF47, 0xFC);
    mmu->WriteByte(0xFF48, 0xFF);
    mmu->WriteByte(0xFF49, 0xFF);
    mmu->WriteByte(0xFF4A, 0x00);
    mmu->WriteByte(0xFF4B, 0x00);
    mmu->WriteByte(0xFFFF, 0x00);
}

void CPU::Loop()
{
    if (counter == 0)
    {
        // Handle interrupts
        if (regs.ime)
        {
            u8 interuptFired = mmu->ReadByte(0xFFFF) & mmu->ReadByte(0xFF0F);
            if (interuptFired & VBLANK_INTERUPT_BIT)
            {
                regs.ime = 0x00; // Disable IME
                u8 byte = mmu->ReadByte(0xFF0F);
                mmu->WriteByte(0xFF0F, byte &= ~VBLANK_INTERUPT_BIT);
                
                RST40();
                halt = false;
            }
            else if (interuptFired & LCDSTAT_INTERUPT_BIT)
            {
                regs.ime = 0x00; // Disable IME
                u8 byte = mmu->ReadByte(0xFF0F);
                mmu->WriteByte(0xFF0F, byte &= ~LCDSTAT_INTERUPT_BIT);

                RST48();
                halt = false;
            }
            else if (interuptFired & TIMER_INTERUPT_BIT)
            {
                regs.ime = 0x00; // Disable IME
                u8 byte = mmu->ReadByte(0xFF0F);
                mmu->WriteByte(0xFF0F, byte &= ~TIMER_INTERUPT_BIT);

                RST50();
                halt = false;
            }
            else if (interuptFired & SERIAL_INTERUPT_BIT)
            {
                regs.ime = 0x00; // Disable IME
                u8 byte = mmu->ReadByte(0xFF0F);
                mmu->WriteByte(0xFF0F, byte &= ~SERIAL_INTERUPT_BIT);

                RST58();
                halt = false;
            }
            else if (interuptFired & JOYPAD_INTERUPT_BIT)
            {
                regs.ime = 0x00; // Disable IME
                u8 byte = mmu->ReadByte(0xFF0F);
                mmu->WriteByte(0xFF0F, byte &= ~JOYPAD_INTERUPT_BIT);

                RST60();
                halt = false;
            }
        }


        if (!halt)
        {
            ProcessInstruction();   // 
        }

        display->Step(counter); // This has to be after the instruction is executed (so that the counter is not 0)

                       
        //counter = 0;
        //display->Update();
        // else
        //running = false;

        ProcessEvents();
        //std::cout << (mmu->ReadByte(0xFFFF) == 0x00 ? "off" : "on") << std::endl;


    }
    else
    {
        counter--;
    }

    u32 msForCycle = SDL_GetTicks() - this->lastCycleTime;
    int delayTimeMs = (17 - msForCycle);

    // Only if it is above 1 do we delay
    if (delayTimeMs > 0)
    {
        //SDL_Delay(delayTimeMs);
    }
    
    
}
 
void CPU::ProcessEvents()
{
    SDL_Event e;
    if (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
        case SDL_KEYDOWN:
            keyboard->KeysDown(e);
            if (e.key.keysym.sym == SDLK_ESCAPE)
            {
                Stop();
            }
            else if (e.key.keysym.sym == SDLK_F1)
            {
                //mmu->WriteSaveFile();
                //DumpToFile();
				// Tetris score writing
				mmu->WriteByte(0xC0A0, 0xFF);
				mmu->WriteByte(0xC0A1, 0xFF);
				mmu->WriteByte(0xC0A2, 0xFF);
            }
            else if (e.key.keysym.sym == SDLK_F5)
            {
                Reset();
            }

            break;
        case SDL_KEYUP:
            keyboard->KeysUp(e);
            break;
        case SDL_QUIT:
            running = false;
            break;
        }

    }
}

// Called by keyboard class when a joypad key is pressed
void CPU::JoypadInterrupt()
{
	u8 byte = mmu->ReadByte(0xFF0F);
	mmu->WriteByte(0xFF0F, byte |= JOYPAD_INTERUPT_BIT);
}

void CPU::ProcessInstruction()
{
    u8 opcodeByte = mmu->ReadByte(regs.pc);

    u8 nextByte = mmu->ReadByte(regs.pc + 1);

//#define _LOG
#ifdef _LOG
    
    
    //std::cout << std::hex << std::setw(4) << std::setfill('0') << std::uppercase << (u16)mmu->ReadByte(0xFFC6) << " - " << regs.pc << " " << opcodeTable[opcodeByte].name << std::endl;
    if (opcodeByte != 0xCB)
        std::cout << std::hex << std::setw(4) << std::setfill('0') << std::uppercase << regs.pc << " " << opcodeTable[opcodeByte].name << std::endl;
    else
        std::cout << std::hex << std::setw(4) << std::setfill('0') << std::uppercase << regs.pc << " " << CBOpcodeTable[nextByte].name << std::endl;
    

#endif 

    /* if (opcodeByte != 0xCB)
         instructionProfiling[opcodeByte]++;
     else
     {
         instructionProfiling[opcodeByte]++;
         instructionProfiling[nextByte]++;
     }*/
     //log = true;

	if (regs.pc == 0x00EF)
	{
		int stop = 0;
	}

	if (regs.pc == 0x0000)
	{
		int stop = 0;
	}

   (this->*opcodeFunction[opcodeByte])();
    //totalInstructions++;
}

void CPU::DumpToFile()
{
    std::ofstream outputFile;

    outputFile.open("Registers.bin");
    
    std::hex;
    outputFile << "Registers:";
    outputFile << "A:" << regs.AF.high << "F:" << regs.AF.low;
    outputFile << "B:" << regs.BC.high << "C:" << regs.BC.low;
    outputFile << "D:" << regs.DE.high << "E:" << regs.DE.low;
    outputFile << "H:" << regs.HL.high << "L:" << regs.HL.low;
    outputFile << "PC:" << (u8)regs.pc;
    outputFile << "SP:" << (u8)regs.sp;


    outputFile.close();

    std::cout << "Registers written to file" << std::endl;

}


void CPU::DumpToScreen()
{

}
