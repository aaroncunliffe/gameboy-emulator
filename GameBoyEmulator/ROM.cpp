#include "ROM.h"

ROM::ROM(u8* buffer, u32 size) : Cartridge(buffer)
{
	romSize = size;

	numberOfRomBanks = romSize / ONE_BANK_SIZE;

	// Splits the rom into the appropriate banks
	for (int bank = 0; bank < numberOfRomBanks; ++bank)
	{
		for (int byte = 0; byte < ONE_BANK_SIZE; ++byte)
		{
			rom[bank][byte] = buffer[(bank * ONE_BANK_SIZE) + byte];
		}
	}
	PrintFormattedData();

	activeRomBank = 1;
	activeExternalRamBank = 0;
}

u8 ROM::ReadROMByte(u16 addr)
{
	return rom[0][addr];

}

void ROM::WriteROMByte(u16 addr, u8 byte)
{
	// None
}


u8 ROM::ReadRAMByte(u16 addr)
{
	return externalRam[activeExternalRamBank][addr - EXTERNAL_RAM_START];
}

void ROM::WriteRAMByte(u16 addr, u8 byte)
{
	externalRam[activeExternalRamBank][addr - EXTERNAL_RAM_START] = byte;
}