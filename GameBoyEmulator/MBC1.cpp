#include "MBC1.h"

MBC1::MBC1()
{
}

MBC1::MBC1(u8* buffer, u32 size) : Cartridge(buffer)
{
	romSize = size;

	numberOfRomBanks = romSize / ONE_BANK_SIZE;

	ROMArray = buffer;

	ramEnabled = false;
	romMode = true;


	RAMArray = nullptr;

	switch (buffer[ramSizeOffset])
	{
	case 0x00: // None
		RAMArray = nullptr;
		break;

	case 0x01: // 2 KB's
		RAMArray = new u8[TWO_KB];
		numberOfRamBanks = 1;
		break;

	case 0x02: // 8 KB's
		RAMArray = new u8[EIGHT_KB];
		numberOfRamBanks = 1;
		break;

	case 0x03: // 32 KB's - 4 * 8 KB banks
		RAMArray = new u8[4 * EIGHT_KB];
		numberOfRamBanks = 4;
		break;

	case 0x04: // 128 KB's - 16 * 8 KB banks
		RAMArray = new u8[16 * EIGHT_KB];
		numberOfRamBanks = 16;
		break;

	case 0x05: // 64 KB's - 8 * 8 KB banks
		RAMArray = new u8[8 * EIGHT_KB];
		numberOfRamBanks = 8;
		break;
	}
	ramBankSize = EIGHT_KB;

}

	

MBC1::~MBC1()
{
	delete ROMArray;

	if (RAMArray != nullptr)
		delete RAMArray;

}


u8 MBC1::ReadROMByte(u16 addr)
{
	
	bool fixedBank = addr < ONE_BANK_SIZE; // if not accessing the fixed bank 0
	u32 bankOffset = (fixedBank ? 0 : activeRomBank) * ONE_BANK_SIZE;
	u16 addrOffset = fixedBank ? addr : addr - ONE_BANK_SIZE;
	
	assert((bankOffset + addrOffset) < romSize);
	

	return ROMArray[bankOffset + addrOffset]; 

}

// A write to addr 0x0000 to 0x7FFF
void MBC1::WriteROMByte(u16 addr, u8 byte)
{
	// None
	if (addr >= 0x0000 && addr <= 0x1FFF) // RAM Enable
	{
		if (byte == 0x0A)
			ramEnabled = true;
		else
			ramEnabled = false;
	}
	else if (addr >= 0x2000 && addr <= 0x3FFF)
	{
		u8 intendedBank = byte & 0x1F;
		if(intendedBank != 0x00 || intendedBank != 0x20 || intendedBank != 0x40 || intendedBank != 0x60)
			activeRomBank = intendedBank;
	}
	else if (addr >= 4000 && addr <= 0x5FFF)
	{
		// This 2bit register can be used to select a RAM Bank in range from 00 - 03h, or to specify the upper two bits(Bit 5 - 6) of the ROM Bank number, depending on the current ROM / RAM Mode. (See below.)
		if (romMode)
		{
			activeRomBank = (activeRomBank & 0x1F) | ((byte & 0x03) << 5);
		}
		else
		{
			activeRamBank = byte & 0x03;
		}
	}
	else if (addr >= 0x6000 && addr <= 0x7FFF)
	{
		if (byte = 0x00)
			romMode = false; // 00h = ROM Banking Mode (up to 8KByte RAM, 2MByte ROM) (default)
		else
			romMode = true; //  01h = RAM Banking Mode (up to 32KByte RAM, 512KByte ROM)

	}

	
}

u8 MBC1::ReadRAMByte(u16 addr)
{
	if (ramEnabled)
	{
		u32 bankOffset = activeRamBank * ramBankSize;
		u16 addrOffset = addr - EXTERNAL_RAM_START;

		return RAMArray[bankOffset + addrOffset];
	}
	else
	{
		return 0x00;
	}
}

void MBC1::WriteRAMByte(u16 addr, u8 byte)
{
	if (ramEnabled)
	{
		u32 bankOffset = activeRamBank * ramBankSize;
		u16 addrOffset = addr - EXTERNAL_RAM_START;

		RAMArray[bankOffset + addrOffset] = byte;
	}
}