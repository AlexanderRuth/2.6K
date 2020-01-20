#include "CPU.h"

bool CPU::tick()
{
	//std::cout << "PC: " << pc << std::endl;
	//if (pc >= 0xF000)
	//	return false;
	//Lookup the next instruction
	uint8_t ins = m_mem->read_rom(pc);

	if (cycles > 1)
	{
		cycles--;
		return true;
	}
	else
	{
		if (!start)
		{
			switch (ins)
			{
			case 0x4C: JMP(abs(), true); break;
			case 0xD0: BNE(rel()); break;
			case 0xE0: CPX(imm(), true); break;
			case 0xE8: INX(); break;
			case 0x84: STY(zpg()); break;
			case 0x85: STA(zpg()); break;
			case 0x86: STX(zpg()); break;
			case 0x88: DEY(); break;
			case 0x95: STA(zpgx()); break;
			case 0xA0: LDY(imm(), true); break;
			case 0xA2: LDX(imm(), true); break;
			case 0xA5: LDA(zpg()); break;
			case 0xA9: LDA(imm(), true); break;
			case 0xC0: CPY(imm(), true); break;
			case 0xC8: INY(); break;
			case 0xE6: INC(zpg()); break;
			case 0xEA: pc += 1; break;				//NOP
			}
		}

		/*if (pc >= 0xF000)
		{
			return false;
		}*/

		ins = m_mem->read_rom(pc);

		//Determine next instruction cycle count
		switch (ins)
		{
		case 0x4C: cycles = 3; break;
		case 0xD0: cycles = 2; break;
		case 0xE0: cycles = 2; break;
		case 0xE8: cycles = 2; break;
		case 0x84: cycles = 3; break;
		case 0x85: cycles = 3; break;
		case 0x86: cycles = 3; break;
		case 0x88: cycles = 2; break;
		case 0x95: cycles = 4; break;
		case 0xA0: cycles = 2; break;
		case 0xA2: cycles = 2; break;
		case 0xA5: cycles = 3; break;
		case 0xA9: cycles = 2; break;
		case 0xC0: cycles = 2; break;
		case 0xC8: cycles = 2; break;
		case 0xE6: cycles = 5; break;
		case 0xEA: cycles = 2; break;
		}

		if(start)
		{
			cycles--;
			start = false;
		}
	}

	return true;
}

//
// Addressing modes
//
uint16_t CPU::abs() 
{ 
	//Two bytes, stored little endian
	uint16_t res = (m_mem->read_rom(pc + 2) << 8) + (m_mem->read_rom(pc + 1));
	pc += 3;
	return res;
}

uint16_t CPU::absx()
{
	uint16_t res = (m_mem->read_rom(pc + 2) << 8) + (m_mem->read_rom(pc + 1)) + x + get_sr(C);
	pc += 3;
	return res;
}

uint16_t CPU::absy()
{
	uint16_t res = (m_mem->read_rom(pc + 2) << 8) + (m_mem->read_rom(pc + 1)) + y + get_sr(C);
	pc += 3;
	return res;
}

uint16_t CPU::imm()
{
	uint16_t res = m_mem->read_rom(pc + 1);
	pc += 2;
	return res;
}

uint16_t CPU::zpg()
{
	uint16_t res = m_mem->read_rom(pc + 1);
	pc += 2;
	return res;
}

uint16_t CPU::zpgx()
{
	uint16_t res = m_mem->read_rom(pc + 1) + x;
	pc += 2;
	return res;
}

uint16_t CPU::rel()
{
	uint16_t res = pc + 2 + (int8_t) m_mem->read_rom(pc + 1);
	pc += 2;
	return res;
}
//status register
void CPU::set_sr(int bit, bool val)
{
	if (val)
		sr |= bit;
	else
		sr &= ~bit;
}

uint8_t CPU::get_sr(int bit)
{
	if (sr & bit)
		return 1;
	else
		return 0;
}

void CPU::BNE(uint16_t addr)
{
	if (debug)
		std::cout << "BNE: " << std::hex << addr << std::endl;
	if (!get_sr(Z))
		pc = addr;
}

void CPU::CPX(uint16_t addr, bool imm)
{
	int8_t tmp;

	if (debug)
		std::cout << "CPX: " << std::hex << addr << std::endl;
	if (imm)
		tmp = x - addr;
	else
		tmp = x - m_mem->read(addr);

	set_sr(N, tmp < 0);
	set_sr(Z, tmp == 0);
	//set_sr(C, 0);
}

void CPU::CPY(uint16_t addr, bool imm)
{
	int8_t tmp;

	if (debug)
		std::cout << "CPY: " << std::hex << addr << std::endl;
	if (imm)
		tmp = y - addr;
	else
		tmp = y - m_mem->read(addr);

	set_sr(N, tmp < 0);
	set_sr(Z, tmp == 0);
	//set_sr(C, 0);
}

void CPU::DEY()
{
	if (debug)
		std::cout << "DEY" << std::endl;

	pc += 1;
	y--;
	set_sr(Z, y == 0);
	set_sr(N, y < 0);
}

void CPU::INC(uint16_t addr)
{
	if (debug)
		std::cout << "INC" << std::hex << addr << std::endl;

	uint8_t tmp = m_mem->read(addr);
	tmp++;
	m_mem->write(addr, tmp);

	set_sr(Z, tmp == 0);
	set_sr(N, tmp < 0);
}

void CPU::INX()
{
	if (debug)
		std::cout << "INX" << std::endl;

	pc += 1;
	x++;
	set_sr(Z, x == 0);
	set_sr(N, x < 0);
}

void CPU::INY()
{
	if (debug)
		std::cout << "INY" << std::endl;

	pc += 1;
	y++;
	set_sr(Z, y == 0);
	set_sr(N, y < 0);
}

void CPU::JMP(uint16_t addr, bool imm)
{
	if (debug)
		std::cout << "JMP: " << std::hex << addr << std::endl;
	if (imm)
		pc = addr;
	else
		pc = m_mem->read(addr);
}

void CPU::LDA(uint16_t addr, bool imm)
{
	if (debug)
		std::cout << "LDA: " << std::hex << addr << std::endl;

	if (imm)
		ac = addr;
	else
		ac = m_mem->read(addr);

	set_sr(Z, ac == 0);
	set_sr(N, ac < 0);
}

void CPU::LDX(uint16_t addr, bool imm)
{
	if (debug)
		std::cout << "LDX: 0x" << std::hex << addr << std::endl;

	if (imm)
		x = addr;
	else
		x = m_mem->read(addr);
	set_sr(Z, x == 0);
	set_sr(N, ac < 0);
}

void CPU::LDY(uint16_t addr, bool imm)
{
	if (debug)
		std::cout << "LDY: 0x" << std::hex << addr << std::endl;
	if (imm)
		y = addr;
	else
		y = m_mem->read(addr);
	set_sr(Z, y == 0);
	set_sr(N, y < 0);
}

void CPU::STA(uint16_t addr)
{
	if (debug)
		std::cout << "STA: " << std::hex << addr << std::endl;

	m_mem->write(addr, ac);
}

void CPU::STX(uint16_t addr)
{
	if (debug)
		std::cout << "STX: " << std::hex << addr << std::endl;

	m_mem->write(addr, x);
}

void CPU::STY(uint16_t addr)
{
	if (debug)
		std::cout << "STY: " << std::hex << addr << std::endl;
	m_mem->write(addr, y);
}