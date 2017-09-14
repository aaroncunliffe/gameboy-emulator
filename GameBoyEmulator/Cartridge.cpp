#include "Cartridge.h"

#include <iomanip>



Cartridge::Cartridge()
{

}


Cartridge::Cartridge(u8* data)
{
    romHeader = data;
    ParseHeader();
}


Cartridge::~Cartridge()
{

}

// Reads all data from the header
void Cartridge::ParseHeader()
{
    // Functions
    CompareGraphics();
    ReadTitle();

    // Direct reads
    gameboyByte = romHeader[gameboyByteOffset];
    licenseeCodeByte = romHeader[licenseCodeOffset];
    cartridgeTypeByte = romHeader[cartridgeTypeOffset];
    romSizeByte = romHeader[romSizeOffset];
    ramSizeByte = romHeader[ramSizeOffset];
    destinationCode = romHeader[destinationCodeOffset];
}

// Print formatted data to console window
void Cartridge::PrintFormattedData()
{
    std::cout << std::endl;
    std::cout << "---- ROM HEADER DATA ----" << std::endl;
    std::cout << "Title:            " << title << std::endl;
    std::cout << "Gameboy:          " << std::uppercase << std::setw(2) << std::setfill('0') << std::hex << (int)gameboyByte << std::endl;
    std::cout << "Graphic Match:    " << (graphicMatch ? "True" : "False") << std::endl;
    std::cout << "Licensee Code:    " << std::uppercase << std::setw(2) << std::setfill('0') << std::hex << (int)licenseeCodeByte << std::endl;
    std::cout << "Cartridge Type:   " << std::uppercase << std::setw(2) << std::setfill('0') << std::hex << (int)cartridgeTypeByte << std::endl;
    std::cout << "Rom Size:         " << std::uppercase << std::setw(2) << std::setfill('0') << std::hex << (int)romSizeByte << std::endl;
    std::cout << "Ram Size:         " << std::uppercase << std::setw(2) << std::setfill('0') << std::hex << (int)ramSizeByte << std::endl;
    std::cout << "Destination Code: " << std::uppercase << std::setw(2) << std::setfill('0') << std::hex << (int)destinationCode << std::endl;
    std::cout << std::endl;
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