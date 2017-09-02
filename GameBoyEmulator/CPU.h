#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <assert.h> // For unused instructions


#include "Definitions.h"
#include "MMU.h"
#include "Cartridge.h"
#include "Display.h"
#include "Joypad.h"
#include "Opcodes.h"

const u32 MEMORY_SIZE = 0x2000; //4096
const u32 VIDEO_MEMORY_SIZE = 0x2000;
const u32 PROGRAM_START = 0x0100;
//const u32 MAX_ROM_SIZE = 0x7A1200; // 8 MB

const u8 ZERO_FLAG = 0x80;
const u8 SUBTRACT_FLAG = 0x40;
const u8 HALF_CARRY_FLAG = 0x20;
const u8 CARRY_FLAG = 0x10;

const u8 ZERO_BIT = 7;
const u8 CARRY_BIT = 4;

// Interupt bits
const u8 VBLANK_INTERUPT_BIT = 0x01;
const u8 LCDSTAT_INTERUPT_BIT = 0x02;
const u8 TIMER_INTERUPT_BIT = 0x04;
const u8 SERIAL_INTERUPT_BIT = 0x08;
const u8 JOYPAD_INTERUPT_BIT = 0x010;



union reg
{
    // access either upper byte, lower byte or full 16 bit word
    struct
    {   
        u8 low;
        u8 high;
    };
    u16 word;
};

struct registers
{
    reg AF;
    reg BC;
    reg DE;
    reg HL;
    //u8 flags; // Zero, Subtract, Half-carry, Carry, 0, 0, 0, 0,

    u16 sp;
    u16 pc;
    u8 ime;
};



class CPU
{
private:

	char* path;

    typedef void(CPU::*opcodePtr)(void);
    opcodePtr opcodeFunction[0x100];
    opcodePtr opcodeFunctionCB[0x100];

    registers regs;

    MMU* mmu;
    Display* display;
    Joypad* keyboard;

    u16 counter;
    u32 lastCycleTime;

    bool running = false;
    bool halt = false;
    bool log = false;


    int totalInstructions = 0;
    u32 instructionProfiling[0x100];
    u32 instructionProfilingCB[0x100];

public:
    CPU();
    CPU(char* romPath);
	~CPU();

    void Loop();
    bool IsRunning() { return running; }   // Getters

	void SetRunning(bool state) { running = state; }
	void JoypadInterrupt();

private:
    void Reset();
    void ProcessEvents();
    void ProcessInstruction();
    void RunBios();

    void DumpToFile();
    void DumpToScreen();

    void InitOpcodeFunctions();
    void InitOpcodeFunctionsCB();




	//----------------------
	//	Instruction and helper functions
	//----------------------

    // Helper Functions
    inline void Increment8BitValue(u8 &reg);
    inline void Decrement8BitValue(u8 &reg);
    inline void Add16BitRegisters(u16 &reg1, u16 &reg2);
    inline void ADD(u8 operand);
    inline void ADC(u8 operand);
    inline void SUB(u8 operand);
    inline void SBC(u8 operand);
    inline void AND(u8 operand);
    inline void XOR(u8 operand);
    inline void OR(u8 operand);
    inline void CP(u8 operand);

    // Helper Functions CB
    inline void RLC(u8& n);
    inline void RRC(u8& n);
    inline void RL(u8& n);
    inline void RR(u8& n);
    inline void SLA(u8& n);
    inline void SRA(u8& n);
    inline void SWAP(u8& n);
    inline void SRL(u8& n);
    inline void BIT(u8 bit, u8 n);
    inline void RES(u8 bit, u8& n);
	inline void SET(u8 bit, u8& n);

    // Interrupt jumps
    void RST40(); // VBlank interrupt
    void RST48(); // LCD STAT interrupt
    void RST50(); // Timer interrupt
    void RST58(); // Serial interrupt    
    void RST60(); // Joypad Interrupt  

    // Instructions
    void opcode0x00();
    void opcode0x01();
    void opcode0x02();
    void opcode0x03();
    void opcode0x04();
    void opcode0x05();
    void opcode0x06();
    void opcode0x07();
    void opcode0x08();
    void opcode0x09();
    void opcode0x0A();
    void opcode0x0B();
    void opcode0x0C();
    void opcode0x0D();
    void opcode0x0E();
    void opcode0x0F();
    void opcode0x10();
    void opcode0x11();
    void opcode0x12();
    void opcode0x13();
    void opcode0x14();
    void opcode0x15();
    void opcode0x16();
    void opcode0x17();
    void opcode0x18();
    void opcode0x19();
    void opcode0x1A();
    void opcode0x1B();
    void opcode0x1C();
    void opcode0x1D();
    void opcode0x1E();
    void opcode0x1F();
    void opcode0x20();
    void opcode0x21();
    void opcode0x22();
    void opcode0x23();
    void opcode0x24();
    void opcode0x25();
    void opcode0x26();
    void opcode0x27();
    void opcode0x28();
    void opcode0x29();
    void opcode0x2A();
    void opcode0x2B();
    void opcode0x2C();
    void opcode0x2D();
    void opcode0x2E();
    void opcode0x2F();
    void opcode0x30();
    void opcode0x31();
    void opcode0x32();
    void opcode0x33();
    void opcode0x34();
    void opcode0x35();
    void opcode0x36();
    void opcode0x37();
    void opcode0x38();
    void opcode0x39();
    void opcode0x3A();
    void opcode0x3B();
    void opcode0x3C();
    void opcode0x3D();
    void opcode0x3E();
    void opcode0x3F();
    void opcode0x40();
    void opcode0x41();
    void opcode0x42();
    void opcode0x43();
    void opcode0x44();
    void opcode0x45();
    void opcode0x46();
    void opcode0x47();
    void opcode0x48();
    void opcode0x49();
    void opcode0x4A();
    void opcode0x4B();
    void opcode0x4C();
    void opcode0x4D();
    void opcode0x4E();
    void opcode0x4F();
    void opcode0x50();
    void opcode0x51();
    void opcode0x52();
    void opcode0x53();
    void opcode0x54();
    void opcode0x55();
    void opcode0x56();
    void opcode0x57();
    void opcode0x58();
    void opcode0x59();
    void opcode0x5A();
    void opcode0x5B();
    void opcode0x5C();
    void opcode0x5D();
    void opcode0x5E();
    void opcode0x5F();
    void opcode0x60();
    void opcode0x61();
    void opcode0x62();
    void opcode0x63();
    void opcode0x64();
    void opcode0x65();
    void opcode0x66();
    void opcode0x67();
    void opcode0x68();
    void opcode0x69();
    void opcode0x6A();
    void opcode0x6B();
    void opcode0x6C();
    void opcode0x6D();
    void opcode0x6E();
    void opcode0x6F();
    void opcode0x70();
    void opcode0x71();
    void opcode0x72();
    void opcode0x73();
    void opcode0x74();
    void opcode0x75();
    void opcode0x76();
    void opcode0x77();
    void opcode0x78();
    void opcode0x79();
    void opcode0x7A();
    void opcode0x7B();
    void opcode0x7C();
    void opcode0x7D();
    void opcode0x7E();
    void opcode0x7F();
    void opcode0x80();
    void opcode0x81();
    void opcode0x82();
    void opcode0x83();
    void opcode0x84();
    void opcode0x85();
    void opcode0x86();
    void opcode0x87();
    void opcode0x88();
    void opcode0x89();
    void opcode0x8A();
    void opcode0x8B();
    void opcode0x8C();
    void opcode0x8D();
    void opcode0x8E();
    void opcode0x8F();
    void opcode0x90();
    void opcode0x91();
    void opcode0x92();
    void opcode0x93();
    void opcode0x94();
    void opcode0x95();
    void opcode0x96();
    void opcode0x97();
    void opcode0x98();
    void opcode0x99();
    void opcode0x9A();
    void opcode0x9B();
    void opcode0x9C();
    void opcode0x9D();
    void opcode0x9E();
    void opcode0x9F();
    void opcode0xA0();
    void opcode0xA1();
    void opcode0xA2();
    void opcode0xA3();
    void opcode0xA4();
    void opcode0xA5();
    void opcode0xA6();
    void opcode0xA7();
    void opcode0xA8();
    void opcode0xA9();
    void opcode0xAA();
    void opcode0xAB();
    void opcode0xAC();
    void opcode0xAD();
    void opcode0xAE();
    void opcode0xAF();
    void opcode0xB0();
    void opcode0xB1();
    void opcode0xB2();
    void opcode0xB3();
    void opcode0xB4();
    void opcode0xB5();
    void opcode0xB6();
    void opcode0xB7();
    void opcode0xB8();
    void opcode0xB9();
    void opcode0xBA();
    void opcode0xBB();
    void opcode0xBC();
    void opcode0xBD();
    void opcode0xBE();
    void opcode0xBF();
    void opcode0xC0();
    void opcode0xC1();
    void opcode0xC2();
    void opcode0xC3();
    void opcode0xC4();
    void opcode0xC5();
    void opcode0xC6();
    void opcode0xC7();
    void opcode0xC8();
    void opcode0xC9();
    void opcode0xCA();
    void opcode0xCB();
    void opcode0xCC();
    void opcode0xCD();
    void opcode0xCE();
    void opcode0xCF();
    void opcode0xD0();
    void opcode0xD1();
    void opcode0xD2();
    void opcode0xD4();
    void opcode0xD5();
    void opcode0xD6();
    void opcode0xD7();
    void opcode0xD8();
    void opcode0xD9();
    void opcode0xDA();
    void opcode0xDC();
    void opcode0xDE();
    void opcode0xDF();
    void opcode0xE0();
    void opcode0xE1();
    void opcode0xE2();
    void opcode0xE5();
    void opcode0xE6();
    void opcode0xE7();
    void opcode0xE8();
    void opcode0xE9();
    void opcode0xEA();
    void opcode0xEE();
    void opcode0xEF();
    void opcode0xF0();
    void opcode0xF1();
    void opcode0xF2();
    void opcode0xF3();
    void opcode0xF5();
    void opcode0xF6();
    void opcode0xF7();
    void opcode0xF8();
    void opcode0xF9();
    void opcode0xFA();
    void opcode0xFB();
    void opcode0xFE();
    void opcode0xFF();

    // CB instructions
    void CBopcode0x00();
    void CBopcode0x01();
    void CBopcode0x02();
    void CBopcode0x03();
    void CBopcode0x04();
    void CBopcode0x05();
    void CBopcode0x06();
    void CBopcode0x07();
    void CBopcode0x08();
    void CBopcode0x09();
    void CBopcode0x0A();
    void CBopcode0x0B();
    void CBopcode0x0C();
    void CBopcode0x0D();
    void CBopcode0x0E();
    void CBopcode0x0F();
    void CBopcode0x10();
    void CBopcode0x11();
    void CBopcode0x12();
    void CBopcode0x13();
    void CBopcode0x14();
    void CBopcode0x15();
    void CBopcode0x16();
    void CBopcode0x17();
    void CBopcode0x18();
    void CBopcode0x19();
    void CBopcode0x1A();
    void CBopcode0x1B();
    void CBopcode0x1C();
    void CBopcode0x1D();
    void CBopcode0x1E();
    void CBopcode0x1F();
    void CBopcode0x20();
    void CBopcode0x21();
    void CBopcode0x22();
    void CBopcode0x23();
    void CBopcode0x24();
    void CBopcode0x25();
    void CBopcode0x26();
    void CBopcode0x27();
    void CBopcode0x28();
    void CBopcode0x29();
    void CBopcode0x2A();
    void CBopcode0x2B();
    void CBopcode0x2C();
    void CBopcode0x2D();
    void CBopcode0x2E();
    void CBopcode0x2F();
    void CBopcode0x30();
    void CBopcode0x31();
    void CBopcode0x32();
    void CBopcode0x33();
    void CBopcode0x34();
    void CBopcode0x35();
    void CBopcode0x36();
    void CBopcode0x37();
    void CBopcode0x38();
    void CBopcode0x39();
    void CBopcode0x3A();
    void CBopcode0x3B();
    void CBopcode0x3C();
    void CBopcode0x3D();
    void CBopcode0x3E();
    void CBopcode0x3F();
    void CBopcode0x40();
    void CBopcode0x41();
    void CBopcode0x42();
    void CBopcode0x43();
    void CBopcode0x44();
    void CBopcode0x45();
    void CBopcode0x46();
    void CBopcode0x47();
    void CBopcode0x48();
    void CBopcode0x49();
    void CBopcode0x4A();
    void CBopcode0x4B();
    void CBopcode0x4C();
    void CBopcode0x4D();
    void CBopcode0x4E();
    void CBopcode0x4F();
    void CBopcode0x50();
    void CBopcode0x51();
    void CBopcode0x52();
    void CBopcode0x53();
    void CBopcode0x54();
    void CBopcode0x55();
    void CBopcode0x56();
    void CBopcode0x57();
    void CBopcode0x58();
    void CBopcode0x59();
    void CBopcode0x5A();
    void CBopcode0x5B();
    void CBopcode0x5C();
    void CBopcode0x5D();
    void CBopcode0x5E();
    void CBopcode0x5F();
    void CBopcode0x60();
    void CBopcode0x61();
    void CBopcode0x62();
    void CBopcode0x63();
    void CBopcode0x64();
    void CBopcode0x65();
    void CBopcode0x66();
    void CBopcode0x67();
    void CBopcode0x68();
    void CBopcode0x69();
    void CBopcode0x6A();
    void CBopcode0x6B();
    void CBopcode0x6C();
    void CBopcode0x6D();
    void CBopcode0x6E();
    void CBopcode0x6F();
    void CBopcode0x70();
    void CBopcode0x71();
    void CBopcode0x72();
    void CBopcode0x73();
    void CBopcode0x74();
    void CBopcode0x75();
    void CBopcode0x76();
    void CBopcode0x77();
    void CBopcode0x78();
    void CBopcode0x79();
    void CBopcode0x7A();
    void CBopcode0x7B();
    void CBopcode0x7C();
    void CBopcode0x7D();
    void CBopcode0x7E();
    void CBopcode0x7F();
    void CBopcode0x80();
    void CBopcode0x81();
    void CBopcode0x82();
    void CBopcode0x83();
    void CBopcode0x84();
    void CBopcode0x85();
    void CBopcode0x86();
    void CBopcode0x87();
    void CBopcode0x88();
    void CBopcode0x89();
    void CBopcode0x8A();
    void CBopcode0x8B();
    void CBopcode0x8C();
    void CBopcode0x8D();
    void CBopcode0x8E();
    void CBopcode0x8F();
    void CBopcode0x90();
    void CBopcode0x91();
    void CBopcode0x92();
    void CBopcode0x93();
    void CBopcode0x94();
    void CBopcode0x95();
    void CBopcode0x96();
    void CBopcode0x97();
    void CBopcode0x98();
    void CBopcode0x99();
    void CBopcode0x9A();
    void CBopcode0x9B();
    void CBopcode0x9C();
    void CBopcode0x9D();
    void CBopcode0x9E();
    void CBopcode0x9F();
    void CBopcode0xA0();
    void CBopcode0xA1();
    void CBopcode0xA2();
    void CBopcode0xA3();
    void CBopcode0xA4();
    void CBopcode0xA5();
    void CBopcode0xA6();
    void CBopcode0xA7();
    void CBopcode0xA8();
    void CBopcode0xA9();
    void CBopcode0xAA();
    void CBopcode0xAB();
    void CBopcode0xAC();
    void CBopcode0xAD();
    void CBopcode0xAE();
    void CBopcode0xAF();
    void CBopcode0xB0();
    void CBopcode0xB1();
    void CBopcode0xB2();
    void CBopcode0xB3();
    void CBopcode0xB4();
    void CBopcode0xB5();
    void CBopcode0xB6();
    void CBopcode0xB7();
    void CBopcode0xB8();
    void CBopcode0xB9();
    void CBopcode0xBA();
    void CBopcode0xBB();
    void CBopcode0xBC();
    void CBopcode0xBD();
    void CBopcode0xBE();
    void CBopcode0xBF();
    void CBopcode0xC0();
    void CBopcode0xC1();
    void CBopcode0xC2();
    void CBopcode0xC3();
    void CBopcode0xC4();
    void CBopcode0xC5();
    void CBopcode0xC6();
    void CBopcode0xC7();
    void CBopcode0xC8();
    void CBopcode0xC9();
    void CBopcode0xCA();
    void CBopcode0xCB();
    void CBopcode0xCC();
    void CBopcode0xCD();
    void CBopcode0xCE();
    void CBopcode0xCF();
    void CBopcode0xD0();
    void CBopcode0xD1();
    void CBopcode0xD2();
    void CBopcode0xD3();
    void CBopcode0xD4();
    void CBopcode0xD5();
    void CBopcode0xD6();
    void CBopcode0xD7();
    void CBopcode0xD8();
    void CBopcode0xD9();
    void CBopcode0xDA();
    void CBopcode0xDB();
    void CBopcode0xDC();
    void CBopcode0xDD();
    void CBopcode0xDE();
    void CBopcode0xDF();
    void CBopcode0xE0();
    void CBopcode0xE1();
    void CBopcode0xE2();
    void CBopcode0xE3();
    void CBopcode0xE4();
    void CBopcode0xE5();
    void CBopcode0xE6();
    void CBopcode0xE7();
    void CBopcode0xE8();
    void CBopcode0xE9();
    void CBopcode0xEA();
    void CBopcode0xEB();
    void CBopcode0xEC();
    void CBopcode0xED();
    void CBopcode0xEE();
    void CBopcode0xEF();
    void CBopcode0xF0();
    void CBopcode0xF1();
    void CBopcode0xF2();
    void CBopcode0xF3();
    void CBopcode0xF5();
    void CBopcode0xF4();
    void CBopcode0xF6();
    void CBopcode0xF7();
    void CBopcode0xF8();
    void CBopcode0xF9();
    void CBopcode0xFA();
    void CBopcode0xFB();
    void CBopcode0xFC();
    void CBopcode0xFD();
    void CBopcode0xFE();
    void CBopcode0xFF();
};
