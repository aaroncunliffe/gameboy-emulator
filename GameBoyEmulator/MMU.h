#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>

#include "Definitions.h"
#include "Cartridge.h"
#include "Display.h"
#include "Joypad.h"


const u32 MAX_ROM_SIZE = 0x7A1200; // 8 MB
const u16 ONE_BANK_SIZE = 0x4000;

const u8 NUM_VRAM_BANKS = 2;
const u16 NUM_ROM_BANKS = 0x300;

const u16 EIGHT_KB = 0x2000;
const u16 SIXTEEN_KB = 0x4000;


const u16 EXTERNAL_RAM_START = 0xA000;
const u16 INTERNAL_RAM_START = 0xC000;
//const u16 OAM_START = 0xFE00;
const u16 IOREG_START = 0xFF00;
const u16 HRAM_START = 0xFF80;


// Memory management unit, redirects requests for memory to the correct location according to the map
// Total addressable memory 0000 - FFFF 
class MMU
{
public:
    Cartridge* cart;

private:
    char* romPath;
    u32 romSize;


    u8 activeRomBank;
    u16 numberOfRomBanks;

    u8 activeExternalRamBank;
    u16 numberOfExternalRamBanks;
    
    
    u8 externalRam[1][EIGHT_KB];            // 8k external ram
    u8 internalRam[SIXTEEN_KB];             // 1 bank in GB 1-7 banks in GBC
    u8 IORegs[0x80];
    u8 hram[0x80];
   

    u8 bios[0x100];
    u8 rom[NUM_ROM_BANKS][SIXTEEN_KB];      // up to 0x200 16kb banks ~ 8MB max rom size
    
    bool biosComplete;

    Display* display;
	Joypad* joypad;


public:

    MMU();
    MMU(Display* d, Joypad* j);
    ~MMU();

    bool LoadRom(char* path);
    bool MMU::LoadBios(char* path);

    u8 ReadByte(u16 addr);
    u16 ReadTwoBytes(u16 addr);
    
    void PushTwoBytes(u16 &sp, u16 data);
    u16 PopTwoBytes(u16 &sp);

    void WriteByte(u16 addr, u8 data);
    void WriteTwoBytes(u16 addr, u16 data);


    void SetBiosComplete(bool val) { biosComplete = val; }
    bool GetBiosComplete() { return biosComplete; }

    void DumpToFile();
    void WriteSaveFile();

private:


};

/* 
  ----- Memory Structure (top down) -----

       ------------------------------
       Interupts Enable Registers (IE)
       ------------------------------   FFFF
       ------------------------------   FFFE
       High RAM (HRAM) 0x7E (126 Bytes)
       ------------------------------   FF80
       ------------------------------   FF7F
       I/O Registers 0x7F (127 Bytes)
       ------------------------------   FF00
       ------------------------------   FEFF ----
       Not Usable - 60 (96 Bytes)                |
       ------------------------------   FEA0     |
       ------------------------------   FE9F     | = 0xFF (255 Bytes)
       Sprite attribute table (OAM)              |
       Size: 0x9F (159 Bytes)                    |
       ------------------------------   FE00 ----
       ------------------------------   FDFF
       Mirror of C000-DDFF (ECHO)
       Generally not used
       ------------------------------   E000
       ------------------------------   DFFF
       8kB internal ram
       D000-DFFF switchable in GBC
       0x01 - 0x07 select bank 1-7
       Select Byte - 0xFF70
       ------------------------------   C000
       ------------------------------   BFFF
       8kB external RAM
       In cartridge, can be switcable
       ------------------------------   A000  
       ------------------------------   9FFF
       8kB VRAM (8kB GB, 16kB GBC)
       Switchable bank 0/1 if GBC
       ------------------------------   8000 
       ------------------------------   7FFF ----
       16kB switchable ROM bank                  |
       01-NN                                     |                                             
       ------------------------------   4000     | = 32kB Cartrigbe
       ------------------------------   3FFF     |
       16kB ROM bank #0 |                        |
       ------------------------------   0000 ----




*/