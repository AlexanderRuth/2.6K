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
#include <vector>
#include "MMU.h"

#define VSYNC 3
#define VBLANK 40
#define PICTURE 232
#define OVERSCAN 262

#define HBLANK 68

//TIA Registers
#define VSYNC_REG 0x00
#define VBLANK_REG 0x01
#define WSYNC 0x02
#define COLUBK	0x09
#define COLUPF 0x08

//Playfield control
#define CTRLPF 0x0A
#define REF 0b00000001	//Reflect playfield

#define PF0 0x0D
#define PF1 0x0E
#define PF2 0x0F

#define PIXEL_WIDTH 2
#define PIXEL_HEIGHT 1

#define PF_WIDTH ((160 * PIXEL_WIDTH) / 40)

enum PIXEL_LEVEL { NONE, BK, PF };					//PF takes precedence over BK, etc.
enum TIA_FLAG { CPU_SLEEP, CPU_WAKEUP, OK };

class TIA
{
public:
	TIA()
		: cur_clock{ 1 }, cur_scanline{ 1 }, m_screen{ nullptr }, m_window{ nullptr }, m_mem{ nullptr }, m_renderer{ nullptr }, cpu_wait{ false }, 
		prev_color{ 0 }, last_pf{ -1 }, m_pixels{ nullptr }, m_claimed{ nullptr }
	{}

	TIA(std::shared_ptr<MMU> mem)
		: cur_clock{ 1 }, cur_scanline{ 1 }, m_screen{ nullptr }, m_window{ nullptr }, 
		  m_mem{ mem }, m_renderer{ nullptr }, cpu_wait{ false }, prev_color{ 0 }, last_pf{ -1 }, m_pixels{ nullptr }, m_claimed{ nullptr }
	{}

	~TIA();

	TIA_FLAG tick();
	void init_screen(int h, int w);
	void draw_background();
	void draw_playfield();
	void draw_pixel(int x, int y, uint8_t r, uint8_t g, uint8_t b);

	TIA_FLAG check_registers();
private:
	int cur_clock;
	int cur_scanline;
	SDL_Window* m_window;
	SDL_Surface* m_screen;
	SDL_Renderer* m_renderer;
	SDL_Texture* m_texture;
	Uint32* m_pixels;
	PIXEL_LEVEL* m_claimed;
	int m_w;
	int m_h;

	std::shared_ptr<MMU> m_mem;
	bool cpu_wait;
	int last_pf;

	uint8_t prev_color;
};