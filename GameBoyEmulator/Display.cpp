#include "display.h"
#include "MMU.h"

Display::Display()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "ERROR Initializing" << std::endl;
    }

    memset(vram, 0x00, 0x2000 * sizeof(u8));

    memset(Tileset, 0x00, (384 * 8 * 8) * sizeof(u8));

    window = NULL;
    renderer = NULL;
    screen = NULL;
    w = DISPLAY_WIDTH;
    h = DISPLAY_HEIGHT;
    pw = 1;
    ph = 1;

    viewport.w = VIEWPORT_WIDTH;
    viewport.h = VIEWPORT_HEIGHT;

    scrollX = 0;
    scrollY = 0;
   
    // 4 shades of gray, default palette
    pixelPalette[0] = { 0xFF, 0xFF, 0xFF, 80 };
    pixelPalette[1] = { 0xC0, 0xC0, 0xC0, 80 };
    pixelPalette[2] = { 0x60, 0x60, 0x60, 80 };
    pixelPalette[3] = { 0x00, 0x00, 0x00, 00 };
}

void Display::SetMMU(MMU* mem)
{
    mmu = mem;
}

Display::~Display()
{
    SDL_DestroyTexture(screen);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
}

void Display::init(int multiplier)
{
    sizeMultiplier = multiplier;
    w = VIEWPORT_WIDTH * multiplier;
    h = VIEWPORT_HEIGHT * multiplier;
    pw = w / VIEWPORT_WIDTH;
    ph = h / VIEWPORT_HEIGHT;

    window = SDL_CreateWindow("Gameboy - Aaron Cunliffe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

    if (renderer == NULL)
    {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    }

    screen = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, VIEWPORT_WIDTH, VIEWPORT_HEIGHT); // SDL_TEXTURE_STATIC
    

    memset(pixels, 0x00000000, VIEWPORT_WIDTH * VIEWPORT_HEIGHT * sizeof(Uint32));

    memset(Tileset, 0x00, 384 * 8 * 8 * sizeof(u8));

    SDL_UpdateTexture(screen, NULL, pixels, VIEWPORT_WIDTH * sizeof(Uint32));
    Update();

    activeMode = OAM;
    currentLine = 0;
    modeClock = 0;

    
}

void Display::RenderScanline()
{
    //Tile map #0 - BIOS uses this, so it's a good place to start.
    uint16_t tilemapbase = (mmu->ReadByte(0xFF40) & BG_TILE_MAP_SELECT_OFFSET) >> BG_TILE_MAP_SELECT_BIT ? 0x1C00 : 0x1800;
    uint16_t offsetbase = tilemapbase + ((((currentLine + scrollY) & 255) >> 3) << 5);
    uint8_t x, y, tindex;

    y = (currentLine + scrollY) & 7;

    for (x = 0; x < 160; x++)
    {
        tindex = vram[offsetbase + (x / 8)];

        pixels[VIEWPORT_WIDTH * currentLine + y].a = pixelPalette[Tileset[tindex][y][x % 8]].a;
        pixels[VIEWPORT_WIDTH * currentLine + x].r = pixelPalette[Tileset[tindex][y][x % 8]].r;
        pixels[VIEWPORT_WIDTH * currentLine + x].g = pixelPalette[Tileset[tindex][y][x % 8]].g;
        pixels[VIEWPORT_WIDTH * currentLine + x].b = pixelPalette[Tileset[tindex][y][x % 8]].b;
    }
    SDL_UpdateTexture(screen, NULL, pixels, VIEWPORT_WIDTH * sizeof(Uint32));
}

void Display::clear()
{
    memset(pixels, 0x00000000, VIEWPORT_WIDTH * VIEWPORT_HEIGHT * sizeof(Uint32));
}

void Display::SetScrollX(u8 val) 
{ 
    scrollX = val;
}

void Display::SetScrollY(u8 val) 
{ 
    scrollY = val;
}

void Display::UpdateTileset(u16 addr)
{
    // Work out which tile and row was updated
    u16 addrtrans = addr & 0x1FFE; // Starts at 0x8001

    //u16 addrtrans = addr & 0x1FFE;
    u16 tile = (addrtrans >> 4); // Divide by 16, 16 bytes in a tile
    u16 y = (addrtrans >> 1) & 0x07; // Get the row, Divide by 2, only need the first byte

    u8 rowIndex;
    for (u8 x = 0; x < 8; x++)
    {
        // Find bit index for this pixel
        rowIndex = 0x01 << (0x07 - x);
        
        // Update tile data by combining 2 consecutive rows in VRAM, stores the index of the colour stored in the background pallete array
        u8 row1 = (vram[addrtrans] & rowIndex);
        u8 row2 = (vram[addrtrans + 1] & rowIndex);
        Tileset[tile][y][x] = (row1 ? 1 : 0) + (row2 ? 2 : 0);
    }
    
}

void Display::Draw()
{
    /*int i;
    for (i = 0; i < (144 / 8) * (160 / 8); i++) {
        int x;
        for (x = 0; x < 8; x++) {
            int y;
            for (y = 0; y < 8; y++) {
                pixels[(i * 8 % 160) + y + (x + i * 8 / 160 * 8) * 160].r = pixelPalette[Tileset[i][x][y]].r;
                pixels[(i * 8 % 160) + y + (x + i * 8 / 160 * 8) * 160].g = pixelPalette[Tileset[i][x][y]].g;
                pixels[(i * 8 % 160) + y + (x + i * 8 / 160 * 8) * 160].b = pixelPalette[Tileset[i][x][y]].b;
            }
        }
    }*/

    
}

void Display::WriteByte(u16 addr, u8 byte)
{
    vram[addr - VRAM_OFFSET] = byte;
    UpdateTileset(addr);
}

u8 Display::ReadByte(u16 addr)
{
    return vram[addr - VRAM_OFFSET];
}

void Display::Process()
{
    //Draw();
   
}

void Display::UpdateRegisters()
{
    // LCDC
    switch (activeMode)
    {
    case HBLANK:
        STAT &= ~0x03;
        break;
    case VBLANK:
        STAT &= ~0x03;
        STAT |=  0x01;
        break;
    case OAM:
        STAT &= ~0x03;
        STAT |= 0x02;
        break;
    case VRAM:
        STAT &= ~0x03;
        STAT |= 0x03;
        break;
    }

    // STAT

}

void Display::Step(u32 clock)
{
    modeClock += clock;

#ifdef _LOG
    //std::cout << modeClock << std::endl;
#endif // _LOG

    switch (activeMode)
    {

    case HBLANK: // 0
        if (modeClock >= 204)
        {
            modeClock = 0;
            currentLine++;

            if (currentLine == 143)
            {
                // Enter vblank
                activeMode = VBLANK;
                
                // Put image on screen here
                Draw();
                Update();

                u8 byte = mmu->ReadByte(0xFF0F);
                mmu->WriteByte(0xFF0F, byte |= 0x01);
            }
            else
            {
                activeMode = OAM;
            }
        }
        break;

    case VBLANK: // 1
        if (modeClock >= 456)
        {
            modeClock = 0;
            currentLine++;

            if (currentLine > 153)
            {
                // Restart scanning modes
                activeMode = OAM;
                currentLine = 0;
            }
        }
        break;

    case OAM: // 2
        if (modeClock >= 80)
        {
            // Enter scanline mode 3
            modeClock = 0;
            activeMode = VRAM;
        }
        break;

    case VRAM: // 3
        if (modeClock >= 172)
        {
            // Enter hblank
            modeClock = 0;
            activeMode = HBLANK;

            // Write a scanline to the framebuffer
            RenderScanline();
        }
        break;
    }

    UpdateRegisters();
}


void Display::Update()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, screen, NULL, NULL); // Puts the texture onto the screen
    //SDL_RenderCopyEx(renderer, screen, NULL, &viewport, 0.0, NULL, SDL_FLIP_NONE);

    

    SDL_RenderPresent(renderer);
}