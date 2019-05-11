#include "Screen.h"

namespace pso {

	Screen::Screen() : m_pWindow(NULL), m_pRenderer(NULL), m_pTexture(NULL), m_pBuffer(NULL), m_pBuffer2(NULL) {

	}

	Screen::~Screen() {

	}

	bool Screen::init() {
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			//cout << "Failed to initialize SDL." << SDL_GetError() << endl;
			return false;
		}

		m_pWindow = SDL_CreateWindow("Particle Swarm Optimization", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
		if (m_pWindow == NULL) {
			//cout << "Failed to initialize SDL_Window." << SDL_GetError() << endl;
			SDL_Quit();
			return false;
		}

		m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_PRESENTVSYNC);
		if (m_pRenderer == NULL) {
			//cout << "Failed to initialize SDL_Renderer." << SDL_GetError() << endl;
			SDL_DestroyWindow(m_pWindow);
			SDL_Quit();
			return false;
		}

		m_pTexture = SDL_CreateTexture(m_pRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, WINDOW_WIDTH, WINDOW_HEIGHT);
		if (m_pTexture == NULL) {
			//cout << "Failed to initialize SDL_Texture." << SDL_GetError() << endl;
			SDL_DestroyRenderer(m_pRenderer);
			SDL_DestroyWindow(m_pWindow);
			SDL_Quit();
			return false;
		}

		m_pBuffer = new Uint32[WINDOW_WIDTH*WINDOW_HEIGHT]; //allocate memory for the pixels on the screen (each pixel need 8*4=32 bits) 
		m_pBuffer2 = new Uint32[WINDOW_WIDTH*WINDOW_HEIGHT];

		memset(m_pBuffer, 0x00, WINDOW_WIDTH*WINDOW_HEIGHT * sizeof(Uint32));
		memset(m_pBuffer2, 0x00, WINDOW_WIDTH*WINDOW_HEIGHT * sizeof(Uint32));

		return true;
	}

	void Screen::update() {
		SDL_UpdateTexture(m_pTexture, NULL, m_pBuffer, WINDOW_WIDTH * sizeof(Uint32)); //update the texture with the pixels contained in the buffer
		SDL_RenderClear(m_pRenderer);
		SDL_RenderCopy(m_pRenderer, m_pTexture, NULL, NULL);
		SDL_RenderPresent(m_pRenderer);
	}

	void Screen::boxBlur() {
		Uint32 *p = m_pBuffer;
		m_pBuffer = m_pBuffer2;
		m_pBuffer2 = p;

		for (int y = 0; y < WINDOW_HEIGHT; y++) {
			for (int x = 0; x < WINDOW_WIDTH; x++) {
				int r = 0;
				int g = 0;
				int b = 0;

				for (int row = -1; row <= 1; row++) {
					for (int col = -1; col <= 1; col++) {
						int xcoord = x + col;
						int ycoord = y + row;
						if (xcoord >= 0 && xcoord < WINDOW_WIDTH && ycoord >= 0 && ycoord < WINDOW_HEIGHT) {
							Uint32 pixel = m_pBuffer2[ycoord*WINDOW_WIDTH + xcoord];
							
							Uint8 rPixel = pixel >> 24;
							Uint8 gPixel = pixel >> 16;
							Uint8 bPixel = pixel >> 8;

							r += rPixel;
							g += gPixel;
							b += bPixel;
						}
					}
				}
				Uint8 rPixel = r / 9;
				Uint8 gPixel = g / 9;
				Uint8 bPixel = b / 9;
				setPixel(x, y, rPixel, gPixel, bPixel);
			}
		}
	}

	void Screen::clear() {
		memset(m_pBuffer, 0x00, WINDOW_WIDTH*WINDOW_HEIGHT * sizeof(Uint32));
		memset(m_pBuffer2, 0x00, WINDOW_WIDTH*WINDOW_HEIGHT * sizeof(Uint32));
	}
	void Screen::setPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b) {

		if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT) {
			return;
		}

		Uint32 color = 0;

		color += r;
		color <<= 8;
		color += g;
		color <<= 8;
		color += b;
		color <<= 8;
		color += 0xFF;

		m_pBuffer[(y * WINDOW_WIDTH) + x] = color;
	}

	bool Screen::process() {
		SDL_Event event;

		while (SDL_PollEvent(&event)) {	//event loop processes the event queue which is happening in the game loop, such as click bottom
			if (event.type == SDL_QUIT) {
				return false;
			}
		}
		return true;
	}

	void Screen::close() {
		delete[] m_pBuffer;
		delete[] m_pBuffer2;
		SDL_DestroyRenderer(m_pRenderer);
		SDL_DestroyTexture(m_pTexture);
		SDL_DestroyWindow(m_pWindow);
		SDL_Quit();
	}

} /* namespace pso */