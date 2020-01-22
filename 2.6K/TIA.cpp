#include "TIA.h"

int num = 128;
int tia_colors[][3] = {
{0x00, 0x00, 0x00},{0x40, 0x40, 0x40},{0x6C, 0x6C, 0x6C},{0x90, 0x90, 0x90},{0xB0, 0xB0, 0xB0},{0xC8, 0xC8, 0xC8},{0xDC, 0xDC, 0xDC},{0xEC, 0xEC, 0xEC},
{0x44, 0x44, 0x00},{0x64, 0x64, 0x10},{0x84, 0x84, 0x24},{0xA0, 0xA0, 0x34},{0xB8, 0xB8, 0x40},{0xD0, 0xD0, 0x50},{0xE8, 0xE8, 0x5C},{0xFC, 0xFC, 0x68},
{0x70, 0x28, 0x00},{0x84, 0x44, 0x14},{0x98, 0x5C, 0x28},{0xAC, 0x78, 0x3C},{0xBC, 0x8C, 0x4C},{0xCC, 0xA0, 0x5C},{0xDC, 0xB4, 0x68},{0xEC, 0xC8, 0x78},
{0x84, 0x18, 0x00},{0x98, 0x34, 0x18},{0xAC, 0x50, 0x30},{0xC0, 0x68, 0x48},{0xD0, 0x80, 0x5C},{0xE0, 0x94, 0x70},{0xEC, 0xA8, 0x80},{0xFC, 0xBC, 0x94},
{0x88, 0x00, 0x00},{0x9C, 0x20, 0x20},{0xB0, 0x3C, 0x3C},{0xC0, 0x58, 0x58},{0xD0, 0x70, 0x70},{0xE0, 0x88, 0x88},{0xEC, 0xA0, 0xA0},{0xFC, 0xB4, 0xB4},
{0x78, 0x00, 0x5C},{0x8C, 0x20, 0x74},{0xA0, 0x3C, 0x88},{0xB0, 0x58, 0x9C},{0xC0, 0x70, 0xB0},{0xD0, 0x84, 0xC0},{0xDC, 0x9C, 0xD0},{0xEC, 0xB0, 0xE0},
{0x48, 0x00, 0x78},{0x60, 0x20, 0x90},{0x78, 0x3C, 0xA4},{0x8C, 0x58, 0xB8},{0xA0, 0x70, 0xCC},{0xB4, 0x84, 0xDC},{0xC4, 0x9C, 0xEC},{0xD4, 0xB0, 0xFC},
{0x14, 0x00, 0x84},{0x30, 0x20, 0x98},{0x4C, 0x3C, 0xAC},{0x68, 0x58, 0xC0},{0x7C, 0x70, 0xD0},{0x94, 0x88, 0xE0},{0xA8, 0xA0, 0xEC},{0xBC, 0xB4, 0xFC},
{0x00, 0x00, 0x88},{0x1C, 0x20, 0x9C},{0x38, 0x40, 0xB0},{0x50, 0x5C, 0xC0},{0x68, 0x74, 0xD0},{0x7C, 0x8C, 0xE0},{0x90, 0xA4, 0xEC},{0xA4, 0xB8, 0xFC},
{0x00, 0x18, 0x7C},{0x1C, 0x38, 0x90},{0x38, 0x54, 0xA8},{0x50, 0x70, 0xBC},{0x68, 0x88, 0xCC},{0x7C, 0x9C, 0xDC},{0x90, 0xB4, 0xEC},{0xA4, 0xC8, 0xFC},
{0x00, 0x2C, 0x5C},{0x1C, 0x4C, 0x78},{0x38, 0x68, 0x90},{0x50, 0x84, 0xAC},{0x68, 0x9C, 0xC0},{0x7C, 0xB4, 0xD4},{0x90, 0xCC, 0xE8},{0xA4, 0xE0, 0xFC},
{0x00, 0x3C, 0x2C},{0x1C, 0x5C, 0x48},{0x38, 0x7C, 0x64},{0x50, 0x9C, 0x80},{0x68, 0xB4, 0x94},{0x7C, 0xD0, 0xAC},{0x90, 0xE4, 0xC0},{0xA4, 0xFC, 0xD4},
{0x00, 0x3C, 0x00},{0x20, 0x5C, 0x20},{0x40, 0x7C, 0x40},{0x5C, 0x9C, 0x5C},{0x74, 0xB4, 0x74},{0x8C, 0xD0, 0x8C},{0xA4, 0xE4, 0xA4},{0xB8, 0xFC, 0xB8},
{0x14, 0x38, 0x00},{0x34, 0x5C, 0x1C},{0x50, 0x7C, 0x38},{0x6C, 0x98, 0x50},{0x84, 0xB4, 0x68},{0x9C, 0xCC, 0x7C},{0xB4, 0xE4, 0x90},{0xC8, 0xFC, 0xA4},
{0x2C, 0x30, 0x00},{0x4C, 0x50, 0x1C},{0x68, 0x70, 0x34},{0x84, 0x8C, 0x4C},{0x9C, 0xA8, 0x64},{0xB4, 0xC0, 0x78},{0xCC, 0xD4, 0x88},{0xE0, 0xEC, 0x9C},
{0x44, 0x28, 0x00},{0x64, 0x48, 0x18},{0x84, 0x68, 0x30},{0xA0, 0x84, 0x44},{0xB8, 0x9C, 0x58},{0xD0, 0xB4, 0x6C},{0xE8, 0xCC, 0x7C},{0xFC, 0xE0, 0x8C}
};

void TIA::init_screen(int h, int w)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return;
	}

	m_window = SDL_CreateWindow(
		"hello_sdl2",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		w, h,
		SDL_WINDOW_SHOWN
	);
	m_screen = SDL_GetWindowSurface(m_window);
	SDL_FillRect(m_screen, NULL, SDL_MapRGB(m_screen->format, 0xFF, 0xFF, 0xFF));
	SDL_UpdateWindowSurface(m_window);

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, w, h);

	m_w = w * PIXEL_WIDTH;
	m_h = h * PIXEL_HEIGHT;
	m_pixels = new Uint32[m_w * m_h];
	memset(m_pixels, 255, m_w * m_h * sizeof(Uint32));

	m_claimed = new PIXEL_LEVEL[m_w * m_h];
	memset(m_claimed, NONE, m_w * m_h * sizeof(PIXEL_LEVEL));
};

TIA::~TIA()
{
	if (m_pixels)
		delete[] m_pixels;
	if (m_claimed)
		delete[] m_claimed;

	if (m_window){
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}
}


TIA_FLAG TIA::tick()
{


	//Check registers (for wsync, etc.)
	TIA_FLAG ret = check_registers();
	
	if (cur_scanline <= VSYNC)
		//VSYNC
		;
	else if (cur_scanline <= VBLANK)
		//VBLANK
		;
	else if (cur_scanline <= OVERSCAN){
		//If past horizontal blank, begin drawing picture
		if (cur_clock > HBLANK){
			draw_player();
			draw_playfield();
			draw_background();
		}

		//If finished overscan, render the texture
		if (cur_scanline == OVERSCAN && cur_clock >= 228){
			SDL_UpdateTexture(m_texture, NULL, m_pixels, m_w * sizeof(Uint32));
			SDL_RenderClear(m_renderer);
			SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
			SDL_RenderPresent(m_renderer);
		}
	}

	//Once done overscan, reset clock and scanline counters
	if (cur_scanline >= OVERSCAN && cur_clock >= 228){
		memset(m_claimed, NONE, m_w);
		cur_clock = 1;
		cur_scanline = 1;

		//Wake up CPU if needed
		if (cpu_wait){
			cpu_wait = false;
			return CPU_WAKEUP;
		}
		else{
			return OK;
		}

	}

	//New scanline
	else if (cur_clock >= 228){
		memset(m_claimed, NONE, m_w);
		cur_scanline += 1;
		cur_clock = 0;
		if (cpu_wait){
			cpu_wait = false;
			return CPU_WAKEUP;
		}
		else{
			return OK;
		}
	}
	else {
		cur_clock++;
	}

	return ret;

}

void TIA::draw_background()
{
	//Read Color
	uint8_t color = m_mem->read_tia(COLUBK);	

	int x = (cur_clock - HBLANK - 1) * PIXEL_WIDTH;
	int y = (cur_scanline - VBLANK - 1);

	if (m_claimed[x] != NONE || m_claimed[x+1] != NONE)
		return;

	for (int i = 0; i < PIXEL_WIDTH; i++)
	{
		draw_pixel(x + i, y, tia_colors[color / 2][0], tia_colors[color / 2][1], tia_colors[color / 2][2]);
	}
}

void TIA::draw_playfield()
{
	//Skip off cycle for the playfield (only render every 4 cycles)
	if ((cur_clock - HBLANK) % 4 != 0)
		return;

	//Read color
	uint8_t color = m_mem->read_tia(COLUPF);

	//The PF bit to use (0 thru 19)
	int pf_bit = std::ceil((cur_clock - HBLANK) / 4) - 1;

	//How to shift the pf register
	int shift = pf_bit >= 20 ? pf_bit - 20 : pf_bit;

	//Draw the pixel?
	uint8_t draw_pf_pixel = 0;

	//Mirror?
	uint8_t mirror = m_mem->read_tia(CTRLPF) & REF;
	
	//The actually index to use for the mirrored portion
	int index = pf_bit;

	//If mirroring is enabled and on the right half of the scanline
	if (mirror && pf_bit >= 20) {

		//The bit to mirror
		pf_bit = 40 - pf_bit - 1;

		//If not claimed in left half, unclaim in right half
		if (m_claimed[pf_bit*PF_WIDTH] != PF) {
			for (int i = 0; i < PF_WIDTH; i++) {
				m_claimed[index * PF_WIDTH + i] = NONE;
			}
			return;
		}

		//Otherwise, duplicate what's in the left half
		for (int i = 0; i < PF_WIDTH; i++) {
			draw_pixel(index*PF_WIDTH + i, cur_scanline - VBLANK - 1, tia_colors[color / 2][0], tia_colors[color / 2][1], tia_colors[color / 2][2]);
			m_claimed[index* PF_WIDTH + i] = PF;
		}

		return;
	}


	//PF0 (reversed)
	if ((pf_bit >= 0 && pf_bit < 4) || (pf_bit >= 20 && pf_bit < 24)){
		shift = 3 - shift;
		draw_pf_pixel = m_mem->read_tia(PF0) & (0b10000000 >> (shift));
	}

	//PF1 (not reversed)
	if ((pf_bit >= 4 && pf_bit < 12) || (pf_bit >= 24 && pf_bit < 32)){
		draw_pf_pixel = m_mem->read_tia(PF1) & (0b10000000 >> (shift - 4));
	}

	//PF2 (not reversed)
	if ((pf_bit >= 12 && pf_bit < 20) || (pf_bit >= 32)){
		draw_pf_pixel = m_mem->read_tia(PF2) & (0b10000000 >> (shift - 12));
	}

	//If the PF pixel is set to draw, draw a width of PF_WIDTH, and claim it for PF
	if (draw_pf_pixel){
		for (int i = 0; i < PF_WIDTH; i++) {
			if (m_claimed[pf_bit * PF_WIDTH + i] != P0 && m_claimed[pf_bit * PF_WIDTH + i] != P1) {
				draw_pixel(pf_bit * PF_WIDTH + i, cur_scanline - VBLANK - 1, tia_colors[color / 2][0], tia_colors[color / 2][1], tia_colors[color / 2][2]);
				m_claimed[pf_bit * PF_WIDTH + i] = PF;
			}
		}
	}
}

void TIA::draw_player()
{
	uint8_t resp = m_mem->read(RESP0);
	int index = cur_clock - HBLANK - 1;
	if (resp) {
		m_mem->clear(RESP0);
		uint8_t player = m_mem->read(GRP0);
		uint8_t color = m_mem->read(COLUP0);
		for (int i = 0; i < 8; i++) {
			if (player & (0b10000000 >> i)) {
				for (int j = 0; j < PIXEL_WIDTH; j++) {
					draw_pixel((index + i) * PIXEL_WIDTH + j, cur_scanline - VBLANK - 1, tia_colors[color / 2][0], tia_colors[color / 2][1], tia_colors[color / 2][2]);
					m_claimed[(index + i) * PIXEL_WIDTH + j] = P0;
				}

			}
		}
	}
	resp = m_mem->read(RESP1);
	index = cur_clock - HBLANK - 1;
	if (resp) {
		m_mem->clear(RESP1);
		uint8_t player = m_mem->read(GRP1);
		uint8_t color = m_mem->read(COLUP1);
		for (int i = 0; i < 8; i++) {
			if (player & (0b10000000 >> i)) {
				for (int j = 0; j < PIXEL_WIDTH; j++) {
					draw_pixel((index + i) * PIXEL_WIDTH + j, cur_scanline - VBLANK - 1, tia_colors[color / 2][0], tia_colors[color / 2][1], tia_colors[color / 2][2]);
					m_claimed[(index + i) * PIXEL_WIDTH + j] = P1;
				}

			}
		}
	}
}

TIA_FLAG TIA::check_registers()
{
	//Check if CPU is sleeping till next scanline
	if (m_mem->read_tia(WSYNC)){
		m_mem->clear(WSYNC);
		cpu_wait = true;
		return CPU_SLEEP;
	}
	return OK;
}

void TIA::draw_pixel(int x, int y, uint8_t r, uint8_t g, uint8_t b)
{
	for(int i = 0; i < PIXEL_HEIGHT; i++)
		m_pixels[(y * PIXEL_HEIGHT + i) * m_w + x] = ((((((255 << 8) + r) << 8) + g) << 8) + b);
}