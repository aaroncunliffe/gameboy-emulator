#pragma once

#include <iostream>


#include "SDL.h"
#include "Definitions.h"

const int DISPLAY_WIDTH  = 160;
const int DISPLAY_HEIGHT = 144; 


const u16 VRAM_OFFSET = 0x8000;
const u16 OAM_START = 0xFE00;

const u16  DMA_LENGTH = 160;

// LCDC offsets
const u8 BG_ENABLE_OFFSET                = 0x01;
const u8 SPRITE_ENABLE_OFFSET            = 0x02;
const u8 SPRITE_SIZE_OFFSET              = 0x04;
const u8 BG_TILE_MAP_SELECT_OFFSET       = 0x08;
const u8 BG_TILE_SET_SELECT_OFFSET       = 0x10;
const u8 WINDOW_ENABLE_OFFSET            = 0x20;
const u8 WINDOW_TILE_MAP_SELECT_OFFSET   = 0x40;
const u8 LCD_ENABLE_OFFSET               = 0x80;

enum GPU_MODE { HBLANK = 0, VBLANK = 1, OAM = 2, VRAM = 3 };

const u8 SPRITE_Y_OFFSET = 0x10;
const u8 SPRITE_X_OFFSET = 0x08;

struct sprite
{
    // first 3 bytes
    u8 y;
    u8 x;
    u8 tileNum;

    // last byte
    bool priority;
    bool yflip;
    bool xflip;
    bool palette;
};
     
// Struct for each pixel value including alpha
struct pixel
{
    u8 r;
    u8 g;
    u8 b;
	u8 a;

	pixel() {};
	pixel(u8 rv, u8 gv, u8 bv, u8 av) : r(rv), g(gv), b(bv), a(av) {}
	
};

class MMU; // Stub

class Display
{

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Texture* screen; 

    GPU_MODE activeMode; // 4 GPU modes
    int modeClock;       // counter for the GPU mode
   
    MMU* mmu; // reference for MMU, required for writing interrupt bytes

    int w, h;
    int pw, ph;
    int sizeMultiplier;

    // 2 display memory stores
    u8 vram[0x2000];    // Holds tiles and the tile maps
    u8 oam[0x100];      // Holds sprites (40?)

    // Default Palettes
	pixel fixedPalette[4];
    pixel bgPalette[4];
	pixel ob0Palette[4];
	pixel ob1Palette[4];

    u8 Tileset[384][8][8]; // 192 in DMG, CGB has 384
    sprite spriteStore[40];

    bool onlyTiles;

    // Display Registers
    u8 LCDC;        // 0xFF40
    u8 STAT;        // 0xFF41
    u8 scrollY;     // 0xFF42
    u8 scrollX;     // 0xFF43
    u8 LY;          // 0xFF44
    u8 LYC;         // 0xFF45

    u8 winX;        // 0xFF4A
    u8 winY;        // 0xFF4B

    SDL_Color pixels[DISPLAY_HEIGHT * DISPLAY_WIDTH]; // viewport region into the frame buffer

public:

    /*
        Initalises the display class
        Sets up SDL and palettes
    */
    Display();
    ~Display();

    /*
        Sets MMU reference in this class so it can be used
        For writing interrupts
        @Param mmu reference
    */
    void SetMMU(MMU* memManager);

    /*
        Intialises the display class
        creates: window, renderer, texture and pixel store

        @param screen size multiplier
    */
    void init(int multiplier);

    /*
        Sets pixel store to blank and update the screen
    */
    void clear();
    
    /*
        @Returns the currently active mode
    */
    GPU_MODE GetMode() { return activeMode; }

    /*
        maps a write to vram, updates tiles

        @param addr - address to write the byte to
        @param byte - byte to write
    */
    void WriteVram(u16 addr, u8 byte);

    /*
        fetches a value from vram

        @param addr - address to read byte from
        @returns - byte at the address
    */
    u8 ReadVram(u16 addr);


    /*
        writes the sprite to oam memory and calls the function to update the sprite

        @param addr - address to write to
        @param byte - byte to write
    */
    void WriteOAM(u16 addr, u8 byte);
    
    /*
        Read from OAM memory

        @param - addr to read from
        @returns - byte at the address
    */
    u8 ReadOAM(u16 addr);

    /*
        Load DMA_LENGTH number of bytes from the source address into the OAM store
        This uses the writeOAM function
        
        @Param - source to start reading from
    */
    void StartDMA(u16 source);

    // LCDC getter and setter
    u8 GetLCDC() { return LCDC; }
    void SetLCDC(u8 val) { LCDC = val; }

    // STAT getter and setter
    u8 GetStat() { return STAT; }
    void SetStat(u8 val) { STAT = val; }

    // SCX and SCY getter and setter
    u8 GetScrollX() { return scrollX; }
    u8 GetScrollY() { return scrollY; }
    void SetScrollX(u8 val);
    void SetScrollY(u8 val);

    // WINX and WINY getter and Setter
    u8 GetWinX() { return winX; }
    u8 GetWinY() { return winY; }
    void SetWinX(u8 val);
    void SetWinY(u8 val);

    // LY getter and LYC getter/setter
    u8 GetLY() { return LY; }
    u8 GetLYC() { return LYC; }
    void SetLYC(u8 val) { LYC = val; }

    /*
        Update BG palette
        @param value
    */
	void UpdateBGPalette(u8 value);

    /*
        Update OBJ (sprite) palette

        @param pal1 - which of the OBJ palettes is being updated
        @param value 
    */
	void UpdateOBPalette(bool pal1, u8 value);

    /*
        Step clock through the cycle and the various modes

        @param clock - Number of steps to take
    */
    void Step(int clock);
    
    /*
        copy and update screen surface
    */
    void Update();

    /*
        Toggle onlytiles bool on or off (changes if tiles are rendered or scanlines)
    */
	void ToggleTileView() { onlyTiles = !onlyTiles; }

private:

    /*
        Draw tiles to the screen
    */
    void DrawTiles();
    
    /*
        Renders in order:
        BG
        Window
        Sprite
    */
    void RenderScanline();

    /*
        Called at the end of every display->step()
        updates the STAT register values
    */
    void UpdateRegisters();

    /*
        Updates tiles in the tile store (called by VRAM writes)

        @param - addr of the tile to update
    */
    void UpdateTileset(u16 addr);

    /*
        
        @param oamAddr - address of sprite in the oam
        @param byte - byte containing the value being updated
                      could be any of the 4 bytes
    */
    void UpdateSprite(u16 oamAddr, u8 byte);
};


// Palette values
// Bit 7 - 6 - Shade for Color Number 3
// Bit 5 - 4 - Shade for Color Number 2
// Bit 3 - 2 - Shade for Color Number 1
// Bit 1 - 0 - Shade for Color Number 0

// Background layers
// - BG 0
// - BG 1
// - BG 2
// - BG 3
// - OBJ
// - WIN 0
// - WIN 1
// - OBJ WIN


/*
8000-87FF	Tile set #1: tiles 0-127
8800-8FFF	Tile set #1: tiles 128-255, Tile set #0: tiles -1 to -128 - OVERLAP
9000-97FF	Tile set #0: tiles 0-127
9800-9BFF	Tile map #0
9C00-9FFF	Tile map #1
*/


// FF40 - LCDC - LCD Control (R/W)
// Bit 7 - LCD Display Enable(0 = Off, 1 = On)
// Bit 6 - Window Tile Map Display Select(0 = 9800 - 9BFF, 1 = 9C00 - 9FFF)
// Bit 5 - Window Display Enable(0 = Off, 1 = On)
// Bit 4 - BG & Window Tile Data Select(0 = 8800 - 97FF, 1 = 8000 - 8FFF)
// Bit 3 - BG Tile Map Display Select(0 = 9800 - 9BFF, 1 = 9C00 - 9FFF)
// Bit 2 - OBJ(Sprite) Size(0 = 8x8, 1 = 8x16)
// Bit 1 - OBJ(Sprite) Display Enable(0 = Off, 1 = On)
// Bit 0 - BG Display(for CGB see below) (0 = Off, 1 = On)