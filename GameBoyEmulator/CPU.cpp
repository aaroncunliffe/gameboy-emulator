

#include "CPU.h"
#include <iomanip>

CPU::CPU()
{
}

CPU::CPU(char* romPath) : CPU()
{
	path = romPath;
	regs.pc = PROGRAM_START;

   
    display = new Display();
    keyboard = new Keyboard();
    display->init(4);

    mmu = new MMU(romPath, display);
    mmu->LoadRom();
    display->SetMMU(mmu);

    mmu->cart->ReadTitle();
    InitOpcodeFunctions();
    InitOpcodeFunctionsCB();

    Reset();

    //RunBios();
    mmu->SetBiosComplete(true);

    /*regs.AF.word = 0xFFFF;
    regs.AF.low &= ~ZERO_FLAG;
    regs.AF.low &= ~SUBTRACT_FLAG;
    regs.AF.low &= ~HALF_CARRY_FLAG;
    regs.AF.low &= ~CARRY_FLAG;*/

    memset(instructionProfiling, (u32)0, 0x100 * sizeof(u32));
    memset(instructionProfilingCB, (u32)0, 0x100 * sizeof(u32));


}

CPU::~CPU()
{
    delete mmu;
    delete display;
    delete keyboard;
}

void CPU::Reset()
{

    display->clear();
    lastCycleTime = SDL_GetTicks();

    running = true;
    counter = 0;
    
    regs.ime = 0x01;

    regs.pc = PROGRAM_START;

    // MANUAL BIOS 
    regs.AF.high = 0x01;
    regs.AF.low = 0xB0;
    regs.BC.word = 0x0013;
    regs.DE.word = 0x00D8;
    regs.HL.word = 0x014D;
    regs.sp = 0xFFFE;
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

void CPU::RunBios()
{
    for (int i = 0; i < 0x100; i++)
    {
        u8 opcodeByte = mmu->ReadByte(regs.pc);

#ifdef _LOG

        std::cout << opcodeTable[opcodeByte].name << std::endl;
#endif 

        (this->*opcodeFunction[opcodeByte])();

    }

    mmu->SetBiosComplete(true);
    
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
       
        display->Step(counter); //

                       
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
        //SDL_Delay( 100 * delayTimeMs);
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
            KeysDown(e);
            break;
        case SDL_KEYUP:
            KeysUp(e);
            break;
        case SDL_QUIT:
            running = false;
            break;
        }

    }
}

void CPU::KeysDown(SDL_Event e)
{
    if (e.key.keysym.sym == SDLK_ESCAPE)
    {
        std::cout << "Quitting" << std::endl;
        running = false;
    }
    else if (e.key.keysym.sym == SDLK_F1)
    {
        DumpToScreen();
    }
    else if (e.key.keysym.sym == SDLK_LEFT)
    {
        //display->Process();
        mmu->keytest = 0x07;
        //log = true;
        //u8 byte = mmu->ReadByte(0xFF0F);
        //mmu->WriteByte(0xFF0F, byte |= JOYPAD_INTERUPT_BIT);
    }
    else if (e.key.keysym.sym == SDLK_RIGHT)
    {
        //display->SetScrollX(display->GetScrollX() + 1);
    }
    else if (e.key.keysym.sym == SDLK_UP)
    {
        //display->SetScrollY(display->GetScrollY() - 1);
    }
    else if (e.key.keysym.sym == SDLK_DOWN)
    {
        //display->SetScrollY(display->GetScrollY() + 1);
    }
    

}

void CPU::KeysUp(SDL_Event e)
{
    if (e.key.keysym.sym == SDLK_LEFT)
    {
        //display->Process();
        mmu->keytest = 0x0F;
    }
}

void CPU::ProcessInstruction()
{
    u8 opcodeByte = mmu->ReadByte(regs.pc);

    u8 nextByte = mmu->ReadByte(regs.pc + 1);

#define _LOG
#ifdef _LOG
    //if (totalInstructions > 0x01527d3a) // Total instructions for 2nd demo block hitting
    //{
    //if(totalInstructions > 0x0131a335)
    //{
    if (log)
    {
        //std::cout << std::hex << std::setw(4) << std::setfill('0') << std::uppercase << (u16)mmu->ReadByte(0xFFC6) << " - " << regs.pc << " " << opcodeTable[opcodeByte].name << std::endl;
        if (opcodeByte != 0xCB)
            std::cout << std::hex << std::setw(4) << std::setfill('0') << std::uppercase << regs.pc << " " << opcodeTable[opcodeByte].name << std::endl;
        else
            std::cout << std::hex << std::setw(4) << std::setfill('0') << std::uppercase << regs.pc << " " << CBOpcodeTable[opcodeByte].name << std::endl;
    }
    //}
    
#endif 

    if (opcodeByte != 0xCB)
        instructionProfiling[opcodeByte]++;
    else
    {
        instructionProfiling[opcodeByte]++;
        instructionProfiling[nextByte]++;
    }
     
    

   (this->*opcodeFunction[opcodeByte])();
    totalInstructions++;
}

void CPU::DumpToFile()
{
    std::ofstream outputFile;

    outputFile.open("Registers.txt");
    
    std::hex;
    outputFile << "Registers:" << std::endl;
    outputFile << "A: " << regs.AF.high << " F: " << regs.AF.low << std::endl;
    outputFile << "B: " << regs.BC.high << " C: " << regs.BC.low << std::endl;
    outputFile << "D: " << regs.DE.high << " E: " << regs.DE.low << std::endl;
    outputFile << "H: " << regs.HL.high << " L: " << regs.HL.low << std::endl;
    outputFile << std::endl;
    outputFile << "PC " << regs.pc << " - " << opcodeTable[mmu->ReadByte(regs.pc)].name <<  std::endl;
    outputFile << "SP " << regs.sp << std::endl;


    outputFile.close();

    std::cout << "Registers written to file" << std::endl;

}

void CPU::DumpToScreen()
{

}
