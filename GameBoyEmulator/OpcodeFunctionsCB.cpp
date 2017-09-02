#include "CPU.h"

void CPU::CBopcode0x00() // RLC B
{
    RLC(regs.BC.high);
    counter += CBOpcodeTable[0x00].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x00].length;
}

void CPU::CBopcode0x01() // RLC C
{
    RLC(regs.BC.low);
    counter += CBOpcodeTable[0x01].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x01].length;
}

void CPU::CBopcode0x02() // RLC D
{
    RLC(regs.DE.high);
    counter += CBOpcodeTable[0x02].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x02].length;
}

void CPU::CBopcode0x03() // RLC E
{
    RLC(regs.DE.low);
    counter += CBOpcodeTable[0x03].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x03].length;
}

void CPU::CBopcode0x04() // RLC H
{
    RLC(regs.HL.high);
    counter += CBOpcodeTable[0x04].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x04].length;
}

void CPU::CBopcode0x05() // RLC L
{
    RLC(regs.HL.low);
    counter += CBOpcodeTable[0x05].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x05].length;
}

void CPU::CBopcode0x06() // RLC (HL)
{
    u8 byte = mmu->ReadByte(regs.HL.word);
    RLC(byte);
    mmu->WriteByte(regs.HL.word, byte);
    counter += CBOpcodeTable[0x06].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x06].length;
}

void CPU::CBopcode0x07() // RLC A
{
    RLC(regs.AF.high);
    counter += CBOpcodeTable[0x07].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x07].length;
}

void CPU::CBopcode0x08() // RRC B
{
    RRC(regs.BC.high);
    counter += CBOpcodeTable[0x08].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x08].length;
}

void CPU::CBopcode0x09() // RRC C
{
    RRC(regs.BC.low);
    counter += CBOpcodeTable[0x09].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x09].length;
}

void CPU::CBopcode0x0A() // RRC D
{
    RRC(regs.DE.high);
    counter += CBOpcodeTable[0x0A].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x0A].length;
}

void CPU::CBopcode0x0B() // RRC E
{
    RRC(regs.DE.low);
    counter += CBOpcodeTable[0x0B].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x0B].length;
}

void CPU::CBopcode0x0C() // RRC H
{
    RRC(regs.HL.high);
    counter += CBOpcodeTable[0x0C].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x0C].length;
}

void CPU::CBopcode0x0D() // RRC L
{
    RRC(regs.HL.low);
    counter += CBOpcodeTable[0x0D].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x0D].length;
}

void CPU::CBopcode0x0E() // RRC (HL)
{
    u8 byte = mmu->ReadByte(regs.HL.word);
    RRC(byte);
    mmu->WriteByte(regs.HL.word, byte);
    counter += CBOpcodeTable[0x0E].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x0E].length;
}

void CPU::CBopcode0x0F() // RRC A
{
    RRC(regs.AF.high);
    counter += CBOpcodeTable[0x0F].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x0F].length;
}

void CPU::CBopcode0x10() // RL B
{
    RL(regs.BC.high);
    counter += CBOpcodeTable[0x10].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x10].length;
}

void CPU::CBopcode0x11() // RL C
{
    RL(regs.BC.low);
    counter += CBOpcodeTable[0x11].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x11].length;
}

void CPU::CBopcode0x12() // RL D
{
    RL(regs.DE.high);
    counter += CBOpcodeTable[0x12].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x12].length;
}

void CPU::CBopcode0x13() // RL E
{
    RL(regs.DE.low);
    counter += CBOpcodeTable[0x13].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x13].length;
}

void CPU::CBopcode0x14() // RL H
{
    RL(regs.HL.high);
    counter += CBOpcodeTable[0x14].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x14].length;
}

void CPU::CBopcode0x15() // RL L
{
    RL(regs.HL.low);
    counter += CBOpcodeTable[0x15].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x15].length;
}

void CPU::CBopcode0x16() // RL (HL)
{
    u8 byte = mmu->ReadByte(regs.HL.word);
    RL(byte);
    mmu->WriteByte(regs.HL.word, byte);
    counter += CBOpcodeTable[0x16].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x16].length;
}

void CPU::CBopcode0x17() // RL A
{
    RL(regs.AF.high);
    counter += CBOpcodeTable[0x17].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x17].length;
}

void CPU::CBopcode0x18() // RRC B
{
    RRC(regs.BC.high);
    counter += CBOpcodeTable[0x18].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x18].length;
}

void CPU::CBopcode0x19() // RR C
{
    RR(regs.BC.low);
    counter += CBOpcodeTable[0x19].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x19].length;
}

void CPU::CBopcode0x1A() // RR D
{
    RR(regs.DE.high);
    counter += CBOpcodeTable[0x1A].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x1A].length;
}

void CPU::CBopcode0x1B() // RR E
{
    RR(regs.DE.low);
    counter += CBOpcodeTable[0x1B].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x1B].length;
}

void CPU::CBopcode0x1C() // RR H
{
    RR(regs.HL.high);
    counter += CBOpcodeTable[0x1C].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x1C].length;
}

void CPU::CBopcode0x1D() // RR L
{
    RR(regs.HL.low);
    counter += CBOpcodeTable[0x1D].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x1D].length;
}

void CPU::CBopcode0x1E() // RR (HL)
{
    u8 byte = mmu->ReadByte(regs.HL.word);
    RR(byte);
    mmu->WriteByte(regs.HL.word, byte);
    counter += CBOpcodeTable[0x1E].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x1E].length;
}

void CPU::CBopcode0x1F() // RR A
{
    RR(regs.AF.high);
    counter += CBOpcodeTable[0x1F].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x1F].length;
}


void CPU::CBopcode0x20() // SLA B
{
    SLA(regs.BC.high);
    counter += CBOpcodeTable[0x20].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x20].length;
}

void CPU::CBopcode0x21() // SLA C
{
    SLA(regs.BC.low);
    counter += CBOpcodeTable[0x21].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x21].length;
}

void CPU::CBopcode0x22() // SLA D
{
    SLA(regs.DE.high);
    counter += CBOpcodeTable[0x22].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x22].length;
}

void CPU::CBopcode0x23() // SLA E
{
    SLA(regs.DE.low);
    counter += CBOpcodeTable[0x23].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x23].length;
}

void CPU::CBopcode0x24() // SLA H
{
    SLA(regs.HL.high);
    counter += CBOpcodeTable[0x24].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x24].length;
}

void CPU::CBopcode0x25() // SLA L
{
    SLA(regs.HL.low);
    counter += CBOpcodeTable[0x25].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x25].length;
}

void CPU::CBopcode0x26() // SLA (HL)
{
    u8 byte = mmu->ReadByte(regs.HL.word);
    SLA(byte);
    mmu->WriteByte(regs.HL.word, byte);
    counter += CBOpcodeTable[0x26].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x26].length;
}

void CPU::CBopcode0x27() // SLA A
{
    SLA(regs.AF.high);
    counter += CBOpcodeTable[0x27].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x27].length;
}

void CPU::CBopcode0x28() // SRA B
{
    SRA(regs.BC.high);
    counter += CBOpcodeTable[0x28].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x28].length;
}

void CPU::CBopcode0x29() // SRA C
{
    SRA(regs.BC.low);
    counter += CBOpcodeTable[0x29].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x29].length;
}

void CPU::CBopcode0x2A() // SRA D
{
    SRA(regs.DE.high);
    counter += CBOpcodeTable[0x2A].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x2A].length;
}

void CPU::CBopcode0x2B() // SRA E
{
    SRA(regs.DE.low);
    counter += CBOpcodeTable[0x2B].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x2B].length;
}

void CPU::CBopcode0x2C() // SRA H
{
    SRA(regs.HL.high);
    counter += CBOpcodeTable[0x2C].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x2C].length;
}

void CPU::CBopcode0x2D() // SRA L
{
    SRA(regs.HL.high);
    counter += CBOpcodeTable[0x2D].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x2D].length;
}

void CPU::CBopcode0x2E() // SRA (HL)
{
    u8 byte = mmu->ReadByte(regs.HL.word);
    SRA(byte);
    mmu->WriteByte(regs.HL.word, byte);
    counter += CBOpcodeTable[0x2E].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x2E].length;
}

void CPU::CBopcode0x2F() // SRA A
{
    SRA(regs.AF.high);
    counter += CBOpcodeTable[0x2F].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x2F].length;
}

void CPU::CBopcode0x30() // SWAP B
{
    SWAP(regs.BC.high);
    counter += CBOpcodeTable[0x30].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x30].length;
}

void CPU::CBopcode0x31() // SWAP C
{
    SWAP(regs.BC.low);
    counter += CBOpcodeTable[0x31].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x31].length;
}

void CPU::CBopcode0x32() // SWAP D
{
    SWAP(regs.DE.high);
    counter += CBOpcodeTable[0x32].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x32].length;
}

void CPU::CBopcode0x33() // SWAP E
{
    SWAP(regs.DE.low);
    counter += CBOpcodeTable[0x33].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x33].length;
}

void CPU::CBopcode0x34() // SWAP H
{
    SWAP(regs.HL.high);
    counter += CBOpcodeTable[0x34].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x34].length;
}

void CPU::CBopcode0x35() // SWAP L
{
    SWAP(regs.HL.low);
    counter += CBOpcodeTable[0x35].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x35].length;
}

void CPU::CBopcode0x36() // SWAP (HL)
{
    u8 byte = mmu->ReadByte(regs.HL.word);
    SWAP(byte);
    mmu->WriteByte(regs.HL.word, byte);
    counter += CBOpcodeTable[0x36].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x36].length;
}

void CPU::CBopcode0x37() // SWAP A
{
    SWAP(regs.AF.high);
    counter += CBOpcodeTable[0x37].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x37].length;
}

void CPU::CBopcode0x38() // SRL B
{
    SRL(regs.BC.high);
    counter += CBOpcodeTable[0x38].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x38].length;
}

void CPU::CBopcode0x39() // SRL B
{
    SRL(regs.BC.low);
    counter += CBOpcodeTable[0x39].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x39].length;
}

void CPU::CBopcode0x3A() // SRL D
{
    SRL(regs.DE.high);
    counter += CBOpcodeTable[0x3A].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x3A].length;
}

void CPU::CBopcode0x3B() // SRL E
{
    SRL(regs.DE.low);
    counter += CBOpcodeTable[0x3B].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x3B].length;
}

void CPU::CBopcode0x3C() // SRL H
{
    SRL(regs.HL.high);
    counter += CBOpcodeTable[0x3C].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x3C].length;
}

void CPU::CBopcode0x3D() // SRL L
{
    SRL(regs.HL.low);
    counter += CBOpcodeTable[0x3D].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x3D].length;
}

void CPU::CBopcode0x3E() // SRL (HL)
{
    u8 byte = mmu->ReadByte(regs.HL.word);
    SRL(byte);
    mmu->WriteByte(regs.HL.word, byte);
    counter += CBOpcodeTable[0x3E].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x3E].length;
}

void CPU::CBopcode0x3F() // SRL A
{
    SRL(regs.AF.high);
    counter += CBOpcodeTable[0x3F].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x3F].length;
}

void CPU::CBopcode0x40() // BIT 0,B
{
    BIT(0x01, regs.BC.high);
    counter += CBOpcodeTable[0x40].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x40].length;
}

void CPU::CBopcode0x41() // BIT 0,C
{
    BIT(0x01, regs.BC.low);
    counter += CBOpcodeTable[0x41].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x41].length;
}

void CPU::CBopcode0x42() // BIT 0,D
{
    BIT(0x01, regs.DE.high);
    counter += CBOpcodeTable[0x42].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x42].length;
}

void CPU::CBopcode0x43() // BIT 0,E
{
    BIT(0x01, regs.DE.low);
    counter += CBOpcodeTable[0x43].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x43].length;
}

void CPU::CBopcode0x44() // BIT 0,H
{
    BIT(0x01, regs.HL.high);
    counter += CBOpcodeTable[0x44].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x44].length;
}

void CPU::CBopcode0x45() // BIT 0,L
{
    BIT(0x01, regs.HL.low);
    counter += CBOpcodeTable[0x45].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x45].length;
}

void CPU::CBopcode0x46() // BIT 0, (HL)
{
	BIT(0x01, mmu->ReadByte(regs.HL.word));
    counter += CBOpcodeTable[0x46].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x46].length;
}

void CPU::CBopcode0x47() // BIT 0,A
{
    BIT(0x01, regs.AF.high);
    counter += CBOpcodeTable[0x47].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x47].length;
}

void CPU::CBopcode0x48() // BIT 1,B
{
    BIT(0x02, regs.BC.high);
    counter += CBOpcodeTable[0x48].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x48].length;
}

void CPU::CBopcode0x49() // BIT 1,C
{
    BIT(0x02, regs.BC.low);
    counter += CBOpcodeTable[0x49].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x49].length;
}

void CPU::CBopcode0x4A() // BIT 1,D
{
    BIT(0x02, regs.DE.high);
    counter += CBOpcodeTable[0x4A].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x4A].length;
}

void CPU::CBopcode0x4B() // BIT 1,E
{
    BIT(0x02, regs.DE.low);
    counter += CBOpcodeTable[0x4B].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x4B].length;
}

void CPU::CBopcode0x4C() // BIT 1,H
{
    BIT(0x02, regs.HL.high);
    counter += CBOpcodeTable[0x4C].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x4C].length;
}

void CPU::CBopcode0x4D() // BIT 1,L
{
    BIT(0x02, regs.HL.low);
    counter += CBOpcodeTable[0x4D].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x4D].length;
}

void CPU::CBopcode0x4E() // BIT 1,(HL)
{
    BIT(0x02, mmu->ReadByte(regs.HL.word));
    counter += CBOpcodeTable[0x4E].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x4E].length;
}

void CPU::CBopcode0x4F() // BIT 1,A
{
    BIT(0x02, regs.AF.high);
    counter += CBOpcodeTable[0x4F].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x4F].length;
}

void CPU::CBopcode0x50() // BIT 2,B
{
    BIT(0x04, regs.BC.high);
    counter += CBOpcodeTable[0x50].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x50].length;
}

void CPU::CBopcode0x51() // BIT 2,C
{
    BIT(0x04, regs.BC.low);
    counter += CBOpcodeTable[0x51].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x51].length;
}

void CPU::CBopcode0x52() // BIT 2,D
{
    BIT(0x04, regs.DE.high);
    counter += CBOpcodeTable[0x52].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x52].length;
}

void CPU::CBopcode0x53() // BIT 2,E
{
    BIT(0x04, regs.DE.low);
    counter += CBOpcodeTable[0x53].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x53].length;
}

void CPU::CBopcode0x54() // BIT 2,H
{
    BIT(0x04, regs.HL.high);
    counter += CBOpcodeTable[0x54].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x54].length;
}

void CPU::CBopcode0x55() // BIT 2,L
{
    BIT(0x04, regs.HL.low);
    counter += CBOpcodeTable[0x55].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x55].length;
}

void CPU::CBopcode0x56() // BIT 2,(HL)
{
    u8 byte = mmu->ReadByte(regs.HL.word);
    BIT(0x04, byte);
    mmu->WriteByte(regs.HL.word, byte);
    counter += CBOpcodeTable[0x56].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x56].length;
}


void CPU::CBopcode0x57() // BIT 2,A
{
    BIT(0x04, regs.AF.high);
    counter += CBOpcodeTable[0x57].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x57].length;
}

void CPU::CBopcode0x58() // BIT 3,B
{
    BIT(0x08, regs.BC.high);
    counter += CBOpcodeTable[0x58].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x58].length;
}

void CPU::CBopcode0x59() // BIT 3,C
{
    BIT(0x08, regs.BC.low);
    counter += CBOpcodeTable[0x59].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x59].length;
}

void CPU::CBopcode0x5A() // BIT 3,D
{
    BIT(0x08, regs.DE.high);
    counter += CBOpcodeTable[0x5A].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x5A].length;
}

void CPU::CBopcode0x5B() // BIT 3,E
{
    BIT(0x08, regs.DE.low);
    counter += CBOpcodeTable[0x5B].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x5B].length;
}

void CPU::CBopcode0x5C() // BIT 3,H
{
    BIT(0x08, regs.HL.high);
    counter += CBOpcodeTable[0x5C].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x5C].length;
}

void CPU::CBopcode0x5D() // BIT 3,L
{
    BIT(0x08, regs.HL.low);
    counter += CBOpcodeTable[0x5D].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x5D].length;
}

void CPU::CBopcode0x5E() // BIT 3,(HL)
{
    BIT(0x08, mmu->ReadByte(regs.HL.word));
    counter += CBOpcodeTable[0x5E].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x5E].length;
}

void CPU::CBopcode0x5F() // BIT 3,A
{
    BIT(0x08, regs.AF.high);
    counter += CBOpcodeTable[0x5F].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x5F].length;
}

void CPU::CBopcode0x60() // BIT 4,B
{
    BIT(0x10, regs.BC.high);
    counter += CBOpcodeTable[0x60].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x60].length;
}

void CPU::CBopcode0x61() // BIT 4,C
{
    BIT(0x10, regs.BC.low);
    counter += CBOpcodeTable[0x61].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x61].length;
}

void CPU::CBopcode0x62() // BIT 4,D
{
    BIT(0x10, regs.DE.high);
    counter += CBOpcodeTable[0x62].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x62].length;
}

void CPU::CBopcode0x63() // BIT 4,E
{
    BIT(0x10, regs.DE.low);
    counter += CBOpcodeTable[0x63].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x63].length;
}

void CPU::CBopcode0x64() // BIT 4,H
{
    BIT(0x10, regs.HL.high);
    counter += CBOpcodeTable[0x64].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x64].length;
}

void CPU::CBopcode0x65() // BIT 4,L
{
    BIT(0x10, regs.HL.low);
    counter += CBOpcodeTable[0x65].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x65].length;
}

void CPU::CBopcode0x66() // BIT 4,(HL)
{
    u8 byte = mmu->ReadByte(regs.HL.word);
    BIT(0x10, byte);
    mmu->WriteByte(regs.HL.word, byte);
    counter += CBOpcodeTable[0x66].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x66].length;
}

void CPU::CBopcode0x67() //BIT 4,A
{
    BIT(0x10, regs.AF.high);
    counter += CBOpcodeTable[0x67].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x67].length;
}


void CPU::CBopcode0x68() // BIT 5,B
{
    BIT(0x20, regs.BC.high);
    counter += CBOpcodeTable[0x68].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x68].length;
}

void CPU::CBopcode0x69() // BIT 5,C
{
    BIT(0x20, regs.BC.low);
    counter += CBOpcodeTable[0x69].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x69].length;
}

void CPU::CBopcode0x6A() // BIT 5,D
{
    BIT(0x20, regs.DE.high);
    counter += CBOpcodeTable[0x6A].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x6A].length;
}

void CPU::CBopcode0x6B() // BIT 5,E
{
    BIT(0x20, regs.DE.low);
    counter += CBOpcodeTable[0x6B].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x6B].length;
}

void CPU::CBopcode0x6C() // BIT 5,H
{
    BIT(0x20, regs.HL.high);
    counter += CBOpcodeTable[0x6C].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x6C].length;
}

void CPU::CBopcode0x6D() // BIT 5,L
{
    BIT(0x20, regs.HL.low);
    counter += CBOpcodeTable[0x6D].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x6D].length;
}

void CPU::CBopcode0x6E() // BIT 5,(HL)
{
    BIT(0x20, mmu->ReadByte(regs.HL.word));
    counter += CBOpcodeTable[0x6E].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x6E].length;
}

void CPU::CBopcode0x6F() // BIT 5,A
{
    BIT(0x20, regs.AF.high);
    counter += CBOpcodeTable[0x6F].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x6F].length;
}

void CPU::CBopcode0x70() // BIT 6,B
{
    BIT(0x40, regs.BC.high);
    counter += CBOpcodeTable[0x70].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x70].length;
}

void CPU::CBopcode0x71() // BIT 6,C
{
    BIT(0x40, regs.BC.low);
    counter += CBOpcodeTable[0x71].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x71].length;
}

void CPU::CBopcode0x72() // BIT 6,D
{
    BIT(0x40, regs.DE.high);
    counter += CBOpcodeTable[0x72].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x72].length;
}

void CPU::CBopcode0x73() // BIT 6,E
{
    BIT(0x40, regs.DE.low);
    counter += CBOpcodeTable[0x73].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x73].length;
}

void CPU::CBopcode0x74() // BIT 6,H
{
    BIT(0x40, regs.HL.high);
    counter += CBOpcodeTable[0x74].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x74].length;
}

void CPU::CBopcode0x75() // BIT 6,L
{
    BIT(0x40, regs.HL.low);
    counter += CBOpcodeTable[0x75].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x75].length;
}

void CPU::CBopcode0x76() // BIT 6,(HL)
{
    u8 byte = mmu->ReadByte(regs.HL.word);
    BIT(0x40, byte);
    mmu->WriteByte(regs.HL.word, byte);
    counter += CBOpcodeTable[0x76].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x76].length;
}


void CPU::CBopcode0x77() //BIT 6,A
{
    BIT(0x40, regs.AF.high);
    counter += CBOpcodeTable[0x77].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x77].length;
}

void CPU::CBopcode0x78() //BIT 7,B
{
    BIT(0x80, regs.BC.high);
    counter += CBOpcodeTable[0x78].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x78].length;
}

void CPU::CBopcode0x79() // BIT 7,C
{
    BIT(0x80, regs.BC.low);
    counter += CBOpcodeTable[0x79].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x79].length;
}

void CPU::CBopcode0x7A() // BIT 7,D
{
    BIT(0x80, regs.DE.high);
    counter += CBOpcodeTable[0x7A].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x7A].length;
}

void CPU::CBopcode0x7B() // BIT 7,E
{
    BIT(0x80, regs.DE.low);
    counter += CBOpcodeTable[0x7B].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x7B].length;
}

void CPU::CBopcode0x7C() // BIT 7,H
{
    BIT(0x80, regs.HL.high);
    counter += CBOpcodeTable[0x7C].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x7C].length;
}

void CPU::CBopcode0x7D() // BIT 7,L
{
    BIT(0x80, regs.HL.low);
    counter += CBOpcodeTable[0x7D].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x7D].length;
}

void CPU::CBopcode0x7E() // BIT 7,(HL)
{
    BIT(0x80, mmu->ReadByte(regs.HL.word));
    counter += CBOpcodeTable[0x7E].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x7E].length;
}

void CPU::CBopcode0x7F() // BIT 7,A
{
    BIT(0x80, regs.AF.high);
    counter += CBOpcodeTable[0x7F].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x7F].length;
}














void CPU::CBopcode0x80() // RES 0,B
{
    RES(0x01, regs.BC.high);
    counter += CBOpcodeTable[0x80].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x80].length;
}

void CPU::CBopcode0x81() // RES 0,C
{
    RES(0x01, regs.BC.low);
    counter += CBOpcodeTable[0x81].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x81].length;
}

void CPU::CBopcode0x82() // RES 0,D
{
    RES(0x01, regs.DE.high);
    counter += CBOpcodeTable[0x82].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x82].length;
}

void CPU::CBopcode0x83() // RES 0,E
{
    RES(0x01, regs.DE.low);
    counter += CBOpcodeTable[0x83].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x83].length;
}

void CPU::CBopcode0x84() // RES 0,H
{
    RES(0x01, regs.HL.high);
    counter += CBOpcodeTable[0x84].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x84].length;
}

void CPU::CBopcode0x85() // RES 0,L
{
    RES(0x01, regs.HL.low);
    counter += CBOpcodeTable[0x85].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x85].length;
}

void CPU::CBopcode0x86() // RES 0,(HL)
{
    u8 byte = mmu->ReadByte(regs.HL.word);
    RES(0x01, byte);
    mmu->WriteByte(regs.HL.word, byte);
    counter += CBOpcodeTable[0x86].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x86].length;
}

void CPU::CBopcode0x87() // RES 0,A
{
    RES(0x01, regs.AF.high);
    counter += CBOpcodeTable[0x87].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x87].length;
}

void CPU::CBopcode0x88() // RES 1,B
{
    RES(0x02, regs.BC.high);
    counter += CBOpcodeTable[0x88].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x88].length;
}

void CPU::CBopcode0x89() // RES 1,C
{
    RES(0x02, regs.BC.low);
    counter += CBOpcodeTable[0x89].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x89].length;
}

void CPU::CBopcode0x8A() // RES 1,D
{
    RES(0x02, regs.DE.high);
    counter += CBOpcodeTable[0x8A].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x8A].length;
}

void CPU::CBopcode0x8B() // RES 1,E
{
    RES(0x02, regs.DE.low);
    counter += CBOpcodeTable[0x8B].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x8B].length;
}

void CPU::CBopcode0x8C() // RES 1,H
{
    RES(0x02, regs.HL.high);
    counter += CBOpcodeTable[0x8C].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x8C].length;
}

void CPU::CBopcode0x8D() // RES 1,L
{
    RES(0x02, regs.HL.low);
    counter += CBOpcodeTable[0x8D].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x8D].length;
}

void CPU::CBopcode0x8E() // RES 1,(HL)
{
    u8 byte = mmu->ReadByte(regs.HL.word);
    RES(0x02, byte);
    mmu->WriteByte(regs.HL.word, byte);
    counter += CBOpcodeTable[0x8E].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x8E].length;
}

void CPU::CBopcode0x8F() // RES 1,A
{
    RES(0x02, regs.AF.high);
    counter += CBOpcodeTable[0x8F].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x8F].length;
}



void CPU::CBopcode0x90() // RES 2,B
{
    RES(0x04, regs.BC.high);
    counter += CBOpcodeTable[0x90].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x90].length;
}

void CPU::CBopcode0x91() // RES 2,C
{
    RES(0x04, regs.BC.low);
    counter += CBOpcodeTable[0x91].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x91].length;
}

void CPU::CBopcode0x92() // RES 2,D
{
    RES(0x04, regs.DE.high);
    counter += CBOpcodeTable[0x92].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x92].length;
}

void CPU::CBopcode0x93() // RES 2,E
{
    RES(0x04, regs.DE.low);
    counter += CBOpcodeTable[0x93].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x93].length;
}

void CPU::CBopcode0x94() // RES 2,H
{
    RES(0x04, regs.HL.high);
    counter += CBOpcodeTable[0x94].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x94].length;
}

void CPU::CBopcode0x95() // RES 2,L
{
    RES(0x04, regs.HL.low);
    counter += CBOpcodeTable[0x95].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x95].length;
}

void CPU::CBopcode0x96() // RES 2,(HL)
{
    u8 byte = mmu->ReadByte(regs.HL.word);
    RES(0x04, byte);
    mmu->WriteByte(regs.HL.word, byte);
    counter += CBOpcodeTable[0x96].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x96].length;
}

void CPU::CBopcode0x97() // RES 2,A
{
    RES(0x04, regs.AF.high);
    counter += CBOpcodeTable[0x97].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x97].length;
}

void CPU::CBopcode0x98() // RES 3,B
{
    RES(0x08, regs.BC.high);
    counter += CBOpcodeTable[0x98].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x98].length;
}

void CPU::CBopcode0x99() // RES 3,C
{
    RES(0x08, regs.BC.low);
    counter += CBOpcodeTable[0x99].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x99].length;
}

void CPU::CBopcode0x9A() // RES 3,D
{
    RES(0x08, regs.DE.high);
    counter += CBOpcodeTable[0x9A].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x9A].length;
}

void CPU::CBopcode0x9B() // RES 3,E
{
    RES(0x08, regs.DE.low);
    counter += CBOpcodeTable[0x9B].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x9B].length;
}

void CPU::CBopcode0x9C() // RES 3,H
{
    RES(0x08, regs.HL.high);
    counter += CBOpcodeTable[0x9C].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x9C].length;
}

void CPU::CBopcode0x9D() // RES 3,L
{
    RES(0x08, regs.HL.low);
    counter += CBOpcodeTable[0x9D].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x9D].length;
}

void CPU::CBopcode0x9E() // RES 3,(HL)
{
    u8 byte = mmu->ReadByte(regs.HL.word);
    RES(0x08, byte);
    mmu->WriteByte(regs.HL.word, byte);
    counter += CBOpcodeTable[0x9E].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x9E].length;
}

void CPU::CBopcode0x9F() // RES 3,A
{
    RES(0x08, regs.AF.high);
    counter += CBOpcodeTable[0x9F].duration.firstCondition;
    regs.pc += CBOpcodeTable[0x9F].length;
}



void CPU::CBopcode0xA0() // RES 4,B
{
    RES(0x10, regs.BC.high);
    counter += CBOpcodeTable[0xA0].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xA0].length;
}

void CPU::CBopcode0xA1() // RES 4,C
{
    RES(0x10, regs.BC.low);
    counter += CBOpcodeTable[0xA1].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xA1].length;
}

void CPU::CBopcode0xA2() // RES 4,D
{
    RES(0x10, regs.DE.high);
    counter += CBOpcodeTable[0xA2].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xA2].length;
}

void CPU::CBopcode0xA3() // RES 4,E
{
    RES(0x10, regs.DE.low);
    counter += CBOpcodeTable[0xA3].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xA3].length;
}

void CPU::CBopcode0xA4() // RES 4,H
{
    RES(0x10, regs.HL.high);
    counter += CBOpcodeTable[0xA4].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xA4].length;
}

void CPU::CBopcode0xA5() // RES 4,L
{
    RES(0x10, regs.HL.low);
    counter += CBOpcodeTable[0xA5].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xA5].length;
}

void CPU::CBopcode0xA6() // RES 4,(HL)
{
    u8 byte = mmu->ReadByte(regs.HL.word);
    RES(0x10, byte);
    mmu->WriteByte(regs.HL.word, byte);
    counter += CBOpcodeTable[0xA6].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xA6].length;
}

void CPU::CBopcode0xA7() // RES 4,A
{
    RES(0x10, regs.AF.high);
    counter += CBOpcodeTable[0xA7].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xA7].length;
}

void CPU::CBopcode0xA8() // RES 5,B
{
    RES(0x20, regs.BC.high);
    counter += CBOpcodeTable[0xA8].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xA8].length;
}

void CPU::CBopcode0xA9() // RES 5,C
{
    RES(0x20, regs.BC.low);
    counter += CBOpcodeTable[0xA9].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xA9].length;
}

void CPU::CBopcode0xAA() // RES 5,D
{
    RES(0x20, regs.DE.high);
    counter += CBOpcodeTable[0xAA].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xAA].length;
}

void CPU::CBopcode0xAB() // RES 5,E
{
    RES(0x20, regs.DE.low);
    counter += CBOpcodeTable[0xAB].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xAB].length;
}

void CPU::CBopcode0xAC() // RES 5,H
{
    RES(0x20, regs.HL.high);
    counter += CBOpcodeTable[0xAC].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xAC].length;
}

void CPU::CBopcode0xAD() // RES 5,L
{
    RES(0x20, regs.HL.low);
    counter += CBOpcodeTable[0xAD].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xAD].length;
}

void CPU::CBopcode0xAE() // RES 5,(HL)
{
    u8 byte = mmu->ReadByte(regs.HL.word);
    RES(0x20, byte);
    mmu->WriteByte(regs.HL.word, byte);
    counter += CBOpcodeTable[0xAE].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xAE].length;
}

void CPU::CBopcode0xAF() // RES 5,A
{
    RES(0x20, regs.AF.high);
    counter += CBOpcodeTable[0xAF].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xAF].length;
}



void CPU::CBopcode0xB0() // RES 6,B
{
    RES(0x40, regs.BC.high);
    counter += CBOpcodeTable[0xB0].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xB0].length;
}

void CPU::CBopcode0xB1() // RES 6,C
{
    RES(0x40, regs.BC.low);
    counter += CBOpcodeTable[0xB1].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xB1].length;
}

void CPU::CBopcode0xB2() // RES 6,D
{
    RES(0x40, regs.DE.high);
    counter += CBOpcodeTable[0xB2].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xB2].length;
}

void CPU::CBopcode0xB3() // RES 6,E
{
    RES(0x40, regs.DE.low);
    counter += CBOpcodeTable[0xB3].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xB3].length;
}

void CPU::CBopcode0xB4() // RES 6,H
{
    RES(0x40, regs.HL.high);
    counter += CBOpcodeTable[0xB4].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xB4].length;
}

void CPU::CBopcode0xB5() // RES 6,L
{
    RES(0x40, regs.HL.low);
    counter += CBOpcodeTable[0xB5].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xB5].length;
}

void CPU::CBopcode0xB6() // RES 6,(HL)
{
    u8 byte = mmu->ReadByte(regs.HL.word);
    RES(0x40, byte);
    mmu->WriteByte(regs.HL.word, byte);
    counter += CBOpcodeTable[0xB6].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xB6].length;
}

void CPU::CBopcode0xB7() // RES 6,A
{
    RES(0x40, regs.AF.high);
    counter += CBOpcodeTable[0xB7].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xB7].length;
}

void CPU::CBopcode0xB8() // RES 7,B
{
    RES(0x80, regs.BC.high);
    counter += CBOpcodeTable[0xB8].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xB8].length;
}

void CPU::CBopcode0xB9() // RES 7,C
{
    RES(0x80, regs.BC.low);
    counter += CBOpcodeTable[0xB9].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xB9].length;
}

void CPU::CBopcode0xBA() // RES 7,D
{
    RES(0x80, regs.DE.high);
    counter += CBOpcodeTable[0xBA].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xBA].length;
}

void CPU::CBopcode0xBB() // RES 7,E
{
    RES(0x80, regs.DE.low);
    counter += CBOpcodeTable[0xBB].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xBB].length;
}

void CPU::CBopcode0xBC() // RES 7,H
{
    RES(0x80, regs.HL.high);
    counter += CBOpcodeTable[0xBC].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xBC].length;
}

void CPU::CBopcode0xBD() // RES 7,L
{
    RES(0x80, regs.HL.low);
    counter += CBOpcodeTable[0xBD].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xBD].length;
}

void CPU::CBopcode0xBE() // RES 7,(HL)
{
	u8 byte = mmu->ReadByte(regs.HL.word);
	RES(0x80, byte);
	mmu->WriteByte(regs.HL.word, byte);
    counter += CBOpcodeTable[0xBE].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xBE].length;
}

void CPU::CBopcode0xBF() // RES 7,A
{
    RES(0x80, regs.AF.high);
    counter += CBOpcodeTable[0xBF].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xBF].length;
}



void CPU::CBopcode0xC0() // SET 0,B
{
    SET(0x01, regs.BC.high);
    counter += CBOpcodeTable[0xC0].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xC0].length;
}

void CPU::CBopcode0xC1() // SET 0,C
{
    SET(0x01, regs.BC.low);
    counter += CBOpcodeTable[0xC1].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xC1].length;
}

void CPU::CBopcode0xC2() // SET 0,D
{
    SET(0x01, regs.DE.high);
    counter += CBOpcodeTable[0xC2].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xC2].length;
}

void CPU::CBopcode0xC3() // SET 0,D
{
    SET(0x01, regs.DE.low);
    counter += CBOpcodeTable[0xD3].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xD3].length;
}

void CPU::CBopcode0xC4() // SET 0,H
{
    SET(0x01, regs.HL.high);
    counter += CBOpcodeTable[0xC4].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xC4].length;
}

void CPU::CBopcode0xC5() // SET 0,L
{
    SET(0x01, regs.HL.low);
    counter += CBOpcodeTable[0xC5].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xC5].length;
}

void CPU::CBopcode0xC6() // SET 0,(HL)
{
    u8 byte = mmu->ReadByte(regs.HL.word);
    SET(0x01, byte);
    mmu->WriteByte(regs.HL.word, byte);
    counter += CBOpcodeTable[0xC6].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xC6].length;
}

void CPU::CBopcode0xC7() // SET 0,A
{
    SET(0x01, regs.AF.high);
    counter += CBOpcodeTable[0xC7].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xC7].length;
}

void CPU::CBopcode0xC8() // SET 1,B
{
    SET(0x02, regs.BC.high);
    counter += CBOpcodeTable[0xC8].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xC8].length;
}

void CPU::CBopcode0xC9() // SET 1,C
{
    SET(0x02, regs.BC.low);
    counter += CBOpcodeTable[0xC9].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xC9].length;
}

void CPU::CBopcode0xCA() // SET 1,D
{
    SET(0x02, regs.DE.high);
    counter += CBOpcodeTable[0xCA].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xCA].length;
}

void CPU::CBopcode0xCB() // SET 1,E
{
    SET(0x02, regs.DE.low);
    counter += CBOpcodeTable[0xCB].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xCB].length;
}

void CPU::CBopcode0xCC() // SET 1,H
{
    SET(0x02, regs.HL.high);
    counter += CBOpcodeTable[0xCD].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xCD].length;
}

void CPU::CBopcode0xCD() // SET 1,L
{
    SET(0x02, regs.HL.low);
    counter += CBOpcodeTable[0xCD].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xCD].length;
}

void CPU::CBopcode0xCE() // SET 1,(HL)
{
    u8 byte = mmu->ReadByte(regs.HL.word);
    SET(0x02, byte);
    mmu->WriteByte(regs.HL.word, byte);
    counter += CBOpcodeTable[0xCE].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xCE].length;
}

void CPU::CBopcode0xCF() // SET 1,A
{
    SET(0x02, regs.AF.high);
    counter += CBOpcodeTable[0xCF].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xCF].length;
}



void CPU::CBopcode0xD0() // SET 2,B
{
    SET(0x04, regs.BC.high);
    counter += CBOpcodeTable[0xD0].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xD0].length;
}

void CPU::CBopcode0xD1() // SET 2,C
{
    SET(0x04, regs.BC.low);
    counter += CBOpcodeTable[0xD1].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xD1].length;
}

void CPU::CBopcode0xD2() // SET 2,D
{
    SET(0x04, regs.DE.high);
    counter += CBOpcodeTable[0xD2].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xD2].length;
}

void CPU::CBopcode0xD3() // SET 2,D
{
    SET(0x04, regs.DE.low);
    counter += CBOpcodeTable[0xD3].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xD3].length;
}

void CPU::CBopcode0xD4() // SET 2,H
{
    SET(0x04, regs.HL.high);
    counter += CBOpcodeTable[0xD4].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xD4].length;
}

void CPU::CBopcode0xD5() // SET 2,L
{
    SET(0x04, regs.HL.low);
    counter += CBOpcodeTable[0xD5].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xD5].length;
}

void CPU::CBopcode0xD6() // SET 2,(HL)
{
    u8 byte = mmu->ReadByte(regs.HL.word);
    SET(0x04, byte);
    mmu->WriteByte(regs.HL.word, byte);
    counter += CBOpcodeTable[0xD6].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xD6].length;
}

void CPU::CBopcode0xD7() // SET 2,A
{
    SET(0x04, regs.AF.high);
    counter += CBOpcodeTable[0xD7].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xD7].length;
}

void CPU::CBopcode0xD8() // SET 3,B
{
    SET(0x08, regs.BC.high);
    counter += CBOpcodeTable[0xD8].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xD8].length;
}

void CPU::CBopcode0xD9() // SET 3,C
{
    SET(0x08, regs.BC.low);
    counter += CBOpcodeTable[0xD9].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xD9].length;
}

void CPU::CBopcode0xDA() // SET 3,D
{
    SET(0x08, regs.DE.high);
    counter += CBOpcodeTable[0xDA].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xDA].length;
}

void CPU::CBopcode0xDB() // SET 3,E
{
    SET(0x08, regs.DE.low);
    counter += CBOpcodeTable[0xDB].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xDB].length;
}

void CPU::CBopcode0xDC() // SET 3,H
{
    SET(0x08, regs.HL.high);
    counter += CBOpcodeTable[0xDD].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xDD].length;
}

void CPU::CBopcode0xDD() // SET 3,L
{
    SET(0x08, regs.HL.low);
    counter += CBOpcodeTable[0xDL].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xDL].length;
}

void CPU::CBopcode0xDE() // SET 3,(HL)
{
    u8 byte = mmu->ReadByte(regs.HL.word);
    SET(0x08, byte);
    mmu->WriteByte(regs.HL.word, byte);
    counter += CBOpcodeTable[0xDE].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xDE].length;
}

void CPU::CBopcode0xDF() // SET 3,A
{
    SET(0x08, regs.AF.high);
    counter += CBOpcodeTable[0xDF].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xDF].length;
}



void CPU::CBopcode0xE0() // SET 4,B
{
    SET(0x10, regs.BC.high);
    counter += CBOpcodeTable[0xE0].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xE0].length;
}

void CPU::CBopcode0xE1() // SET 4,C
{
    SET(0x10, regs.BC.low);
    counter += CBOpcodeTable[0xE1].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xE1].length;
}

void CPU::CBopcode0xE2() // SET 4,D
{
    SET(0x10, regs.DE.high);
    counter += CBOpcodeTable[0xE2].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xE2].length;
}

void CPU::CBopcode0xE3() // SET 4,E
{
    SET(0x10, regs.DE.low);
    counter += CBOpcodeTable[0xE3].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xE3].length;
}

void CPU::CBopcode0xE4() // SET 4,H
{
    SET(0x10, regs.HL.high);
    counter += CBOpcodeTable[0xE4].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xE4].length;
}

void CPU::CBopcode0xE5() // SET 4,L
{
    SET(0x10, regs.HL.low);
    counter += CBOpcodeTable[0xE5].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xE5].length;
}

void CPU::CBopcode0xE6() // SET 4,(HL)
{
    u8 byte = mmu->ReadByte(regs.HL.word);
    SET(0x10, byte);
    mmu->WriteByte(regs.HL.word, byte);
    counter += CBOpcodeTable[0xE6].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xE6].length;
}

void CPU::CBopcode0xE7() // SET 4,A
{
    SET(0x10, regs.AF.high);
    counter += CBOpcodeTable[0xE7].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xE7].length;
}

void CPU::CBopcode0xE8() // SET 5,B
{
    SET(0x20, regs.BC.high);
    counter += CBOpcodeTable[0xE8].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xE8].length;
}

void CPU::CBopcode0xE9() // SET 5,C
{
    SET(0x20, regs.BC.low);
    counter += CBOpcodeTable[0xE9].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xE9].length;
}

void CPU::CBopcode0xEA() // SET 5,D
{
    SET(0x20, regs.DE.high);
    counter += CBOpcodeTable[0xEA].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xEA].length;
}

void CPU::CBopcode0xEB() // SET 5,E
{
    SET(0x20, regs.DE.low);
    counter += CBOpcodeTable[0xEB].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xEB].length;
}

void CPU::CBopcode0xEC() // SET 5,H
{
    SET(0x20, regs.HL.high);
    counter += CBOpcodeTable[0xEC].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xEC].length;
}

void CPU::CBopcode0xED() // SET 5,L
{
    SET(0x20, regs.HL.low);
    counter += CBOpcodeTable[0xED].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xED].length;
}

void CPU::CBopcode0xEE() // SET 5,(hl)
{
    u8 byte = mmu->ReadByte(regs.HL.word);
    SET(0x20, byte);
    mmu->WriteByte(regs.HL.word, byte);
    counter += CBOpcodeTable[0xEE].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xEE].length;
}

void CPU::CBopcode0xEF() // SET 5,A
{
    SET(0x20, regs.AF.high);
    counter += CBOpcodeTable[0xEF].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xEF].length;
}



void CPU::CBopcode0xF0() // SET 6,B
{
    SET(0x40, regs.BC.high);
    counter += CBOpcodeTable[0xF0].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xF0].length;
}

void CPU::CBopcode0xF1() // SET 6,C
{
    SET(0x40, regs.BC.low);
    counter += CBOpcodeTable[0xF1].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xF1].length;
}

void CPU::CBopcode0xF2() // SET 6,D
{
    SET(0x40, regs.DE.high);
    counter += CBOpcodeTable[0xF2].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xF2].length;
}

void CPU::CBopcode0xF3() // SET 6,E
{
    SET(0x40, regs.DE.low);
    counter += CBOpcodeTable[0xF3].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xF3].length;
}

void CPU::CBopcode0xF4() // SET 6,H
{
    SET(0x40, regs.HL.high);
    counter += CBOpcodeTable[0xF4].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xF4].length;
}

void CPU::CBopcode0xF5() // SET 6,L
{
    SET(0x40, regs.HL.low);
    counter += CBOpcodeTable[0xF5].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xF5].length;
}

void CPU::CBopcode0xF6() // SET 6,(HL)
{
    u8 byte = mmu->ReadByte(regs.HL.word);
    SET(0x40, byte);
    mmu->WriteByte(regs.HL.word, byte);
    counter += CBOpcodeTable[0xF6].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xF6].length;
}

void CPU::CBopcode0xF7() // SET 6,A
{
    SET(0x40, regs.AF.high);
    counter += CBOpcodeTable[0xF7].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xF7].length;
}

void CPU::CBopcode0xF8() // SET 7,B
{
    SET(0x80, regs.BC.high);
    counter += CBOpcodeTable[0xF8].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xF8].length;
}

void CPU::CBopcode0xF9() // SET 7,C
{
    SET(0x80, regs.BC.low);
    counter += CBOpcodeTable[0xF9].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xF9].length;
}

void CPU::CBopcode0xFA() // SET 7,D
{
    SET(0x80, regs.DE.high);
    counter += CBOpcodeTable[0xFA].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xFA].length;
}

void CPU::CBopcode0xFB() // SET 7,E
{
    SET(0x80, regs.DE.low);
    counter += CBOpcodeTable[0xFB].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xFB].length;
}

void CPU::CBopcode0xFC() // SET 7,H
{
    SET(0x80, regs.HL.high);
    counter += CBOpcodeTable[0xFC].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xFC].length;
}

void CPU::CBopcode0xFD() // SET 7,L
{
    SET(0x80, regs.HL.low);
    counter += CBOpcodeTable[0xFD].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xFD].length;
}

void CPU::CBopcode0xFE() // SET 7,(HL)
{
	u8 byte = mmu->ReadByte(regs.HL.word);
	SET(0x80, byte);
	mmu->WriteByte(regs.HL.word, byte);
    counter += CBOpcodeTable[0xFE].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xFE].length;
}

void CPU::CBopcode0xFF() // SET 7,A
{
    SET(0x80, regs.AF.high);
    counter += CBOpcodeTable[0xFF].duration.firstCondition;
    regs.pc += CBOpcodeTable[0xFF].length;
}



// Helper Functions CB


inline void CPU::RLC(u8& n) // Flags: Z 0 0 C - Rotate n left. Old bit 7 to Carry flag
{
    regs.AF.low &= ~SUBTRACT_FLAG;
    regs.AF.low &= ~HALF_CARRY_FLAG;
    
    u8 oldbit7 = (n & 0x80);

    n = n << 1;

    if (oldbit7)
        regs.AF.low |= CARRY_FLAG;
    else
        regs.AF.low &= CARRY_FLAG;

    if (n == 0x00)
        regs.AF.low |= ZERO_FLAG;
    else
        regs.AF.low &= ~ZERO_FLAG;
}

inline void CPU::RRC(u8& n) // Flags: Z 0 0 C - Rotate n right. Old bit 0 to Carry flag
{
    regs.AF.low &= ~SUBTRACT_FLAG;
    regs.AF.low &= ~HALF_CARRY_FLAG;

    u8 oldbit0 = (n & 0x01);

    n = n >> 1;

    if(oldbit0)
        regs.AF.low |= CARRY_FLAG;
    else
        regs.AF.low &= CARRY_FLAG;

    if (n == 0x00)
        regs.AF.low |= ZERO_FLAG;
    else
        regs.AF.low &= ~ZERO_FLAG;

}


inline void CPU::RL(u8& n) // Flags: Z 0 0 C - Rotate n left through Carry flag.
{
    regs.AF.low &= ~SUBTRACT_FLAG;
    regs.AF.low &= ~HALF_CARRY_FLAG;

    u8 carryValue = (regs.AF.low & CARRY_FLAG) >> CARRY_BIT; // Gets the old carry value

    if (n & 0x08)
        regs.AF.low |= CARRY_FLAG;
    else
        regs.AF.low &= CARRY_FLAG;

    n = n << 1;
    n = n + carryValue;

    if (n == 0x00)
        regs.AF.low |= ZERO_FLAG;
    else
        regs.AF.low &= ~ZERO_FLAG;

}

// TODO: Carry value replaced with ternary operators rather than shifting
inline void CPU::RR(u8& n) // Flags: Z 0 0 C - Rotate n right through Carry flag.
{
    regs.AF.low &= ~SUBTRACT_FLAG;
    regs.AF.low &= ~HALF_CARRY_FLAG;

    u8 carryValue = (regs.AF.low & CARRY_FLAG) >> CARRY_BIT; // Gets the old carry value

    if (n & 0x01)
        regs.AF.low |= CARRY_FLAG;
    else
        regs.AF.low &= CARRY_FLAG;

    n = n >> 1;
    n = n + carryValue;

    if(n == 0x00)
        regs.AF.low |= ZERO_FLAG;
    else
        regs.AF.low &= ~ZERO_FLAG;

}



inline void CPU::SLA(u8& n) // Flags: Z 0 0 C - Shift n left into Carry. LSB of n set to 0.
{
    u8 msb = (n & 0x80); // Store the msb before the shift

    regs.AF.low &= ~SUBTRACT_FLAG;
    regs.AF.low &= ~HALF_CARRY_FLAG;

    if (msb)
        regs.AF.low |= CARRY_FLAG;
    else
        regs.AF.low &= ~CARRY_FLAG;

    n = n << 1;

    if (n == 0x00)
        regs.AF.low |= ZERO_FLAG;
    else
        regs.AF.low &= ~ZERO_FLAG;
}


inline void CPU::SRA(u8& n) // Flags: Z 0 0 C - Shift n right into Carry. MSB doesn't change.
{
    u8 msb = (n & 0x80); // Store the msb before the shift

    regs.AF.low &= ~SUBTRACT_FLAG;
    regs.AF.low &= ~HALF_CARRY_FLAG;

    if (msb)
        regs.AF.low |= CARRY_FLAG;
    else
        regs.AF.low &= ~CARRY_FLAG;

    n = n >> 1;
    n = n | msb; // maintain the MSB's old value

    if (n == 0x00)
        regs.AF.low |= ZERO_FLAG;
    else
        regs.AF.low &= ~ZERO_FLAG;

}

inline void CPU::SWAP(u8& n) // Flags: Z 0 0 0
{
    // reset flags
    regs.AF.low &= ~SUBTRACT_FLAG;
    regs.AF.low &= ~HALF_CARRY_FLAG;
    regs.AF.low &= ~CARRY_FLAG;

    u8 lower = n & 0x0F;
    n = (n >> 4) | (lower << 4);

    if (n == 0x00)
        regs.AF.low |= ZERO_FLAG;
    else
        regs.AF.low &= ~ZERO_FLAG;
}

inline void CPU::SRL(u8& n) // Flags: Z 0 0 C - Shift n right into Carry. MSB set to 0
{
    u8 lsb = (n & 0x01); // Store the msb before the shift

    regs.AF.low &= ~SUBTRACT_FLAG;
    regs.AF.low &= ~HALF_CARRY_FLAG;

    if (lsb)
        regs.AF.low |= CARRY_FLAG;
    else
        regs.AF.low &= ~CARRY_FLAG;

    n = n >> 1;

    if (n == 0x00)
        regs.AF.low |= ZERO_FLAG;
    else
        regs.AF.low &= ~ZERO_FLAG;
}

inline void CPU::BIT(u8 bit, u8 n) // Test bit in register, FLAGS: Z 0 1 -
{
    if (n & bit)
        regs.AF.low &= ~ZERO_FLAG;
    else
        regs.AF.low |= ZERO_FLAG;

    regs.AF.low &= ~SUBTRACT_FLAG;
    regs.AF.low |= HALF_CARRY_FLAG;

}


inline void CPU::RES(u8 bit, u8& n) // Flags:: - - - - : Reset bit in byte n
{
    n &= ~bit;
}

inline void CPU::SET(u8 bit, u8& n) // Flags:: - - - - : Set bit bit in register n
{
	n |= bit;
}



// Assigns all of the function pointers
void CPU::InitOpcodeFunctionsCB()
{
    opcodeFunctionCB[0x00] = &CPU::CBopcode0x00;
    opcodeFunctionCB[0x01] = &CPU::CBopcode0x01;
    opcodeFunctionCB[0x02] = &CPU::CBopcode0x02;
    opcodeFunctionCB[0x03] = &CPU::CBopcode0x03;
    opcodeFunctionCB[0x04] = &CPU::CBopcode0x04;
    opcodeFunctionCB[0x05] = &CPU::CBopcode0x05;
    opcodeFunctionCB[0x06] = &CPU::CBopcode0x06;
    opcodeFunctionCB[0x07] = &CPU::CBopcode0x07;
    opcodeFunctionCB[0x08] = &CPU::CBopcode0x08;
    opcodeFunctionCB[0x09] = &CPU::CBopcode0x09;
    opcodeFunctionCB[0x0A] = &CPU::CBopcode0x0A;
    opcodeFunctionCB[0x0B] = &CPU::CBopcode0x0B;
    opcodeFunctionCB[0x0C] = &CPU::CBopcode0x0C;
    opcodeFunctionCB[0x0D] = &CPU::CBopcode0x0D;
    opcodeFunctionCB[0x0E] = &CPU::CBopcode0x0E;
    opcodeFunctionCB[0x0F] = &CPU::CBopcode0x0F;
    opcodeFunctionCB[0x10] = &CPU::CBopcode0x10;
    opcodeFunctionCB[0x11] = &CPU::CBopcode0x11;
    opcodeFunctionCB[0x12] = &CPU::CBopcode0x12;
    opcodeFunctionCB[0x13] = &CPU::CBopcode0x13;
    opcodeFunctionCB[0x14] = &CPU::CBopcode0x14;
    opcodeFunctionCB[0x15] = &CPU::CBopcode0x15;
    opcodeFunctionCB[0x16] = &CPU::CBopcode0x16;
    opcodeFunctionCB[0x17] = &CPU::CBopcode0x17;
    opcodeFunctionCB[0x18] = &CPU::CBopcode0x18;
    opcodeFunctionCB[0x19] = &CPU::CBopcode0x19;
    opcodeFunctionCB[0x1A] = &CPU::CBopcode0x1A;
    opcodeFunctionCB[0x1B] = &CPU::CBopcode0x1B;
    opcodeFunctionCB[0x1C] = &CPU::CBopcode0x1C;
    opcodeFunctionCB[0x1D] = &CPU::CBopcode0x1D;
    opcodeFunctionCB[0x1E] = &CPU::CBopcode0x1E;
    opcodeFunctionCB[0x1F] = &CPU::CBopcode0x1F;
    opcodeFunctionCB[0x20] = &CPU::CBopcode0x20;
    opcodeFunctionCB[0x21] = &CPU::CBopcode0x21;
    opcodeFunctionCB[0x22] = &CPU::CBopcode0x22;
    opcodeFunctionCB[0x23] = &CPU::CBopcode0x23;
    opcodeFunctionCB[0x24] = &CPU::CBopcode0x24;
    opcodeFunctionCB[0x25] = &CPU::CBopcode0x25;
    opcodeFunctionCB[0x26] = &CPU::CBopcode0x26;
    opcodeFunctionCB[0x27] = &CPU::CBopcode0x27;
    opcodeFunctionCB[0x28] = &CPU::CBopcode0x28;
    opcodeFunctionCB[0x29] = &CPU::CBopcode0x29;
    opcodeFunctionCB[0x2A] = &CPU::CBopcode0x2A;
    opcodeFunctionCB[0x2B] = &CPU::CBopcode0x2B;
    opcodeFunctionCB[0x2C] = &CPU::CBopcode0x2C;
    opcodeFunctionCB[0x2D] = &CPU::CBopcode0x2D;
    opcodeFunctionCB[0x2E] = &CPU::CBopcode0x2E;
    opcodeFunctionCB[0x2F] = &CPU::CBopcode0x2F;
    opcodeFunctionCB[0x30] = &CPU::CBopcode0x30;
    opcodeFunctionCB[0x31] = &CPU::CBopcode0x31;
    opcodeFunctionCB[0x32] = &CPU::CBopcode0x32;
    opcodeFunctionCB[0x33] = &CPU::CBopcode0x33;
    opcodeFunctionCB[0x34] = &CPU::CBopcode0x34;
    opcodeFunctionCB[0x35] = &CPU::CBopcode0x35;
    opcodeFunctionCB[0x36] = &CPU::CBopcode0x36;
    opcodeFunctionCB[0x37] = &CPU::CBopcode0x37;
    opcodeFunctionCB[0x38] = &CPU::CBopcode0x38;
    opcodeFunctionCB[0x39] = &CPU::CBopcode0x39;
    opcodeFunctionCB[0x3A] = &CPU::CBopcode0x3A;
    opcodeFunctionCB[0x3B] = &CPU::CBopcode0x3B;
    opcodeFunctionCB[0x3C] = &CPU::CBopcode0x3C;
    opcodeFunctionCB[0x3D] = &CPU::CBopcode0x3D;
    opcodeFunctionCB[0x3E] = &CPU::CBopcode0x3E;
    opcodeFunctionCB[0x3F] = &CPU::CBopcode0x3F;
    opcodeFunctionCB[0x40] = &CPU::CBopcode0x40;
    opcodeFunctionCB[0x41] = &CPU::CBopcode0x41;
    opcodeFunctionCB[0x42] = &CPU::CBopcode0x42;
    opcodeFunctionCB[0x43] = &CPU::CBopcode0x43;
    opcodeFunctionCB[0x44] = &CPU::CBopcode0x44;
    opcodeFunctionCB[0x45] = &CPU::CBopcode0x45;
    opcodeFunctionCB[0x46] = &CPU::CBopcode0x46;
    opcodeFunctionCB[0x47] = &CPU::CBopcode0x47;
    opcodeFunctionCB[0x48] = &CPU::CBopcode0x48;
    opcodeFunctionCB[0x49] = &CPU::CBopcode0x49;
    opcodeFunctionCB[0x4A] = &CPU::CBopcode0x4A;
    opcodeFunctionCB[0x4B] = &CPU::CBopcode0x4B;
    opcodeFunctionCB[0x4C] = &CPU::CBopcode0x4C;
    opcodeFunctionCB[0x4D] = &CPU::CBopcode0x4D;
    opcodeFunctionCB[0x4E] = &CPU::CBopcode0x4E;
    opcodeFunctionCB[0x4F] = &CPU::CBopcode0x4F;
    opcodeFunctionCB[0x50] = &CPU::CBopcode0x50;
    opcodeFunctionCB[0x51] = &CPU::CBopcode0x51;
    opcodeFunctionCB[0x52] = &CPU::CBopcode0x52;
    opcodeFunctionCB[0x53] = &CPU::CBopcode0x53;
    opcodeFunctionCB[0x54] = &CPU::CBopcode0x54;
    opcodeFunctionCB[0x55] = &CPU::CBopcode0x55;
    opcodeFunctionCB[0x56] = &CPU::CBopcode0x56;
    opcodeFunctionCB[0x57] = &CPU::CBopcode0x57;
    opcodeFunctionCB[0x58] = &CPU::CBopcode0x58;
    opcodeFunctionCB[0x59] = &CPU::CBopcode0x59;
    opcodeFunctionCB[0x5A] = &CPU::CBopcode0x5A;
    opcodeFunctionCB[0x5B] = &CPU::CBopcode0x5B;
    opcodeFunctionCB[0x5C] = &CPU::CBopcode0x5C;
    opcodeFunctionCB[0x5D] = &CPU::CBopcode0x5D;
    opcodeFunctionCB[0x5E] = &CPU::CBopcode0x5E;
    opcodeFunctionCB[0x5F] = &CPU::CBopcode0x5F;
    opcodeFunctionCB[0x60] = &CPU::CBopcode0x60;
    opcodeFunctionCB[0x61] = &CPU::CBopcode0x61;
    opcodeFunctionCB[0x62] = &CPU::CBopcode0x62;
    opcodeFunctionCB[0x63] = &CPU::CBopcode0x63;
    opcodeFunctionCB[0x64] = &CPU::CBopcode0x64;
    opcodeFunctionCB[0x65] = &CPU::CBopcode0x65;
    opcodeFunctionCB[0x66] = &CPU::CBopcode0x66;
    opcodeFunctionCB[0x67] = &CPU::CBopcode0x67;
    opcodeFunctionCB[0x68] = &CPU::CBopcode0x68;
    opcodeFunctionCB[0x69] = &CPU::CBopcode0x69;
    opcodeFunctionCB[0x6A] = &CPU::CBopcode0x6A;
    opcodeFunctionCB[0x6B] = &CPU::CBopcode0x6B;
    opcodeFunctionCB[0x6C] = &CPU::CBopcode0x6C;
    opcodeFunctionCB[0x6D] = &CPU::CBopcode0x6D;
    opcodeFunctionCB[0x6E] = &CPU::CBopcode0x6E;
    opcodeFunctionCB[0x6F] = &CPU::CBopcode0x6F;
    opcodeFunctionCB[0x70] = &CPU::CBopcode0x70;
    opcodeFunctionCB[0x71] = &CPU::CBopcode0x71;
    opcodeFunctionCB[0x72] = &CPU::CBopcode0x72;
    opcodeFunctionCB[0x73] = &CPU::CBopcode0x73;
    opcodeFunctionCB[0x74] = &CPU::CBopcode0x74;
    opcodeFunctionCB[0x75] = &CPU::CBopcode0x75;
    opcodeFunctionCB[0x76] = &CPU::CBopcode0x76;
    opcodeFunctionCB[0x77] = &CPU::CBopcode0x77;
    opcodeFunctionCB[0x78] = &CPU::CBopcode0x78;
    opcodeFunctionCB[0x79] = &CPU::CBopcode0x79;
    opcodeFunctionCB[0x7A] = &CPU::CBopcode0x7A;
    opcodeFunctionCB[0x7B] = &CPU::CBopcode0x7B;
    opcodeFunctionCB[0x7C] = &CPU::CBopcode0x7C;
    opcodeFunctionCB[0x7D] = &CPU::CBopcode0x7D;
    opcodeFunctionCB[0x7E] = &CPU::CBopcode0x7E;
    opcodeFunctionCB[0x7F] = &CPU::CBopcode0x7F;
    opcodeFunctionCB[0x80] = &CPU::CBopcode0x80;
    opcodeFunctionCB[0x81] = &CPU::CBopcode0x81;
    opcodeFunctionCB[0x82] = &CPU::CBopcode0x82;
    opcodeFunctionCB[0x83] = &CPU::CBopcode0x83;
    opcodeFunctionCB[0x84] = &CPU::CBopcode0x84;
    opcodeFunctionCB[0x85] = &CPU::CBopcode0x85;
    opcodeFunctionCB[0x86] = &CPU::CBopcode0x86;
    opcodeFunctionCB[0x87] = &CPU::CBopcode0x87;
    opcodeFunctionCB[0x88] = &CPU::CBopcode0x88;
    opcodeFunctionCB[0x89] = &CPU::CBopcode0x89;
    opcodeFunctionCB[0x8A] = &CPU::CBopcode0x8A;
    opcodeFunctionCB[0x8B] = &CPU::CBopcode0x8B;
    opcodeFunctionCB[0x8C] = &CPU::CBopcode0x8C;
    opcodeFunctionCB[0x8D] = &CPU::CBopcode0x8D;
    opcodeFunctionCB[0x8E] = &CPU::CBopcode0x8E;
    opcodeFunctionCB[0x8F] = &CPU::CBopcode0x8F;
    opcodeFunctionCB[0x90] = &CPU::CBopcode0x90;
    opcodeFunctionCB[0x91] = &CPU::CBopcode0x91;
    opcodeFunctionCB[0x92] = &CPU::CBopcode0x92;
    opcodeFunctionCB[0x93] = &CPU::CBopcode0x93;
    opcodeFunctionCB[0x94] = &CPU::CBopcode0x94;
    opcodeFunctionCB[0x95] = &CPU::CBopcode0x95;
    opcodeFunctionCB[0x96] = &CPU::CBopcode0x96;
    opcodeFunctionCB[0x97] = &CPU::CBopcode0x97;
    opcodeFunctionCB[0x98] = &CPU::CBopcode0x98;
    opcodeFunctionCB[0x99] = &CPU::CBopcode0x99;
    opcodeFunctionCB[0x9A] = &CPU::CBopcode0x9A;
    opcodeFunctionCB[0x9B] = &CPU::CBopcode0x9B;
    opcodeFunctionCB[0x9C] = &CPU::CBopcode0x9C;
    opcodeFunctionCB[0x9D] = &CPU::CBopcode0x9D;
    opcodeFunctionCB[0x9E] = &CPU::CBopcode0x9E;
    opcodeFunctionCB[0x9F] = &CPU::CBopcode0x9F;
    opcodeFunctionCB[0xA0] = &CPU::CBopcode0xA0;
    opcodeFunctionCB[0xA1] = &CPU::CBopcode0xA1;
    opcodeFunctionCB[0xA2] = &CPU::CBopcode0xA2;
    opcodeFunctionCB[0xA3] = &CPU::CBopcode0xA3;
    opcodeFunctionCB[0xA4] = &CPU::CBopcode0xA4;
    opcodeFunctionCB[0xA5] = &CPU::CBopcode0xA5;
    opcodeFunctionCB[0xA6] = &CPU::CBopcode0xA6;
    opcodeFunctionCB[0xA7] = &CPU::CBopcode0xA7;
    opcodeFunctionCB[0xA8] = &CPU::CBopcode0xA8;
    opcodeFunctionCB[0xA9] = &CPU::CBopcode0xA9;
    opcodeFunctionCB[0xAA] = &CPU::CBopcode0xAA;
    opcodeFunctionCB[0xAB] = &CPU::CBopcode0xAB;
    opcodeFunctionCB[0xAC] = &CPU::CBopcode0xAC;
    opcodeFunctionCB[0xAD] = &CPU::CBopcode0xAD;
    opcodeFunctionCB[0xAE] = &CPU::CBopcode0xAE;
    opcodeFunctionCB[0xAF] = &CPU::CBopcode0xAF;
    opcodeFunctionCB[0xB0] = &CPU::CBopcode0xB0;
    opcodeFunctionCB[0xB1] = &CPU::CBopcode0xB1;
    opcodeFunctionCB[0xB2] = &CPU::CBopcode0xB2;
    opcodeFunctionCB[0xB3] = &CPU::CBopcode0xB3;
    opcodeFunctionCB[0xB4] = &CPU::CBopcode0xB4;
    opcodeFunctionCB[0xB5] = &CPU::CBopcode0xB5;
    opcodeFunctionCB[0xB6] = &CPU::CBopcode0xB6;
    opcodeFunctionCB[0xB7] = &CPU::CBopcode0xB7;
    opcodeFunctionCB[0xB8] = &CPU::CBopcode0xB8;
    opcodeFunctionCB[0xB9] = &CPU::CBopcode0xB9;
    opcodeFunctionCB[0xBA] = &CPU::CBopcode0xBA;
    opcodeFunctionCB[0xBB] = &CPU::CBopcode0xBB;
    opcodeFunctionCB[0xBC] = &CPU::CBopcode0xBC;
    opcodeFunctionCB[0xBD] = &CPU::CBopcode0xBD;
    opcodeFunctionCB[0xBE] = &CPU::CBopcode0xBE;
    opcodeFunctionCB[0xBF] = &CPU::CBopcode0xBF;
    opcodeFunctionCB[0xC0] = &CPU::CBopcode0xC0;
    opcodeFunctionCB[0xC1] = &CPU::CBopcode0xC1;
    opcodeFunctionCB[0xC2] = &CPU::CBopcode0xC2;
    opcodeFunctionCB[0xC3] = &CPU::CBopcode0xC3;
    opcodeFunctionCB[0xC4] = &CPU::CBopcode0xC4;
    opcodeFunctionCB[0xC5] = &CPU::CBopcode0xC5;
    opcodeFunctionCB[0xC6] = &CPU::CBopcode0xC6;
    opcodeFunctionCB[0xC7] = &CPU::CBopcode0xC7;
    opcodeFunctionCB[0xC8] = &CPU::CBopcode0xC8;
    opcodeFunctionCB[0xC9] = &CPU::CBopcode0xC9;
    opcodeFunctionCB[0xCA] = &CPU::CBopcode0xCA;
    opcodeFunctionCB[0xCB] = &CPU::CBopcode0xCB;
    opcodeFunctionCB[0xCC] = &CPU::CBopcode0xCC;
    opcodeFunctionCB[0xCD] = &CPU::CBopcode0xCD;
    opcodeFunctionCB[0xCE] = &CPU::CBopcode0xCE;
    opcodeFunctionCB[0xCF] = &CPU::CBopcode0xCF;
    opcodeFunctionCB[0xD0] = &CPU::CBopcode0xD0;
    opcodeFunctionCB[0xD1] = &CPU::CBopcode0xD1;
    opcodeFunctionCB[0xD2] = &CPU::CBopcode0xD2;
    opcodeFunctionCB[0xD4] = &CPU::CBopcode0xD4;
    opcodeFunctionCB[0xD5] = &CPU::CBopcode0xD5;
    opcodeFunctionCB[0xD6] = &CPU::CBopcode0xD6;
    opcodeFunctionCB[0xD7] = &CPU::CBopcode0xD7;
    opcodeFunctionCB[0xD8] = &CPU::CBopcode0xD8;
    opcodeFunctionCB[0xD9] = &CPU::CBopcode0xD9;
    opcodeFunctionCB[0xDA] = &CPU::CBopcode0xDA;
    opcodeFunctionCB[0xDC] = &CPU::CBopcode0xDC;
    opcodeFunctionCB[0xDE] = &CPU::CBopcode0xDE;
    opcodeFunctionCB[0xDF] = &CPU::CBopcode0xDF;
    opcodeFunctionCB[0xE0] = &CPU::CBopcode0xE0;
    opcodeFunctionCB[0xE1] = &CPU::CBopcode0xE1;
    opcodeFunctionCB[0xE2] = &CPU::CBopcode0xE2;
    opcodeFunctionCB[0xE5] = &CPU::CBopcode0xE5;
    opcodeFunctionCB[0xE6] = &CPU::CBopcode0xE6;
    opcodeFunctionCB[0xE7] = &CPU::CBopcode0xE7;
    opcodeFunctionCB[0xE8] = &CPU::CBopcode0xE8;
    opcodeFunctionCB[0xE9] = &CPU::CBopcode0xE9;
    opcodeFunctionCB[0xEA] = &CPU::CBopcode0xEA;
    opcodeFunctionCB[0xEE] = &CPU::CBopcode0xEE;
    opcodeFunctionCB[0xEF] = &CPU::CBopcode0xEF;
    opcodeFunctionCB[0xF0] = &CPU::CBopcode0xF0;
    opcodeFunctionCB[0xF1] = &CPU::CBopcode0xF1;
    opcodeFunctionCB[0xF2] = &CPU::CBopcode0xF2;
    opcodeFunctionCB[0xF3] = &CPU::CBopcode0xF3;
    opcodeFunctionCB[0xF5] = &CPU::CBopcode0xF5;
    opcodeFunctionCB[0xF6] = &CPU::CBopcode0xF6;
    opcodeFunctionCB[0xF7] = &CPU::CBopcode0xF7;
    opcodeFunctionCB[0xF8] = &CPU::CBopcode0xF8;
    opcodeFunctionCB[0xF9] = &CPU::CBopcode0xF9;
    opcodeFunctionCB[0xFA] = &CPU::CBopcode0xFA;
    opcodeFunctionCB[0xFB] = &CPU::CBopcode0xFB;
    opcodeFunctionCB[0xFE] = &CPU::CBopcode0xFE;
    opcodeFunctionCB[0xFF] = &CPU::CBopcode0xFF;

}
