#pragma once

#include <string>
#include <SDL.h>

namespace pso {
	class Screen {
	public:
		const static int WINDOW_WIDTH = 800;
		const static int WINDOW_HEIGHT = 600;
		
		Screen();
		~Screen();

		bool init();
		bool process();
		void close();
		void update();
		void clear();
		void boxBlur();
		void setPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b);

	private:
		SDL_Window *m_pWindow;
		SDL_Renderer *m_pRenderer;
		SDL_Texture *m_pTexture;
		Uint32 *m_pBuffer;
		Uint32 *m_pBuffer2;

	};
} /* namespace pso */

