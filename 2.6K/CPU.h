#pragma once

//6502 (really, 6507) processor
#include <memory>
#include <cstdint>
#include <iostream>
#include "MMU.h"

//LDA #$immediate
//STA address
//INX
//STX $immediate
//JMP $

//STATUS FLAGS
#define N 0b10000000
#define V 0b01000000
#define B 0b00010000
#define D 0b00001000
#define I 0b00000100
#define Z 0b00000010
#define C 0b00000001

class CPU
{
public:
	CPU(std::shared_ptr<MMU> mem)
		: pc{ 0 }, ac{ 0 }, x{ 0 }, y{ 0 }, sr{ 0 }, sp{ 0 }, m_mem{ mem }, 
		cycles{ 0 }, start{ true }, debug{ true }
	{}

	//Run a clock cycle
	bool tick();

	//addressing modes
	uint16_t abs();
	uint16_t absx();
	uint16_t absy();
	uint16_t imm();
	uint16_t zpg();
	uint16_t rel();

	//status register
	void set_sr(int bit, bool val);
	uint8_t get_sr(int bit);

private:
	std::shared_ptr<MMU> m_mem;
	uint16_t pc;
	uint8_t ac;
	uint8_t x;
	uint8_t y;
	uint8_t sr;
	uint8_t sp;
	int cycles;
	bool start;
	bool debug;

	//INSTRUCTIONS
	void BNE(uint16_t addr);
	void CPX(uint16_t addr, bool imm = false);
	void DEY();
	void INX();
	void JMP(uint16_t addr, bool imm = false);
	void LDA(uint16_t addr, bool imm = false);
	void LDX(uint16_t addr, bool imm = false);
	void LDY(uint16_t addr, bool imm = false);
	void STA(uint16_t addr);
	void STX(uint16_t addr);
	void STY(uint16_t addr);
};