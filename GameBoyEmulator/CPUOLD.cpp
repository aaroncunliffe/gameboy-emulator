//# include "CPU.h"
//
//CPU::CPU(char* path)
//{
//
//    //Start SDL
//    SDL_Init(SDL_INIT_EVERYTHING);
//
//    display = new Display();
//    display->init(10);
//    keyboard = new Keyboard();
//
//    memcpy(&memory, &charset, sizeof(charset));
//
//    running = true;
//    romPath = path;
//
//    if (ReadRom() < 0)
//    {
//        running = false;
//    }
//
//    Reset();
//
//}
//
//
//CPU::~CPU()
//{
//    delete display;
//    delete keyboard;
//
//    //Quit SDL
//    SDL_Quit();
//}
//
//void CPU::Reset()
//{
//    pc = PROGRAM_START;
//
//    IReg = 0;
//    sp = 0;
//
//    for (int i = 0; i < VREGS; i++)
//    {
//        stack[i] = 0;
//        VRegs[i] = 0;
//    }
//    DT = 0;
//    ST = 0;
//
//    display->clear();
//    lastCycleTime = SDL_GetTicks();
//}
//
//
//int CPU::ReadRom()
//{
//    std::ifstream file;
//    file.open(romPath, std::ios::binary | std::ios::ate); // ate is to set the pointer to the end of the file
//
//    std::cout << "Opening rom file: " << romPath << std::endl;
//    if (file.is_open())
//    {
//        
//        romSize = file.tellg();
//        std::cout << "Rom Size: " << romSize << " Bytes" << std::endl;
//
//        if (romSize > MAX_ROM_SIZE)
//            return -1;
//        
//        file.seekg(0, std::ios::beg); // Move pointer back to the beginning of file
//        file.read((char*)&memory[PROGRAM_START], romSize);
//
//        std::cout << "Rom loaded successfully" << std::endl;
//        file.close();
//        return 1;
//    }
//
//    return -1;
//}
//
//
//void CPU::Loop()
//{
//    display->Process();
//
//    //if (pc < (romSize + PROGRAM_START))
//        ProcessInstruction();
//   // else
//        //running = false;
//    
//    ProcessEvents();
//
//    display->Update();
//
//    u32 msForCycle = SDL_GetTicks() - this->lastCycleTime;
//    int delayTimeMs = (17 - msForCycle);
//
//    // Only if it is above 1 do we delay
//    if (delayTimeMs > 0)
//    {
//        SDL_Delay(delayTimeMs);
//    }
//    
//}
// 
//void CPU::ProcessEvents()
//{
//    SDL_Event e;
//    if (SDL_PollEvent(&e))
//    {
//        switch (e.type)
//        {
//        case SDL_KEYDOWN:
//            KeysDown(e);
//            break;
//        case SDL_KEYUP:
//            KeysUp(e);
//            break;
//        case SDL_QUIT:
//            running = false;
//            break;
//        }
//
//    }
//}
//
//void CPU::KeysDown(SDL_Event e)
//{
//    if (e.key.keysym.sym == SDLK_ESCAPE)
//    {
//        std::cout << "Quitting" << std::endl;
//        running = false;
//    }
//    if (e.key.keysym.sym == SDLK_q)
//    {
//        //Beep(750, 300);
//        display->clear();
//    }
//    if (e.key.keysym.sym == Key_1)
//        keyboard->SetKey(0x1, true);
//    else if (e.key.keysym.sym == Key_2)
//        keyboard->SetKey(0x2, true);
//    else if (e.key.keysym.sym == Key_3)
//        keyboard->SetKey(0x3, true);
//    else if (e.key.keysym.sym == Key_4)
//        keyboard->SetKey(0x4, true);
//    else if (e.key.keysym.sym == Key_5)
//        keyboard->SetKey(0x5, true);
//    else if (e.key.keysym.sym == Key_6)
//        keyboard->SetKey(0x6, true);
//    else if (e.key.keysym.sym == Key_7)
//        keyboard->SetKey(0x7, true);
//    else if (e.key.keysym.sym == Key_8)
//        keyboard->SetKey(0x8, true);
//    else if (e.key.keysym.sym == Key_9)
//        keyboard->SetKey(0x9, true);
//    else if (e.key.keysym.sym == Key_A)
//        keyboard->SetKey(0xA, true);
//    else if (e.key.keysym.sym == Key_B)
//        keyboard->SetKey(0xB, true);
//    else if (e.key.keysym.sym == Key_C)
//        keyboard->SetKey(0xC, true);
//    else if (e.key.keysym.sym == Key_D)
//        keyboard->SetKey(0xD, true);
//    else if (e.key.keysym.sym == Key_E)
//        keyboard->SetKey(0xE, true);
//    else if (e.key.keysym.sym == Key_F)
//        keyboard->SetKey(0xF, true);
//    
//
//}
//
//void CPU::KeysUp(SDL_Event e)
//{
//    if (e.key.keysym.sym == Key_1)
//        keyboard->SetKey(0x1, false);
//    else if (e.key.keysym.sym == Key_2)
//        keyboard->SetKey(0x2, false);
//    else if (e.key.keysym.sym == Key_3)
//        keyboard->SetKey(0x3, false);
//    else if (e.key.keysym.sym == Key_4)
//        keyboard->SetKey(0x4, false);
//    else if (e.key.keysym.sym == Key_5)
//        keyboard->SetKey(0x5, false);
//    else if (e.key.keysym.sym == Key_6)
//        keyboard->SetKey(0x6, false);
//    else if (e.key.keysym.sym == Key_7)
//        keyboard->SetKey(0x7, false);
//    else if (e.key.keysym.sym == Key_8)
//        keyboard->SetKey(0x8, false);
//    else if (e.key.keysym.sym == Key_9)
//        keyboard->SetKey(0x9, false);
//    else if (e.key.keysym.sym == Key_A)
//        keyboard->SetKey(0xA, false);
//    else if (e.key.keysym.sym == Key_B)
//        keyboard->SetKey(0xB, false);
//    else if (e.key.keysym.sym == Key_C)
//        keyboard->SetKey(0xC, false);
//    else if (e.key.keysym.sym == Key_D)
//        keyboard->SetKey(0xD, false);
//    else if (e.key.keysym.sym == Key_E)
//        keyboard->SetKey(0xE, false);
//    else if (e.key.keysym.sym == Key_F)
//        keyboard->SetKey(0xF, false);
//
//}
//
//void CPU::ProcessInstruction()
//{
//u16 opcode = (memory[pc] << 8) | memory[pc+1]; 

    //printf("%04x | %04x \n", pc, opcode);
       
    //pc += 2;
//}
//
//
//void CPU::PushStack(u16 data)
//{
//    if (sp < STACK_MEMORY)
//    {
//        sp++;
//        stack[sp] = data;
//    }
//
//}
//
//u16 CPU::PopStack()
//{
//    u16 value = stack[sp];
//    sp--;
//    return value;
//
//}