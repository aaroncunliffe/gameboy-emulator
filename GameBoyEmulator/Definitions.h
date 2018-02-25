#pragma once


// Defined types, we dont care about specific types such as char, short, int etc
// we just care about its size in bits.
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;


// Definitions for keybinds
#define Key_Right	SDLK_RIGHT
#define Key_Left	SDLK_LEFT
#define Key_Up		SDLK_UP
#define Key_Down	SDLK_DOWN
#define Key_A		SDLK_s      // Changed to match BGB
#define Key_B		SDLK_a
#define Key_Select	SDLK_LSHIFT
#define Key_Start	SDLK_RETURN

#define CARTRIDGE_TYPE_OFFSET = 0x147