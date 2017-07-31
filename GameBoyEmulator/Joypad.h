#pragma once
#include "definitions.h"
#include <SDL.h>

class CPU;


class Joypad
{

private:

	// Joypad is activelow
	u8 row1;
	u8 row2;

	CPU* cpu;

public:
	Joypad(CPU* c);

	u8 GetRow1() { return row1; }
	u8 GetRow2() { return row2; }
    
	void KeysDown(SDL_Event e);
	void KeysUp(SDL_Event e);


};


// This is the matrix layout for register $FF00:
//
//            P14            P15
//             |              |
// P10------ - O - Right----  O - A
//             |              |
// P11------ - O - Left---- - O - B
//             |              |
// P12------ - O - Up------ - O - Select
//             |              |
// P13------ - O - Down---- - O - Start
//             |              |
