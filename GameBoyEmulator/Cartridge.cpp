#include "Cartridge.h"

#include <iomanip>



Cartridge::Cartridge()
{

}


Cartridge::Cartridge(char* path, u8* data)
{
    romPath = path;
    romHeader = data;
    ParseHeader();


	PrintFormattedData();

	activeRomBank = 1; // Switched rom bank segment starts at bank 1
	activeRamBank = 0;

}



Cartridge::~Cartridge()
{

}

bool Cartridge::ReadSaveFile()
{
    std::string filename = romPath;
    int lastindex = filename.find_last_of(".");
    std::string rawname = filename.substr(0, lastindex);
    rawname += ".sav";

    std::ifstream file;

    file.open(rawname, std::ios::ate | std::ios::binary);

    if (file.is_open())
    {
        std::cout << "Save file exists loading..." << std::endl;

        int fileSize = file.tellg();
        
        if (fileSize > ramSize)
            return false;

        file.seekg(0, std::ios::beg); // Move pointer back to the beginning of file

        // Create buffer of the right size and read data to it
        u8* buffer = new u8[fileSize];
        file.read((char*)buffer, fileSize);

        RAMArray = buffer;

    }
    else
    {
        std::cout << "Save file does not exist, creating..." << std::endl;
        return false;
    }

}


void Cartridge::WriteSaveFile()
{
    if (ramSize > 0x0000)
    {
        std::string filename = romPath;
        int lastindex = filename.find_last_of(".");
        std::string rawname = filename.substr(0, lastindex);
        rawname += ".sav";

        std::ofstream outputFile;
        outputFile.open(rawname, std::ios::out | std::ios::binary);


        // write first rom bank
        for (int i = 0; i < ramSize; ++i)
        {
            outputFile << RAMArray[i];
        }

        outputFile.close();
        std::cout << "Memory written to file" << std::endl;

    }
    
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