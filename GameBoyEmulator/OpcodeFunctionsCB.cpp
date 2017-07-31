#include "CPU.h"


void CPU::CBopcode0x27() // SLA A
{
    SLA(regs.AF.high);
    regs.pc += 2;
    counter += 8;
}

void CPU::CBopcode0x30() // SWAP B
{
    SWAP(regs.BC.high);
    regs.pc += 2;
    counter += 8;
}

void CPU::CBopcode0x33() // SWAP E
{
    SWAP(regs.DE.low);
    regs.pc += 2;
    counter += 8;
}

void CPU::CBopcode0x37() // SWAP A
{
    SWAP(regs.AF.high);
    regs.pc += 2;
    counter += 8;
}

void CPU::CBopcode0x3F() // SRL A
{
    SRL(regs.AF.high);
    regs.pc += 2;
    counter += 8;
}

void CPU::CBopcode0x40() // BIT 0,B
{
    BIT(0x01, regs.BC.high);
    regs.pc += 2;
    counter += 8;
}

void CPU::CBopcode0x46() // BIT 0, (HL)
{
	BIT(0x01, mmu->ReadByte(regs.HL.word));
	regs.pc += 2;
	counter += 16;
}

void CPU::CBopcode0x47() // BIT 0,A
{
    BIT(0x01, regs.AF.high);
    regs.pc += 2;
    counter += 8;
}

void CPU::CBopcode0x48() // BIT 1,E
{
    BIT(0x02, regs.DE.low);
    regs.pc += 2;
    counter += 8;
}

void CPU::CBopcode0x50() // BIT 2,B
{
    BIT(0x04, regs.BC.high);
    regs.pc += 2;
    counter += 8;
}

void CPU::CBopcode0x58() // BIT 3,B
{
    BIT(0x08, regs.BC.high);
    regs.pc += 2;
    counter += 8;
}

void CPU::CBopcode0x5F() // BIT 3,A
{
    BIT(0x80, regs.AF.high);
    regs.pc += 2;
    counter += 8;
}

void CPU::CBopcode0x60() // BIT 4,B
{
    BIT(0x10, regs.BC.high);
    regs.pc += 2;
    counter += 8;
}

void CPU::CBopcode0x61() // BIT 4,C
{
    BIT(0x10, regs.BC.low);
    regs.pc += 2;
    counter += 8;
}

void CPU::CBopcode0x68() // BIT 5,B
{
    BIT(0x20, regs.BC.high);
    regs.pc += 2;
    counter += 8;
}

void CPU::CBopcode0x69()
{
    BIT(0x20, regs.BC.low);
    regs.pc += 2;
    counter += 8;
}

void CPU::CBopcode0x6F() // BIT 5,A
{
    BIT(0x20, regs.AF.high);
    regs.pc += 2;
    counter += 8;
}

void CPU::CBopcode0x77() //BIT 6,A
{
    BIT(0x40, regs.AF.high);
    regs.pc += 2;
    counter += 8;
}

void CPU::CBopcode0x7E() // BIT 7,(HL)
{
    BIT(0x80, mmu->ReadByte(regs.HL.word));
    regs.pc += 2;
    counter += 16;
}

void CPU::CBopcode0x7F() // BIT 7,A
{
    BIT(0x80, regs.AF.high);
    regs.pc += 2;
    counter += 8;
}

void CPU::CBopcode0x86()
{
    u8 byte = mmu->ReadByte(regs.HL.word);
    RES(0x01, byte);
    mmu->WriteByte(regs.HL.word, byte);
    regs.pc += 2;
    counter += 8;
}

void CPU::CBopcode0x87() // RES 0,A
{
    RES(0x01, regs.AF.high);
    regs.pc += 2;
    counter += 8;
}

void CPU::CBopcode0xBE() // RES 7,(HL)
{
	u8 byte = mmu->ReadByte(regs.HL.word);
	RES(0x80, byte);
	mmu->WriteByte(regs.HL.word, byte);

	regs.pc += 2;
	counter += 16;
}

void CPU::CBopcode0xFE() // SET 7,(HL)
{
	u8 byte = mmu->ReadByte(regs.HL.word);
	SET(0x80, byte);
	mmu->WriteByte(regs.HL.word, byte);

	regs.pc += 2;
	counter += 16;
}



// Helper Functions CB

inline void CPU::BIT(u8 bit, u8 reg) // Test bit in register, FLAGS: Z 0 1 -
{
    if (reg & bit)
        regs.AF.low &= ~ZERO_FLAG;
    else
        regs.AF.low |= ZERO_FLAG;

    regs.AF.low &= ~SUBTRACT_FLAG;
    regs.AF.low |= HALF_CARRY_FLAG;
    
}

inline void CPU::SWAP(u8& reg) // Flags: Z 0 0 0
{
    // reset flags
    regs.AF.low &= ~SUBTRACT_FLAG;
    regs.AF.low &= ~HALF_CARRY_FLAG;
    regs.AF.low &= ~CARRY_FLAG;

    u8 lower = reg & 0x0F;
    reg = (reg >> 4) | (lower << 4);

    if (reg == 0x00)
        regs.AF.low |= ZERO_FLAG;
    else
        regs.AF.low &= ~ZERO_FLAG;
}

inline void CPU::RES(u8 bit, u8& reg) // Reset bit
{
    reg &= ~bit;
}

inline void CPU::SLA(u8& reg) // Flags: Z 0 0 C - Shift n left into Carry.LSB of n set to 0.
{
    u8 msb = (reg & 0x80) >> 7; // Store the msb before the shift

    regs.AF.low &= ~SUBTRACT_FLAG;
    regs.AF.low &= ~HALF_CARRY_FLAG;

    if (msb)
        regs.AF.low |= CARRY_FLAG;
    else
        regs.AF.low &= ~CARRY_FLAG;

    reg = reg << 1;

    if (reg == 0x00)
        regs.AF.low |= ZERO_FLAG;
    else
        regs.AF.low &= ~ZERO_FLAG;
}

inline void CPU::SRL(u8& reg) // Flags: Z 0 0 C - Shift n right into Carry. MSB set to 0
{
    u8 lsb = (reg & 0x01); // Store the msb before the shift

    regs.AF.low &= ~SUBTRACT_FLAG;
    regs.AF.low &= ~HALF_CARRY_FLAG;

    if (lsb)
        regs.AF.low |= CARRY_FLAG;
    else
        regs.AF.low &= ~CARRY_FLAG;

    reg = reg >> 1;

    if (reg == 0x00)
        regs.AF.low |= ZERO_FLAG;
    else
        regs.AF.low &= ~ZERO_FLAG;
}


inline void CPU::SET(u8 bit, u8& reg) // Flags:: - - - - : Set bit bit in register reg
{
	reg |= bit;
}



// Assigns all of the function pointers
void CPU::InitOpcodeFunctionsCB()
{
    opcodeFunctionCB[0x00] = nullptr; // = &CPU::CBopcode0x00;
    opcodeFunctionCB[0x01] = nullptr; // = &CPU::CBopcode0x01;
    opcodeFunctionCB[0x02] = nullptr; // = &CPU::CBopcode0x02;
    opcodeFunctionCB[0x03] = nullptr; // = &CPU::CBopcode0x03;
    opcodeFunctionCB[0x04] = nullptr; // = &CPU::CBopcode0x04;
    opcodeFunctionCB[0x05] = nullptr; // = &CPU::CBopcode0x05;
    opcodeFunctionCB[0x06] = nullptr; // = &CPU::CBopcode0x06;
    opcodeFunctionCB[0x07] = nullptr; // = &CPU::CBopcode0x07;
    opcodeFunctionCB[0x08] = nullptr; // = &CPU::CBopcode0x08;
    opcodeFunctionCB[0x09] = nullptr; // = &CPU::CBopcode0x09;
    opcodeFunctionCB[0x0A] = nullptr; // = &CPU::CBopcode0x0A;
    opcodeFunctionCB[0x0B] = nullptr; // = &CPU::CBopcode0x0B;
    opcodeFunctionCB[0x0C] = nullptr; // = &CPU::CBopcode0x0C;
    opcodeFunctionCB[0x0D] = nullptr; // = &CPU::CBopcode0x0D;
    opcodeFunctionCB[0x0E] = nullptr; // = &CPU::CBopcode0x0E;
    opcodeFunctionCB[0x0F] = nullptr; // = &CPU::CBopcode0x0F;
    opcodeFunctionCB[0x10] = nullptr; // = &CPU::CBopcode0x10;
    opcodeFunctionCB[0x11] = nullptr; // = &CPU::CBopcode0x11;
    opcodeFunctionCB[0x12] = nullptr; // = &CPU::CBopcode0x12;
    opcodeFunctionCB[0x13] = nullptr; // = &CPU::CBopcode0x13;
    opcodeFunctionCB[0x14] = nullptr; // = &CPU::CBopcode0x14;
    opcodeFunctionCB[0x15] = nullptr; // = &CPU::CBopcode0x15;
    opcodeFunctionCB[0x16] = nullptr; // = &CPU::CBopcode0x16;
    opcodeFunctionCB[0x17] = nullptr; // = &CPU::CBopcode0x17;
    opcodeFunctionCB[0x18] = nullptr; // = &CPU::CBopcode0x18;
    opcodeFunctionCB[0x19] = nullptr; // = &CPU::CBopcode0x19;
    opcodeFunctionCB[0x1A] = nullptr; // = &CPU::CBopcode0x1A;
    opcodeFunctionCB[0x1B] = nullptr; // = &CPU::CBopcode0x1B;
    opcodeFunctionCB[0x1C] = nullptr; // = &CPU::CBopcode0x1C;
    opcodeFunctionCB[0x1D] = nullptr; // = &CPU::CBopcode0x1D;
    opcodeFunctionCB[0x1E] = nullptr; // = &CPU::CBopcode0x1E;
    opcodeFunctionCB[0x1F] = nullptr; // = &CPU::CBopcode0x1F;
    opcodeFunctionCB[0x20] = nullptr; // = &CPU::CBopcode0x20;
    opcodeFunctionCB[0x21] = nullptr; // = &CPU::CBopcode0x21;
    opcodeFunctionCB[0x22] = nullptr; // = &CPU::CBopcode0x22;
    opcodeFunctionCB[0x23] = nullptr; // = &CPU::CBopcode0x23;
    opcodeFunctionCB[0x24] = nullptr; // = &CPU::CBopcode0x24;
    opcodeFunctionCB[0x25] = nullptr; // = &CPU::CBopcode0x25;
    opcodeFunctionCB[0x26] = nullptr; // = &CPU::CBopcode0x26;
    opcodeFunctionCB[0x27] = &CPU::CBopcode0x27;
    opcodeFunctionCB[0x28] = nullptr; // = &CPU::CBopcode0x28;
    opcodeFunctionCB[0x29] = nullptr; // = &CPU::CBopcode0x29;
    opcodeFunctionCB[0x2A] = nullptr; // = &CPU::CBopcode0x2A;
    opcodeFunctionCB[0x2B] = nullptr; // = &CPU::CBopcode0x2B;
    opcodeFunctionCB[0x2C] = nullptr; // = &CPU::CBopcode0x2C;
    opcodeFunctionCB[0x2D] = nullptr; // = &CPU::CBopcode0x2D;
    opcodeFunctionCB[0x2E] = nullptr; // = &CPU::CBopcode0x2E;
    opcodeFunctionCB[0x2F] = nullptr; // = &CPU::CBopcode0x2F;
    opcodeFunctionCB[0x30] = &CPU::CBopcode0x30;
    opcodeFunctionCB[0x31] = nullptr; // = &CPU::CBopcode0x31;
    opcodeFunctionCB[0x32] = nullptr; // = &CPU::CBopcode0x32;
    opcodeFunctionCB[0x33] = &CPU::CBopcode0x33;
    opcodeFunctionCB[0x34] = nullptr; // = &CPU::CBopcode0x34;
    opcodeFunctionCB[0x35] = nullptr; // = &CPU::CBopcode0x35;
    opcodeFunctionCB[0x36] = nullptr; // = &CPU::CBopcode0x36;
    opcodeFunctionCB[0x37] = &CPU::CBopcode0x37;
    opcodeFunctionCB[0x38] = nullptr; // = &CPU::CBopcode0x38;
    opcodeFunctionCB[0x39] = nullptr; // = &CPU::CBopcode0x39;
    opcodeFunctionCB[0x3A] = nullptr; // = &CPU::CBopcode0x3A;
    opcodeFunctionCB[0x3B] = nullptr; // = &CPU::CBopcode0x3B;
    opcodeFunctionCB[0x3C] = nullptr; // = &CPU::CBopcode0x3C;
    opcodeFunctionCB[0x3D] = nullptr; // = &CPU::CBopcode0x3D;
    opcodeFunctionCB[0x3E] = nullptr; // = &CPU::CBopcode0x3E;
    opcodeFunctionCB[0x3F] = &CPU::CBopcode0x3F;
    opcodeFunctionCB[0x40] = &CPU::CBopcode0x40;
    opcodeFunctionCB[0x41] = nullptr; // = &CPU::CBopcode0x41;
    opcodeFunctionCB[0x42] = nullptr; // = &CPU::CBopcode0x42;
    opcodeFunctionCB[0x43] = nullptr; // = &CPU::CBopcode0x43;
    opcodeFunctionCB[0x44] = nullptr; // = &CPU::CBopcode0x44;
    opcodeFunctionCB[0x45] = nullptr; // = &CPU::CBopcode0x45;
    opcodeFunctionCB[0x46] = &CPU::CBopcode0x46;
    opcodeFunctionCB[0x47] = &CPU::CBopcode0x47;
    opcodeFunctionCB[0x48] = &CPU::CBopcode0x48;
    opcodeFunctionCB[0x49] = nullptr; // = &CPU::CBopcode0x49;
    opcodeFunctionCB[0x4A] = nullptr; // = &CPU::CBopcode0x4A;
    opcodeFunctionCB[0x4B] = nullptr; // = &CPU::CBopcode0x4B;
    opcodeFunctionCB[0x4C] = nullptr; // = &CPU::CBopcode0x4C;
    opcodeFunctionCB[0x4D] = nullptr; // = &CPU::CBopcode0x4D;
    opcodeFunctionCB[0x4E] = nullptr; // = &CPU::CBopcode0x4E;
    opcodeFunctionCB[0x4F] = nullptr; // = &CPU::CBopcode0x4F;
    opcodeFunctionCB[0x50] = &CPU::CBopcode0x50;
    opcodeFunctionCB[0x51] = nullptr; // = &CPU::CBopcode0x51;
    opcodeFunctionCB[0x52] = nullptr; // = &CPU::CBopcode0x52;
    opcodeFunctionCB[0x53] = nullptr; // = &CPU::CBopcode0x53;
    opcodeFunctionCB[0x54] = nullptr; // = &CPU::CBopcode0x54;
    opcodeFunctionCB[0x55] = nullptr; // = &CPU::CBopcode0x55;
    opcodeFunctionCB[0x56] = nullptr; // = &CPU::CBopcode0x56;
    opcodeFunctionCB[0x57] = nullptr; // = &CPU::CBopcode0x57;
    opcodeFunctionCB[0x58] = &CPU::CBopcode0x58;
    opcodeFunctionCB[0x59] = nullptr; // = &CPU::CBopcode0x59;
    opcodeFunctionCB[0x5A] = nullptr; // = &CPU::CBopcode0x5A;
    opcodeFunctionCB[0x5B] = nullptr; // = &CPU::CBopcode0x5B;
    opcodeFunctionCB[0x5C] = nullptr; // = &CPU::CBopcode0x5C;
    opcodeFunctionCB[0x5D] = nullptr; // = &CPU::CBopcode0x5D;
    opcodeFunctionCB[0x5E] = nullptr; // = &CPU::CBopcode0x5E;
    opcodeFunctionCB[0x5F] = &CPU::CBopcode0x5F;
    opcodeFunctionCB[0x60] = &CPU::CBopcode0x60;
    opcodeFunctionCB[0x61] = &CPU::CBopcode0x61;
    opcodeFunctionCB[0x62] = nullptr; // = &CPU::CBopcode0x62;
    opcodeFunctionCB[0x63] = nullptr; // = &CPU::CBopcode0x63;
    opcodeFunctionCB[0x64] = nullptr; // = &CPU::CBopcode0x64;
    opcodeFunctionCB[0x65] = nullptr; // = &CPU::CBopcode0x65;
    opcodeFunctionCB[0x66] = nullptr; // = &CPU::CBopcode0x66;
    opcodeFunctionCB[0x67] = nullptr; // = &CPU::CBopcode0x67;
    opcodeFunctionCB[0x68] = &CPU::CBopcode0x68;
    opcodeFunctionCB[0x69] = &CPU::CBopcode0x69;
    opcodeFunctionCB[0x6A] = nullptr; // = &CPU::CBopcode0x6A;
    opcodeFunctionCB[0x6B] = nullptr; // = &CPU::CBopcode0x6B;
    opcodeFunctionCB[0x6C] = nullptr; // = &CPU::CBopcode0x6C;
    opcodeFunctionCB[0x6D] = nullptr; // = &CPU::CBopcode0x6D;
    opcodeFunctionCB[0x6E] = nullptr; // = &CPU::CBopcode0x6E;
    opcodeFunctionCB[0x6F] = &CPU::CBopcode0x6F;
    opcodeFunctionCB[0x70] = nullptr; // = &CPU::CBopcode0x70;
    opcodeFunctionCB[0x71] = nullptr; // = &CPU::CBopcode0x71;
    opcodeFunctionCB[0x72] = nullptr; // = &CPU::CBopcode0x72;
    opcodeFunctionCB[0x73] = nullptr; // = &CPU::CBopcode0x73;
    opcodeFunctionCB[0x74] = nullptr; // = &CPU::CBopcode0x74;
    opcodeFunctionCB[0x75] = nullptr; // = &CPU::CBopcode0x75;
    opcodeFunctionCB[0x76] = nullptr; // = &CPU::CBopcode0x76;
    opcodeFunctionCB[0x77] = &CPU::CBopcode0x77;
    opcodeFunctionCB[0x78] = nullptr; // = &CPU::CBopcode0x78;
    opcodeFunctionCB[0x79] = nullptr; // = &CPU::CBopcode0x79;
    opcodeFunctionCB[0x7A] = nullptr; // = &CPU::CBopcode0x7A;
    opcodeFunctionCB[0x7B] = nullptr; // = &CPU::CBopcode0x7B;
    opcodeFunctionCB[0x7C] = nullptr; // = &CPU::CBopcode0x7C;
    opcodeFunctionCB[0x7D] = nullptr; // = &CPU::CBopcode0x7D;
    opcodeFunctionCB[0x7E] = &CPU::CBopcode0x7E;
    opcodeFunctionCB[0x7F] = &CPU::CBopcode0x7F;
    opcodeFunctionCB[0x80] = nullptr; // = &CPU::CBopcode0x80;
    opcodeFunctionCB[0x81] = nullptr; // = &CPU::CBopcode0x81;
    opcodeFunctionCB[0x82] = nullptr; // = &CPU::CBopcode0x82;
    opcodeFunctionCB[0x83] = nullptr; // = &CPU::CBopcode0x83;
    opcodeFunctionCB[0x84] = nullptr; // = &CPU::CBopcode0x84;
    opcodeFunctionCB[0x85] = nullptr; // = &CPU::CBopcode0x85;
    opcodeFunctionCB[0x86] = &CPU::CBopcode0x86;
    opcodeFunctionCB[0x87] = &CPU::CBopcode0x87;
    opcodeFunctionCB[0x88] = nullptr; // = &CPU::CBopcode0x88;
    opcodeFunctionCB[0x89] = nullptr; // = &CPU::CBopcode0x89;
    opcodeFunctionCB[0x8A] = nullptr; // = &CPU::CBopcode0x8A;
    opcodeFunctionCB[0x8B] = nullptr; // = &CPU::CBopcode0x8B;
    opcodeFunctionCB[0x8C] = nullptr; // = &CPU::CBopcode0x8C;
    opcodeFunctionCB[0x8D] = nullptr; // = &CPU::CBopcode0x8D;
    opcodeFunctionCB[0x8E] = nullptr; // = &CPU::CBopcode0x8E;
    opcodeFunctionCB[0x8F] = nullptr; // = &CPU::CBopcode0x8F;
    opcodeFunctionCB[0x90] = nullptr; // = &CPU::CBopcode0x90;
    opcodeFunctionCB[0x91] = nullptr; // = &CPU::CBopcode0x91;
    opcodeFunctionCB[0x92] = nullptr; // = &CPU::CBopcode0x92;
    opcodeFunctionCB[0x93] = nullptr; // = &CPU::CBopcode0x93;
    opcodeFunctionCB[0x94] = nullptr; // = &CPU::CBopcode0x94;
    opcodeFunctionCB[0x95] = nullptr; // = &CPU::CBopcode0x95;
    opcodeFunctionCB[0x96] = nullptr; // = &CPU::CBopcode0x96;
    opcodeFunctionCB[0x97] = nullptr; // = &CPU::CBopcode0x97;
    opcodeFunctionCB[0x98] = nullptr; // = &CPU::CBopcode0x98;
    opcodeFunctionCB[0x99] = nullptr; // = &CPU::CBopcode0x99;
    opcodeFunctionCB[0x9A] = nullptr; // = &CPU::CBopcode0x9A;
    opcodeFunctionCB[0x9B] = nullptr; // = &CPU::CBopcode0x9B;
    opcodeFunctionCB[0x9C] = nullptr; // = &CPU::CBopcode0x9C;
    opcodeFunctionCB[0x9D] = nullptr; // = &CPU::CBopcode0x9D;
    opcodeFunctionCB[0x9E] = nullptr; // = &CPU::CBopcode0x9E;
    opcodeFunctionCB[0x9F] = nullptr; // = &CPU::CBopcode0x9F;
    opcodeFunctionCB[0xA0] = nullptr; // = &CPU::CBopcode0xA0;
    opcodeFunctionCB[0xA1] = nullptr; // = &CPU::CBopcode0xA1;
    opcodeFunctionCB[0xA2] = nullptr; // = &CPU::CBopcode0xA2;
    opcodeFunctionCB[0xA3] = nullptr; // = &CPU::CBopcode0xA3;
    opcodeFunctionCB[0xA4] = nullptr; // = &CPU::CBopcode0xA4;
    opcodeFunctionCB[0xA5] = nullptr; // = &CPU::CBopcode0xA5;
    opcodeFunctionCB[0xA6] = nullptr; // = &CPU::CBopcode0xA6;
    opcodeFunctionCB[0xA7] = nullptr; // = &CPU::CBopcode0xA7;
    opcodeFunctionCB[0xA8] = nullptr; // = &CPU::CBopcode0xA8;
    opcodeFunctionCB[0xA9] = nullptr; // = &CPU::CBopcode0xA9;
    opcodeFunctionCB[0xAA] = nullptr; // = &CPU::CBopcode0xAA;
    opcodeFunctionCB[0xAB] = nullptr; // = &CPU::CBopcode0xAB;
    opcodeFunctionCB[0xAC] = nullptr; // = &CPU::CBopcode0xAC;
    opcodeFunctionCB[0xAD] = nullptr; // = &CPU::CBopcode0xAD;
    opcodeFunctionCB[0xAE] = nullptr; // = &CPU::CBopcode0xAE;
    opcodeFunctionCB[0xAF] = nullptr; // = &CPU::CBopcode0xAF;
    opcodeFunctionCB[0xB0] = nullptr; // = &CPU::CBopcode0xB0;
    opcodeFunctionCB[0xB1] = nullptr; // = &CPU::CBopcode0xB1;
    opcodeFunctionCB[0xB2] = nullptr; // = &CPU::CBopcode0xB2;
    opcodeFunctionCB[0xB3] = nullptr; // = &CPU::CBopcode0xB3;
    opcodeFunctionCB[0xB4] = nullptr; // = &CPU::CBopcode0xB4;
    opcodeFunctionCB[0xB5] = nullptr; // = &CPU::CBopcode0xB5;
    opcodeFunctionCB[0xB6] = nullptr; // = &CPU::CBopcode0xB6;
    opcodeFunctionCB[0xB7] = nullptr; // = &CPU::CBopcode0xB7;
    opcodeFunctionCB[0xB8] = nullptr; // = &CPU::CBopcode0xB8;
    opcodeFunctionCB[0xB9] = nullptr; // = &CPU::CBopcode0xB9;
    opcodeFunctionCB[0xBA] = nullptr; // = &CPU::CBopcode0xBA;
    opcodeFunctionCB[0xBB] = nullptr; // = &CPU::CBopcode0xBB;
    opcodeFunctionCB[0xBC] = nullptr; // = &CPU::CBopcode0xBC;
    opcodeFunctionCB[0xBD] = nullptr; // = &CPU::CBopcode0xBD;
    opcodeFunctionCB[0xBE] = &CPU::CBopcode0xBE;
    opcodeFunctionCB[0xBF] = nullptr; // = &CPU::CBopcode0xBF;
    opcodeFunctionCB[0xC0] = nullptr; // = &CPU::CBopcode0xC0;
    opcodeFunctionCB[0xC1] = nullptr; // = &CPU::CBopcode0xC1;
    opcodeFunctionCB[0xC2] = nullptr; // = &CPU::CBopcode0xC2;
    opcodeFunctionCB[0xC3] = nullptr; // = &CPU::CBopcode0xC3;
    opcodeFunctionCB[0xC4] = nullptr; // = &CPU::CBopcode0xC4;
    opcodeFunctionCB[0xC5] = nullptr; // = &CPU::CBopcode0xC5;
    opcodeFunctionCB[0xC6] = nullptr; // = &CPU::CBopcode0xC6;
    opcodeFunctionCB[0xC7] = nullptr; // = &CPU::CBopcode0xC7;
    opcodeFunctionCB[0xC8] = nullptr; // = &CPU::CBopcode0xC8;
    opcodeFunctionCB[0xC9] = nullptr; // = &CPU::CBopcode0xC9;
    opcodeFunctionCB[0xCA] = nullptr; // = &CPU::CBopcode0xCA;
    opcodeFunctionCB[0xCB] = nullptr; // = &CPU::CBopcode0xCB;
    opcodeFunctionCB[0xCC] = nullptr; // = &CPU::CBopcode0xCC;
    opcodeFunctionCB[0xCD] = nullptr; // = &CPU::CBopcode0xCD;
    opcodeFunctionCB[0xCE] = nullptr; // = &CPU::CBopcode0xCE;
    opcodeFunctionCB[0xCF] = nullptr; // = &CPU::CBopcode0xCF;
    opcodeFunctionCB[0xD0] = nullptr; // = &CPU::CBopcode0xD0;
    opcodeFunctionCB[0xD1] = nullptr; // = &CPU::CBopcode0xD1;
    opcodeFunctionCB[0xD2] = nullptr; // = &CPU::CBopcode0xD2;
    opcodeFunctionCB[0xD4] = nullptr; // = &CPU::CBopcode0xD4;
    opcodeFunctionCB[0xD5] = nullptr; // = &CPU::CBopcode0xD5;
    opcodeFunctionCB[0xD6] = nullptr; // = &CPU::CBopcode0xD6;
    opcodeFunctionCB[0xD7] = nullptr; // = &CPU::CBopcode0xD7;
    opcodeFunctionCB[0xD8] = nullptr; // = &CPU::CBopcode0xD8;
    opcodeFunctionCB[0xD9] = nullptr; // = &CPU::CBopcode0xD9;
    opcodeFunctionCB[0xDA] = nullptr; // = &CPU::CBopcode0xDA;
    opcodeFunctionCB[0xDC] = nullptr; // = &CPU::CBopcode0xDC;
    opcodeFunctionCB[0xDE] = nullptr; // = &CPU::CBopcode0xDE;
    opcodeFunctionCB[0xDF] = nullptr; // = &CPU::CBopcode0xDF;
    opcodeFunctionCB[0xE0] = nullptr; // = &CPU::CBopcode0xE0;
    opcodeFunctionCB[0xE1] = nullptr; // = &CPU::CBopcode0xE1;
    opcodeFunctionCB[0xE2] = nullptr; // = &CPU::CBopcode0xE2;
    opcodeFunctionCB[0xE5] = nullptr; // = &CPU::CBopcode0xE5;
    opcodeFunctionCB[0xE6] = nullptr; // = &CPU::CBopcode0xE6;
    opcodeFunctionCB[0xE7] = nullptr; // = &CPU::CBopcode0xE7;
    opcodeFunctionCB[0xE8] = nullptr; // = &CPU::CBopcode0xE8;
    opcodeFunctionCB[0xE9] = nullptr; // = &CPU::CBopcode0xE9;
    opcodeFunctionCB[0xEA] = nullptr; // = &CPU::CBopcode0xEA;
    opcodeFunctionCB[0xEE] = nullptr; // = &CPU::CBopcode0xEE;
    opcodeFunctionCB[0xEF] = nullptr; // = &CPU::CBopcode0xEF;
    opcodeFunctionCB[0xF0] = nullptr; // = &CPU::CBopcode0xF0;
    opcodeFunctionCB[0xF1] = nullptr; // = &CPU::CBopcode0xF1;
    opcodeFunctionCB[0xF2] = nullptr; // = &CPU::CBopcode0xF2;
    opcodeFunctionCB[0xF3] = nullptr; // = &CPU::CBopcode0xF3;
    opcodeFunctionCB[0xF5] = nullptr; // = &CPU::CBopcode0xF5;
    opcodeFunctionCB[0xF6] = nullptr; // = &CPU::CBopcode0xF6;
    opcodeFunctionCB[0xF7] = nullptr; // = &CPU::CBopcode0xF7;
    opcodeFunctionCB[0xF8] = nullptr; // = &CPU::CBopcode0xF8;
    opcodeFunctionCB[0xF9] = nullptr; // = &CPU::CBopcode0xF9;
    opcodeFunctionCB[0xFA] = nullptr; // = &CPU::CBopcode0xFA;
    opcodeFunctionCB[0xFB] = nullptr; // = &CPU::CBopcode0xFB;
    opcodeFunctionCB[0xFE] = &CPU::CBopcode0xFE;
    opcodeFunctionCB[0xFF] = nullptr; // = &CPU::CBopcode0xFF;

}
