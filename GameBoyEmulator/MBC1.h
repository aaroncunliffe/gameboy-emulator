#pragma once
#include "Cartridge.h"

class MBC1 : public Cartridge
{
private:

	bool ramEnabled;
	
	bool romMode; // true = ROM banking mode, false = RAM banking mode

public:
	MBC1();
	MBC1(char* path, u8* buffer, u32 size);
	~MBC1();


	virtual u8 ReadROMByte(u16 addr);
	virtual void WriteROMByte(u16 addr, u8 byte);


	virtual u8 ReadRAMByte(u16 addr);
	virtual void WriteRAMByte(u16 addr, u8 byte);
};