
#include <memory>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <SDL.h>

#include "TIA.h"
#include "MMU.h"
#include "CPU.h"

#define SCREEN_WIDTH 160 * 2
#define SCREEN_HEIGHT 222

int main(int argc, char* args[]) {
	std::string file = "test3.bin";

	unsigned char rom[4096];
	std::ifstream fin;
	fin.open(file, std::ios::binary);
	fin.read((char*)rom, 4096);
	fin.close();

	//Create Atari 2600 components
	std::shared_ptr<MMU> mem = std::shared_ptr<MMU>{ new MMU() };
	mem->set_rom((uint8_t*)rom);

	TIA tia(mem);
	CPU cpu(mem);

	tia.init_screen(SCREEN_HEIGHT, SCREEN_WIDTH);


	TIA_FLAG ret;
	bool cpu_sleep = false;
	bool cont = true;

	int when = 0;

	while (cont)
	{
		for (int i = 0; i < 3; i++)
		{
			if (!cpu_sleep && when == i)
				cont = cpu.tick();

			ret = tia.tick();
			if (ret == CPU_SLEEP)
				cpu_sleep = true;
			if (ret == CPU_WAKEUP)
			{
				cpu_sleep = false;
				when = i;
				cpu.tick();
			}

		}
	}

	SDL_Delay(5000);
	return 0;
}