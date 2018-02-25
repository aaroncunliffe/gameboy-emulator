#include "Display.h"
#include "MMU.h"

Display::Display()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) // SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER
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
    //winX = 0;
    //winY = 0;

    onlyTiles = false; // To show only tiles, if false, scanlines are rendered as normal
	

	// 4 shades of gray, default palette

	fixedPalette[0] = { 0xFF, 0xFF, 0xFF, 0xFF };
	fixedPalette[1] = { 0xC0, 0xC0, 0xC0, 0xFF };
	fixedPalette[2] = { 0x60, 0x60, 0x60, 0xFF };
	fixedPalette[3] = { 0x00, 0x00, 0x00, 0xFF };

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
	 SDL_Quit();
    
}

void Display::init(int multiplier)
{
    sizeMultiplier = multiplier;
    
    window = SDL_CreateWindow("Gameboy - Aaron Cunliffe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DISPLAY_WIDTH, DISPLAY_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); // Accelerated or software | Accelerated fails with Tamagotchi.gb?
    screen = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, DISPLAY_WIDTH, DISPLAY_HEIGHT); // STATIC or STREAMING - Also pixel format is ABGR


	//SDL_SetWindowGrab(window, SDL_TRUE);

    // Clear VRAM, Tileset and raw pixel store
    memset(vram, 0x00, 0x2000 * sizeof(u8));
    memset(oam, 0x00, 0x9F * sizeof(u8));
    memset(Tileset, 0x00, (384 * 8 * 8) * sizeof(u8));
    
    
    memset(pixels, 0x00000000, DISPLAY_WIDTH * DISPLAY_HEIGHT * sizeof(SDL_Color));

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
    u8 scanrow[DISPLAY_WIDTH]; // Store 1 complete row of pixels - for sprite drawing

    // Background render
    if (LCDC & BG_ENABLE_OFFSET)
    {
		u16 mapBaseAddress = (LCDC & BG_TILE_MAP_SELECT_OFFSET) ? 0x9C00 - VRAM_OFFSET : 0x9800 - VRAM_OFFSET; // Base address of the selected map
		u16 offsetBase = mapBaseAddress + ((((LY + scrollY) & 0xFF) / 8 ) * 32);

		// Above line declares the total offset from the base of VRAM, There are 32 bytes per line in the map.
		// Given any line, need to work out which block of 0x20 bytes we need from the map.

		u16 lineOffset = scrollX / 8;
		
        u16 y = (LY + scrollY) & 0x07;
		u16 x = scrollX & 0x07;

		pixel colour;

        // For each pixel in the current row
        for (u16 i = 0; i < DISPLAY_WIDTH; i++)
        {
			u16 tileIndex = vram[offsetBase + lineOffset];
			
			if ((LCDC & BG_TILE_SET_SELECT_OFFSET) == 0x00 && tileIndex < 128)
				tileIndex += 256; // if tile map #1 selected, the indexes are signed (-128 to 127 instead of 0 to 255)

            
			scanrow[i] = Tileset[tileIndex][y][x]; // Store this for the sprites
			colour = bgPalette[Tileset[tileIndex][y][x]];
            x++;


            pixels[(DISPLAY_WIDTH * LY) + i].r = colour.r;
            pixels[(DISPLAY_WIDTH * LY) + i].g = colour.g;
            pixels[(DISPLAY_WIDTH * LY) + i].b = colour.b;
            pixels[(DISPLAY_WIDTH * LY) + i].a = colour.a;
            
            // If one tile has been completed, reset X, increment the byte offset on the 32 byte line, to load the next tile
            if (x == 8)
            {
                x = 0;
                lineOffset++;
                lineOffset &= 0x1F;
            }


        }
    }
    

	// Render window, a static (non-scrolling) background that starts at winX, winY until the bottom right of the screen
	if (LCDC & WINDOW_ENABLE_OFFSET)
	{
		if (LY >= winY && LY <= DISPLAY_HEIGHT)
		{

			u16 mapBaseAddress = (LCDC & WINDOW_TILE_MAP_SELECT_OFFSET) ? 0x9C00 - VRAM_OFFSET : 0x9800 - VRAM_OFFSET; // Base address of the selected map
			u16 offsetBase = mapBaseAddress + ((((LY - winY) & 0xFF) / 8) * 32);

			// Above line declares the total offset from the base of VRAM, There are 32 bytes per line in the map.
			// Given any line, need to work out which block of 0x20 bytes we need from the map.

			u16 lineOffset = 0x00 / 8;

			u16 y = (LY - winY) & 0x07;
			u16 x = winX & 0x07;

			pixel colour;

			// For each pixel in the current row
			for (u16 i = winX; i < DISPLAY_WIDTH; i++)
			{
				u16 tileIndex = vram[offsetBase + lineOffset];

				if ((LCDC & BG_TILE_SET_SELECT_OFFSET) == 0x00 && tileIndex < 128)
					tileIndex += 256; // if tile map #1 selected, the indexes are signed (-128 to 127 instead of 0 to 255)

				colour = bgPalette[Tileset[tileIndex][y][x]];

				pixels[(DISPLAY_WIDTH * LY) + i].r = colour.r;
				pixels[(DISPLAY_WIDTH * LY) + i].g = colour.g;
				pixels[(DISPLAY_WIDTH * LY) + i].b = colour.b;
				pixels[(DISPLAY_WIDTH * LY) + i].a = colour.a;

				x++;
				// If one tile has been completed, reset X, increment the byte offset on the 32 byte line, to load the next tile
				if (x == 8)
				{
					x = 0;
					lineOffset++;
					lineOffset &= 0x1F;
				}


			}

		}
	}

    if (LCDC & SPRITE_ENABLE_OFFSET)
    {
        for (int i = 0; i < 40; i++)
        {
            sprite sprite = spriteStore[i]; // current sprite to be worked on


			u8 sixteenPixelSprite = LCDC & SPRITE_SIZE_OFFSET;
			u8 spriteYSize = sixteenPixelSprite ? 16 : 8;

            // Check if this sprite falls on this scanline
            if ((sprite.y - SPRITE_Y_OFFSET) <= LY && ((sprite.y - SPRITE_Y_OFFSET) + spriteYSize) > LY)
            {
                // Data for this horizontal line of the sprite
                u8 tilerow[8];

                
                u8 screenYOffset = (LY - (sprite.y - SPRITE_Y_OFFSET)); // Distance from LY that the sprite.y is (range 0-15);
                u8 tileOffset = screenYOffset >= 8 ? 1 : 0; // Whether the current line being drawn is of tile 1 or tile 2 (16 pixel mode)
                
                // if sprite.y flip, read from other end of the tile, 
                if (sprite.yflip)
                {
                    for (int i = 0; i < 8; i++) 
                    { 
                        tilerow[i] = Tileset[sprite.tileNum][(spriteYSize - 1) - (screenYOffset)][i]; 
                    }
                }
                else
                {
                    for (int i = 0; i < 8; i++) 
                    { 
                        tilerow[i] = Tileset[sprite.tileNum + tileOffset][screenYOffset % 8][i];
                    }
                }

                
                for (u8 x = 0; x < 8; x++)
                {
                    // If this pixel is still on-screen, AND
                    // if it's not colour 0 (transparent), AND
                    // if this sprite has priority OR shows under the bg
                    // then render the pixel

					// If the sprite is X-flipped write pixels in reverse order
					u8 index = sprite.xflip ? (7 - x) : x;

					int offset = (sprite.x - SPRITE_X_OFFSET) + x; // Need a signed value as tiles are "scrolled" in from off the screen

                    if (offset >= 0 && offset < DISPLAY_WIDTH && tilerow[index] != 0 && (!sprite.priority || scanrow[offset] == 0x00)) // !sprite.priority or sprite.prority??
                    {
                        pixel colour;
                        // Depending on sprite palette
                        if (sprite.palette)
                        	colour = ob1Palette[tilerow[index]];
                        else
                        	colour = ob0Palette[tilerow[index]];
                        
                        pixels[(DISPLAY_WIDTH * LY) + offset].g = colour.g;
						pixels[(DISPLAY_WIDTH * LY) + offset].r = colour.r;
						pixels[(DISPLAY_WIDTH * LY) + offset].b = colour.b;
						pixels[(DISPLAY_WIDTH * LY) + offset].a = colour.a;
                       
                        
                   }
                } // end for each pixel in the sprite
            }
        } // end for all 40 sprites 
    } 

	

    //SDL_UpdateTexture(screen, NULL, pixels, DISPLAY_WIDTH * sizeof(u32));
}

void Display::clear()
{
    memset(pixels, 0x00000000, DISPLAY_WIDTH * DISPLAY_HEIGHT * sizeof(u32));

    SDL_UpdateTexture(screen, NULL, pixels, DISPLAY_WIDTH * sizeof(u32));
    Update();
}


void Display::UpdateTileset(u16 addr)
{

    // 2 bytes per tile row, 8 tile rows, stored in 1 memory row from 0x0 to 0xF
    // From Memory Location 0x8000 to 0x9800
    

    // Work out which tile and row was updated
    u16 rowAddr = addr - VRAM_OFFSET; // Starts at 0x8000
    
    u16 tile = (rowAddr / 16); // Divide by 16, 16 bytes in a tile
    u16 y = (rowAddr / 2) & 0x07; // Get the row, Divide by 2, only need the first byte

    for (u8 x = 0; x < 8; x++)
    {
        // Find bit index for this pixel
		u8 rowIndex = 0x80 >> x;
		// 80, 40, 20, 10, 08, 04, 02, 01
        
        // Update tile data by combining 2 consecutive rows in VRAM, stored value is the index of the correct colour in the palette arrays
        u8 row1 = vram[(rowAddr & 0xFFFE)] & rowIndex;
        u8 row2 = vram[(rowAddr & 0xFFFE) + 1] & rowIndex; // Because it is + 1 we need to & FFFE to make sure it doesnt overflow into the next byte
        Tileset[tile][y][x] = (row1 ? 1 : 0) + (row2 ? 2 : 0);
    }
 

}

void Display::UpdateSprite(u16 oamAddr, u8 byte)
{
    u8 val = byte;
    u8 sprite = (oamAddr - OAM_START) / 4; 

    if (sprite < 40)
    {
        switch ((oamAddr - OAM_START) & 0x03) // 0-3 4 bytes per sprite data
        {
        case 0: // Y-coordinate
            spriteStore[sprite].y = val; // Decrementing comes later
			break;                         
                                           
        case 1: // X-coordinate            
            spriteStore[sprite].x = val; // Decrementing comes later
			break;

        case 2: // Data tile  
			spriteStore[sprite].tileNum = val; 
			break;

            
        case 3: // Options
            spriteStore[sprite].palette = (val & 0x10) ?  true : false;
            spriteStore[sprite].xflip = (val & 0x20) ?    true : false;
            spriteStore[sprite].yflip = (val & 0x40) ?    true : false;
            spriteStore[sprite].priority = (val & 0x80) ? true : false; // True - Below background, False - on top
            break;
        }
    }
}

// Fit as many tiles to the screen as possible
void Display::DrawTiles()
{
    for (int i = 0; i < (DISPLAY_HEIGHT / 8) * (DISPLAY_WIDTH / 8); i++) {
 
        for (int x = 0; x < 8; x++) {
            
            for (int y = 0; y < 8; y++) {
                pixels[(i * 8 % DISPLAY_WIDTH) + y + (x + i * 8 / DISPLAY_WIDTH * 8) * DISPLAY_WIDTH].r = bgPalette[Tileset[i][x][y]].r;
                pixels[(i * 8 % DISPLAY_WIDTH) + y + (x + i * 8 / DISPLAY_WIDTH * 8) * DISPLAY_WIDTH].g = bgPalette[Tileset[i][x][y]].g;
                pixels[(i * 8 % DISPLAY_WIDTH) + y + (x + i * 8 / DISPLAY_WIDTH * 8) * DISPLAY_WIDTH].b = bgPalette[Tileset[i][x][y]].b;
				pixels[(i * 8 % DISPLAY_WIDTH) + y + (x + i * 8 / DISPLAY_WIDTH * 8) * DISPLAY_WIDTH].a = bgPalette[Tileset[i][x][y]].a;
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
        if( addr < 0x9800) // Make sure write to VRAM is definitely writing to tiles and not the tilemap
            UpdateTileset(addr);
    //}
    //else
    //{
    //    int stop = 0;
    //}

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


// At the end of every display->Step() process any changes to the display registers
void Display::UpdateRegisters()
{

    // STAT

	// Bits 0-1
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
	
	// Bit 2
	if (LY == LYC)
	{
		STAT |= 0x04;
        if (STAT & 0x40) // Bit 6
        {
          u8 byte = mmu->ReadByte(0xFF0F);
          mmu->WriteByte(0xFF0F, byte |= 0x02); // Write for LY == LYC 
        }
		
	}
    else
    {
        STAT &= ~0x04;
    }



	// Bit 4






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

            if (LY == DISPLAY_HEIGHT)
            {
                // Enter vblank
                activeMode = VBLANK;
                
				STAT |= 0x10;

				//u8 byte = mmu->ReadByte(0xFF0F);
				//mmu->WriteByte(0xFF0F, byte |= 0x02); // Write for V-Blank

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

				//STAT |= 0x02;
				//
				//u8 byte = mmu->ReadByte(0xFF0F);
				//mmu->WriteByte(0xFF0F, byte |= 0x02); // Write for V-Blank
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

			//STAT |= 0x08;
			//u8 byte = mmu->ReadByte(0xFF0F);
			//mmu->WriteByte(0xFF0F, byte |= 0x02); // Write for V-Blank

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

	SDL_UpdateTexture(screen, NULL, pixels, DISPLAY_WIDTH * sizeof(SDL_Colour));

    SDL_RenderCopy(renderer, screen, NULL, NULL); // Puts the texture onto the screen
    SDL_RenderPresent(renderer);
}

void Display::SetScrollX(u8 val)
{
    scrollX = val;
}

void Display::SetScrollY(u8 val)
{
    scrollY = val;
}

void Display::SetWinX(u8 val)
{
    // Make sure that winX doesn't get set below 0.
    // otherwise it will wrap round and be shown off the screen.
    // This was found in Zelda
    if (((s16)winX - 7) < 0x00)
    {
        winX = 0x00;
    }
    else
    {
        winX = val - 7;

    }

        
}

void Display::SetWinY(u8 val)
{
    if (val < DISPLAY_HEIGHT)
    {
      winY = val;
    }
    
}



void Display::StartDMA(u16 source)
{
    for (int i = 0; i < DMA_LENGTH; i++)
    {
        WriteOAM(OAM_START + i, mmu->ReadByte(source + i));
    }
}


// Palette values
// Bit 7 - 6 - Shade for Color Number 3
// Bit 5 - 4 - Shade for Color Number 2
// Bit 3 - 2 - Shade for Color Number 1
// Bit 1 - 0 - Shade for Color Number 0

void Display::UpdateBGPalette(u8 value)
{
	for (int i = 0; i < 4; i++)
	{
		u8 halfNibble = value >> i * 2; // Shift to get 2 bits at a time
		u8 index = halfNibble & 0x03;	// Select only the first 2 bits.

		bgPalette[i] = fixedPalette[index];
			
	}
}

void Display::UpdateOBPalette(bool pal1, u8 value)
{
	for (int i = 0; i < 4; i++)
	{
		u8 halfNibble = value >> i * 2; // Shift to get 2 bits at a time
		u8 index = halfNibble & 0x03;	// Select only the first 2 bits.
		
		pal1 ? ob1Palette[i] = fixedPalette[index] : ob0Palette[i] = fixedPalette[index];

	}
}

