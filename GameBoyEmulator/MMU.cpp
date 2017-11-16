#include "MMU.h"

MMU::MMU()
{

}


MMU::MMU(Display* d, Joypad* j)
{
    srand(time(NULL));

    display = d;
	joypad = j;
	cart = nullptr;

    biosComplete = false;

    //memset(externalRam, 0x00, EIGHT_KB * sizeof(u8));
    //memset(internalRam, 0x00, SIXTEEN_KB * sizeof(u8));
    //memset(IORegs, 0x00, 0x7F *sizeof(u8));
    //memset(hram, 0x00, 0x7F *sizeof(u8));

}

MMU::~MMU()
{
    if(cart != nullptr)
        delete cart;
}


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

		switch (buffer[0x147])
		{
			case 0x00: // ROM
			case 0x08: // ROM + RAM
			case 0x09: // ROM + RAM + BATTERY
				cart = new ROM(romPath, buffer, romSize);
				break;


			case 0x01: // MBC1
			case 0x02: // MBC1 + RAM
			case 0x03: // MBC1 + RAM + BATTERY
				cart = new MBC1(romPath, buffer, romSize);
				break;

		}

		assert(cart != nullptr); // Assert if the cart hasn't been made correctly

        std::cout << "Rom loaded successfully" << std::endl;
        file.close();
		
        //delete buffer;
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


u8 MMU::ReadByte(u16 addr)
{
    // Switch is faster than if/else if > 5 paths, uses jump table
    switch ((addr & 0xF000) >> 12) // compare just the most significant nibble, the shift is to clean up the case statement
    {
        
    case 0x0: case 0x1: case 0x2: case 0x3:
		if (biosComplete)
			return cart->ReadROMByte(addr);
        else
            if (addr < 0x100)
                return bios[addr];
            else
                return cart->ReadROMByte(addr); // BIOS still needs to access rom data

        break;

    case 0x4: case 0x5: case 0x6: case 0x7:
        return cart->ReadROMByte(addr);
        break;

    case 0x8: case 0x9:
        // 8kB vram
        // Switcable 0-1 on GBC
        return display->ReadVram(addr);
        break;

    case 0xA: case 0xB:
        // 8kB external ram
        // Switchable
		return cart->ReadRAMByte(addr);
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

        switch ((addr & 0x0F00) >> 8)   //0x0F00 -  lower nibble of the 2nd byte
        {
        case 0x1: case 0x2: case 0x3: case 0x4: case 0x5: case 0x6: case 0x7: case 0x8: case 0x9: case 0xA: case 0xB: case 0xC: case 0xD:
            // RAM shadow - 0xE000 to 0xFDFF
            break;

        case 0xE: // OAM Table
            if (addr > 0xFE9F) // Not addressable
            {
                break;
            }

            return display->ReadOAM(addr);
            break;

        case 0xF:

            switch ((addr & 0x00F0) >> 4) // Most significant nibble of the first byte
            {
            case 0x0: case 0x1: case 0x2: case 0x3: case 0x4: case 0x5: case 0x6: case 0x7: // I/O registers

                switch (addr) // Whole address for single byte registers
                {
                case 0xFF00:
                    if ((IORegs[addr - IOREG_START] & 0x10) == 0x10)
                        return IORegs[addr - IOREG_START] | 0xC0 | joypad->GetRow1(); // joypad reg
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
                    return display->GetScrollY();
                    break;
                case 0xFF43:
                    return display->GetScrollX();
                    break;
                case 0xFF44: // LY
                    return display->GetLY();
                    break;
                case 0xFF45:
                    return display->GetLYC();
                    break;

                case 0xFF47: // BG palette
					break;
				case 0xFF48: // OB palette 0
					break;
				case 0xFF49: // OB palette 1
					break;
                case 0xFF4A:
                    return display->GetWinY();
                case 0xFF4B:
                    return display->GetWinX();
                }

            default: // Still writes to the IORegs array even it hits a case in the above nested switch statement
                return IORegs[addr - IOREG_START];
                break;
            

            case 0x8: case 0x9: case 0xA: case 0xB: case 0xC: case 0xD: case 0xE: case 0xF: // HRAM
                if (addr == 0xFFFF)
                {
                    return IEReg;
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



void MMU::WriteByte(u16 addr, u8 byte)
{
    // Switch is faster than if/else if - >5 items, uses lookup table, need to check if this gets optimised out anyway...
    switch ((addr & 0xF000) >> 12) // compare just the most significant nibble, the shift is to clean up the case statement
    {

    case 0x0: case 0x1: case 0x2: case 0x3: // ROM FIXED
		cart->WriteROMByte(addr, byte);
        break;

    case 0x4: case 0x5: case 0x6: case 0x7: // ROM SWIITCHABLE
		cart->WriteROMByte(addr, byte);
		break;

    case 0x8: case 0x9:
        // 8kB vram
        // Switcable 0-1 on GBC
        display->WriteVram(addr, byte);
        break;

    case 0xA: case 0xB:
        // 8kB external ram
        // Switchable
		cart->WriteRAMByte(addr, byte);
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

        switch ((addr & 0x0F00) >> 8)   //0x0F00 -  lower nibble of the 2nd byte
        {
        case 0x1: case 0x2: case 0x3: case 0x4: case 0x5: case 0x6: case 0x7: case 0x8: case 0x9: case 0xA: case 0xB: case 0xC: case 0xD:
            // RAM shadow - 0xE000 to 0xFDFF
            break;

        case 0xE: // OAM Table
            if (addr > 0xFE9F) // Not addressable
            {
                break;
            }

            display->WriteOAM(addr, byte);
            break;

        case 0xF:

            switch ((addr & 0x00F0) >> 4) // Most significant nibble of the first byte
            {
            case 0x0: case 0x1: case 0x2: case 0x3: case 0x4: case 0x5: case 0x6: case 0x7: // I/O registers
                switch (addr) // Whole address for single byte registers
                {
                case 0xFF00:
                    // Joypad regs
                    IORegs[addr - IOREG_START] = byte; // This needs to be written so when it is read, we can return the correct joypad data.
                break;
                   
                case 0xFF40:
                    display->SetLCDC(byte);
                    break;
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
                    display->SetLYC(byte);
                    break;
                case 0xFF46:
                    display->StartDMA(byte << 8);
                    break;
				case 0xFF47: // BG palette
					display->UpdateBGPalette(byte);
					break;
				case 0xFF48: // OB palette 0
					display->UpdateOBPalette(false, byte);
					break;
				case 0xFF49: // OB palette 1
					display->UpdateOBPalette(true, byte);
					break;
                case 0xFF4A:
                    display->SetWinY(byte);
                    break;
                case 0xFF4B: 
                    display->SetWinX(byte);
                    break;
                case 0xFF50:
                    if (byte == 0x01) 
                        SetBiosComplete(true); // BIOS lockout to allow rom to access 0x0000 - 0x0100
                    break;
                
                }
            default: // Still writes to the IORegs array even if it sets a value in the above nested switch statement
                IORegs[addr - IOREG_START] = byte;
                break;

            case 0x8: case 0x9: case 0xA: case 0xB: case 0xC: case 0xD: case 0xE: case 0xF: // HRAM
                if (addr == 0xFFFF)
                {
                    IEReg = byte;
                }

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
    WriteByte(addr, data & 0xFF); // Write lower byte first
    WriteByte(addr + 1, data >> 8); // Write higher byte.
}


u16 MMU::ReadTwoBytes(u16 addr)
{
    u8 lowByte = ReadByte(addr);
    u16 highByte = ReadByte(addr + 1) << 8;
    return highByte | lowByte;
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
        //outputFile << rom[0][i];
    }

    outputFile << std::endl << std::endl;


    outputFile << "selectedRomBank" << std::endl;
    // write selected rom bank
    for (int i = 0; i < SIXTEEN_KB; ++i)
    {
        //outputFile << rom[activeRomBank][i];
    }

    //outputFile << std::endl << std::endl;


    outputFile.close();
    std::cout << "Memory written to file" << std::endl;
}

void MMU::WriteSaveFile()
{
    std::ofstream outputFile;

    /*outputFile.open("game.sav");

    std::hex;
    for (int byte = 0x0000; byte < EIGHT_KB; ++byte)
    {
        outputFile << externalRam[1][byte];
    }
*/

    outputFile.close();

    std::cout << "Registers written to file" << std::endl;

}