

#include "CPU.h"
#include <iomanip>


// Definitions
//#define _LOG
//#define _PROFILE

CPU::CPU()
{
    biosLoaded = false;
	RomLoaded = false;

    regs.pc = 0x0000;
    regs.ime = 0x00;

    display = new Display();
    joypad = new Joypad(this);
    display->init(4);

    mmu = new MMU(display, joypad);

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

   /* regs.AF.word = 0x0300;
    SUB(0x01);
    opcode0x27();
    u8 byte = regs.AF.high;

    int stop = 0;*/
}

CPU::CPU(char* romPath) : CPU()
{
	path = romPath;
    SetRom(path);
}

CPU::~CPU()
{
    delete mmu;
	delete joypad;
	delete display;

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
    counter = 0;
	display->clear();
    if (!biosLoaded)
    {
        std::cout << "Bios file not loaded" << std::endl;
        std::cout << std::endl;
        DefaultValues();
        mmu->SetBiosComplete(true);
    }
	assert(RomLoaded); // No rom loaded
	
    running = true;
}

void CPU::Stop()
{
    running = false;

#ifdef _PROFILE
    PrintProfilingInfo();
#endif 


}

void CPU::Reset()
{
    counter = 0;
    //display->clear();
	mmu->WriteByte(0xFF40, 0x00); // Disable LCD before resetting to stop a graphic bug where tile at position 0 is written accross the entire screen
    
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
    Uint64 frameStart = SDL_GetPerformanceCounter();
                              

    if (counter == 0)
    {
        
        // Handle interrupts
        if (regs.ime)
        {
            u8 interruptFired = mmu->ReadByte(0xFFFF) & mmu->ReadByte(0xFF0F);
            
            if (interruptFired & VBLANK_INTERRUPT_BIT)
            {
                regs.ime = 0x00; // Disable IME
                u8 byte = mmu->ReadByte(0xFF0F);
                mmu->WriteByte(0xFF0F, byte &= ~VBLANK_INTERRUPT_BIT);
                
                RST40();
                halt = false;
            }
            else if (interruptFired & LCDSTAT_INTERRUPT_BIT)
            {
                regs.ime = 0x00; // Disable IME
                u8 byte = mmu->ReadByte(0xFF0F);
                mmu->WriteByte(0xFF0F, byte &= ~LCDSTAT_INTERRUPT_BIT);

                RST48();
                halt = false;
            }
            else if (interruptFired & TIMER_INTERRUPT_BIT)
            {
                regs.ime = 0x00; // Disable IME
                u8 byte = mmu->ReadByte(0xFF0F);
                mmu->WriteByte(0xFF0F, byte &= ~TIMER_INTERRUPT_BIT);

                RST50();
                halt = false;
            }
            else if (interruptFired & SERIAL_INTERRUPT_BIT)
            {
                regs.ime = 0x00; // Disable IME
                u8 byte = mmu->ReadByte(0xFF0F);
                mmu->WriteByte(0xFF0F, byte &= ~SERIAL_INTERRUPT_BIT);

                RST58();
                halt = false;
            }
            else if (interruptFired & JOYPAD_INTERRUPT_BIT)
            {
                regs.ime = 0x00; // Disable IME
                u8 byte = mmu->ReadByte(0xFF0F);
                mmu->WriteByte(0xFF0F, byte &= ~JOYPAD_INTERRUPT_BIT);

                RST60();
                halt = false;
            }
        }


        if (!halt)
        {
            ProcessInstruction();   // 
        }

        display->Step(counter); // This has to be after the instruction is executed (so that the counter is not 0)

        ProcessEvents();
        //counter = 0;
        //display->Update();
        // else
        //running = false;

        //std::cout << (mmu->ReadByte(0xFFFF) == 0x00 ? "off" : "on") << std::endl;
        

    }
    else
    {
        counter--;
    }



    //int freq = SDL_GetPerformanceFrequency();
    //timerFps = ((SDL_GetPerformanceCounter() - frameStart));

    //std::cout << std::dec << timerFps << std::endl;

    //while (timerFps / freq * 1000 < (1000 / 59))
    //{
    //    timerFps += SDL_GetPerformanceCounter();
    //    //std::cout << timerFps << std::endl;
    //     
    //}

    //timerFps /= 0xFFFFFFFF;
    //totalInstructions = timerFps;

    // volatile

}
 
void CPU::ProcessEvents()
{
    SDL_Event e;
    if (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
        case SDL_KEYDOWN:
            joypad->KeysDown(e);
            if (e.key.keysym.sym == SDLK_ESCAPE)
            {
                mmu->WriteSaveFile();
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
			else if (e.key.keysym.sym == SDLK_F2)
			{
				display->ToggleTileView();
			}
			else if (e.key.keysym.sym == SDLK_F3)
			{
                mmu->WriteSaveFile();
			}
            else if (e.key.keysym.sym == SDLK_F5)
            {
                Reset();
            }

            break;
        case SDL_KEYUP:
            joypad->KeysUp(e);
            break;
        case SDL_QUIT:
            running = false;
            break;
        case SDL_CONTROLLERDEVICEADDED:
            if (SDL_IsGameController(e.cdevice.which)) {
                SDL_GameController *pad = SDL_GameControllerOpen(e.cdevice.which);

                if (pad) {
                    SDL_Joystick *joy = SDL_GameControllerGetJoystick(pad);
                    int instanceID = SDL_JoystickInstanceID(joy);

                    std::cout << "Game Controller Detected" << std::endl;
                    // You can add to your own map of joystick IDs to controllers here.
                    //YOUR_FUNCTION_THAT_CREATES_A_MAPPING(id, pad);
                }
            }

            break;

        case SDL_CONTROLLERBUTTONDOWN:
            joypad->GamepadButtonDown(e);
            break;
        case SDL_CONTROLLERBUTTONUP:
            joypad->GamepadButtonUp(e);
            break;
        }

    }
}

// Called by keyboard class when a joypad key is pressed
void CPU::JoypadInterrupt()
{
	u8 byte = mmu->ReadByte(0xFF0F);
	mmu->WriteByte(0xFF0F, byte |= JOYPAD_INTERRUPT_BIT);
}

void CPU::ProcessInstruction()
{
    u8 opcodeByte = mmu->ReadByte(regs.pc);

    u8 nextByte = mmu->ReadByte(regs.pc + 1);

#ifdef _LOG
    
    if (opcodeByte != 0xCB)
        std::cout << std::hex << std::setw(4) << std::setfill('0') << std::uppercase << regs.pc << " " << opcodeTable[opcodeByte].name << std::endl;
    else
        std::cout << std::hex << std::setw(4) << std::setfill('0') << std::uppercase << regs.pc << " " << CBOpcodeTable[nextByte].name << std::endl;
    

#endif 
    
#ifdef _PROFILE
     if (opcodeByte != 0xCB) //  Profiling: can see what instructions are called and what are not used.
         instructionProfiling[opcodeByte]++;
     else
     {
         instructionProfiling[opcodeByte]++;
         instructionProfilingCB[nextByte]++;
     }
#endif

	
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


// Prints info about the instructions that have been used since the start of the current session
void CPU::PrintProfilingInfo()
{

    u8 mostUsedInstruction;
    const u8 totalNormalInstructions = 0xF4; // Normal table instructions that don't exist are 0xD3, 0xDB, 0xDD, 0xE3, 0xE4, 0xEB, 0xEC, 0xED, 0xF4, 0xFC, 0xFD expect these to be zero.
    const u8 totalCBInstructions = 0xFF;

    u8 totalUnusedInstructions = 0x00;
    u8 totalUnusedCBInstructions = 0x00;

    std::cout << " Unused Instructions normal table:" << std::endl;
    for (u16 opcode = 0x00; opcode <= 0xFF; opcode++)
    {
        if (instructionProfiling[(u8)opcode] == 0x00)
        {
            if (opcodeFunction[(u8)opcode] != nullptr)
            {
                std::cout << std::hex << std::setw(2) << std::setfill('0') << std::uppercase << opcode << ", ";
                totalUnusedInstructions++;
            }
            
        }
    }
    float result = ((float)totalUnusedInstructions / (float)totalNormalInstructions) * 100.0f;
    std::cout << std::endl;
    std::cout << std::dec << "Total Unused instructions = " << (int)totalUnusedInstructions << " (" << (int)result << "%)" << std::endl;

    totalInstructions;

    std::cout << std::endl;
    std::cout << "Unused Instructions CB table:" << std::endl;
    for (u16 opcode = 0x00; opcode <= 0xFF; opcode++)
    {
        if (instructionProfilingCB[(u8)opcode] == 0x00)
        {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << std::uppercase << opcode << ", ";
            totalUnusedCBInstructions++;

        }
    }
    float CBResult = ((float)totalUnusedCBInstructions / (float)totalCBInstructions) * 100.0f;
    std::cout << std::endl;
    std::cout << std::dec << "Total Unused CB instructions = " << (int)totalUnusedCBInstructions << " (" << (int)CBResult  << "%)" << std::endl;

    std::cout << std::endl;
    system("pause");    // Not sure if there is a more elagent way to stop the shutdown here. 
                        // I think this is a windows only feature, need to look into it
}
