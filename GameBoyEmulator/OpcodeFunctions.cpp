#include "CPU.h"

void CPU::opcode0x00() // NOP
{
    counter += opcodeTable[0x00].duration.firstCondition;
    regs.pc++;

}

void CPU::opcode0x01() // LD BC, d16
{
    regs.BC.word = mmu->ReadTwoBytes(regs.pc + 1);
    counter += opcodeTable[0x01].duration.firstCondition;
    regs.pc += opcodeTable[0x01].length;
}

void CPU::opcode0x02() // LD (BC), A
{
    mmu->WriteByte(regs.BC.word, regs.AF.high);
    counter += opcodeTable[0x02].duration.firstCondition;
    regs.pc += opcodeTable[0x02].length;
}

void CPU::opcode0x03() // INC BC
{
    regs.BC.word++;
    counter += opcodeTable[0x03].duration.firstCondition;
    regs.pc += opcodeTable[0x03].length;
}

void CPU::opcode0x04() // INC B
{
    INC(regs.BC.high);
    counter += opcodeTable[0x04].duration.firstCondition;
    regs.pc += opcodeTable[0x04].length;
}

void CPU::opcode0x05() // DEC B
{
    DEC(regs.BC.high);
    counter += opcodeTable[0x05].duration.firstCondition;
    regs.pc += opcodeTable[0x05].length;
}

void CPU::opcode0x06() // LD B, d8
{
    regs.BC.high = mmu->ReadByte(regs.pc + 1);
    counter += opcodeTable[0x06].duration.firstCondition;
    regs.pc += opcodeTable[0x06].length;
}

void CPU::opcode0x07() // RLCA - Rotate A left. Old bit 7 to Carry flag.
{
    // Clear first 3 flags
    UnsetFlag(ZERO_FLAG); // TODO: whether this should be set or reset
    UnsetFlag(SUBTRACT_FLAG);
    UnsetFlag(HALF_CARRY_FLAG);

    u8 msb = (regs.AF.high & 0x80) >> 7; // Store the msb before the shift

    regs.AF.high = regs.AF.high << 1;    // Rotate by 1
    regs.AF.high |= msb;                 // Replace the msb into the lsb position

                                         // Set the flag with the msb
    if (msb)
        SetFlag(CARRY_FLAG);   // Set to 1
    else
        UnsetFlag(CARRY_FLAG);  // set to 0


    counter += opcodeTable[0x07].duration.firstCondition;
    regs.pc += opcodeTable[0x07].length;
}

void CPU::opcode0x08() // LD (a16), SP
{
    //regs.sp = mmu->ReadTwoBytes(regs.pc + 1);
    mmu->WriteTwoBytes(mmu->ReadTwoBytes(regs.pc + 1), regs.sp);
    counter += opcodeTable[0x08].duration.firstCondition;
    regs.pc += opcodeTable[0x08].length;
}

void CPU::opcode0x09() // ADD HL, BC
{
    ADD16(regs.HL.word, regs.BC.word);
    counter += opcodeTable[0x09].duration.firstCondition;
    regs.pc += opcodeTable[0x09].length;
}

void CPU::opcode0x0A() // LD A, (BC)
{
    regs.AF.high = mmu->ReadByte(regs.BC.word);

    counter += opcodeTable[0x0A].duration.firstCondition;
    regs.pc += opcodeTable[0x0A].length;
}

void CPU::opcode0x0B() // DEC BC
{
    regs.BC.word--;
    counter += opcodeTable[0x0B].duration.firstCondition;
    regs.pc += opcodeTable[0x0B].length;
}

void CPU::opcode0x0C() // INC C
{
    INC(regs.BC.low);
    counter += opcodeTable[0x0C].duration.firstCondition;
    regs.pc += opcodeTable[0x0C].length;
}

void CPU::opcode0x0D() // DEC C
{
    DEC(regs.BC.low);
    counter += opcodeTable[0x0D].duration.firstCondition;
    regs.pc += opcodeTable[0x0D].length;
}

void CPU::opcode0x0E() // LD C, d8
{
    regs.BC.low = mmu->ReadByte(regs.pc + 1);
    counter += opcodeTable[0x0E].duration.firstCondition;
    regs.pc += opcodeTable[0x0E].length;
}

void CPU::opcode0x0F() // RRCA - Rotate A right, old bit 0 to carry
{
    // Clear first 3 flags
    UnsetFlag(ZERO_FLAG);    // TODO: whether this should be set or reset
    UnsetFlag(SUBTRACT_FLAG);
    UnsetFlag(HALF_CARRY_FLAG);

    u8 lsb = regs.AF.high & 0x01; // Store the msb before the shift

    regs.AF.high = regs.AF.high >> 1;    // Rotate right by 1
    regs.AF.high |= (lsb << 7);          // Replace the msb into the lsb position

    // Set the flag with the lsb
    if (lsb)
        SetFlag(CARRY_FLAG);   // Set to 1
    else
        UnsetFlag(CARRY_FLAG);  // set to 0

    counter += opcodeTable[0x0F].duration.firstCondition;
    regs.pc += opcodeTable[0x0F].length;
}

void CPU::opcode0x10() // STOP
{
    while (mmu->ReadByte(0xFF00) == 0)
    {

    }

    counter += opcodeTable[0x0F].duration.firstCondition;
    mmu->ReadByte(regs.pc + 1) == 0x00 ? regs.pc += opcodeTable[0x0F].length + 1 : regs.pc += opcodeTable[0x0F].length; // Stop sometimes considered as 0x0000 (2 byte)

}

void CPU::opcode0x11() // LD DE, d16
{
    regs.DE.word = mmu->ReadTwoBytes(regs.pc + 1);
    counter += opcodeTable[0x11].duration.firstCondition;
    regs.pc += opcodeTable[0x11].length;
}

void CPU::opcode0x12() // LD (DE), A
{
    mmu->WriteByte(regs.DE.word, regs.AF.high);
    counter += opcodeTable[0x12].duration.firstCondition;
    regs.pc += opcodeTable[0x12].length;
}

void CPU::opcode0x13() // INC DE
{
    regs.DE.word++;
    counter += opcodeTable[0x13].duration.firstCondition;
    regs.pc += opcodeTable[0x13].length;
}

void CPU::opcode0x14() // INC D
{
    INC(regs.DE.high);
    counter += opcodeTable[0x14].duration.firstCondition;
    regs.pc += opcodeTable[0x14].length;
}

void CPU::opcode0x15() // DEC D
{
    DEC(regs.DE.high);
    counter += opcodeTable[0x15].duration.firstCondition;
    regs.pc += opcodeTable[0x15].length;
}

void CPU::opcode0x16() // LD D, d8   
{
    regs.DE.high = mmu->ReadByte(regs.pc + 1);
    counter += opcodeTable[0x16].duration.firstCondition;
    regs.pc += opcodeTable[0x16].length;
}

// TODO: Ternary operator instead of shift
void CPU::opcode0x17() // RLA - Flags: 0 0 0 C    Rotate A left through Carry flag
{
    // Clear first 3 flags
    UnsetFlag(ZERO_FLAG); 
    UnsetFlag(SUBTRACT_FLAG);
    UnsetFlag(HALF_CARRY_FLAG);

    u8 msb = (regs.AF.high & 0x80) ? 1 : 0; // Store the msb before the shift
    u8 carryValue = (regs.AF.low & CARRY_FLAG) ? 1 : 0;

    regs.AF.high = regs.AF.high << 1;    // Rotate by 1

    if (carryValue)
        regs.AF.high |= 0x01;           // Replace the lsb with the carry value
    else
        regs.AF.high &= ~0x01;

    // Set the flag with the msb
    if (msb)
        SetFlag(CARRY_FLAG);   // Set to 1
    else
        UnsetFlag(CARRY_FLAG);  // set to 0


    counter += opcodeTable[0x17].duration.firstCondition;
    regs.pc += opcodeTable[0x17].length;
}

void CPU::opcode0x18() // JR r8 
{
    regs.pc += (s8)mmu->ReadByte(regs.pc + 1);
    counter += opcodeTable[0x18].duration.firstCondition;
    regs.pc += opcodeTable[0x18].length;
}

void CPU::opcode0x19() // ADD HL, DE 
{
    ADD16(regs.HL.word, regs.DE.word);
    counter += opcodeTable[0x19].duration.firstCondition;
    regs.pc += opcodeTable[0x19].length;
}

void CPU::opcode0x1A() // LD A, (DE) 
{
    regs.AF.high = mmu->ReadByte(regs.DE.word);
    counter += opcodeTable[0x1A].duration.firstCondition;
    regs.pc += opcodeTable[0x1A].length;
}

void CPU::opcode0x1B() // DEC DE 
{
    regs.DE.word--;
    counter += opcodeTable[0x1B].duration.firstCondition;
    regs.pc += opcodeTable[0x1B].length;
}

void CPU::opcode0x1C() // INC E 
{
    INC(regs.DE.low);
    counter += opcodeTable[0x1C].duration.firstCondition;
    regs.pc += opcodeTable[0x1C].length;
}

void CPU::opcode0x1D() // DEC E  
{
    DEC(regs.DE.low);
    counter += opcodeTable[0x1D].duration.firstCondition;
    regs.pc += opcodeTable[0x1D].length;
}

void CPU::opcode0x1E() // LD E, d8 
{
    regs.DE.low = mmu->ReadByte(regs.pc + 1);
    counter += opcodeTable[0x1E].duration.firstCondition;
    regs.pc += opcodeTable[0x1E].length;
}

void CPU::opcode0x1F() //  RRA - Flags: 0 0 0 C - Rotate A right through Carry flag
{
    // Clear first 3 flags
    UnsetFlag(ZERO_FLAG); // TODO: whether this should be set or reset
    UnsetFlag(SUBTRACT_FLAG);
    UnsetFlag(HALF_CARRY_FLAG);

    u8 lsb = regs.AF.high & 0x01; // Store the lsb before the shift
    u8 carryValue = (regs.AF.low & CARRY_FLAG) ? 1 : 0;

    regs.AF.high = regs.AF.high >> 1;    // Rotate by 1

if (carryValue)
regs.AF.high |= 0x80;   // Replace the lsb with the carry value
else
regs.AF.high &= ~0x80;

// Set the flag with the msb
if (lsb)
SetFlag(CARRY_FLAG);   // Set to 1
else
UnsetFlag(CARRY_FLAG);  // set to 0

counter += opcodeTable[0x1F].duration.firstCondition;
regs.pc += opcodeTable[0x1F].length;
}

void CPU::opcode0x20() // JR NZ, r8 
{
    if (((regs.AF.low & ZERO_FLAG) >> ZERO_BIT) == 0x00)
    {
        regs.pc += (s8)mmu->ReadByte(regs.pc + 1);
        regs.pc += opcodeTable[0x20].length;
        counter += opcodeTable[0x20].duration.firstCondition;
    }
    else
    {
        regs.pc += opcodeTable[0x20].length;
        counter += opcodeTable[0x20].duration.secondCondition;
    }
}

void CPU::opcode0x21() // LD HL, d16 
{
    regs.HL.word = mmu->ReadTwoBytes(regs.pc + 1);
    counter += opcodeTable[0x21].duration.firstCondition;
    regs.pc += opcodeTable[0x21].length;
}

void CPU::opcode0x22() // LD(HL+), A 
{
    mmu->WriteByte(regs.HL.word++, regs.AF.high);
    //regs.HL.word++;

    counter += opcodeTable[0x22].duration.firstCondition;
    regs.pc += opcodeTable[0x22].length;
}

void CPU::opcode0x23() // INC HL 
{
    regs.HL.word++;
    counter += opcodeTable[0x23].duration.firstCondition;
    regs.pc += opcodeTable[0x23].length;
}

void CPU::opcode0x24() // INC H 
{
    INC(regs.HL.high);
    counter += opcodeTable[0x24].duration.firstCondition;
    regs.pc += opcodeTable[0x24].length;
}

void CPU::opcode0x25() // DEC H 
{
    DEC(regs.HL.high);
    counter += opcodeTable[0x25].duration.firstCondition;
    regs.pc += opcodeTable[0x25].length;
}

void CPU::opcode0x26() // LD H, d8 
{
    regs.HL.high = mmu->ReadByte(regs.pc + 1);
    counter += opcodeTable[0x26].duration.firstCondition;
    regs.pc += opcodeTable[0x26].length;
}

// Decimal adjust register A.
// This instruction adjusts register A so that the correct representation of Binary Coded Decimal(BCD) is obtained.
void CPU::opcode0x27() // Flags: Z - 0 C
{
    u16 a = regs.AF.high;

    if (regs.AF.low & SUBTRACT_FLAG) // if last instruction was an Subtraction
    {
        if (regs.AF.low & HALF_CARRY_FLAG)
            a -= 0x06;

        if (regs.AF.low & CARRY_FLAG)
            a -= 0x60;

        a &= 0xFF;

    }
    else // if last instruction was an Addition
    {
        if (regs.AF.low & HALF_CARRY_FLAG || (a & 0xF) > 0x09)
            a += 0x06;

        if (regs.AF.low & CARRY_FLAG || a > 0x9F)
            a += 0x60;
    }


    if ((a & 0x100) == 0x100)
        SetFlag(CARRY_FLAG);
    //else
    //    UnsetFlag(CARRY_FLAG); // Is not unset if no carry


    // Adjust flags
    UnsetFlag(HALF_CARRY_FLAG);

    if ((a & 0xFF) == 0x00)
        SetFlag(ZERO_FLAG);
    else
        UnsetFlag(ZERO_FLAG);


    regs.AF.high = a & 0xFF; // Assign result back to A reg

    counter += opcodeTable[0x27].duration.firstCondition;
    regs.pc += opcodeTable[0x27].length;
}

void CPU::opcode0x28() // JR Z, r8 
{
    if (((regs.AF.low & ZERO_FLAG) >> ZERO_BIT) == 0x01)
    {
        regs.pc += (s8)mmu->ReadByte(regs.pc + 1);
        regs.pc += opcodeTable[0x28].length;
        counter += opcodeTable[0x28].duration.firstCondition;
    }
    else
    {
        regs.pc += opcodeTable[0x28].length;
        counter += opcodeTable[0x28].duration.secondCondition;
    }

}

void CPU::opcode0x29() // ADD HL, HL  
{
    ADD16(regs.HL.word, regs.HL.word);
    counter += opcodeTable[0x29].duration.firstCondition;
    regs.pc += opcodeTable[0x29].length;
}

void CPU::opcode0x2A() // LD A, (HL+) 
{
    regs.AF.high = mmu->ReadByte(regs.HL.word++);
    //regs.HL.word++;
    counter += opcodeTable[0x2A].duration.firstCondition;
    regs.pc += opcodeTable[0x2A].length;
}

void CPU::opcode0x2B() // DEC HL 
{
    regs.HL.word--;
    counter += opcodeTable[0x2B].duration.firstCondition;
    regs.pc += opcodeTable[0x2B].length;
}

void CPU::opcode0x2C() // INC L 
{
    INC(regs.HL.low);
    counter += opcodeTable[0x2C].duration.firstCondition;
    regs.pc += opcodeTable[0x2C].length;
}

void CPU::opcode0x2D() // DEC L 
{
    DEC(regs.HL.low);
    counter += opcodeTable[0x2D].duration.firstCondition;
    regs.pc += opcodeTable[0x2D].length;
}

void CPU::opcode0x2E() // LD L, d8 
{
    regs.HL.low = mmu->ReadByte(regs.pc + 1);
    counter += opcodeTable[0x2E].duration.firstCondition;
    regs.pc += opcodeTable[0x2E].length;
}

void CPU::opcode0x2F() // CPL - Complement A register. (Flip all bits.) -, 1, 1, -
{
    regs.AF.high = ~regs.AF.high;
    SetFlag(SUBTRACT_FLAG);
    SetFlag(HALF_CARRY_FLAG);
    counter += opcodeTable[0x2F].duration.firstCondition;
    regs.pc += opcodeTable[0x2F].length;
}

void CPU::opcode0x30() // JR NC, r8
{
    if ((regs.AF.low & CARRY_FLAG) == 0x00)
    {
        regs.pc += (s8)mmu->ReadByte(regs.pc + 1);
        regs.pc += opcodeTable[0x30].length;
        counter += opcodeTable[0x30].duration.firstCondition;
    }
    else
    {
        regs.pc += opcodeTable[0x30].length;
        counter += opcodeTable[0x30].duration.secondCondition;
    }
}

void CPU::opcode0x31() // LD SP, d16
{
    regs.sp = mmu->ReadTwoBytes(regs.pc + 1);
    counter += opcodeTable[0x31].duration.firstCondition;
    regs.pc += opcodeTable[0x31].length;
}

void CPU::opcode0x32() // LD (HL-), A
{
    mmu->WriteByte(regs.HL.word, regs.AF.high);
    regs.HL.word--;
    counter += opcodeTable[0x32].duration.firstCondition;
    regs.pc += opcodeTable[0x32].length;
}

void CPU::opcode0x33() // INC SP 
{
    regs.sp++;
    counter += opcodeTable[0x33].duration.firstCondition;
    regs.pc += opcodeTable[0x33].length;
}

void CPU::opcode0x34() // INC (HL) Flags: Z 0 H -
{
    u8 byte = mmu->ReadByte(regs.HL.word);
    INC(byte);
    mmu->WriteByte(regs.HL.word, byte);
    counter += opcodeTable[0x34].duration.firstCondition;
    regs.pc += opcodeTable[0x34].length;
}

void CPU::opcode0x35() // DEC (HL) Flags: Z 1 H -
{
    u8 byte = mmu->ReadByte(regs.HL.word);
    DEC(byte);
    mmu->WriteByte(regs.HL.word, byte);
    counter += opcodeTable[0x35].duration.firstCondition;
    regs.pc += opcodeTable[0x35].length;
}

void CPU::opcode0x36() // LD (HL), d8
{
    u8 byte = mmu->ReadByte(regs.pc + 1);
    mmu->WriteByte(regs.HL.word, byte);
    counter += opcodeTable[0x36].duration.firstCondition;
    regs.pc += opcodeTable[0x36].length;
}

void CPU::opcode0x37() // SCF - Set Carry Flag Flags: - 0 0 1
{
    UnsetFlag(SUBTRACT_FLAG);
    UnsetFlag(HALF_CARRY_FLAG);
    SetFlag(CARRY_FLAG);
    counter += opcodeTable[0x37].duration.firstCondition;
    regs.pc += opcodeTable[0x37].length;
}

void CPU::opcode0x38() // JR C, r8
{
    if ((regs.AF.low & CARRY_FLAG) == 0x10)
    {
        regs.pc += (s8)mmu->ReadByte(regs.pc + 1);
        regs.pc += opcodeTable[0x38].length;
        counter += opcodeTable[0x38].duration.firstCondition;
    }
    else
    {
        regs.pc += opcodeTable[0x38].length;
        counter += opcodeTable[0x38].duration.secondCondition;
    }

}

void CPU::opcode0x39() // ADD HL, SP
{
    ADD16(regs.HL.word, regs.sp);
    counter += opcodeTable[0x39].duration.firstCondition;
    regs.pc += opcodeTable[0x39].length;
}

void CPU::opcode0x3A() // LD A, (HL-)
{
    regs.AF.high = mmu->ReadByte(regs.HL.word);
    regs.HL.word--;
    counter += opcodeTable[0x3A].duration.firstCondition;
    regs.pc += opcodeTable[0x3A].length;
}

void CPU::opcode0x3B() // DEC SP
{
    regs.sp--;
    counter += opcodeTable[0x3B].duration.firstCondition;
    regs.pc += opcodeTable[0x3B].length;
}

void CPU::opcode0x3C() // INC A
{
    INC(regs.AF.high);
    counter += opcodeTable[0x3C].duration.firstCondition;
    regs.pc += opcodeTable[0x3C].length;
}

void CPU::opcode0x3D() // DEC A
{
    DEC(regs.AF.high);
    counter += opcodeTable[0x3D].duration.firstCondition;
    regs.pc += opcodeTable[0x3D].length;
}

void CPU::opcode0x3E() // LD A, d8
{
    regs.AF.high = mmu->ReadByte(regs.pc + 1);
    counter += opcodeTable[0x3E].duration.firstCondition;
    regs.pc += opcodeTable[0x3E].length;
}

void CPU::opcode0x3F() // CCF - Flags: - 0 0 C    Complement carry flag.
{
    UnsetFlag(SUBTRACT_FLAG);
    UnsetFlag(HALF_CARRY_FLAG);

    u8 flag = (regs.AF.low & CARRY_FLAG) ? 1 : 0;

    if (flag)
        UnsetFlag(CARRY_FLAG);
    else
        SetFlag(CARRY_FLAG);
       

    counter += opcodeTable[0x3F].duration.firstCondition;
    regs.pc += opcodeTable[0x3F].length;
}

void CPU::opcode0x40() // LD B, B
{
    counter += opcodeTable[0x40].duration.firstCondition;
    regs.pc += opcodeTable[0x40].length;
}

void CPU::opcode0x41() // LD B, C
{
    regs.BC.high = regs.BC.low;
    counter += opcodeTable[0x41].duration.firstCondition;
    regs.pc += opcodeTable[0x41].length;
}

void CPU::opcode0x42() // LD B, D
{
    regs.BC.high = regs.DE.high;
    counter += opcodeTable[0x42].duration.firstCondition;
    regs.pc += opcodeTable[0x42].length;
}

void CPU::opcode0x43() // LD B, E
{
    regs.BC.high = regs.DE.low;
    counter += opcodeTable[0x43].duration.firstCondition;
    regs.pc += opcodeTable[0x43].length;
}

void CPU::opcode0x44() // B, H
{
    regs.BC.high = regs.HL.high;
    counter += opcodeTable[0x44].duration.firstCondition;
    regs.pc += opcodeTable[0x44].length;
}

void CPU::opcode0x45() // LD B, L
{
    regs.BC.high = regs.HL.low;
    counter += opcodeTable[0x45].duration.firstCondition;
    regs.pc += opcodeTable[0x45].length;
}

void CPU::opcode0x46() // LD B, (HL)
{
    regs.BC.high = mmu->ReadByte(regs.HL.word);
    counter += opcodeTable[0x46].duration.firstCondition;
    regs.pc += opcodeTable[0x46].length;
}

void CPU::opcode0x47() // LD B, A
{
    regs.BC.high = regs.AF.high;
    counter += opcodeTable[0x47].duration.firstCondition;
    regs.pc += opcodeTable[0x47].length;
}

void CPU::opcode0x48() // LD C, B
{
    regs.BC.low = regs.BC.high;
    counter += opcodeTable[0x48].duration.firstCondition;
    regs.pc += opcodeTable[0x48].length;
}

void CPU::opcode0x49() // LD C, C
{
    counter += opcodeTable[0x49].duration.firstCondition;
    regs.pc += opcodeTable[0x49].length;
}

void CPU::opcode0x4A() // LD C, D
{
    regs.BC.low = regs.DE.high;
    counter += opcodeTable[0x4A].duration.firstCondition;
    regs.pc += opcodeTable[0x4A].length;
}

void CPU::opcode0x4B() // LD C, E
{
    regs.BC.low = regs.DE.low;
    counter += opcodeTable[0x4B].duration.firstCondition;
    regs.pc += opcodeTable[0x4B].length;
}

void CPU::opcode0x4C() // LD C, H
{
    regs.BC.low = regs.HL.high;
    counter += opcodeTable[0x4C].duration.firstCondition;
    regs.pc += opcodeTable[0x4C].length;
}

void CPU::opcode0x4D() // LD C, L
{
    regs.BC.low = regs.HL.low;
    counter += opcodeTable[0x4D].duration.firstCondition;
    regs.pc += opcodeTable[0x4D].length;
}

void CPU::opcode0x4E() // LD C, (HL)
{
    regs.BC.low = mmu->ReadByte(regs.HL.word);
    counter += opcodeTable[0x4C].duration.firstCondition;
    regs.pc += opcodeTable[0x4C].length;
}

void CPU::opcode0x4F() // LD C, A
{
    regs.BC.low = regs.AF.high;
    counter += opcodeTable[0x4C].duration.firstCondition;
    regs.pc += opcodeTable[0x4C].length;
}

void CPU::opcode0x50() // LD D, B
{
    regs.DE.high = regs.BC.high;
    counter += opcodeTable[0x50].duration.firstCondition;
    regs.pc += opcodeTable[0x50].length;
}

void CPU::opcode0x51() // LD D, C
{
    regs.DE.high = regs.BC.low;
    counter += opcodeTable[0x51].duration.firstCondition;
    regs.pc += opcodeTable[0x51].length;
}

void CPU::opcode0x52() // LD D, D
{
    counter += opcodeTable[0x52].duration.firstCondition;
    regs.pc += opcodeTable[0x52].length;
}

void CPU::opcode0x53() // LD D, E
{
    regs.DE.high = regs.DE.low;
    counter += opcodeTable[0x53].duration.firstCondition;
    regs.pc += opcodeTable[0x53].length;
}

void CPU::opcode0x54() // LD D, H
{
    regs.DE.high = regs.HL.high;
    counter += opcodeTable[0x54].duration.firstCondition;
    regs.pc += opcodeTable[0x54].length;
}

void CPU::opcode0x55() // LD D, L
{
    regs.DE.high = regs.HL.low;
    counter += opcodeTable[0x55].duration.firstCondition;
    regs.pc += opcodeTable[0x55].length;
}

void CPU::opcode0x56() // LD D, (HL)
{
    regs.DE.high = mmu->ReadByte(regs.HL.word);
    counter += opcodeTable[0x56].duration.firstCondition;
    regs.pc += opcodeTable[0x56].length;
}

void CPU::opcode0x57() // LD D, A
{
    regs.DE.high = regs.AF.high;
    counter += opcodeTable[0x57].duration.firstCondition;
    regs.pc += opcodeTable[0x57].length;
}

void CPU::opcode0x58() // LD E, B
{
    regs.DE.low = regs.BC.high;
    counter += opcodeTable[0x58].duration.firstCondition;
    regs.pc += opcodeTable[0x58].length;
}

void CPU::opcode0x59() // LD E, C
{
    regs.DE.low = regs.BC.low;
    counter += opcodeTable[0x59].duration.firstCondition;
    regs.pc += opcodeTable[0x59].length;
}

void CPU::opcode0x5A() // LD E, D
{
    regs.DE.low = regs.DE.high;
    counter += opcodeTable[0x5A].duration.firstCondition;
    regs.pc += opcodeTable[0x5A].length;
}

void CPU::opcode0x5B() // LD E, E
{
    counter += opcodeTable[0x5B].duration.firstCondition;
    regs.pc += opcodeTable[0x5B].length;
}

void CPU::opcode0x5C() // LD E, H
{
    regs.DE.low = regs.HL.high;
    counter += opcodeTable[0x5C].duration.firstCondition;
    regs.pc += opcodeTable[0x5C].length;
}

void CPU::opcode0x5D() // LD E, L
{
    regs.DE.low = regs.HL.low;
    counter += opcodeTable[0x5D].duration.firstCondition;
    regs.pc += opcodeTable[0x5D].length;
}

void CPU::opcode0x5E() // LD E, (HL)
{
    regs.DE.low = mmu->ReadByte(regs.HL.word);
    counter += opcodeTable[0x5E].duration.firstCondition;
    regs.pc += opcodeTable[0x5E].length;
}

void CPU::opcode0x5F() // LD E, A
{
    regs.DE.low = regs.AF.high;
    counter += opcodeTable[0x5F].duration.firstCondition;
    regs.pc += opcodeTable[0x5F].length;
}

void CPU::opcode0x60() // LD H, B
{
    regs.HL.high = regs.BC.high;
    counter += opcodeTable[0x60].duration.firstCondition;
    regs.pc += opcodeTable[0x60].length;
}

void CPU::opcode0x61() // LD H, C
{
    regs.HL.high = regs.BC.low;
    counter += opcodeTable[0x61].duration.firstCondition;
    regs.pc += opcodeTable[0x61].length;
}

void CPU::opcode0x62() // LD H, D
{
    regs.HL.high = regs.DE.high;
    counter += opcodeTable[0x62].duration.firstCondition;
    regs.pc += opcodeTable[0x62].length;
}

void CPU::opcode0x63() // LD H, E
{
    regs.HL.high = regs.DE.low;
    counter += opcodeTable[0x63].duration.firstCondition;
    regs.pc += opcodeTable[0x63].length;
}

void CPU::opcode0x64() // LD H, H
{
    regs.HL.high = regs.HL.high;
    counter += opcodeTable[0x64].duration.firstCondition;
    regs.pc += opcodeTable[0x64].length;
}

void CPU::opcode0x65() // LD H, L
{
    regs.HL.high = regs.HL.low;
    counter += opcodeTable[0x65].duration.firstCondition;
    regs.pc += opcodeTable[0x65].length;
}

void CPU::opcode0x66() // LD H, (HL)
{
    regs.HL.high = mmu->ReadByte(regs.HL.word);
    counter += opcodeTable[0x66].duration.firstCondition;
    regs.pc += opcodeTable[0x66].length;
}

void CPU::opcode0x67() // LD H, A
{
    regs.HL.high = regs.AF.high;
    counter += opcodeTable[0x67].duration.firstCondition;
    regs.pc += opcodeTable[0x67].length;
}

void CPU::opcode0x68() // LD L, B
{
    regs.HL.low = regs.BC.high;
    counter += opcodeTable[0x68].duration.firstCondition;
    regs.pc += opcodeTable[0x68].length;
}

void CPU::opcode0x69() // LD L, C
{
    regs.HL.low = regs.BC.low;
    counter += opcodeTable[0x69].duration.firstCondition;
    regs.pc += opcodeTable[0x69].length;
}

void CPU::opcode0x6A() // LD L, D
{
    regs.HL.low = regs.DE.high;
    counter += opcodeTable[0x6A].duration.firstCondition;
    regs.pc += opcodeTable[0x6A].length;
}

void CPU::opcode0x6B() // LD L, E
{
    regs.HL.low = regs.DE.low;
    counter += opcodeTable[0x6B].duration.firstCondition;
    regs.pc += opcodeTable[0x6B].length;
}

void CPU::opcode0x6C() // LD L, H
{
    regs.HL.low = regs.HL.high;
    counter += opcodeTable[0x6C].duration.firstCondition;
    regs.pc += opcodeTable[0x6C].length;
}

void CPU::opcode0x6D() // LD L, L
{
    regs.HL.low = regs.HL.low;
    counter += opcodeTable[0x6D].duration.firstCondition;
    regs.pc += opcodeTable[0x6D].length;
}

void CPU::opcode0x6E() // LD L, (HL)
{
    regs.HL.low = mmu->ReadByte(regs.HL.word);
    counter += opcodeTable[0x6E].duration.firstCondition;
    regs.pc += opcodeTable[0x6E].length;
}

void CPU::opcode0x6F() // LD L, A 
{
    regs.HL.low = regs.AF.high;
    counter += opcodeTable[0x6F].duration.firstCondition;
    regs.pc += opcodeTable[0x6F].length;
}

void CPU::opcode0x70() // LD (HL), B
{
    mmu->WriteByte(regs.HL.word, regs.BC.high);
    counter += opcodeTable[0x70].duration.firstCondition;
    regs.pc += opcodeTable[0x70].length;
}

void CPU::opcode0x71() // LD (HL), C
{
    mmu->WriteByte(regs.HL.word, regs.BC.low);
    counter += opcodeTable[0x71].duration.firstCondition;
    regs.pc += opcodeTable[0x71].length;
}

void CPU::opcode0x72() // LD (HL), D
{
    mmu->WriteByte(regs.HL.word, regs.DE.high);
    counter += opcodeTable[0x72].duration.firstCondition;
    regs.pc += opcodeTable[0x72].length;
}

void CPU::opcode0x73() // LD (HL), E
{
    mmu->WriteByte(regs.HL.word, regs.DE.low);
    counter += opcodeTable[0x73].duration.firstCondition;
    regs.pc += opcodeTable[0x73].length;
}

void CPU::opcode0x74() // LD (HL), H
{
    mmu->WriteByte(regs.HL.word, regs.HL.high);
    counter += opcodeTable[0x74].duration.firstCondition;
    regs.pc += opcodeTable[0x74].length;
}

void CPU::opcode0x75() // LD (HL), L
{
    mmu->WriteByte(regs.HL.word, regs.HL.low);
    counter += opcodeTable[0x75].duration.firstCondition;
    regs.pc += opcodeTable[0x75].length;
}

void CPU::opcode0x76() // HALT   
{
    // Power down CPU until an interrupt occurs. Use this when ever possible to reduce energy consumption.
    //halt = true;
    counter += opcodeTable[0x76].duration.firstCondition;
    regs.pc += opcodeTable[0x76].length;
}

void CPU::opcode0x77() // LD (HL), A
{
    mmu->WriteByte(regs.HL.word, regs.AF.high);
    counter += opcodeTable[0x77].duration.firstCondition;
    regs.pc += opcodeTable[0x77].length;
}

void CPU::opcode0x78() // LD A, B
{
    regs.AF.high = regs.BC.high;
    counter += opcodeTable[0x78].duration.firstCondition;
    regs.pc += opcodeTable[0x78].length;
}

void CPU::opcode0x79() // LD A, C
{
    regs.AF.high = regs.BC.low;
    counter += opcodeTable[0x79].duration.firstCondition;
    regs.pc += opcodeTable[0x79].length;
}

void CPU::opcode0x7A() // LD A, D
{
    regs.AF.high = regs.DE.high;
    counter += opcodeTable[0x7A].duration.firstCondition;
    regs.pc += opcodeTable[0x7A].length;
}

void CPU::opcode0x7B() // LD A, E
{
    regs.AF.high = regs.DE.low;
    counter += opcodeTable[0x7B].duration.firstCondition;
    regs.pc += opcodeTable[0x7B].length;
}

void CPU::opcode0x7C() // LD A, H
{
    regs.AF.high = regs.HL.high;
    counter += opcodeTable[0x7C].duration.firstCondition;
    regs.pc += opcodeTable[0x7C].length;
}

void CPU::opcode0x7D() // LD A, L
{
    regs.AF.high = regs.HL.low;
    counter += opcodeTable[0x7D].duration.firstCondition;
    regs.pc += opcodeTable[0x7D].length;
}

void CPU::opcode0x7E() // LD A, (HL)
{
    regs.AF.high = mmu->ReadByte(regs.HL.word);
    counter += opcodeTable[0x7E].duration.firstCondition;
    regs.pc += opcodeTable[0x7E].length;
}

void CPU::opcode0x7F() // LD A, A
{
    regs.AF.high = regs.AF.high;
    counter += opcodeTable[0x7F].duration.firstCondition;
    regs.pc += opcodeTable[0x7F].length;
}

void CPU::opcode0x80() // ADD A, B
{
    ADD(regs.BC.high);
    counter += opcodeTable[0x80].duration.firstCondition;
    regs.pc += opcodeTable[0x80].length;
}

void CPU::opcode0x81() // ADD A, C
{
    ADD(regs.BC.low);
    counter += opcodeTable[0x81].duration.firstCondition;
    regs.pc += opcodeTable[0x81].length;
}

void CPU::opcode0x82() // ADD A, D
{
    ADD(regs.DE.high);
    counter += opcodeTable[0x82].duration.firstCondition;
    regs.pc += opcodeTable[0x82].length;
}

void CPU::opcode0x83() // ADD A, E
{
    ADD(regs.DE.low);
    counter += opcodeTable[0x83].duration.firstCondition;
    regs.pc += opcodeTable[0x83].length;
}

void CPU::opcode0x84() // ADD A, H
{
    ADD(regs.HL.high);
    counter += opcodeTable[0x84].duration.firstCondition;
    regs.pc += opcodeTable[0x84].length;
}

void CPU::opcode0x85()// ADD A, L
{
    ADD(regs.HL.low);
    counter += opcodeTable[0x85].duration.firstCondition;
    regs.pc += opcodeTable[0x85].length;
}

void CPU::opcode0x86() // ADD A, (HL)
{
    ADD(mmu->ReadByte(regs.HL.word));
    counter += opcodeTable[0x86].duration.firstCondition;
    regs.pc += opcodeTable[0x86].length;
}

void CPU::opcode0x87() // ADD A, A
{
    ADD(regs.AF.high);
    counter += opcodeTable[0x87].duration.firstCondition;
    regs.pc += opcodeTable[0x87].length;
}

void CPU::opcode0x88() // ADC A, B
{
    ADC(regs.BC.high);
    counter += opcodeTable[0x88].duration.firstCondition;
    regs.pc += opcodeTable[0x88].length;
}

void CPU::opcode0x89() // ADC A, C
{
    ADC(regs.BC.low);
    counter += opcodeTable[0x89].duration.firstCondition;
    regs.pc += opcodeTable[0x89].length;
}

void CPU::opcode0x8A() // ADC A, D
{
    ADC(regs.DE.high);
    counter += opcodeTable[0x8A].duration.firstCondition;
    regs.pc += opcodeTable[0x8A].length;
}

void CPU::opcode0x8B() // ADC A, E
{
    ADC(regs.DE.low);
    counter += opcodeTable[0x8B].duration.firstCondition;
    regs.pc += opcodeTable[0x8B].length;
}

void CPU::opcode0x8C() // ADC A, H
{
    ADC(regs.HL.high);
    counter += opcodeTable[0x8C].duration.firstCondition;
    regs.pc += opcodeTable[0x8C].length;
}

void CPU::opcode0x8D() // ADC A, L
{
    ADC(regs.HL.low);
    counter += opcodeTable[0x8D].duration.firstCondition;
    regs.pc += opcodeTable[0x8D].length;
}

void CPU::opcode0x8E() // ADC A, (HL)
{
    ADC(mmu->ReadByte(regs.HL.word));
    counter += opcodeTable[0x8E].duration.firstCondition;
    regs.pc += opcodeTable[0x8E].length;
}

void CPU::opcode0x8F() // ADC A, A
{
    ADC(regs.AF.high);
    counter += opcodeTable[0x8F].duration.firstCondition;
    regs.pc += opcodeTable[0x8F].length;
}

void CPU::opcode0x90() // SUB B
{
    SUB(regs.BC.high);
    counter += opcodeTable[0x90].duration.firstCondition;
    regs.pc += opcodeTable[0x90].length;
}

void CPU::opcode0x91() // SUB C
{
    SUB(regs.BC.low);
    counter += opcodeTable[0x91].duration.firstCondition;
    regs.pc += opcodeTable[0x91].length;
}

void CPU::opcode0x92() // SUB D
{
    SUB(regs.DE.high);
    counter += opcodeTable[0x92].duration.firstCondition;
    regs.pc += opcodeTable[0x92].length;
}

void CPU::opcode0x93() // SUB E
{
    SUB(regs.DE.low);
    counter += opcodeTable[0x93].duration.firstCondition;
    regs.pc += opcodeTable[0x93].length;
}

void CPU::opcode0x94() // SUB H
{
    SUB(regs.HL.high);
    counter += opcodeTable[0x94].duration.firstCondition;
    regs.pc += opcodeTable[0x94].length;
}

void CPU::opcode0x95() // SUB L
{
    SUB(regs.HL.low);
    counter += opcodeTable[0x95].duration.firstCondition;
    regs.pc += opcodeTable[0x95].length;
}

void CPU::opcode0x96() // SUB (HL)
{
    SUB(mmu->ReadByte(regs.HL.word));
    counter += opcodeTable[0x96].duration.firstCondition;
    regs.pc += opcodeTable[0x96].length;
}

void CPU::opcode0x97() // SUB A
{
    SUB(regs.AF.high);
    counter += opcodeTable[0x97].duration.firstCondition;
    regs.pc += opcodeTable[0x97].length;
}

void CPU::opcode0x98() // SBC A, B
{
    SBC(regs.BC.high);
    counter += opcodeTable[0x98].duration.firstCondition;
    regs.pc += opcodeTable[0x98].length;
}

void CPU::opcode0x99() // SBC A, C
{
    SBC(regs.BC.low);
    counter += opcodeTable[0x99].duration.firstCondition;
    regs.pc += opcodeTable[0x99].length;
}

void CPU::opcode0x9A() // SBC A, D
{
    SBC(regs.DE.high);
    counter += opcodeTable[0x9A].duration.firstCondition;
    regs.pc += opcodeTable[0x9A].length;
}

void CPU::opcode0x9B() // SBC A, E
{
    SBC(regs.DE.low);
    counter += opcodeTable[0x9B].duration.firstCondition;
    regs.pc += opcodeTable[0x9B].length;
}

void CPU::opcode0x9C() // SBC A, H
{
    SBC(regs.HL.high);
    counter += opcodeTable[0x9C].duration.firstCondition;
    regs.pc += opcodeTable[0x9C].length;
}

void CPU::opcode0x9D() // SBC A, L
{
    SBC(regs.HL.low);
    counter += opcodeTable[0x9D].duration.firstCondition;
    regs.pc += opcodeTable[0x9D].length;
}

void CPU::opcode0x9E() // SBC A, (HL)
{
    SBC(mmu->ReadByte(regs.HL.word));
    counter += opcodeTable[0x9E].duration.firstCondition;
    regs.pc += opcodeTable[0x9E].length;
}

void CPU::opcode0x9F() // SBC A, A
{
    SBC(regs.AF.high);
    counter += opcodeTable[0x9F].duration.firstCondition;
    regs.pc += opcodeTable[0x9F].length;
}

void CPU::opcode0xA0() // AND B
{
    AND(regs.BC.high);
    counter += opcodeTable[0xA0].duration.firstCondition;
    regs.pc += opcodeTable[0xA0].length;
}

void CPU::opcode0xA1() // AND C
{
    AND(regs.BC.low);
    counter += opcodeTable[0xA1].duration.firstCondition;
    regs.pc += opcodeTable[0xA1].length;
}

void CPU::opcode0xA2() // AND D
{
    AND(regs.DE.high);
    counter += opcodeTable[0xA2].duration.firstCondition;
    regs.pc += opcodeTable[0xA2].length;
}

void CPU::opcode0xA3() // AND E
{
    AND(regs.DE.low);
    counter += opcodeTable[0xA3].duration.firstCondition;
    regs.pc += opcodeTable[0xA3].length;
}

void CPU::opcode0xA4() // AND H
{
    AND(regs.HL.high);
    counter += opcodeTable[0xA4].duration.firstCondition;
    regs.pc += opcodeTable[0xA4].length;
}

void CPU::opcode0xA5() // AND L
{
    AND(regs.HL.low);
    counter += opcodeTable[0xA5].duration.firstCondition;
    regs.pc += opcodeTable[0xA5].length;
}


void CPU::opcode0xA6() // AND (HL)
{
    AND(mmu->ReadByte(regs.HL.word));
    counter += opcodeTable[0xA6].duration.firstCondition;
    regs.pc += opcodeTable[0xA6].length;
}


void CPU::opcode0xA7() // AND A
{
    AND(regs.AF.high);
    counter += opcodeTable[0xA7].duration.firstCondition;
    regs.pc += opcodeTable[0xA7].length;
}

void CPU::opcode0xA8() // XOR B
{
    XOR(regs.BC.high);
    counter += opcodeTable[0xA8].duration.firstCondition;
    regs.pc += opcodeTable[0xA8].length;
}

void CPU::opcode0xA9() // XOR C
{
    XOR(regs.BC.low);
    counter += opcodeTable[0xA9].duration.firstCondition;
    regs.pc += opcodeTable[0xA9].length;
}

void CPU::opcode0xAA() // XOR D
{
    XOR(regs.DE.high);
    counter += opcodeTable[0xAA].duration.firstCondition;
    regs.pc += opcodeTable[0xAA].length;
}

void CPU::opcode0xAB() // XOR E
{
    XOR(regs.DE.low);
    counter += opcodeTable[0xAB].duration.firstCondition;
    regs.pc += opcodeTable[0xAB].length;
}

void CPU::opcode0xAC() // XOR H
{
    XOR(regs.HL.high);
    counter += opcodeTable[0xAC].duration.firstCondition;
    regs.pc += opcodeTable[0xAC].length;
}

void CPU::opcode0xAD() // XOR L
{
    XOR(regs.HL.low);
    counter += opcodeTable[0xAD].duration.firstCondition;
    regs.pc += opcodeTable[0xAD].length;
}

void CPU::opcode0xAE() // XOR (HL)
{
    XOR(mmu->ReadByte(regs.HL.word));
    counter += opcodeTable[0xAE].duration.firstCondition;
    regs.pc += opcodeTable[0xAE].length;
}

void CPU::opcode0xAF() // XOR A
{
    XOR(regs.AF.high);
    counter += opcodeTable[0xAF].duration.firstCondition;
    regs.pc += opcodeTable[0xAF].length;
}

void CPU::opcode0xB0() // OR B
{
    OR(regs.BC.high);
    counter += opcodeTable[0xB0].duration.firstCondition;
    regs.pc += opcodeTable[0xB0].length;
}

void CPU::opcode0xB1() // OR C
{
    OR(regs.BC.low);
    counter += opcodeTable[0xB1].duration.firstCondition;
    regs.pc += opcodeTable[0xB1].length;
}

void CPU::opcode0xB2() // OR D
{
    OR(regs.DE.high);
    counter += opcodeTable[0xB2].duration.firstCondition;
    regs.pc += opcodeTable[0xB2].length;
}

void CPU::opcode0xB3() // OR E
{
    OR(regs.DE.low);
    counter += opcodeTable[0xB3].duration.firstCondition;
    regs.pc += opcodeTable[0xB3].length;
}

void CPU::opcode0xB4() // OR H
{
    OR(regs.HL.high);
    counter += opcodeTable[0xB4].duration.firstCondition;
    regs.pc += opcodeTable[0xB4].length;
}

void CPU::opcode0xB5() // OR L
{
    OR(regs.HL.low);
    counter += opcodeTable[0xB5].duration.firstCondition;
    regs.pc += opcodeTable[0xB5].length;
}

void CPU::opcode0xB6() // OR (HL)
{
    OR(mmu->ReadByte(regs.HL.word));
    counter += opcodeTable[0xB6].duration.firstCondition;
    regs.pc += opcodeTable[0xB6].length;
}

void CPU::opcode0xB7() // OR A
{
    OR(regs.AF.high);
    counter += opcodeTable[0xB7].duration.firstCondition;
    regs.pc += opcodeTable[0xB7].length;
}

void CPU::opcode0xB8() // CP B
{
    CP(regs.BC.high);
    counter += opcodeTable[0xB8].duration.firstCondition;
    regs.pc += opcodeTable[0xB8].length;
}

void CPU::opcode0xB9() // CP C
{
    CP(regs.BC.low);
    counter += opcodeTable[0xB9].duration.firstCondition;
    regs.pc += opcodeTable[0xB9].length;
}

void CPU::opcode0xBA() // CP D
{
    CP(regs.DE.high);
    counter += opcodeTable[0xBA].duration.firstCondition;
    regs.pc += opcodeTable[0xBA].length;
}

void CPU::opcode0xBB() // CP E
{
    CP(regs.DE.low);
    counter += opcodeTable[0xBB].duration.firstCondition;
    regs.pc += opcodeTable[0xBB].length;
}

void CPU::opcode0xBC() // CP H
{
    CP(regs.HL.high);
    counter += opcodeTable[0xBC].duration.firstCondition;
    regs.pc += opcodeTable[0xBC].length;
}

void CPU::opcode0xBD() // CP L
{
    CP(regs.HL.low);
    counter += opcodeTable[0xBD].duration.firstCondition;
    regs.pc += opcodeTable[0xBD].length;
}

void CPU::opcode0xBE() // CP (HL)
{
    CP(mmu->ReadByte(regs.HL.word));
    counter += opcodeTable[0xBE].duration.firstCondition;
    regs.pc += opcodeTable[0xBE].length;
}

void CPU::opcode0xBF() // CP A
{
    CP(regs.AF.high);
    counter += opcodeTable[0xBF].duration.firstCondition;
    regs.pc += opcodeTable[0xBF].length;
}

void CPU::opcode0xC0() // RET NZ
{
    if (((regs.AF.low & ZERO_FLAG) >> ZERO_BIT) == 0x00)
    {
        counter += opcodeTable[0xC0].duration.firstCondition;
        regs.pc = mmu->PopTwoBytes(regs.sp);
    }
    else
    {
        counter += opcodeTable[0xC0].duration.secondCondition;
        regs.pc += opcodeTable[0xC0].length;
    }
}

void CPU::opcode0xC1() // POP BC
{
    regs.BC.word = mmu->PopTwoBytes(regs.sp);
    counter += opcodeTable[0xC1].duration.firstCondition;
    regs.pc += opcodeTable[0xC1].length;
}

void CPU::opcode0xC2() // JP NZ, a16
{
    if (((regs.AF.low & ZERO_FLAG) >> ZERO_BIT) == 0x00)
    {
        counter += opcodeTable[0xC2].duration.firstCondition;
        //regs.pc += opcodeTable[0xC2].length;
        regs.pc = mmu->ReadTwoBytes(regs.pc + 1);
    }
    else
    {
        counter += opcodeTable[0xC2].duration.secondCondition;
        regs.pc += opcodeTable[0xc2].length;
    }
}

void CPU::opcode0xC3() // jp a16
{
    counter += opcodeTable[0xC3].duration.firstCondition;
    regs.pc = mmu->ReadTwoBytes(regs.pc + 1);
}

void CPU::opcode0xC4() // CALL NZ, a16
{
    if (((regs.AF.low & ZERO_FLAG) >> ZERO_FLAG) == 0x00)
    {
        counter += opcodeTable[0xC4].duration.firstCondition;
        mmu->PushTwoBytes(regs.sp, regs.pc + opcodeTable[0xC4].length);
        regs.pc = mmu->ReadTwoBytes(regs.pc + 1);
    }
    else
    {
        counter += opcodeTable[0xC4].duration.secondCondition;
        regs.pc += opcodeTable[0xc4].length;
    }
}

void CPU::opcode0xC5() // PUSH BC
{
    mmu->PushTwoBytes(regs.sp, regs.BC.word);
    counter += opcodeTable[0xC5].duration.firstCondition;
    regs.pc += opcodeTable[0xc5].length;
}

void CPU::opcode0xC6() // ADD A, d8
{
    ADD(mmu->ReadByte(regs.pc + 1));
    counter += opcodeTable[0xC6].duration.firstCondition;
    regs.pc += opcodeTable[0xC6].length;
}

void CPU::opcode0xC7() // RST 00h
{
    counter += opcodeTable[0xC7].duration.firstCondition;
    regs.pc += opcodeTable[0xC7].length;
    mmu->PushTwoBytes(regs.sp, regs.pc);
    regs.pc = 0x0000;
}

void CPU::opcode0xC8() // RET Z
{
    if (((regs.AF.low & ZERO_FLAG) >> ZERO_BIT) == 0x01)
    {
        counter += opcodeTable[0xC8].duration.firstCondition;
        regs.pc = mmu->PopTwoBytes(regs.sp);
    }
    else
    {
        counter += opcodeTable[0xC8].duration.secondCondition;
        regs.pc += opcodeTable[0xC8].length;
    }
}

void CPU::opcode0xC9() // RET
{
    counter += opcodeTable[0xC9].duration.firstCondition;
    regs.pc = mmu->PopTwoBytes(regs.sp);
}

void CPU::opcode0xCA() // JP Z, a16
{
    if (((regs.AF.low & ZERO_FLAG) >> ZERO_BIT) == 0x01)
    {
        counter += opcodeTable[0xCA].duration.firstCondition;
        //regs.pc += opcodeTable[0xCA].length;
        regs.pc = mmu->ReadTwoBytes(regs.pc + 1);
    }
    else
    {
        counter += opcodeTable[0xCA].duration.secondCondition;
        regs.pc += opcodeTable[0xcA].length;
    }
}

void CPU::opcode0xCB() // prefix CB
{
    u8 opcodeByte = mmu->ReadByte(regs.pc + 1);
    
	assert(opcodeFunctionCB[opcodeByte] != nullptr); // Unknown CB operation

    (this->*opcodeFunctionCB[opcodeByte])(); // Process instruction from other table
   

}

void CPU::opcode0xCC() // CALL Z, a16
{
    if (((regs.AF.low & ZERO_FLAG) >> ZERO_BIT) == 0x01)
    {
        counter += opcodeTable[0xCC].duration.firstCondition;
        mmu->PushTwoBytes(regs.sp, regs.pc + opcodeTable[0xCC].length);
        regs.pc = mmu->ReadTwoBytes(regs.pc + 1);
    }
    else
    {
        counter += opcodeTable[0xCC].duration.secondCondition;
        regs.pc += opcodeTable[0xcC].length;
    }
}

void CPU::opcode0xCD() // CALL a16
{
    counter += opcodeTable[0xCD].duration.firstCondition;
    mmu->PushTwoBytes(regs.sp, regs.pc + opcodeTable[0xCD].length);
    regs.pc = mmu->ReadTwoBytes(regs.pc + 1);
}

void CPU::opcode0xCE() // ADC A, d8
{
    ADC(mmu->ReadByte(regs.pc + 1));
    counter += opcodeTable[0xCE].duration.firstCondition;
    regs.pc += opcodeTable[0xCE].length;

}

void CPU::opcode0xCF() // RST 08h
{
    counter += opcodeTable[0xCF].duration.firstCondition;
    regs.pc += opcodeTable[0xCF].length;
    mmu->PushTwoBytes(regs.sp, regs.pc);
    regs.pc = 0x0008;
}

void CPU::opcode0xD0() // RET NC
{
    if (((regs.AF.low & CARRY_FLAG) >> CARRY_BIT) == 0x00)
    {
        counter += opcodeTable[0xD0].duration.firstCondition;
        regs.pc = mmu->PopTwoBytes(regs.sp);
    }
    else
    {
        counter += opcodeTable[0xD0].duration.secondCondition;
        regs.pc += opcodeTable[0xD0].length;
    }
}

void CPU::opcode0xD1() //POP DE
{
    regs.DE.word = mmu->PopTwoBytes(regs.sp);
    counter += opcodeTable[0xD1].duration.firstCondition;
    regs.pc += opcodeTable[0xD1].length;
}

void CPU::opcode0xD2() // JP NC, a16
{
    if (((regs.AF.low & CARRY_FLAG) >> CARRY_BIT) == 0x00)
    {
        counter += opcodeTable[0xD2].duration.firstCondition;
        regs.pc = mmu->ReadTwoBytes(regs.pc + 1);
        //regs.pc += opcodeTable[0xD2].length;
    }
    else
    {
        counter += opcodeTable[0xD2].duration.secondCondition;
        regs.pc += opcodeTable[0xD2].length;
    }
}

// opcode D3 unused

void CPU::opcode0xD4() // CALL NC a16
{
    if (((regs.AF.low & CARRY_FLAG) >> CARRY_BIT) == 0x00)
    {
        counter += opcodeTable[0xD4].duration.firstCondition;
        mmu->PushTwoBytes(regs.sp, regs.pc + opcodeTable[0xD4].length);
        regs.pc = mmu->ReadTwoBytes(regs.pc + 1);
    }
    else
    {
        counter += opcodeTable[0xD4].duration.secondCondition;
        regs.pc += opcodeTable[0xD4].length;
    }
}

void CPU::opcode0xD5() // PUSH DE
{
    mmu->PushTwoBytes(regs.sp, regs.DE.word);
    counter += opcodeTable[0xD5].duration.firstCondition;
    regs.pc += opcodeTable[0xD5].length;
}

void CPU::opcode0xD6() // SUB d8
{
    SUB(mmu->ReadByte(regs.pc + 1));
    counter += opcodeTable[0xD6].duration.firstCondition;
    regs.pc += opcodeTable[0xD6].length;
}

void CPU::opcode0xD7() // RST 10h
{
    counter += opcodeTable[0xD7].duration.firstCondition;
    regs.pc += opcodeTable[0xD7].length;
    mmu->PushTwoBytes(regs.sp, regs.pc);
    regs.pc = 0x0010;
}

void CPU::opcode0xD8() // RET C
{
    if (((regs.AF.low & CARRY_FLAG) >> CARRY_BIT) == 0x01)
    {
        counter += opcodeTable[0xD8].duration.firstCondition;
        regs.pc = mmu->PopTwoBytes(regs.sp);
    }
    else
    {
        counter += opcodeTable[0xD8].duration.secondCondition;
        regs.pc += opcodeTable[0xD8].length;
    }
}

void CPU::opcode0xD9() // RETI
{
    regs.ime = 0x01;
    counter += opcodeTable[0xD9].duration.firstCondition;
    regs.pc = mmu->PopTwoBytes(regs.sp);
   
    
}

void CPU::opcode0xDA() // JP C, a16
{
    if (((regs.AF.low & CARRY_FLAG) >> CARRY_BIT) == 0x01)
    {
        counter += opcodeTable[0xDA].duration.firstCondition;
        regs.pc = mmu->ReadTwoBytes(regs.pc + 1);
        //regs.pc += opcodeTable[0xDA].length;
    }
    else
    {
        counter += opcodeTable[0xDA].duration.secondCondition;
        regs.pc += opcodeTable[0xDA].length;
    }
}

// opcode DB unused

void CPU::opcode0xDC() // CALL C,a16
{
    if (((regs.AF.low & CARRY_FLAG) >> CARRY_BIT) == 0x01)
    {
        counter += opcodeTable[0xDC].duration.firstCondition;
        mmu->PushTwoBytes(regs.sp, regs.pc + +opcodeTable[0xDC].length);
        regs.pc = mmu->ReadTwoBytes(regs.pc + 1);
    }
    else
    {
        counter += opcodeTable[0xDC].duration.secondCondition;
        regs.pc += opcodeTable[0xDC].length;
    }
}

// opcode DE unused

void CPU::opcode0xDE() // SBC A, d8
{
    SBC(mmu->ReadByte(regs.pc + 1));
    counter += opcodeTable[0xDE].duration.firstCondition;
    regs.pc += opcodeTable[0xDE].length;
}

void CPU::opcode0xDF() // RST 18H
{
    counter += opcodeTable[0xDF].duration.firstCondition;
    regs.pc += opcodeTable[0xDF].length;
    mmu->PushTwoBytes(regs.sp, regs.pc);
    regs.pc = 0x0018;
}

void CPU::opcode0xE0() // LDH (a8), A
{
    // Put A into memory address $FF00+n
    u8 location = mmu->ReadByte(regs.pc + 1);
    mmu->WriteByte(0xFF00 + location, regs.AF.high);
    counter += opcodeTable[0xE0].duration.firstCondition;
    regs.pc += opcodeTable[0xE0].length;
}

void CPU::opcode0xE1() // POP HL
{
    regs.HL.word = mmu->PopTwoBytes(regs.sp);
    counter += opcodeTable[0xE1].duration.firstCondition;
    regs.pc += opcodeTable[0xE1].length;
}

void CPU::opcode0xE2() // LD (C), A
{
    // Put A into address $FF00 + register C.
    mmu->WriteByte(0xFF00 + regs.BC.low, regs.AF.high);
    counter += opcodeTable[0xE2].duration.firstCondition;
    regs.pc += opcodeTable[0xE2].length;
}

// opcode E3 unused
// opcode E4 unused

void CPU::opcode0xE5() // PUSH HL
{
    mmu->PushTwoBytes(regs.sp, regs.HL.word);
    counter += opcodeTable[0xE5].duration.firstCondition;
    regs.pc += opcodeTable[0xE5].length;
}

void CPU::opcode0xE6() // AND d8
{
    AND(mmu->ReadByte(regs.pc + 1));
    counter += opcodeTable[0xE6].duration.firstCondition;
    regs.pc += opcodeTable[0xE6].length;
}

void CPU::opcode0xE7() // RST 20h
{
    counter += opcodeTable[0xE7].duration.firstCondition;
    regs.pc += opcodeTable[0xE7].length;
    mmu->PushTwoBytes(regs.sp, regs.pc);
    regs.pc = 0x0020;
}

void CPU::opcode0xE8() // ADD SP, r8 Flags: 0 0 H C
{
    u8 operand = mmu->ReadByte(regs.pc + 1);
	
	int result = regs.sp + (s8)operand;
	UnsetFlag(ZERO_FLAG);
    UnsetFlag(SUBTRACT_FLAG); // reset zero and subtract flag
	
	if (((regs.sp & 0xFF) + (operand & 0xFF) > 0xFF))
		SetFlag(CARRY_FLAG);
	else
		UnsetFlag(CARRY_FLAG);

	
	if ((((regs.sp & 0x0F) + (operand & 0x0F)) & 0x10) == 0x10) 
        SetFlag(HALF_CARRY_FLAG);
    else
        UnsetFlag(HALF_CARRY_FLAG);

    
	regs.sp = (s16)result;
    counter += opcodeTable[0xE8].duration.firstCondition;
    regs.pc += opcodeTable[0xE8].length;
}

void CPU::opcode0xE9() // JP (HL)
{
    regs.pc = regs.HL.word; // ->ReadByte(regs.HL.word);
    counter += opcodeTable[0xE9].duration.firstCondition;
    //regs.pc += opcodeTable[0xE9].length; // No need to add length
}

void CPU::opcode0xEA() // LD (a16), A
{
    // write A to two byte immediate value
    mmu->WriteByte(mmu->ReadTwoBytes(regs.pc + 1), regs.AF.high);
    counter += opcodeTable[0xEA].duration.firstCondition;
    regs.pc += opcodeTable[0xEA].length;
}

// opcode EB unused
// opcode EC unused
// opcode ED unused

void CPU::opcode0xEE() // XOR d8
{
    XOR(mmu->ReadByte(regs.pc + 1));
    counter += opcodeTable[0xEE].duration.firstCondition;
    regs.pc += opcodeTable[0xEE].length;
}

void CPU::opcode0xEF() // RST 28h
{
    counter += opcodeTable[0xEF].duration.firstCondition;
    regs.pc += opcodeTable[0xEF].length;
    mmu->PushTwoBytes(regs.sp, regs.pc);
    regs.pc = 0x0028;
   
}

void CPU::opcode0xF0() // LDH A, (a8)
{
    // Put memory address $FF00+n into A.
    u8 location = mmu->ReadByte(regs.pc + 1);
    regs.AF.high = mmu->ReadByte(0xFF00 + location);
    counter += opcodeTable[0xF0].duration.firstCondition;
    regs.pc += opcodeTable[0xF0].length;
}

void CPU::opcode0xF1() // POP AF
{

    regs.AF.word = mmu->PopTwoBytes(regs.sp) & 0xFFF0; // Can't access the flags part of the F register

    counter += opcodeTable[0xF1].duration.firstCondition;
    regs.pc += opcodeTable[0xF1].length;
}

void CPU::opcode0xF2() // LD A, (c)
{
    // Put value at address $FF00 + register C into A
    regs.AF.high = mmu->ReadByte(0xFF00 + regs.BC.low);
    counter += opcodeTable[0xE2].duration.firstCondition;
    regs.pc += opcodeTable[0xE2].length;
}

void CPU::opcode0xF3() // DI
{
    regs.ime = 0x00;
    // Disable interrupts AFTER the next instruction is executed
    counter += opcodeTable[0xF3].duration.firstCondition;
    regs.pc += opcodeTable[0xF3].length;
   
}

// opcode F4 unused

void CPU::opcode0xF5() // PUSH AF
{
    mmu->PushTwoBytes(regs.sp, regs.AF.word);
    counter += opcodeTable[0xF5].duration.firstCondition;
    regs.pc += opcodeTable[0xF5].length;
}

void CPU::opcode0xF6() // OR d8
{
    OR(mmu->ReadByte(regs.pc + 1));
    counter += opcodeTable[0xF6].duration.firstCondition;
    regs.pc += opcodeTable[0xF6].length;
}

void CPU::opcode0xF7() // RST 30h
{
    counter += opcodeTable[0xF7].duration.firstCondition;
    regs.pc += opcodeTable[0xF7].length;
    mmu->PushTwoBytes(regs.sp, regs.pc);
    regs.pc = 0x0030;
}

void CPU::opcode0xF8() // LD HL,SP+r8 Flags: 0 0 H C
{
    u8 operand = mmu->ReadByte(regs.pc + 1);
	int result = regs.sp + (s8)operand;

    UnsetFlag(ZERO_FLAG);
    UnsetFlag(SUBTRACT_FLAG); // reset subtract flag

	if (((regs.sp & 0xFF) + (operand & 0xFF) > 0xFF))
		SetFlag(CARRY_FLAG);
	else
		UnsetFlag(CARRY_FLAG);


	if ((((regs.sp & 0x0F) + (operand & 0x0F)) & 0x10) == 0x10)
		SetFlag(HALF_CARRY_FLAG);
	else
		UnsetFlag(HALF_CARRY_FLAG);

    regs.HL.word = result & 0xFFFF;
    counter += opcodeTable[0xF8].duration.firstCondition;
    regs.pc += opcodeTable[0xF8].length;
}

void CPU::opcode0xF9() // LD SP, HL
{
    regs.sp = regs.HL.word;
    counter += opcodeTable[0xF9].duration.firstCondition;
    regs.pc += opcodeTable[0xF9].length;
}

void CPU::opcode0xFA() // LD A, (a16)
{
    regs.AF.high = mmu->ReadByte(mmu->ReadTwoBytes(regs.pc + 1));
    counter += opcodeTable[0xFA].duration.firstCondition;
    regs.pc += opcodeTable[0xFA].length;
}

void CPU::opcode0xFB() // EI
{
    // Enable interrupts AFTER the next instruction is executed
    regs.ime = 0x01;
    counter += opcodeTable[0xFB].duration.firstCondition;
    regs.pc += opcodeTable[0xFB].length;
}

// opcode FC unused
// opcode FD unused

void CPU::opcode0xFE() // CP d8
{
    CP(mmu->ReadByte(regs.pc + 1)); // Could be an issue with flags here, specifically Z H and C
    counter += opcodeTable[0xFE].duration.firstCondition;
    regs.pc += opcodeTable[0xFE].length;
}

void CPU::opcode0xFF() // RST 38h
{
    counter += opcodeTable[0xFF].duration.firstCondition;
    regs.pc += opcodeTable[0xFF].length;
    mmu->PushTwoBytes(regs.sp, regs.pc);
    regs.pc = 0x0038;

}





//---------------------------------------------
//      Helper functions
//---------------------------------------------

inline void CPU::INC(u8 &reg) // Flags: Z 0 H -
{
    reg++;

    // Set flags
    if (reg == 0x00)
        SetFlag(ZERO_FLAG);
    else
        UnsetFlag(ZERO_FLAG);

    UnsetFlag(SUBTRACT_FLAG); // Reset flag

    if (((((reg - 0x01) & 0xF) + (0x1 & 0xF)) & 0x10) == 0x10) // Carry from 3rd bit
        SetFlag(HALF_CARRY_FLAG);
    else
        UnsetFlag(HALF_CARRY_FLAG);
}

inline void CPU::DEC(u8 &reg) // Flags: Z 1 H -
{

    reg--;

	if (reg == 0x00)
		SetFlag(ZERO_FLAG);
	else
		UnsetFlag(ZERO_FLAG);
    
    SetFlag(SUBTRACT_FLAG); // Set flag

	if ((reg & 0x0F) == 0x0F) // Set if no borrow from bit 4
		SetFlag(HALF_CARRY_FLAG);
	else
        UnsetFlag(HALF_CARRY_FLAG);
}

// TODO: Ordering of flags or addition
inline void CPU::ADD16(u16 &reg1, u16 &reg2) // Flags: - 0 H C
{
    UnsetFlag(SUBTRACT_FLAG); // Reset flag

	if ((((reg1 & 0xFFF) + (reg2 & 0xFFF)) & 0x1000) == 0x1000) // Carry from 11th bit
		SetFlag(HALF_CARRY_FLAG);
	else
        UnsetFlag(HALF_CARRY_FLAG);

	if ((reg1 + reg2) > 0xFFFF) // Carry from 15th bit
		SetFlag(CARRY_FLAG);
	else
        UnsetFlag(CARRY_FLAG);

    reg1 += reg2;
}

inline void CPU::ADD(u8 operand) // Flags: Z 0 H C
{
    s32 result = (regs.AF.high + operand);

    if (result & 0xFF00)
        SetFlag(CARRY_FLAG);
    else
        UnsetFlag(CARRY_FLAG);

    regs.AF.high = (u8)(result & 0xFF);

    if (regs.AF.high == 0x00) // Check for Zero flag
        SetFlag(ZERO_FLAG);
    else
        UnsetFlag(ZERO_FLAG);

    UnsetFlag(SUBTRACT_FLAG); // reset subtract flag

    if ((((regs.AF.high & 0xF) - (operand & 0xF)) & 0x10) == 0x10) // Carry from 3rd bit
        SetFlag(HALF_CARRY_FLAG);
    else
        UnsetFlag(HALF_CARRY_FLAG);
}

inline void CPU::SUB(u8 operand) // Flags: Z 1 H C
{
	if ((regs.AF.high - operand) == 0x00) // Check for Zero flag
		SetFlag(ZERO_FLAG);
	else
		UnsetFlag(ZERO_FLAG);

	SetFlag(SUBTRACT_FLAG); // Set subtract flag

	if ((operand & 0x0F) > (regs.AF.high & 0x0F))
		SetFlag(HALF_CARRY_FLAG);
	else
		UnsetFlag(HALF_CARRY_FLAG);

	if (operand > regs.AF.high)
		SetFlag(CARRY_FLAG);
	else
		UnsetFlag(CARRY_FLAG);

	regs.AF.high -= operand;
}

inline void CPU::ADC(u8 operand) // FLAGS: Z 0 H C
{
    u8 carry = (regs.AF.low & CARRY_FLAG) ? 1 : 0;


    int result = regs.AF.high + operand + carry;

    if ((u8)result == 0x00) // Check for Zero flag
        SetFlag(ZERO_FLAG);
    else
        UnsetFlag(ZERO_FLAG);

    UnsetFlag(SUBTRACT_FLAG); // reset subtract flag
	
    if (result > 0xFF) // Set if carry from bit 7
        SetFlag(CARRY_FLAG);
    else
        UnsetFlag(CARRY_FLAG);

    if (((regs.AF.high & 0x0F) + (operand & 0x0F) + carry) > 0x0F) // Set if carry from bit 3
        SetFlag(HALF_CARRY_FLAG);
    else
        UnsetFlag(HALF_CARRY_FLAG);

    regs.AF.high = (u8)(result);
}

inline void CPU::SBC(u8 operand) // Flags: Z 1 H C - Subtract n + Carry flag from A
{
    u8 carry = (regs.AF.low & CARRY_FLAG) ? 1 : 0;
	int result = regs.AF.high - operand - carry;

    if ((u8)result == 0x00) // Check for Zero flag
        SetFlag(ZERO_FLAG);
    else
        UnsetFlag(ZERO_FLAG);

    SetFlag(SUBTRACT_FLAG); // Set subtract flag

	if (result < 0) // Set if no borrow
		SetFlag(CARRY_FLAG);
	else
		UnsetFlag(CARRY_FLAG);


    if (((regs.AF.high & 0x0F) - (operand & 0x0F) - carry) < 0) // Borrow from bit 3
        SetFlag(HALF_CARRY_FLAG);
    else
        UnsetFlag(HALF_CARRY_FLAG);

    
    regs.AF.high = (u8)result;

}

inline void CPU::AND(u8 operand) // Flags: Z 0 1 0
{
    UnsetFlag(SUBTRACT_FLAG);  // Reset
    SetFlag(HALF_CARRY_FLAG); // Set
    UnsetFlag(CARRY_FLAG);     // Reset

    regs.AF.high &= operand;
    
    if (regs.AF.high == 0x00)
        SetFlag(ZERO_FLAG);
    else
        UnsetFlag(ZERO_FLAG);

}

inline void CPU::XOR(u8 operand) // Flags: Z 0 0 0 
{
    // reset flags
    UnsetFlag(SUBTRACT_FLAG);
    UnsetFlag(HALF_CARRY_FLAG);
    UnsetFlag(CARRY_FLAG);

    regs.AF.high ^= operand;

    if (regs.AF.high == 0x00)
        SetFlag(ZERO_FLAG);
    else
        UnsetFlag(ZERO_FLAG);
}

inline void CPU::OR(u8 operand) // Flags: Z 0 0 0
{
    // reset flags
    UnsetFlag(SUBTRACT_FLAG);
    UnsetFlag(HALF_CARRY_FLAG);
    UnsetFlag(CARRY_FLAG);

    regs.AF.high |= operand;

    if (regs.AF.high == 0x00)
        SetFlag(ZERO_FLAG);
    else
        UnsetFlag(ZERO_FLAG);
}

inline void CPU::CP(u8 operand) // Flags: Z 1 H C
{
    if (regs.AF.high == operand)
        SetFlag(ZERO_FLAG);   // 1
    else
        UnsetFlag(ZERO_FLAG);  // 0

    SetFlag(SUBTRACT_FLAG); // Set

    if((operand & 0x0F) > (regs.AF.high & 0x0F))
        SetFlag(HALF_CARRY_FLAG);
    else
        UnsetFlag(HALF_CARRY_FLAG);

    if(operand > regs.AF.high)
        SetFlag(CARRY_FLAG);
    else
        UnsetFlag(CARRY_FLAG);
}

// Interrupt jumps

void CPU::RST40() // RST 40h
{
    counter += opcodeTable[0xFF].duration.firstCondition;
    //regs.pc += opcodeTable[0xFF].length;
    mmu->PushTwoBytes(regs.sp, regs.pc);
    regs.pc = 0x0040;

}

void CPU::RST48() // RST 48h
{
    counter += opcodeTable[0xFF].duration.firstCondition;
    //regs.pc += opcodeTable[0xFF].length;
    mmu->PushTwoBytes(regs.sp, regs.pc);
    regs.pc = 0x0048;

}

void CPU::RST50() // RST 50h
{
    counter += opcodeTable[0xFF].duration.firstCondition;
    //regs.pc += opcodeTable[0xFF].length;
    mmu->PushTwoBytes(regs.sp, regs.pc);
    regs.pc = 0x0050;

}

void CPU::RST58() // RST 58h
{
    counter += opcodeTable[0xFF].duration.firstCondition;
    //regs.pc += opcodeTable[0xFF].length;
    mmu->PushTwoBytes(regs.sp, regs.pc);
    regs.pc = 0x0058;
}

void CPU::RST60() // RST 60h
{
    counter += opcodeTable[0xFF].duration.firstCondition;
    //regs.pc += opcodeTable[0xFF].length;
    mmu->PushTwoBytes(regs.sp, regs.pc);
    regs.pc = 0x0060;

}

// Assigns all of the function pointers
void CPU::InitOpcodeFunctions()
{
    opcodeFunction[0x00] = &CPU::opcode0x00;
    opcodeFunction[0x01] = &CPU::opcode0x01;
    opcodeFunction[0x02] = &CPU::opcode0x02;
    opcodeFunction[0x03] = &CPU::opcode0x03;
    opcodeFunction[0x04] = &CPU::opcode0x04;
    opcodeFunction[0x05] = &CPU::opcode0x05;
    opcodeFunction[0x06] = &CPU::opcode0x06;
    opcodeFunction[0x07] = &CPU::opcode0x07;
    opcodeFunction[0x08] = &CPU::opcode0x08;
    opcodeFunction[0x09] = &CPU::opcode0x09;
    opcodeFunction[0x0A] = &CPU::opcode0x0A;
    opcodeFunction[0x0B] = &CPU::opcode0x0B;
    opcodeFunction[0x0C] = &CPU::opcode0x0C;
    opcodeFunction[0x0D] = &CPU::opcode0x0D;
    opcodeFunction[0x0E] = &CPU::opcode0x0E;
    opcodeFunction[0x0F] = &CPU::opcode0x0F;
    opcodeFunction[0x10] = &CPU::opcode0x10;
    opcodeFunction[0x11] = &CPU::opcode0x11;
    opcodeFunction[0x12] = &CPU::opcode0x12;
    opcodeFunction[0x13] = &CPU::opcode0x13;
    opcodeFunction[0x14] = &CPU::opcode0x14;
    opcodeFunction[0x15] = &CPU::opcode0x15;
    opcodeFunction[0x16] = &CPU::opcode0x16;
    opcodeFunction[0x17] = &CPU::opcode0x17;
    opcodeFunction[0x18] = &CPU::opcode0x18;
    opcodeFunction[0x19] = &CPU::opcode0x19;
    opcodeFunction[0x1A] = &CPU::opcode0x1A;
    opcodeFunction[0x1B] = &CPU::opcode0x1B;
    opcodeFunction[0x1C] = &CPU::opcode0x1C;
    opcodeFunction[0x1D] = &CPU::opcode0x1D;
    opcodeFunction[0x1E] = &CPU::opcode0x1E;
    opcodeFunction[0x1F] = &CPU::opcode0x1F;
    opcodeFunction[0x20] = &CPU::opcode0x20;
    opcodeFunction[0x21] = &CPU::opcode0x21;
    opcodeFunction[0x22] = &CPU::opcode0x22;
    opcodeFunction[0x23] = &CPU::opcode0x23;
    opcodeFunction[0x24] = &CPU::opcode0x24;
    opcodeFunction[0x25] = &CPU::opcode0x25;
    opcodeFunction[0x26] = &CPU::opcode0x26;
    opcodeFunction[0x27] = &CPU::opcode0x27;
    opcodeFunction[0x28] = &CPU::opcode0x28;
    opcodeFunction[0x29] = &CPU::opcode0x29;
    opcodeFunction[0x2A] = &CPU::opcode0x2A;
    opcodeFunction[0x2B] = &CPU::opcode0x2B;
    opcodeFunction[0x2C] = &CPU::opcode0x2C;
    opcodeFunction[0x2D] = &CPU::opcode0x2D;
    opcodeFunction[0x2E] = &CPU::opcode0x2E;
    opcodeFunction[0x2F] = &CPU::opcode0x2F;
    opcodeFunction[0x30] = &CPU::opcode0x30;
    opcodeFunction[0x31] = &CPU::opcode0x31;
    opcodeFunction[0x32] = &CPU::opcode0x32;
    opcodeFunction[0x33] = &CPU::opcode0x33;
    opcodeFunction[0x34] = &CPU::opcode0x34;
    opcodeFunction[0x35] = &CPU::opcode0x35;
    opcodeFunction[0x36] = &CPU::opcode0x36;
    opcodeFunction[0x37] = &CPU::opcode0x37;
    opcodeFunction[0x38] = &CPU::opcode0x38;
    opcodeFunction[0x39] = &CPU::opcode0x39;
    opcodeFunction[0x3A] = &CPU::opcode0x3A;
    opcodeFunction[0x3B] = &CPU::opcode0x3B;
    opcodeFunction[0x3C] = &CPU::opcode0x3C;
    opcodeFunction[0x3D] = &CPU::opcode0x3D;
    opcodeFunction[0x3E] = &CPU::opcode0x3E;
    opcodeFunction[0x3F] = &CPU::opcode0x3F;
    opcodeFunction[0x40] = &CPU::opcode0x40;
    opcodeFunction[0x41] = &CPU::opcode0x41;
    opcodeFunction[0x42] = &CPU::opcode0x42;
    opcodeFunction[0x43] = &CPU::opcode0x43;
    opcodeFunction[0x44] = &CPU::opcode0x44;
    opcodeFunction[0x45] = &CPU::opcode0x45;
    opcodeFunction[0x46] = &CPU::opcode0x46;
    opcodeFunction[0x47] = &CPU::opcode0x47;
    opcodeFunction[0x48] = &CPU::opcode0x48;
    opcodeFunction[0x49] = &CPU::opcode0x49;
    opcodeFunction[0x4A] = &CPU::opcode0x4A;
    opcodeFunction[0x4B] = &CPU::opcode0x4B;
    opcodeFunction[0x4C] = &CPU::opcode0x4C;
    opcodeFunction[0x4D] = &CPU::opcode0x4D;
    opcodeFunction[0x4E] = &CPU::opcode0x4E;
    opcodeFunction[0x4F] = &CPU::opcode0x4F;
    opcodeFunction[0x50] = &CPU::opcode0x50;
    opcodeFunction[0x51] = &CPU::opcode0x51;
    opcodeFunction[0x52] = &CPU::opcode0x52;
    opcodeFunction[0x53] = &CPU::opcode0x53;
    opcodeFunction[0x54] = &CPU::opcode0x54;
    opcodeFunction[0x55] = &CPU::opcode0x55;
    opcodeFunction[0x56] = &CPU::opcode0x56;
    opcodeFunction[0x57] = &CPU::opcode0x57;
    opcodeFunction[0x58] = &CPU::opcode0x58;
    opcodeFunction[0x59] = &CPU::opcode0x59;
    opcodeFunction[0x5A] = &CPU::opcode0x5A;
    opcodeFunction[0x5B] = &CPU::opcode0x5B;
    opcodeFunction[0x5C] = &CPU::opcode0x5C;
    opcodeFunction[0x5D] = &CPU::opcode0x5D;
    opcodeFunction[0x5E] = &CPU::opcode0x5E;
    opcodeFunction[0x5F] = &CPU::opcode0x5F;
    opcodeFunction[0x60] = &CPU::opcode0x60;
    opcodeFunction[0x61] = &CPU::opcode0x61;
    opcodeFunction[0x62] = &CPU::opcode0x62;
    opcodeFunction[0x63] = &CPU::opcode0x63;
    opcodeFunction[0x64] = &CPU::opcode0x64;
    opcodeFunction[0x65] = &CPU::opcode0x65;
    opcodeFunction[0x66] = &CPU::opcode0x66;
    opcodeFunction[0x67] = &CPU::opcode0x67;
    opcodeFunction[0x68] = &CPU::opcode0x68;
    opcodeFunction[0x69] = &CPU::opcode0x69;
    opcodeFunction[0x6A] = &CPU::opcode0x6A;
    opcodeFunction[0x6B] = &CPU::opcode0x6B;
    opcodeFunction[0x6C] = &CPU::opcode0x6C;
    opcodeFunction[0x6D] = &CPU::opcode0x6D;
    opcodeFunction[0x6E] = &CPU::opcode0x6E;
    opcodeFunction[0x6F] = &CPU::opcode0x6F;
    opcodeFunction[0x70] = &CPU::opcode0x70;
    opcodeFunction[0x71] = &CPU::opcode0x71;
    opcodeFunction[0x72] = &CPU::opcode0x72;
    opcodeFunction[0x73] = &CPU::opcode0x73;
    opcodeFunction[0x74] = &CPU::opcode0x74;
    opcodeFunction[0x75] = &CPU::opcode0x75;
    opcodeFunction[0x76] = &CPU::opcode0x76;
    opcodeFunction[0x77] = &CPU::opcode0x77;
    opcodeFunction[0x78] = &CPU::opcode0x78;
    opcodeFunction[0x79] = &CPU::opcode0x79;
    opcodeFunction[0x7A] = &CPU::opcode0x7A;
    opcodeFunction[0x7B] = &CPU::opcode0x7B;
    opcodeFunction[0x7C] = &CPU::opcode0x7C;
    opcodeFunction[0x7D] = &CPU::opcode0x7D;
    opcodeFunction[0x7E] = &CPU::opcode0x7E;
    opcodeFunction[0x7F] = &CPU::opcode0x7F;
    opcodeFunction[0x80] = &CPU::opcode0x80;
    opcodeFunction[0x81] = &CPU::opcode0x81;
    opcodeFunction[0x82] = &CPU::opcode0x82;
    opcodeFunction[0x83] = &CPU::opcode0x83;
    opcodeFunction[0x84] = &CPU::opcode0x84;
    opcodeFunction[0x85] = &CPU::opcode0x85;
    opcodeFunction[0x86] = &CPU::opcode0x86;
    opcodeFunction[0x87] = &CPU::opcode0x87;
    opcodeFunction[0x88] = &CPU::opcode0x88;
    opcodeFunction[0x89] = &CPU::opcode0x89;
    opcodeFunction[0x8A] = &CPU::opcode0x8A;
    opcodeFunction[0x8B] = &CPU::opcode0x8B;
    opcodeFunction[0x8C] = &CPU::opcode0x8C;
    opcodeFunction[0x8D] = &CPU::opcode0x8D;
    opcodeFunction[0x8E] = &CPU::opcode0x8E;
    opcodeFunction[0x8F] = &CPU::opcode0x8F;
    opcodeFunction[0x90] = &CPU::opcode0x90;
    opcodeFunction[0x91] = &CPU::opcode0x91;
    opcodeFunction[0x92] = &CPU::opcode0x92;
    opcodeFunction[0x93] = &CPU::opcode0x93;
    opcodeFunction[0x94] = &CPU::opcode0x94;
    opcodeFunction[0x95] = &CPU::opcode0x95;
    opcodeFunction[0x96] = &CPU::opcode0x96;
    opcodeFunction[0x97] = &CPU::opcode0x97;
    opcodeFunction[0x98] = &CPU::opcode0x98;
    opcodeFunction[0x99] = &CPU::opcode0x99;
    opcodeFunction[0x9A] = &CPU::opcode0x9A;
    opcodeFunction[0x9B] = &CPU::opcode0x9B;
    opcodeFunction[0x9C] = &CPU::opcode0x9C;
    opcodeFunction[0x9D] = &CPU::opcode0x9D;
    opcodeFunction[0x9E] = &CPU::opcode0x9E;
    opcodeFunction[0x9F] = &CPU::opcode0x9F;
    opcodeFunction[0xA0] = &CPU::opcode0xA0;
    opcodeFunction[0xA1] = &CPU::opcode0xA1;
    opcodeFunction[0xA2] = &CPU::opcode0xA2;
    opcodeFunction[0xA3] = &CPU::opcode0xA3;
    opcodeFunction[0xA4] = &CPU::opcode0xA4;
    opcodeFunction[0xA5] = &CPU::opcode0xA5;
    opcodeFunction[0xA6] = &CPU::opcode0xA6;
    opcodeFunction[0xA7] = &CPU::opcode0xA7;
    opcodeFunction[0xA8] = &CPU::opcode0xA8;
    opcodeFunction[0xA9] = &CPU::opcode0xA9;
    opcodeFunction[0xAA] = &CPU::opcode0xAA;
    opcodeFunction[0xAB] = &CPU::opcode0xAB;
    opcodeFunction[0xAC] = &CPU::opcode0xAC;
    opcodeFunction[0xAD] = &CPU::opcode0xAD;
    opcodeFunction[0xAE] = &CPU::opcode0xAE;
    opcodeFunction[0xAF] = &CPU::opcode0xAF;
    opcodeFunction[0xB0] = &CPU::opcode0xB0;
    opcodeFunction[0xB1] = &CPU::opcode0xB1;
    opcodeFunction[0xB2] = &CPU::opcode0xB2;
    opcodeFunction[0xB3] = &CPU::opcode0xB3;
    opcodeFunction[0xB4] = &CPU::opcode0xB4;
    opcodeFunction[0xB5] = &CPU::opcode0xB5;
    opcodeFunction[0xB6] = &CPU::opcode0xB6;
    opcodeFunction[0xB7] = &CPU::opcode0xB7;
    opcodeFunction[0xB8] = &CPU::opcode0xB8;
    opcodeFunction[0xB9] = &CPU::opcode0xB9;
    opcodeFunction[0xBA] = &CPU::opcode0xBA;
    opcodeFunction[0xBB] = &CPU::opcode0xBB;
    opcodeFunction[0xBC] = &CPU::opcode0xBC;
    opcodeFunction[0xBD] = &CPU::opcode0xBD;
    opcodeFunction[0xBE] = &CPU::opcode0xBE;
    opcodeFunction[0xBF] = &CPU::opcode0xBF;
    opcodeFunction[0xC0] = &CPU::opcode0xC0;
    opcodeFunction[0xC1] = &CPU::opcode0xC1;
    opcodeFunction[0xC2] = &CPU::opcode0xC2;
    opcodeFunction[0xC3] = &CPU::opcode0xC3;
    opcodeFunction[0xC4] = &CPU::opcode0xC4;
    opcodeFunction[0xC5] = &CPU::opcode0xC5;
    opcodeFunction[0xC6] = &CPU::opcode0xC6;
    opcodeFunction[0xC7] = &CPU::opcode0xC7;
    opcodeFunction[0xC8] = &CPU::opcode0xC8;
    opcodeFunction[0xC9] = &CPU::opcode0xC9;
    opcodeFunction[0xCA] = &CPU::opcode0xCA;
    opcodeFunction[0xCB] = &CPU::opcode0xCB;
    opcodeFunction[0xCC] = &CPU::opcode0xCC;
    opcodeFunction[0xCD] = &CPU::opcode0xCD;
    opcodeFunction[0xCE] = &CPU::opcode0xCE;
    opcodeFunction[0xCF] = &CPU::opcode0xCF;
    opcodeFunction[0xD0] = &CPU::opcode0xD0;
    opcodeFunction[0xD1] = &CPU::opcode0xD1;
    opcodeFunction[0xD2] = &CPU::opcode0xD2;
    opcodeFunction[0xD3] = nullptr;
    opcodeFunction[0xD4] = &CPU::opcode0xD4;
    opcodeFunction[0xD5] = &CPU::opcode0xD5;
    opcodeFunction[0xD6] = &CPU::opcode0xD6;
    opcodeFunction[0xD7] = &CPU::opcode0xD7;
    opcodeFunction[0xD8] = &CPU::opcode0xD8;
    opcodeFunction[0xD9] = &CPU::opcode0xD9;
    opcodeFunction[0xDA] = &CPU::opcode0xDA;
    opcodeFunction[0xDB] = nullptr;
    opcodeFunction[0xDC] = &CPU::opcode0xDC;
    opcodeFunction[0xDD] = nullptr;
    opcodeFunction[0xDE] = &CPU::opcode0xDE;
    opcodeFunction[0xDF] = &CPU::opcode0xDF;
    opcodeFunction[0xE0] = &CPU::opcode0xE0;
    opcodeFunction[0xE1] = &CPU::opcode0xE1;
    opcodeFunction[0xE2] = &CPU::opcode0xE2;
    opcodeFunction[0xE3] = nullptr;
    opcodeFunction[0xE4] = nullptr;
    opcodeFunction[0xE5] = &CPU::opcode0xE5;
    opcodeFunction[0xE6] = &CPU::opcode0xE6;
    opcodeFunction[0xE7] = &CPU::opcode0xE7;
    opcodeFunction[0xE8] = &CPU::opcode0xE8;
    opcodeFunction[0xE9] = &CPU::opcode0xE9;
    opcodeFunction[0xEA] = &CPU::opcode0xEA;
    opcodeFunction[0xEB] = nullptr;
    opcodeFunction[0xEC] = nullptr;
    opcodeFunction[0xED] = nullptr;
    opcodeFunction[0xEE] = &CPU::opcode0xEE;
    opcodeFunction[0xEF] = &CPU::opcode0xEF;
    opcodeFunction[0xF0] = &CPU::opcode0xF0;
    opcodeFunction[0xF1] = &CPU::opcode0xF1;
    opcodeFunction[0xF2] = &CPU::opcode0xF2;
    opcodeFunction[0xF3] = &CPU::opcode0xF3;
    opcodeFunction[0xF4] = nullptr;
    opcodeFunction[0xF5] = &CPU::opcode0xF5;
    opcodeFunction[0xF6] = &CPU::opcode0xF6;
    opcodeFunction[0xF7] = &CPU::opcode0xF7;
    opcodeFunction[0xF8] = &CPU::opcode0xF8;
    opcodeFunction[0xF9] = &CPU::opcode0xF9;
    opcodeFunction[0xFA] = &CPU::opcode0xFA;
    opcodeFunction[0xFB] = &CPU::opcode0xFB;
    opcodeFunction[0xFC] = nullptr;
    opcodeFunction[0xFD] = nullptr;
    opcodeFunction[0xFE] = &CPU::opcode0xFE;
    opcodeFunction[0xFF] = &CPU::opcode0xFF;
}
