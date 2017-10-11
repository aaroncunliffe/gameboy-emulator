#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>

#include "Definitions.h"
#include "Cartridge.h"
#include "ROM.h"
#include "Display.h"
#include "Joypad.h"



//const u16 EIGHT_KB = 0x2000;
//const u16 SIXTEEN_KB = 0x4000;

const u16 INTERNAL_RAM_START = 0xC000;
//const u16 OAM_START = 0xFE00;
const u16 IOREG_START = 0xFF00;
const u16 HRAM_START = 0xFF80;


// Memory management unit, redirects requests for memory to the correct location according to the map
// Total addressable memory 0000 - FFFF 
class MMU
{

private:
	
    Cartridge* cart;

    char* romPath;
    u32 romSize;


    
    
    u8 internalRam[SIXTEEN_KB];             // 1 bank in GB 1-7 banks in GBC
    u8 IORegs[0x80];
    u8 hram[0x7F];
    u8 IEReg; 
   

    u8 bios[0x100];
    
    bool biosComplete;

    Display* display;
	Joypad* joypad;


public:

    MMU();

    /*
        Constructor for MMU (Memory management unit) sets active banks to default.

        @param pointer to Display object - Needed for reading/writing to display memory and registers
        @param pointer to Joypad object - Needed so CPU can read joypad data
    */
    MMU(Display* d, Joypad* j);

    ~MMU();


    /*
        Loads each byte from a binary file into the array for the ROM file
        returns false if the file is not found or the file size is too large.
        Handles placing the ROM file into "banks" just as it would be in the cartridge.
        Creates a Cartridge object and passes it a pointer to the first ROM bank
        so that it can extract header data.

        @param  character array of the path of the binary bios file
        @return boolean identifying success or failure of the file read operation
    */
    bool LoadRom(char* path);

    /*
        Loads each byte from a binary file into a fixed size array of 0x100.
        returns false if the file is not found or the file size is too large.

        @param  character array of the path of the binary bios file
        @return boolean identifying success or failure of the file read operation
    */
    bool LoadBios(char* path);

    /*
        Read byte from the correct location in the memory map.
        This can be direct reads from the data stores or calling other methods
        such as Getters.

        @param  2 byte address
        @return 1 byte value
    */
    u8 ReadByte(u16 addr);

    /*
        Read two bytes to memory by using 2 individual Read operations
        and combines them into a two byte value using bitwise OR

        @param  2 byte address of the first byte to be read
        @return Two byte value
    */
    u16 ReadTwoBytes(u16 addr);

    /*
        Writes byte to the correct location in the memory map.
        This can be direct writes to the data stores or calling other methods
        such as Setters.

        @param  2 byte address
        @param  1 byte value to be written
    */
    void WriteByte(u16 addr, u8 data);

    /*
        Write two bytes to memory by using 2 individual write operations

        @param  The 2 byte address where the first byte will be written
        @param  2 byte value to be written
    */
    void WriteTwoBytes(u16 addr, u16 data);

    /*
        A function that decrements the stack pointer by 2 then
        writes two bytes of data to the location it is pointing at.

        @param  Reference to stack pointer
        @return 2 byte value
    */
    void PushTwoBytes(u16 &sp, u16 data);

    /*
        A function that returns 2 bytes of data at the location
        of the stack pointer, then increments the stack pointer by 2.

        @param  Reference to stack pointer
        @return 2 byte value
    */
    u16 PopTwoBytes(u16 &sp);



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