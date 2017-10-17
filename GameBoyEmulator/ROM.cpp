#include "ROM.h"


ROM::ROM()
{

}

ROM::ROM(u8* buffer, u32 size) : Cartridge(buffer)
{
	romSize = size;

	numberOfRomBanks = romSize / ONE_BANK_SIZE;
	
	ROMArray = buffer;
	
}

ROM::~ROM()
{
	delete ROMArray;
}

u8 ROM::ReadROMByte(u16 addr)
{
	bool fixedBank = addr < ONE_BANK_SIZE; // if not accessing the fixed bank 0
	u32 bankOffset = (fixedBank ? 0 : activeRomBank) * ONE_BANK_SIZE;
	u16 addrOffset = fixedBank ?  addr : addr - ONE_BANK_SIZE;
	
	return ROMArray[bankOffset + addrOffset]; //rom[0][addr];

}

void ROM::WriteROMByte(u16 addr, u8 byte)
{
	// None
}


u8 ROM::ReadRAMByte(u16 addr)
{
	//u32 bankOffset = activeRamBank * ramBankSize;
	//u16 addrOffset = addr - EXTERNAL_RAM_START;
	
	//return externalRam[activeExternalRamBank][addr - EXTERNAL_RAM_START];
	return 0xFF;
}

void ROM::WriteRAMByte(u16 addr, u8 byte)
{
	//u32 bankOffset = activeRamBank * ramBankSize;
	//u16 addrOffset = addr - EXTERNAL_RAM_START;
	
	//RAM[activeRamBank][addr - EXTERNAL_RAM_START] = byte;
}