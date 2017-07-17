//#pragma once
//
//#include <iostream>
//#include <fstream>
//#include <windows.h>
//
//#include "SDL.h"
//#include "Definitions.h"
//#include "Display.h"
//#include "Keyboard.h"
//
//
//
//
//class CPU
//{
//
//private:
//    
//
//    Display* display;
//    Keyboard* keyboard;
//
//    bool running = false;
//    char* romPath;
//
//    u32 lastCycleTime;
//
//public:
//
//    CPU(char* path);
//    ~CPU();
//
//    void Reset();
//
//    int  ReadRom();
//    void Loop();
//    
//
//    void ProcessEvents();
//    void KeysDown(SDL_Event e);
//    void KeysUp(SDL_Event e);
//
//    void ProcessInstruction();
//
//    void PushStack(u16 data);
//    u16  PopStack();
//    
//
//    // Getters
//    bool IsRunning() { return running; }
//
//};