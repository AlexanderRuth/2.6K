#pragma once
/*
	0x0000 - 0x007F			TIA Registers
	0x0080 - 0x00FF			RAM
	0x0280 - 0x02FF			RIOT
	0x1000 - 0x1FFF			ROM
*/

#include <cstdint>
#include <stdio.h>
#include <string.h>

#define MEM_SIZE 0xFFFF
#define TIA_OFFSET 0x0000
#define RAM_OFFSET 0x0080
#define ROM_OFFSET 0xF000

class MMU
{
public:

	MMU()
	{
		//Zero out memory
		memset(m_mem, 0, MEM_SIZE);
	}

	void set_rom(unsigned char data[4192]);

	//READS
	int8_t read(uint16_t addr);
	int8_t read_tia(uint16_t addr);
	int8_t read_ram(uint16_t addr);
	uint8_t read_rom(uint16_t addr);
	
	//WRITES
	void write(uint16_t addr, int8_t data);
	void write_tia(uint16_t addr, int8_t data);
	void write_ram(uint16_t addr, int8_t data);
	void clear(uint16_t addr);
private:
	uint8_t m_mem[MEM_SIZE];
};