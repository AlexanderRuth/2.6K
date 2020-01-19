#pragma once

/*
	Scanlines:
	-----
	3 VSYNC
	37 VBLANK
	192 (NTSC) Picture
	30 Overscan
	-----
	262 Scanlines (NTSC)

	Clocks per scanline:
	-----
	68 HBLANK
	160 Pixels
	-----
	228 clocks per scanline
*/
#include <SDL.h>
#include <memory>
#include <iostream>
#include "MMU.h"

#define VSYNC 3
#define VBLANK 40
#define PICTURE 232
#define OVERSCAN 262

#define HBLANK 68

#define WSYNC 0x02
#define COLUBK	0x09

#define PIXEL_WIDTH 3
#define PIXEL_HEIGHT 1


enum TIA_FLAG { CPU_SLEEP, CPU_WAKEUP, OK };

class TIA
{
public:
	TIA()
		: cur_clock{ 1 }, cur_scanline{ 1 }, m_screen{ nullptr }, m_window{ nullptr }, m_mem{ nullptr }, m_renderer{ nullptr }, cpu_wait{ false }, prev_color{0}
	{}

	TIA(std::shared_ptr<MMU> mem)
		: cur_clock{ 1 }, cur_scanline{ 1 }, m_screen{ nullptr }, m_window{ nullptr }, m_mem{ mem }, m_renderer{ nullptr }, cpu_wait{ false }, prev_color{ 0 }
	{}

	~TIA();

	TIA_FLAG tick();
	void init_screen(int h, int w);
	void draw_background();

	TIA_FLAG check_registers();
private:
	int cur_clock;
	int cur_scanline;
	SDL_Window* m_window;
	SDL_Surface* m_screen;
	SDL_Renderer* m_renderer;
	std::shared_ptr<MMU> m_mem;
	bool cpu_wait;

	uint8_t prev_color;
};