#pragma once


#include <iostream>

#include "Definitions.h"

// Each cartridge has a header of information at offset 0100-014F

const u16 romGraphicOffset =        0x104;      // 0104 - 0133 - Length of 30
const u16 gameTitleOffset =         0x134;      // 0134 - 0142 - length of F, padded with 0's
const u16 gameboyByteOffset =       0x143;      // 0x00 GB, 0x80 Supports GBC functions but works on old GB, 0xC0 GBC only
const u16 licenseOffset =           0x144;      // 0144 - 0145 - Length 2,
const u16 superGameboyOffset =      0x146;      // Whether supergameboy functions are enabled
const u16 cartridgeTypeOffset =     0x147;      //
const u16 romSizeOffset =           0x148;      //
const u16 ramSizeOffset =           0x149;      //
const u16 destinationCodeOffset =   0x14A;      // 0 = Japanese, 1 = non-Japanese
const u16 licenseCodeOffset =       0x14B;      //
const u16 romVersionOffset =        0x14C;      //

// Also have complement check and checksum.



class Cartridge
{
private:

    // 30 bytes to be compared with the version on the rom
    const u8 ORIGINAL_GRAPHIC[0x30] =
    {
        0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D,
        0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E, 0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99,
        0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC, 0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E
    };

    u8* romHeader;
    
    bool graphicMatch;
    char* title;
    u8 gameboyByte;
    u8 licenseeCodeByte;
    u8 cartridgeTypeByte;
    u8 romSizeByte;
    u8 ramSizeByte;
    u8 destinationCode;


public:

    Cartridge();
    Cartridge(u8* data);
    ~Cartridge();

    void PrintFormattedData();

private:

    void ReadTitle();
    void CompareGraphics();
    void ParseHeader();
    

};