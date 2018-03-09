#include "Joypad.h"
#include "CPU.h"



Joypad::Joypad(CPU* c)
{
	cpu = c;
    
    // Set values to all unpressed
	row1 = 0x0F;
	row2 = 0x0F;
}

void Joypad::KeysDown(SDL_Event e)
{

	// Row 1
	if (e.key.keysym.sym == Key_Start)
	{
		row1 &= ~0x08;
		cpu->JoypadInterrupt();
	}
	if (e.key.keysym.sym == Key_Select)
	{
		row1 &= ~0x04;
		cpu->JoypadInterrupt();
	}
	if (e.key.keysym.sym == Key_B)
	{
		row1 &= ~0x02;
		cpu->JoypadInterrupt();
	}
	if (e.key.keysym.sym == Key_A)
	{
		row1 &= ~0x01;
		cpu->JoypadInterrupt();
	}

	// Row 2
	if (e.key.keysym.sym == Key_Down)
	{
		row2 &= ~0x08;
		cpu->JoypadInterrupt();
	}
	if (e.key.keysym.sym == Key_Up)
	{
		row2 &= ~0x04;
		cpu->JoypadInterrupt();
	}
	if (e.key.keysym.sym == Key_Left)
	{
		row2 &= ~0x02;
		cpu->JoypadInterrupt();
	}
	if (e.key.keysym.sym == Key_Right)
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
	if (e.key.keysym.sym == Key_Select)
	{
		row1 |= 0x04;
	}
	if (e.key.keysym.sym == Key_B)
	{
		row1 |= 0x02;
	}
	if (e.key.keysym.sym == Key_A)
	{
		row1 |= 0x01;
	}

	// Row 2
	if (e.key.keysym.sym == Key_Down)
	{
		row2 |= 0x08;
	}
	if (e.key.keysym.sym == Key_Up)
	{
		row2 |= 0x04;
	}
	if (e.key.keysym.sym == Key_Left)
	{
		row2 |= 0x02;
	}
	if (e.key.keysym.sym == Key_Right)
	{
		row2 |= 0x01;
	}
}


void Joypad::GamepadButtonDown(SDL_Event e)
{
    // Row 1
    if (e.cbutton.button == Button_Start)
    {
        row1 &= ~0x08;
        cpu->JoypadInterrupt();
    }
    if (e.cbutton.button == Button_Select)
    {
        row1 &= ~0x04;
        cpu->JoypadInterrupt();
    }
    if (e.cbutton.button == Button_B)
    {
        row1 &= ~0x02;
        cpu->JoypadInterrupt();
    }
    if (e.cbutton.button == Button_A)
    {
        row1 &= ~0x01;
        cpu->JoypadInterrupt();
    }

    // Row 2
    if (e.cbutton.button == Button_Down)
    {
        row2 &= ~0x08;
        cpu->JoypadInterrupt();
    }
    if (e.cbutton.button == Button_Up)
    {
        row2 &= ~0x04;
        cpu->JoypadInterrupt();
    }
    if (e.cbutton.button == Button_Left)
    {
        row2 &= ~0x02;
        cpu->JoypadInterrupt();
    }
    if (e.cbutton.button == Button_Right)
    {
        row2 &= ~0x01;
        cpu->JoypadInterrupt();
    }
}

void Joypad::GamepadButtonUp(SDL_Event e)
{
    // Row 1
    if (e.cbutton.button == Button_Start)
    {
        row1 |= 0x08;
    }
    if (e.cbutton.button == Button_Select)
    {
        row1 |= 0x04;
    }
    if (e.cbutton.button == Button_B)
    {
        row1 |= 0x02;
    }
    if (e.cbutton.button == Button_A)
    {
        row1 |= 0x01;
    }

    // Row 2
    if (e.cbutton.button == Button_Down)
    {
        row2 |= 0x08;
    }
    if (e.cbutton.button == Button_Up)
    {
        row2 |= 0x04;
    }
    if (e.cbutton.button == Button_Left)
    {
        row2 |= 0x02;
    }
    if (e.cbutton.button == Button_Right)
    {
        row2 |= 0x01;
    }
}
