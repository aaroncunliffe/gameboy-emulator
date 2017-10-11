#pragma once
#include "Cartridge.h"




class ROM : public Cartridge
{

private:


	u8 rom[NUM_ROM_BANKS][SIXTEEN_KB];      // up to 0x200 16kb banks ~ 8MB max rom size
	u8 externalRam[1][EIGHT_KB];            // 8k external ram

public:

	ROM(u8* buffer, u32 size);
	~ROM();


	virtual u8 ReadROMByte(u16 addr);
	virtual void WriteROMByte(u16 addr, u8 byte);


	virtual u8 ReadRAMByte(u16 addr);
	virtual void WriteRAMByte(u16 addr, u8 byte);
};