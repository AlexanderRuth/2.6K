#include "MMU.h"
#include <iostream>

void MMU::set_rom(unsigned char data[4096])
{
	memcpy(m_mem + ROM_OFFSET, data, 4096);
}

int8_t MMU::read(uint16_t addr)
{
	if (addr >> 13 > 0)
		//error: addr out of range
		return -1;

	return m_mem[addr];
}

int8_t MMU::read_ram(uint16_t addr)
{
	return m_mem[RAM_OFFSET + addr];
}

int8_t MMU::read_tia(uint16_t addr)
{
	return m_mem[TIA_OFFSET + addr];
}
uint8_t MMU::read_rom(uint16_t addr)
{
	return m_mem[addr];
}

void MMU::write(uint16_t addr, int8_t data)
{
	//TIA strobe registers
	if (addr == 0x02)
	{
		m_mem[addr] = 1;
		return;
	}

	if (addr >> 13 > 0)
		//error: addr out of range
		return;
	m_mem[addr] = data;
}

void MMU::write_ram(uint16_t addr, int8_t data)
{
	m_mem[RAM_OFFSET + addr] = data;
}

void MMU::write_tia(uint16_t addr, int8_t data)
{
	m_mem[TIA_OFFSET + addr] = data;
}

void MMU::clear(uint16_t addr)
{
	m_mem[addr] = 0;
}