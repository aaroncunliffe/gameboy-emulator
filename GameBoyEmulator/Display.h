#pragma once

#include <iostream>


#include "SDL.h"
#include "Definitions.h"

const int DISPLAY_WIDTH  = 160;
const int DISPLAY_HEIGHT = 144;


const u16 VRAM_OFFSET = 0x8000;
const u8 BG_TILE_MAP_SELECT_OFFSET = 0x08;
const u8 BG_TILE_MAP_SELECT_BIT = 0x03;

enum GPU_MODE { HBLANK = 0, VBLANK = 1, OAM = 2, VRAM = 3 };


      
struct pixel
{
    u8 r;
    u8 g;
    u8 b;
    u8 a;
       
};

class MMU;


class Display
{

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* screen;

    Uint32 OnColor =  0xFF00FF00; // White
    Uint32 OffColor = 0x00000000; // Black

    GPU_MODE activeMode;
    u32 modeClock;
    u32 currentLine;

    MMU* mmu;

    int w, h;
    int pw, ph;
    int sizeMultiplier;

    bool displayMemory[DISPLAY_WIDTH * DISPLAY_HEIGHT] = { true };

    u8 vram[0x2000];

    /*  
    8000-87FF	Tile set #1: tiles 0-127
    8800-8FFF	Tile set #1: tiles 128-255, Tile set #0: tiles -1 to -128 - OVERLAP
    9000-97FF	Tile set #0: tiles 0-127
    9800-9BFF	Tile map #0
    9C00-9FFF	Tile map #1
    */



    pixel pixelPalette[4];

    u8 Tileset[384][8][8];


    SDL_Rect viewport;

    u8 STAT;
    u8 LCDC;
    u8 scrollX;
    u8 scrollY;
    
    u8 bgMapInUse;

    SDL_Color pixels[DISPLAY_HEIGHT * DISPLAY_WIDTH]; // display or viewport

    bool pixelChanged = false;

public:

    Display();
    ~Display();
    void SetMMU(MMU* memManager);

    void init(int multiplier);
    void clear();
    
    GPU_MODE GetMode() { return activeMode; }

    void WriteByte(u16 addr, u8 byte);
    u8 ReadByte(u16 addr);


    // Get display registers

    u8 GetLCDC() { return LCDC; }
    void SetLCDC(u8 val) { LCDC = val; }

    u8 GetStat() { return STAT; }
    void SetStat(u8 val) { STAT = val; }

    void SetScrollX(u8 val);
    void SetScrollY(u8 val);

    u8 GetScrollX() { return scrollX; }
    u8 GetScrollY() { return scrollY; }

    u8 GetLine() { return currentLine; }

    

    void Step(u32 clock);
    void Process();
    void Update();

private:
    void Draw();
    void RenderScanline();

    void UpdateRegisters();
    void UpdateTileset(u16 addr);
};


// Background layers
// - BG 0
// - BG 1
// - BG 2
// - BG 3
// - OBJ
// - WIN 0
// - WIN 1
// - OBJ WIN

// FF40 - LCDC - LCD Control (R/W)
// Bit 7 - LCD Display Enable(0 = Off, 1 = On)
// Bit 6 - Window Tile Map Display Select(0 = 9800 - 9BFF, 1 = 9C00 - 9FFF)
// Bit 5 - Window Display Enable(0 = Off, 1 = On)
// Bit 4 - BG & Window Tile Data Select(0 = 8800 - 97FF, 1 = 8000 - 8FFF)
// Bit 3 - BG Tile Map Display Select(0 = 9800 - 9BFF, 1 = 9C00 - 9FFF)
// Bit 2 - OBJ(Sprite) Size(0 = 8x8, 1 = 8x16)
// Bit 1 - OBJ(Sprite) Display Enable(0 = Off, 1 = On)
// Bit 0 - BG Display(for CGB see below) (0 = Off, 1 = On)