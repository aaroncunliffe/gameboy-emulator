#include "MMU.h"

MMU::MMU()
{

}

MMU::MMU(Display* d, Joypad* j)
{
    srand(time(NULL));

    display = d;
	joypad = j;

    activeRomBank = 1;
    activeExternalRamBank = 0;
    biosComplete = false;

    memset(externalRam, 0x00, EIGHT_KB * sizeof(u8));
    memset(internalRam, 0x00, SIXTEEN_KB * sizeof(u8));
    
    memset(IORegs, 0x00, 0x7F *sizeof(u8));
    memset(hram, 0x00, 0x7F *sizeof(u8));

}

MMU::~MMU()
{
    if(cart != nullptr)
        delete cart;
}

// Loads Rom from path that is passed in the constructor of MMU
bool MMU::LoadRom(char* path)
{
    romPath = path;
    std::ifstream file;
    file.open(path, std::ios::binary | std::ios::ate); // ate is to set the pointer to the end of the file so we can read the size

    std::cout << "Opening rom file: " << path << std::endl;
    if (file.is_open())
    {
        romSize = file.tellg();
        std::cout << "Rom Size: " << romSize << " Bytes" << std::endl;

        if (romSize > MAX_ROM_SIZE)
            return false;

        file.seekg(0, std::ios::beg); // Move pointer back to the beginning of file
        
        // Create buffer of the right size and read data to it
        u8* buffer = new u8[romSize];
        file.read((char*)buffer, romSize);

        std::cout << "Rom loaded successfully" << std::endl;
        file.close();

        numberOfRomBanks = romSize / ONE_BANK_SIZE;

        // Splits the rom into the appropriate banks
        for (int bank = 0; bank < numberOfRomBanks; ++bank)
        {
            for (int byte = 0; byte < ONE_BANK_SIZE; ++byte)
            {
                rom[bank][byte] = buffer[(bank * ONE_BANK_SIZE) + byte];
            }
        }

        cart = new Cartridge(rom[0]); // Cartridge class only requires the header data 0x100 - 0x14F
        cart->PrintFormattedData();

        delete buffer;
        return true;
    }
    return false;
}

bool MMU::LoadBios(char* path)
{
    std::ifstream file;
    file.open(path, std::ios::binary | std::ios::ate); // ate is to set the pointer to the end of the file so we can read the size

    std::cout << "Opening bios file " << path << std::endl;
    if (file.is_open())
    {
        u16 size = file.tellg();
        std::cout << "bios Size: " << size << " Bytes" << std::endl;

        if (size > 0x100)
            return false;

        file.seekg(0, std::ios::beg); // Move pointer back to the beginning of file

        // Create buffer of the right size and read data to it
        u8* buffer = new u8[size];
        file.read((char*)buffer, size);

        std::cout << "bios loaded successfully" << std::endl;
        std::cout << std::endl;
        file.close();

        // Moves the data from the buffer to the array
        for (int byte = 0; byte < size; ++byte)
        {
            bios[byte] = buffer[byte];
        }

        delete buffer;
        return true;
    }

    return false;
}

// Reads byte from the correct location in the memory map
u8 MMU::ReadByte(u16 addr)
{
    // Switch is faster than if/else if > 5 paths, uses lookup table
    switch ((addr & 0xF000) >> 12)
    {
        
    case 0x0: case 0x1: case 0x2: case 0x3:
        if (biosComplete)
            return rom[0][addr];
        else
            if (addr < 0x100)
                return bios[addr];
            else
                return rom[0][addr];

        break;

    case 0x4: case 0x5: case 0x6: case 0x7:
        return rom[activeRomBank][addr - ONE_BANK_SIZE];
        break;

    case 0x8: case 0x9:
        // 8kB vram
        // Switcable 0-1 on GBC
        return display->ReadVram(addr);
        break;

    case 0xA: case 0xB:
        // 8kB external ram
        // Switchable
        return externalRam[activeExternalRamBank][addr - EXTERNAL_RAM_START];
        break;
        
    case 0xC: case 0xD:
        // 8kB internal ram
        // 1 bank on GB
        // Switchable 1-7 on GBC
        

        return internalRam[addr - INTERNAL_RAM_START];
        break;

    case 0xE:
        // RAM Shadow
        
        break;


    case 0xF: // Rest of RAM shadow, sprite table, I/O registers, HRAM, Interupts

        switch ((addr & 0x0F00) >> 8)   //0x0F00
        {
        case 0x1: case 0x2: case 0x3: case 0x4: case 0x5: case 0x6: case 0x7: case 0x8: case 0x9: case 0xA: case 0xB: case 0xC: case 0xD:
            // RAM shadow
            break;

        case 0xE: // OAM Table
            if (addr > 0xFE9F) // Not addressable
            {
                break;
            }

            return display->ReadOAM(addr);
            break;

        case 0xF:

            switch ((addr & 0x00F0) >> 4)
            {
            case 0x0: case 0x1: case 0x2: case 0x3: case 0x4: case 0x5: case 0x6: case 0x7: // I/O registers

                switch (addr)
                {
                case 0xFF00:
                    if ((IORegs[addr - IOREG_START] & 0x10) == 0x10)
                        return IORegs[addr - IOREG_START] | 0xC0 | joypad->GetRow1(); // joypad reg
                        //return 0xFF;
                    else if ((IORegs[addr - IOREG_START] & 0x20) == 0x20)
                        return IORegs[addr - IOREG_START] | 0xC0 | joypad->GetRow2(); // joypad reg
                    else
                        return 0xFF;
                    break;

                case 0xFF04:
                    return (u8)rand(); // good enough for now?
                    break;
                case 0xFF05:  // Timer Counter
                    return 0x00;
                    break;
                case 0xFF06:  // Timer Modulo
                    return 0x00;
                    break;
                case 0xFF40:
                    return display->GetLCDC();
                    break;
                case 0xFF41:
                    return display->GetStat();
                case 0xFF42:
                    display->GetScrollY();
                    break;
                case 0xFF43:
                    display->GetScrollX();
                    break;
                case 0xFF44: // LY
                    return display->GetLY(); //0x94 - tetris
                    break;
                case 0xFF45:
                    return display->GetLYC();
                    break;
                }

            default:
                return IORegs[addr - IOREG_START];
                break;
            

            case 0x8: case 0x9: case 0xA: case 0xB: case 0xC: case 0xD: case 0xE: case 0xF:// HRAM
                //if (addr == 0xFFFF)
                //{
                //    // Interupt enable registers
                //    return IME;
                //    break;
                //}
                // STACK
                if (addr == 0xFF80 || addr == 0xFF81)
                {
                    int stop = 0;
                }
                return hram[addr - HRAM_START];

                break;
            }
        }
        break; // case 0xF:
    

    default:
        std::cout << "ERROR - attempt to read from invalid address: " << std::hex << addr << std::endl;
        break;
    }     

return 0xFF;

}

u16 MMU::ReadTwoBytes(u16 addr)
{
    return (ReadByte(addr)) | (ReadByte(addr + 1) << 8);
}

// Writes byte to the correct location in the memory map.
void MMU::WriteByte(u16 addr, u8 byte)
{   
    // Blargg's CPU test
    if (addr == 0xFF02 && byte == 0x81) {
        std::cout << (char)ReadByte(0xFF01) << std::endl;
    }


    // Switch is faster than if/else if - >5 items, uses lookup table, need to check if this gets optimised out anyway...
    switch ((addr & 0xF000) >> 12)
    {

    case 0x0: case 0x1: case 0x2: case 0x3: // ROM FIXED
        break;

    case 0x4: case 0x5: case 0x6: case 0x7: // ROM SWIITCHABLE
        break;

    case 0x8: case 0x9:
        // 8kB vram
        // Switcable 0-1 on GBC
        display->WriteVram(addr, byte);
        break;

    case 0xA: case 0xB:
        // 8kB external ram
        // Switchable
        externalRam[activeExternalRamBank][addr - EXTERNAL_RAM_START] = byte;
        break;

    case 0xC: case 0xD:
        // 8kB internal ram
        // 1 bank on GB
        // Switchable 1-7 on GBC
        internalRam[addr - INTERNAL_RAM_START] = byte;
        break;

    case 0xE:
        // RAM Shadow
        break;


    case 0xF: // Rest of RAM shadow, sprite table, I/O registers, HRAM, Interupts

        switch ((addr & 0x0F00) >> 8)   //0x0F00
        {
        case 0x1: case 0x2: case 0x3: case 0x4: case 0x5: case 0x6: case 0x7: case 0x8: case 0x9: case 0xA: case 0xB: case 0xC: case 0xD:
            // RAM shadow
            break;

        case 0xE: // OAM Table
            if (addr > 0xFE9F) // Not addressable
            {
                break;
            }

            display->WriteOAM(addr, byte);
            break;

        case 0xF:

            switch ((addr & 0x00F0) >> 4)
            {
            case 0x0: case 0x1: case 0x2: case 0x3: case 0x4: case 0x5: case 0x6: case 0x7: // I/O registers
                switch (addr)
                {
                case 0xFF00:
                    // Joypad regs
                    IORegs[addr - IOREG_START] = byte; // ??????
                break;
                   
                case 0xFF40:
                {
                    display->SetLCDC(byte);
                    break;
                } 
                   
                case 0xFF41:
                    display->SetStat(byte);
                    break;
                case 0xFF42:
                    display->SetScrollY(byte);
                    break;
                case 0xFF43:
                    display->SetScrollX(byte);
                    break;
                case 0xFF44: // LY - Read only.
                    break;
                case 0xFF45:
                    //display->SetLYC(byte);
                    break;
                case 0xFF46:
                    display->StartDMA(byte << 8);
                    break;
                case 0xFF50:
                    if (byte == 0x01) 
                        SetBiosComplete(true); // BIOS lockout
                    break;
                
                }
            default:
                IORegs[addr - IOREG_START] = byte; // ??????
                break;
            // Could put default statement here too

            case 0x8: case 0x9: case 0xA: case 0xB: case 0xC: case 0xD: case 0xE: case 0xF:// HRAM
                //if (addr == 0xFFFF)
                //{
                //    // Interupt enable registers
                //    IME = byte;
                //    hram[addr - HRAM_START] = byte;
                //    break;
                //}
                
                
                // STACK
                hram[addr - HRAM_START] = byte;

                break;
            }
            
            break; // case 0xF:
        }

        break;

    default:
        std::cout << "ERROR - attempt to write to invalid address: " << std::hex << addr << std::endl;
        break;
    }
      

   
}

void MMU::WriteTwoBytes(u16 addr, u16 data)
{
    WriteByte(addr, data & 0xFF);
    WriteByte(addr + 1, data >> 8);
}

void MMU::PushTwoBytes(u16 &sp, u16 data)
{
    sp -= 2;
    WriteTwoBytes(sp, data);
}

u16 MMU::PopTwoBytes(u16 &sp)
{
    u16 data = ReadTwoBytes(sp);
    sp += 2;
    return data;
}

void MMU::DumpToFile()
{
    std::ofstream outputFile;

    outputFile.open("Memory.ac", std::ios::out | std::ios::binary);

    outputFile << "FirstRomBank" << std::endl;
    // write first rom bank
    for (int i = 0; i < SIXTEEN_KB; ++i)
    {
        outputFile << rom[0][i];
    }

    outputFile << std::endl << std::endl;


    outputFile << "selectedRomBank" << std::endl;
    // write selected rom bank
    for (int i = 0; i < SIXTEEN_KB; ++i)
    {
        outputFile << rom[activeRomBank][i];
    }

    //outputFile << std::endl << std::endl;


    outputFile.close();
    std::cout << "Memory written to file" << std::endl;
} 