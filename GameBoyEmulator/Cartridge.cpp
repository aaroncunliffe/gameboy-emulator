#include "Cartridge.h"



Cartridge::Cartridge()
{

}


Cartridge::Cartridge(u8* data)
{
    romHeader = data;

}


Cartridge::~Cartridge()
{

}

// Reads the title from 0x134 - 0x142 in the header and stores it in a char*
void Cartridge::ReadTitle()
{
    u16 offset = gameTitleOffset;
    u8 titleOffset = 0;
    title = new char[0xF]; // max length 15 bytes

    while (romHeader[offset] != 0x00) // the section is padded with 0's if title is shorter than the space
    {
        char character = romHeader[offset];
        title[titleOffset] = character;
        offset++;
        titleOffset++;
    }
    title[titleOffset] = '\0'; // Manually add the null terminating character to trim the 00's

}

// Compares graphic on the ROM to the known correct graphic
void Cartridge::CompareGraphics()
{
    for (int i = 0; i < 0x30; ++i)
    {
        if (romHeader[i + romGraphicOffset] != ORIGINAL_GRAPHIC[i])
        {
            graphicMatch = false;
            return;
        }
    }
    graphicMatch = true;
}