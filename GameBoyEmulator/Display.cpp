#include "Display.h"
#include "MMU.h"

Display::Display()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    }

    window = NULL;
    renderer = NULL;
    screen = NULL;
    w = DISPLAY_WIDTH;
    h = DISPLAY_HEIGHT;
    pw = 1;
    ph = 1;

    scrollX = 0;
    scrollY = 0;

    onlyTiles = false; // To show only tiles, if false, scanlines are rendered as normal
	
    // 4 shades of gray, default palette
    bgPalette[0]  = { 0xFF, 0xFF, 0xFF, 0xFF };
    bgPalette[1]  = { 0xC0, 0xC0, 0xC0, 0xFF };
    bgPalette[2]  = { 0x60, 0x60, 0x60, 0xFF };
	bgPalette[3]  = { 0x00, 0x00, 0x00, 0xFF };
	
	ob0Palette[0] = { 0xFF, 0xFF, 0xFF, 0x80 };
	ob0Palette[1] = { 0xC0, 0xC0, 0xC0, 0x80 };
	ob0Palette[2] = { 0x60, 0x60, 0x60, 0x80 };
	ob0Palette[3] = { 0x00, 0x00, 0x00, 0x80 };

	ob1Palette[0] = { 0xFF, 0xFF, 0xFF, 0x80 };
	ob1Palette[1] = { 0xC0, 0xC0, 0xC0, 0x80 };
	ob1Palette[2] = { 0x60, 0x60, 0x60, 0x80 };
	ob1Palette[3] = { 0x00, 0x00, 0x00, 0x80 };

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
    w = DISPLAY_WIDTH;
    h = DISPLAY_HEIGHT;

    window = SDL_CreateWindow("Gameboy - Aaron Cunliffe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); // Accelerated or software
    screen = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, DISPLAY_WIDTH, DISPLAY_HEIGHT); // STATIC or STREAMING - Also pixel format is ABGR


	//SDL_SetWindowGrab(window, SDL_TRUE);

    // Clear VRAM, Tileset and raw pixel store
    memset(vram, 0x00, 0x2000 * sizeof(u8));
    memset(oam, 0x00, 0x9F * sizeof(u8));
    memset(Tileset, 0x00, (384 * 8 * 8) * sizeof(u8));
    //memset(pixels, 0x00000000, DISPLAY_WIDTH * DISPLAY_HEIGHT * sizeof(u32));

	//SDL_SetTextureBlendMode(screen, SDL_BLENDMODE_MOD);
    //SDL_UpdateTexture(screen, NULL, pixels, DISPLAY_WIDTH * sizeof(u32));
    //Update();

    activeMode = OAM;
    LY = 0;
    modeClock = 0;
    SDL_SetWindowSize(window, DISPLAY_WIDTH * multiplier, DISPLAY_HEIGHT * multiplier);
}

void Display::RenderScanline()
{
    u8 scanrow[160]; // 1 complete row of pixels

    // Background render
    if (LCDC & BG_ENABLE_OFFSET)
    {
        u16 tilemapbase = (LCDC & BG_TILE_MAP_SELECT_OFFSET) ? 0x1C00 : 0x1800;
        u16 offsetbase = tilemapbase + ((((LY + scrollY) & 255) >> 3) << 5);
        u16 x, y, tileIndex;

        y = (LY + scrollY) & 7;


		pixel colour;

        for (x = 0; x < 160; x++)
        {
            tileIndex = vram[offsetbase + (x / 8)];
			scanrow[x] = Tileset[tileIndex][y][x % 8];


			if ((LCDC & BG_TILE_SET_SELECT_OFFSET) == 0x00 && tileIndex < 128)
				tileIndex += 256; // if tile map #1 selected, the indexes are signed (-128 to 127 instead of 0 to 255)

			colour = bgPalette[Tileset[tileIndex][y][x % 8]];

            pixels[DISPLAY_WIDTH * LY + x].r = colour.r;
            pixels[DISPLAY_WIDTH * LY + x].g = colour.g;
            pixels[DISPLAY_WIDTH * LY + x].b = colour.b;
            pixels[DISPLAY_WIDTH * LY + x].a = colour.a;
        }
    }

    if (LCDC & SPRITE_ENABLE_OFFSET)
    {

        for (int i = 0; i < 40; i++)
        {
            sprite sprite = spriteStore[i];

            // Check if this sprite falls on this scanline
            if (sprite.y <= LY && (sprite.y + 8) > LY)
            {
                // Data for this line of the sprite
                u8 tilerow[8];

                // If the sprite is Y-flipped,
                // use the opposite side of the tile
                if (sprite.yflip)
                {
                    for (int i = 0; i < 8; i++) { tilerow[i] = Tileset[sprite.tileNum][7 - (LY - sprite.y)][i]; }
                }
                else
                {
                    for (int i = 0; i < 8; i++) { tilerow[i] = Tileset[sprite.tileNum][(LY - sprite.y)][i]; }
                }

                pixel colour;
                
                for (int x = 0; x < 8; x++)
                {
                    // If this pixel is still on-screen, AND
                    // if it's not colour 0 (transparent), AND
                    // if this sprite has priority OR shows under the bg
                    // then render the pixel

					// If the sprite is X-flipped write pixels in reverse order
					int index = sprite.xflip ? (7 - x) : x;

                    if ((sprite.x + x) >= 0 && (sprite.x + x) < 160 && tilerow[index] && (!sprite.priority || !scanrow[sprite.x + x])) // !sprite.priority or sprite.prority??
                    {
						if (sprite.palette)
							colour = ob1Palette[tilerow[index]];
						else
							colour = ob0Palette[tilerow[index]];


						pixels[DISPLAY_WIDTH * LY + sprite.x + x].r = colour.r; 
                        pixels[DISPLAY_WIDTH * LY + sprite.x + x].g = colour.g;	  
                        pixels[DISPLAY_WIDTH * LY + sprite.x + x].b = colour.b;	  
                        pixels[DISPLAY_WIDTH * LY + sprite.x + x].a = colour.a;	  
                   }
                }
            }
        }
    }        
    
   
    //SDL_UpdateTexture(screen, NULL, pixels, DISPLAY_WIDTH * sizeof(u32));
}

void Display::clear()
{
    memset(pixels, 0x00000000, DISPLAY_WIDTH * DISPLAY_HEIGHT * sizeof(u32));

    SDL_UpdateTexture(screen, NULL, pixels, DISPLAY_WIDTH * sizeof(u32));
    Update();
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
    u16 tile = (addrtrans >> 4) & 511; // Divide by 16, 16 bytes in a tile
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

void Display::UpdateSprite(u16 oamAddr, u8 byte)
{
    u8 val = byte;
    u8 sprite = (oamAddr - OAM_START) >> 2;

    if (sprite < 40)
    {
        switch ((oamAddr - OAM_START) & 3)
        {
            // Y-coordinate
        case 0: 
			spriteStore[sprite].y = val - 16;
			break;

            // X-coordinate
        case 1:  
			spriteStore[sprite].x = val - 8; 
			break;

            // Data tile
        case 2:  
			spriteStore[sprite].tileNum = val; 
			break;

            // Options
        case 3:
            spriteStore[sprite].palette = (val & 0x10) ?  true : false;
            spriteStore[sprite].xflip = (val & 0x20) ?    true : false;
            spriteStore[sprite].yflip = (val & 0x40) ?    true : false;
            spriteStore[sprite].priority = (val & 0x80) ? true : false; // True - Below background, False - on top
            break;
        }
    }
}

void Display::DrawTiles()
{
    
    int i;
    for (i = 0; i < (144 / 8) * (160 / 8); i++) {
        int x;
        for (x = 0; x < 8; x++) {
            int y;
            for (y = 0; y < 8; y++) {
                pixels[(i * 8 % 160) + y + (x + i * 8 / 160 * 8) * 160].r = bgPalette[Tileset[i][x][y]].r;
                pixels[(i * 8 % 160) + y + (x + i * 8 / 160 * 8) * 160].g = bgPalette[Tileset[i][x][y]].g;
                pixels[(i * 8 % 160) + y + (x + i * 8 / 160 * 8) * 160].b = bgPalette[Tileset[i][x][y]].b;
            }
        }
    }
    //SDL_UpdateTexture(screen, NULL, pixels, DISPLAY_WIDTH * sizeof(Uint32));

    
}

void Display::WriteVram(u16 addr, u8 byte)
{
    //if (activeMode != VRAM)
    //{
        vram[addr - VRAM_OFFSET] = byte;
        if( addr < 0x9800)
            UpdateTileset(addr);
    //}
    //else
    //{
    //    int stop = 0;
    //}


        if (vram[0x99A4 - VRAM_OFFSET] == 0x60 && vram[0x99E4 - VRAM_OFFSET] == 0x60)
        {
            int stop = 0;
        }
}

u8 Display::ReadVram(u16 addr)
{
    if (activeMode != VRAM)
    {
        return vram[addr - VRAM_OFFSET];
    }
    return 0xFF;
}

void Display::WriteOAM(u16 addr, u8 byte)
{
    if (activeMode != OAM && activeMode != VRAM)
    {
        oam[addr - OAM_START] = byte;
        UpdateSprite(addr, byte);
    }
  
}

u8 Display::ReadOAM(u16 addr)
{
    if (activeMode != OAM && activeMode != VRAM)
    {
        return oam[addr - OAM_START];
    }
    return 0xFF;
}

void Display::ProcessSprites()
{
    //for (int i = 0; i < 160; i++)
    //{
    //    u8 val = ReadOAM(OAM_START + i);
    //    u8 sprite = (OAM_START + i) >> 2;


    //    if (sprite < 40)
    //    {
    //        switch ((OAM_START + i) & 3)
    //        {
    //            // Y-coordinate
    //        case 0: spriteStore[sprite].y = val - 16; break;

    //            // X-coordinate
    //        case 1:  spriteStore[sprite].x = val - 8; break;

    //            // Data tile
    //        case 2:  spriteStore[sprite].tileNum = val; break;

    //            // Options
    //        case 3:
    //            spriteStore[sprite].palette = (val & 0x10) ? true : false;
    //            spriteStore[sprite].xflip = (val & 0x20) ? true : false;
    //            spriteStore[sprite].yflip = (val & 0x40) ? true : false;
    //            spriteStore[sprite].priority = (val & 0x80) ? true : false;
    //            break;
    //        }
    //    }
    //}
    
}

// At the end of every display->Step() process any changes to the display registers
void Display::UpdateRegisters()
{
    // LCDC
    

    // STAT
    switch (activeMode)
    {
    case HBLANK:
        STAT &= ~0x03;
        break;
    case VBLANK:
        STAT &= ~0x03;
        STAT |= 0x01;
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
            LY++;

            if (LY == 143)
            {
                // Enter vblank
                activeMode = VBLANK;
                
                // Put image on screen here
                if(onlyTiles)
                    DrawTiles();

                Update();

                u8 byte = mmu->ReadByte(0xFF0F);
                mmu->WriteByte(0xFF0F, byte |= 0x01); // Write for V-Blank
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
            LY++;

            if (LY > 153)
            {
                // Restart scanning modes
                activeMode = OAM;
                LY = 0;
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
            if (!onlyTiles)
                RenderScanline();
        }
        break;
    }

    UpdateRegisters();
}

// Clear copy update screen surface
void Display::Update()
{
    //SDL_RenderClear(renderer);

	SDL_UpdateTexture(screen, NULL, pixels, DISPLAY_WIDTH * sizeof(u32));

    SDL_RenderCopy(renderer, screen, NULL, NULL); // Puts the texture onto the screen
    SDL_RenderPresent(renderer);
}


void Display::StartDMA(u16 source)
{
    for (int i = 0; i < DMA_LENGTH; i++)
    {
        WriteOAM(OAM_START + i, mmu->ReadByte(source + i));
    }
}


void Display::UpdateBGPalette(u8 value)
{
	for (int i = 0; i < 4; i++)
	{
		switch ((value >> (i * 2)) & 3) {
		case 0:
			bgPalette[i] = { 0xFF, 0xFF, 0xFF, 0xFF };
			break;
		case 1:
			bgPalette[i] = { 0xC0, 0xC0, 0xC0, 0xFF };
			break;
		case 2:
			bgPalette[i] = { 0x60, 0x60, 0x60, 0xFF };
			break;
		case 3:
			bgPalette[i] = { 0x00, 0x00, 0x00, 0xFF };
			break;
		}
			
	}
}

void Display::UpdateOBPalette(bool pal1, u8 value)
{
	for (int i = 0; i < 4; i++)
	{
		switch ((value >> (i * 2)) & 3) {
		case 0:
			pal1 ? ob1Palette[i] = { 0xFF, 0xFF, 0xFF, 0xFF } : ob0Palette[i] = { 0xFF, 0xFF, 0xFF, 0xFF };
			break;
		case 1:
			pal1 ? ob1Palette[i] = { 0xC0, 0xC0, 0xC0, 0xFF } : ob0Palette[i] = { 0xC0, 0xC0, 0xC0, 0xFF };
			break;
		case 2:
			pal1 ? ob1Palette[i] = { 0x60, 0x60, 0x60, 0xFF } : ob0Palette[i] = { 0x60, 0x60, 0x60, 0xFF };
			break;
		case 3:
			pal1 ? ob1Palette[i] = { 0x00, 0x00, 0x00, 0xFF } : ob0Palette[i] = { 0x00, 0x00, 0x00, 0xFF };
			break;
		}

	}
}