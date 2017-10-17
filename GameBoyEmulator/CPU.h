#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <assert.h> // For unused instructions


#include "Definitions.h"
#include "MMU.h"
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
    bool biosLoaded;
	bool RomLoaded;

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
    void DefaultValues();
	~CPU();

    void Loop();
    bool IsRunning() { return running; }   // Get

    void Start();
    void Stop();
    void SetRom(char* path);
    void SetBios(char* path);
	void JoypadInterrupt();

private:

    void Reset();
    void ProcessEvents();
    void ProcessInstruction();

    void DumpToFile();
    void DumpToScreen();

    void InitOpcodeFunctions();
    void InitOpcodeFunctionsCB();


	//----------------------
	//	Instruction and helper functions
	//----------------------

    // Helper Functions
    inline void INC(u8 &reg);
    inline void DEC(u8 &reg);
    inline void ADD16(u16 &reg1, u16 &reg2);
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
    
    void opcode0x00();      // NOP
    void opcode0x01();      // LD BC, d16
    void opcode0x02();      // LD(BC), A
    void opcode0x03();      // INC BC
    void opcode0x04();      // INC B
    void opcode0x05();      // DEC B
    void opcode0x06();      // LD B, d8
    void opcode0x07();      // RLCA
    void opcode0x08();      // LD(a16), SP
    void opcode0x09();      // ADD HL, BC
    void opcode0x0A();      // LD A, (BC)
    void opcode0x0B();      // DEC BC
    void opcode0x0C();      // INC C
    void opcode0x0D();      // DEC C
    void opcode0x0E();      // LD C, d8
    void opcode0x0F();      // RRCA
    void opcode0x10();      // STOP
    void opcode0x11();      // LD DE, d16
    void opcode0x12();      // LD (DE), A
    void opcode0x13();      // INC DE
    void opcode0x14();      // INC D
    void opcode0x15();      // DEC D
    void opcode0x16();      // LD D, d8
    void opcode0x17();      // RLA
    void opcode0x18();      // JR r8
    void opcode0x19();      // ADD HL, DE
    void opcode0x1A();      // LD A, (DE)
    void opcode0x1B();      // DEC DE
    void opcode0x1C();      // INC E
    void opcode0x1D();      // DEC E
    void opcode0x1E();      // LD E, d8
    void opcode0x1F();      // RRA
    void opcode0x20();      // JR NZ, r8
    void opcode0x21();      // LD HL, d16
    void opcode0x22();      // LD (HL+), A
    void opcode0x23();      // INC HL
    void opcode0x24();      // INC H
    void opcode0x25();      // DEC H
    void opcode0x26();      // LD H, d8
    void opcode0x27();      // DAA
    void opcode0x28();      // JR Z, r8
    void opcode0x29();      // ADD HL, HL
    void opcode0x2A();      // LD A, (HL+)
    void opcode0x2B();      // DEC HL
    void opcode0x2C();      // INC L
    void opcode0x2D();      // DEC L
    void opcode0x2E();      // LD L, d8
    void opcode0x2F();      // CPL
    void opcode0x30();      // JR NC, r8
    void opcode0x31();      // LD SP, d16
    void opcode0x32();      // LD (HL-), A
    void opcode0x33();      // INC SP
    void opcode0x34();      // INC (HL)
    void opcode0x35();      // DEC (HL)
    void opcode0x36();      // LD (HL), d8
    void opcode0x37();      // SCF
    void opcode0x38();      // JR C, r8
    void opcode0x39();      // ADD HL, SP
    void opcode0x3A();      // LD A, (HL-)
    void opcode0x3B();      // DEC SP
    void opcode0x3C();      // INC A
    void opcode0x3D();      // DEC A
    void opcode0x3E();      // LD A, d8
    void opcode0x3F();      // CCF
    void opcode0x40();      // LD B, B
    void opcode0x41();      // LD B, C
    void opcode0x42();      // LD B, D
    void opcode0x43();      // LD B, E
    void opcode0x44();      // LD B, H
    void opcode0x45();      // LD B, L
    void opcode0x46();      // LD B, (HL)
    void opcode0x47();      // LD B, A 
    void opcode0x48();      // LD C, B
    void opcode0x49();      // LD C, C
    void opcode0x4A();      // LD C, D
    void opcode0x4B();      // LD C, E
    void opcode0x4C();      // LD C, H
    void opcode0x4D();      // LD C, L
    void opcode0x4E();      // LD C, (HL)
    void opcode0x4F();      // LD C, A
    void opcode0x50();      // LD D, B   
    void opcode0x51();      // LD D, C   
    void opcode0x52();      // LD D, D   
    void opcode0x53();      // LD D, E   
    void opcode0x54();      // LD D, H   
    void opcode0x55();      // LD D, L   
    void opcode0x56();      // LD D, (HL)
    void opcode0x57();      // LD D, A  
    void opcode0x58();      // LD E, B  
    void opcode0x59();      // LD E, C  
    void opcode0x5A();      // LD E, D  
    void opcode0x5B();      // LD E, E  
    void opcode0x5C();      // LD E, H  
    void opcode0x5D();      // LD E, L  
    void opcode0x5E();      // LD E, (HL)
    void opcode0x5F();      // LD E, A   
    void opcode0x60();      // LD H, B  
    void opcode0x61();      // LD H, C  
    void opcode0x62();      // LD H, D  
    void opcode0x63();      // LD H, E  
    void opcode0x64();      // LD H, H  
    void opcode0x65();      // LD H, L  
    void opcode0x66();      // LD H, (HL)
    void opcode0x67();      // LD H, A
    void opcode0x68();      // LD L, B
    void opcode0x69();      // LD L, C
    void opcode0x6A();      // LD L, D
    void opcode0x6B();      // LD L, E
    void opcode0x6C();      // LD L, H
    void opcode0x6D();      // LD L, L
    void opcode0x6E();      // LD L, (HL)
    void opcode0x6F();      // LD L, A  
    void opcode0x70();      // LD (HL), B
    void opcode0x71();      // LD (HL), C
    void opcode0x72();      // LD (HL), D
    void opcode0x73();      // LD (HL), E
    void opcode0x74();      // LD (HL), H
    void opcode0x75();      // LD (HL), L
    void opcode0x76();      // HALT
    void opcode0x77();      // LD (HL), A
    void opcode0x78();      // LD A, B
    void opcode0x79();      // LD A, C
    void opcode0x7A();      // LD A, D
    void opcode0x7B();      // LD A, E
    void opcode0x7C();      // LD A, H
    void opcode0x7D();      // LD A, L
    void opcode0x7E();      // LD A, (HL)
    void opcode0x7F();      // LD A, A 
    void opcode0x80();      // ADD A, B 
    void opcode0x81();      // ADD A, C 
    void opcode0x82();      // ADD A, D 
    void opcode0x83();      // ADD A, E 
    void opcode0x84();      // ADD A, H 
    void opcode0x85();      // ADD A, L 
    void opcode0x86();      // ADD A, (HL)
    void opcode0x87();      // ADD A, A 
    void opcode0x88();      // ADC A, B 
    void opcode0x89();      // ADC A, C 
    void opcode0x8A();      // ADC A, D 
    void opcode0x8B();      // ADC A, E 
    void opcode0x8C();      // ADC A, H 
    void opcode0x8D();      // ADC A, L 
    void opcode0x8E();      // ADC A, (HL)
    void opcode0x8F();      // ADC A, A
    void opcode0x90();      // SUB B   
    void opcode0x91();      // SUB C   
    void opcode0x92();      // SUB D   
    void opcode0x93();      // SUB E   
    void opcode0x94();      // SUB H   
    void opcode0x95();      // SUB L   
    void opcode0x96();      // SUB (HL)
    void opcode0x97();      // SUB A
    void opcode0x98();      // SBC A, B 
    void opcode0x99();      // SBC A, C 
    void opcode0x9A();      // SBC A, D 
    void opcode0x9B();      // SBC A, E 
    void opcode0x9C();      // SBC A, H 
    void opcode0x9D();      // SBC A, L 
    void opcode0x9E();      // SBC A, (HL)
    void opcode0x9F();      // SBC A, A
    void opcode0xA0();      // AND B  
    void opcode0xA1();      // AND C  
    void opcode0xA2();      // AND D  
    void opcode0xA3();      // AND E  
    void opcode0xA4();      // AND H  
    void opcode0xA5();      // AND L  
    void opcode0xA6();      // AND (HL)
    void opcode0xA7();      // AND A  
    void opcode0xA8();      // XOR B  
    void opcode0xA9();      // XOR C  
    void opcode0xAA();      // XOR D  
    void opcode0xAB();      // XOR E  
    void opcode0xAC();      // XOR H  
    void opcode0xAD();      // XOR L  
    void opcode0xAE();      // XOR (HL)
    void opcode0xAF();      // XOR A  
    void opcode0xB0();      // OR B  
    void opcode0xB1();      // OR C  
    void opcode0xB2();      // OR D  
    void opcode0xB3();      // OR E  
    void opcode0xB4();      // OR H  
    void opcode0xB5();      // OR L  
    void opcode0xB6();      // OR (HL)
    void opcode0xB7();      // OR A  
    void opcode0xB8();      // CP B  
    void opcode0xB9();      // CP C  
    void opcode0xBA();      // CP D  
    void opcode0xBB();      // CP E  
    void opcode0xBC();      // CP H  
    void opcode0xBD();      // CP L  
    void opcode0xBE();      // CP (HL)
    void opcode0xBF();      // CP A  
    void opcode0xC0();      // RET NZ     
    void opcode0xC1();      // POP BC     
    void opcode0xC2();      // JP NZ, a16 
    void opcode0xC3();      // JP a16     
    void opcode0xC4();      // CALL NZ, a16
    void opcode0xC5();      // PUSH BC    
    void opcode0xC6();      // ADD A, d8  
    void opcode0xC7();      // RST 00H    
    void opcode0xC8();      // RET Z      
    void opcode0xC9();      // RET        
    void opcode0xCA();      // JP Z, a16  
    void opcode0xCB();      // PREFIX CB  
    void opcode0xCC();      // CALL Z, a16
    void opcode0xCD();      // CALL a16   
    void opcode0xCE();      // ADC A, d8  
    void opcode0xCF();      // RST 08H    
    void opcode0xD0();      // RET NC      
    void opcode0xD1();      // POP DE      
    void opcode0xD2();      // JP NC, a16           
    void opcode0xD4();      // CALL NC, a16
    void opcode0xD5();      // PUSH DE     
    void opcode0xD6();      // SUB d8      
    void opcode0xD7();      // RST 10H     
    void opcode0xD8();      // RET C       
    void opcode0xD9();      // RETI        
    void opcode0xDA();      // JP C, a16    
    void opcode0xDC();      // CALL C, a16 
    void opcode0xDE();      // SBC A, d8   
    void opcode0xDF();      // RST 18H     
    void opcode0xE0();      // LDH (a8), A 
    void opcode0xE1();      // POP HL      
    void opcode0xE2();      // LD (C), A       
    void opcode0xE5();      // PUSH HL     
    void opcode0xE6();      // AND d8      
    void opcode0xE7();      // RST 20H     
    void opcode0xE8();      // ADD SP, r8  
    void opcode0xE9();      // JP (HL)     
    void opcode0xEA();      // LD (a16), A           
    void opcode0xEE();      // XOR d8      
    void opcode0xEF();      // RST 28H     
    void opcode0xF0();      // LDH A, (a8) 
    void opcode0xF1();      // POP AF      
    void opcode0xF2();      // LD A, (C)   
    void opcode0xF3();      // DI                    
    void opcode0xF5();      // PUSH AF     
    void opcode0xF6();      // OR d8       
    void opcode0xF7();      // RST 30H     
    void opcode0xF8();      // LD HL, SP+r8
    void opcode0xF9();      // LD SP, HL   
    void opcode0xFA();      // LD A, (a16) 
    void opcode0xFB();      // EI                   
    void opcode0xFE();      // CP d8       
    void opcode0xFF();      // RST 38H     

    // CB instructions
    void CBopcode0x00();    // RLC B     
    void CBopcode0x01();    // RLC C     
    void CBopcode0x02();    // RLC D     
    void CBopcode0x03();    // RLC E     
    void CBopcode0x04();    // RLC H     
    void CBopcode0x05();    // RLC L     
    void CBopcode0x06();    // RLC (HL)  
    void CBopcode0x07();    // RLC A     
    void CBopcode0x08();    // RRC B     
    void CBopcode0x09();    // RRC C     
    void CBopcode0x0A();    // RRC D     
    void CBopcode0x0B();    // RRC E     
    void CBopcode0x0C();    // RRC H     
    void CBopcode0x0D();    // RRC L     
    void CBopcode0x0E();    // RRC (HL)  
    void CBopcode0x0F();    // RRC A     
    void CBopcode0x10();    // RL B      
    void CBopcode0x11();    // RL C      
    void CBopcode0x12();    // RL D      
    void CBopcode0x13();    // RL E      
    void CBopcode0x14();    // RL H      
    void CBopcode0x15();    // RL L      
    void CBopcode0x16();    // RL (HL)   
    void CBopcode0x17();    // RL A      
    void CBopcode0x18();    // RR B      
    void CBopcode0x19();    // RR C      
    void CBopcode0x1A();    // RR D      
    void CBopcode0x1B();    // RR E      
    void CBopcode0x1C();    // RR H      
    void CBopcode0x1D();    // RR L      
    void CBopcode0x1E();    // RR (HL)   
    void CBopcode0x1F();    // RR A      
    void CBopcode0x20();    // SLA B     
    void CBopcode0x21();    // SLA C     
    void CBopcode0x22();    // SLA D     
    void CBopcode0x23();    // SLA E     
    void CBopcode0x24();    // SLA H     
    void CBopcode0x25();    // SLA L     
    void CBopcode0x26();    // SLA (HL)  
    void CBopcode0x27();    // SLA A     
    void CBopcode0x28();    // SLA B     
    void CBopcode0x29();    // SRA C     
    void CBopcode0x2A();    // SRA D     
    void CBopcode0x2B();    // SRA E     
    void CBopcode0x2C();    // SRA H     
    void CBopcode0x2D();    // SRA L     
    void CBopcode0x2E();    // SRA (HL)  
    void CBopcode0x2F();    // SRA A     
    void CBopcode0x30();    // SWAP B    
    void CBopcode0x31();    // SWAP C    
    void CBopcode0x32();    // SWAP D    
    void CBopcode0x33();    // SWAP E    
    void CBopcode0x34();    // SWAP H    
    void CBopcode0x35();    // SWAP L    
    void CBopcode0x36();    // SWAP (HL) 
    void CBopcode0x37();    // SWAP A    
    void CBopcode0x38();    // SRL B     
    void CBopcode0x39();    // SRL C     
    void CBopcode0x3A();    // SRL D     
    void CBopcode0x3B();    // SRL E     
    void CBopcode0x3C();    // SRL H     
    void CBopcode0x3D();    // SRL L     
    void CBopcode0x3E();    // SRL (HL)  
    void CBopcode0x3F();    // SRL A     
    void CBopcode0x40();    // BIT 0, B  
    void CBopcode0x41();    // BIT 0, C  
    void CBopcode0x42();    // BIT 0, D  
    void CBopcode0x43();    // BIT 0, E  
    void CBopcode0x44();    // BIT 0, H  
    void CBopcode0x45();    // BIT 0, L  
    void CBopcode0x46();    // BIT 0, (HL)
    void CBopcode0x47();    // BIT 0, A  
    void CBopcode0x48();    // BIT 1, B  
    void CBopcode0x49();    // BIT 1, C  
    void CBopcode0x4A();    // BIT 1, D  
    void CBopcode0x4B();    // BIT 1, E  
    void CBopcode0x4C();    // BIT 1, H  
    void CBopcode0x4D();    // BIT 1, L  
    void CBopcode0x4E();    // BIT 1, (HL)
    void CBopcode0x4F();    // BIT 1, A  
    void CBopcode0x50();    // BIT 2, B  
    void CBopcode0x51();    // BIT 2, C  
    void CBopcode0x52();    // BIT 2, D  
    void CBopcode0x53();    // BIT 2, E  
    void CBopcode0x54();    // BIT 2, H  
    void CBopcode0x55();    // BIT 2, L  
    void CBopcode0x56();    // BIT 2, (HL)
    void CBopcode0x57();    // BIT 2, A  
    void CBopcode0x58();    // BIT 3, B  
    void CBopcode0x59();    // BIT 3, C  
    void CBopcode0x5A();    // BIT 3, D  
    void CBopcode0x5B();    // BIT 3, E  
    void CBopcode0x5C();    // BIT 3, H  
    void CBopcode0x5D();    // BIT 3, L  
    void CBopcode0x5E();    // BIT 3, (HL)
    void CBopcode0x5F();    // BIT 3, A  
    void CBopcode0x60();    // BIT 4, B  
    void CBopcode0x61();    // BIT 4, C  
    void CBopcode0x62();    // BIT 4, D  
    void CBopcode0x63();    // BIT 4, E  
    void CBopcode0x64();    // BIT 4, H  
    void CBopcode0x65();    // BIT 4, L  
    void CBopcode0x66();    // BIT 4, (HL)
    void CBopcode0x67();    // BIT 4, A  
    void CBopcode0x68();    // BIT 5, B  
    void CBopcode0x69();    // BIT 5, C  
    void CBopcode0x6A();    // BIT 5, D  
    void CBopcode0x6B();    // BIT 5, E  
    void CBopcode0x6C();    // BIT 5, H  
    void CBopcode0x6D();    // BIT 5, L  
    void CBopcode0x6E();    // BIT 5, (HL)
    void CBopcode0x6F();    // BIT 5, A  
    void CBopcode0x70();    // BIT 6, B  
    void CBopcode0x71();    // BIT 6, C  
    void CBopcode0x72();    // BIT 6, D  
    void CBopcode0x73();    // BIT 6, E  
    void CBopcode0x74();    // BIT 6, H  
    void CBopcode0x75();    // BIT 6, L  
    void CBopcode0x76();    // BIT 6, (HL)
    void CBopcode0x77();    // BIT 6, A  
    void CBopcode0x78();    // BIT 7, B  
    void CBopcode0x79();    // BIT 7, C  
    void CBopcode0x7A();    // BIT 7, D  
    void CBopcode0x7B();    // BIT 7, E  
    void CBopcode0x7C();    // BIT 7, H  
    void CBopcode0x7D();    // BIT 7, L  
    void CBopcode0x7E();    // BIT 7, (HL)
    void CBopcode0x7F();    // BIT 7, A  
    void CBopcode0x80();    // RES 0, B  
    void CBopcode0x81();    // RES 0, C  
    void CBopcode0x82();    // RES 0, D  
    void CBopcode0x83();    // RES 0, E  
    void CBopcode0x84();    // RES 0, H  
    void CBopcode0x85();    // RES 0, L  
    void CBopcode0x86();    // RES 0, (HL)
    void CBopcode0x87();    // RES 0, A  
    void CBopcode0x88();    // RES 1, B  
    void CBopcode0x89();    // RES 1, C  
    void CBopcode0x8A();    // RES 1, D  
    void CBopcode0x8B();    // RES 1, E  
    void CBopcode0x8C();    // RES 1, H  
    void CBopcode0x8D();    // RES 1, L  
    void CBopcode0x8E();    // RES 1, (HL)
    void CBopcode0x8F();    // RES 1, A  
    void CBopcode0x90();    // RES 2, B  
    void CBopcode0x91();    // RES 2, C  
    void CBopcode0x92();    // RES 2, D  
    void CBopcode0x93();    // RES 2, E  
    void CBopcode0x94();    // RES 2, H  
    void CBopcode0x95();    // RES 2, L  
    void CBopcode0x96();    // RES 2, (HL)
    void CBopcode0x97();    // RES 2, A  
    void CBopcode0x98();    // RES 3, B  
    void CBopcode0x99();    // RES 3, C  
    void CBopcode0x9A();    // RES 3, D  
    void CBopcode0x9B();    // RES 3, E  
    void CBopcode0x9C();    // RES 3, H  
    void CBopcode0x9D();    // RES 3, L  
    void CBopcode0x9E();    // RES 3, (HL)
    void CBopcode0x9F();    // RES 3, A  
    void CBopcode0xA0();    // RES 4, B  
    void CBopcode0xA1();    // RES 4, C  
    void CBopcode0xA2();    // RES 4, D  
    void CBopcode0xA3();    // RES 4, E  
    void CBopcode0xA4();    // RES 4, H  
    void CBopcode0xA5();    // RES 4, L  
    void CBopcode0xA6();    // RES 4, (HL)
    void CBopcode0xA7();    // RES 4, A  
    void CBopcode0xA8();    // RES 5, B  
    void CBopcode0xA9();    // RES 5, C  
    void CBopcode0xAA();    // RES 5, D  
    void CBopcode0xAB();    // RES 5, E  
    void CBopcode0xAC();    // RES 5, H  
    void CBopcode0xAD();    // RES 5, L  
    void CBopcode0xAE();    // RES 5, (HL)
    void CBopcode0xAF();    // RES 5, A  
    void CBopcode0xB0();    // RES 6, B  
    void CBopcode0xB1();    // RES 6, C  
    void CBopcode0xB2();    // RES 6, D  
    void CBopcode0xB3();    // RES 6, E  
    void CBopcode0xB4();    // RES 6, H  
    void CBopcode0xB5();    // RES 6, L  
    void CBopcode0xB6();    // RES 6, (HL)
    void CBopcode0xB7();    // RES 6, A  
    void CBopcode0xB8();    // RES 7, B  
    void CBopcode0xB9();    // RES 7, C  
    void CBopcode0xBA();    // RES 7, D  
    void CBopcode0xBB();    // RES 7, E  
    void CBopcode0xBC();    // RES 7, H  
    void CBopcode0xBD();    // RES 7, L  
    void CBopcode0xBE();    // RES 7, (HL)
    void CBopcode0xBF();    // RES 7, A  
    void CBopcode0xC0();    // SET 0, B  
    void CBopcode0xC1();    // SET 0, C  
    void CBopcode0xC2();    // SET 0, D  
    void CBopcode0xC3();    // SET 0, E  
    void CBopcode0xC4();    // SET 0, H  
    void CBopcode0xC5();    // SET 0, L  
    void CBopcode0xC6();    // SET 0, (HL)
    void CBopcode0xC7();    // SET 0, A  
    void CBopcode0xC8();    // SET 1, B  
    void CBopcode0xC9();    // SET 1, C  
    void CBopcode0xCA();    // SET 1, D  
    void CBopcode0xCB();    // SET 1, E  
    void CBopcode0xCC();    // SET 1, H  
    void CBopcode0xCD();    // SET 1, L  
    void CBopcode0xCE();    // SET 1, (HL)
    void CBopcode0xCF();    // SET 1, A       
    void CBopcode0xD0();    // SET 2, B  
    void CBopcode0xD1();    // SET 2, C  
    void CBopcode0xD2();    // SET 2, D  
    void CBopcode0xD3();    // SET 2, E  
    void CBopcode0xD4();    // SET 2, H  
    void CBopcode0xD5();    // SET 2, L  
    void CBopcode0xD6();    // SET 2, (HL)
    void CBopcode0xD7();    // SET 2, A  
    void CBopcode0xD8();    // SET 3, B  
    void CBopcode0xD9();    // SET 3, C  
    void CBopcode0xDA();    // SET 3, D  
    void CBopcode0xDB();    // SET 3, E  
    void CBopcode0xDC();    // SET 3, H  
    void CBopcode0xDD();    // SET 3, L  
    void CBopcode0xDE();    // SET 3, (HL)
    void CBopcode0xDF();    // SET 3, A      
    void CBopcode0xE0();    // SET 4, B  
    void CBopcode0xE1();    // SET 4, C  
    void CBopcode0xE2();    // SET 4, D  
    void CBopcode0xE3();    // SET 4, E  
    void CBopcode0xE4();    // SET 4, H  
    void CBopcode0xE5();    // SET 4, L  
    void CBopcode0xE6();    // SET 4, (HL)
    void CBopcode0xE7();    // SET 4, A  
    void CBopcode0xE8();    // SET 5, B  
    void CBopcode0xE9();    // SET 5, C  
    void CBopcode0xEA();    // SET 5, D  
    void CBopcode0xEB();    // SET 5, E  
    void CBopcode0xEC();    // SET 5, H  
    void CBopcode0xED();    // SET 5, L  
    void CBopcode0xEE();    // SET 5, (HL)
    void CBopcode0xEF();    // SET 5, A    
    void CBopcode0xF0();    // SET 6, B  
    void CBopcode0xF1();    // SET 6, C  
    void CBopcode0xF2();    // SET 6, D  
    void CBopcode0xF3();    // SET 6, E  
    void CBopcode0xF5();    // SET 6, H  
    void CBopcode0xF4();    // SET 6, L  
    void CBopcode0xF6();    // SET 6, (HL)
    void CBopcode0xF7();    // SET 6, A  
    void CBopcode0xF8();    // SET 7, B  
    void CBopcode0xF9();    // SET 7, C  
    void CBopcode0xFA();    // SET 7, D  
    void CBopcode0xFB();    // SET 7, E  
    void CBopcode0xFC();    // SET 7, H  
    void CBopcode0xFD();    // SET 7, L  
    void CBopcode0xFE();    // SET 7, (HL)
    void CBopcode0xFF();    // SET 7, A  
};
