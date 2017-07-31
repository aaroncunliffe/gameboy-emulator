#include "Joypad.h"
#include "CPU.h"



Joypad::Joypad(CPU* c)
{
	cpu = c;
	row1 = 0x0F;
	row2 = 0x0F;
}

void Joypad::KeysDown(SDL_Event e)
{
	// Utility
	if (e.key.keysym.sym == SDLK_ESCAPE)
	{
		std::cout << "Quitting" << std::endl;
		cpu->SetRunning(false);
	}
	else if (e.key.keysym.sym == SDLK_F1)
	{
		//cpu->DumpToScreen();
	}

	// Row 1
	if (e.key.keysym.sym == Key_Start)
	{
		row1 &= ~0x08;
		cpu->JoypadInterrupt();
	}
	else if (e.key.keysym.sym == Key_Select)
	{
		row1 &= ~0x04;
		cpu->JoypadInterrupt();
	}
	else if (e.key.keysym.sym == Key_B)
	{
		row1 &= ~0x02;
		cpu->JoypadInterrupt();
	}
	else if (e.key.keysym.sym == Key_A)
	{
		row1 &= ~0x01;
		cpu->JoypadInterrupt();
	}

	// Row 2
	else if (e.key.keysym.sym == Key_Down)
	{
		row2 &= ~0x08;
		cpu->JoypadInterrupt();
	}
	else if (e.key.keysym.sym == Key_Up)
	{
		row2 &= ~0x04;
		cpu->JoypadInterrupt();
	}
	else if (e.key.keysym.sym == Key_Left)
	{
		row2 &= ~0x02;
		cpu->JoypadInterrupt();
	}
	else if (e.key.keysym.sym == Key_Right)
	{
		row2 &= ~0x01;
		cpu->JoypadInterrupt();
	}


}

void Joypad::KeysUp(SDL_Event e)
{
	// Row 1
	if (e.key.keysym.sym == Key_Start)
	{
		row1 |= 0x08;
	}
	else if (e.key.keysym.sym == Key_Select)
	{
		row1 |= 0x04;
	}
	else if (e.key.keysym.sym == Key_B)
	{
		row1 |= 0x02;
	}
	else if (e.key.keysym.sym == Key_A)
	{
		row1 |= 0x01;
	}

	// Row 2
	else if (e.key.keysym.sym == Key_Down)
	{
		row2 |= 0x08;
	}
	else if (e.key.keysym.sym == Key_Up)
	{
		row2 |= 0x04;
	}
	else if (e.key.keysym.sym == Key_Left)
	{
		row2 |= 0x02;
	}
	else if (e.key.keysym.sym == Key_Right)
	{
		row2 |= 0x01;
	}

	


}
