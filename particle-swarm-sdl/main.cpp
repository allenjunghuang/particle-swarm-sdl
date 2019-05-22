#include <SDL.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Screen.h"
#include "Swarm.h"
#include "Optimizer.h"

using namespace std;
using namespace pso;

int main(int argc, char *args[]) {
	
	srand(time(NULL)); // create different seeds for random number generator
	 
	Screen screen;

	if (screen.init() == false) {
		cout << "Failed to initialize SDL." << endl;
	}
	int windowCenterX = Screen::WINDOW_WIDTH / 2;
	int windowCenterY = Screen::WINDOW_HEIGHT / 2;

	Swarm swarm;
	Ackley optimizer;

	while (true) { //game loop runs as long as the game is running, such as draw particles, check events
		
		int elapsed = SDL_GetTicks();

		//screen.clear();
		swarm.update(elapsed);
		
		const Particle * const pParticles = swarm.collect();

		for (int i = 0; i < Swarm::NPARTICLES; i++) {
			Particle particle = pParticles[i];

			int x = windowCenterX + (particle.m_x)*Screen::WINDOW_WIDTH / 2;
			int y = windowCenterY + (particle.m_y)*Screen::WINDOW_WIDTH / 2;

			screen.setPixel(x, y, 255, 255, 255);
		}
		
		/* wax and wane canvas color
		int elapsed = SDL_GetTicks();
		unsigned char g = (1 + sin(elapsed*0.001)) * 128; // use unsigned char to range the integer 0~255

		for (int y = 0; y < Screen::WINDOW_HEIGHT; y++) {
			for (int x = 0; x < Screen::WINDOW_WIDTH; x++) {
				screen.setPixel(x, y, 0, g, 0);
			}
		}
		*/

		screen.boxBlur();

		//draw the screen
		screen.update();

		//check event or message
		if (screen.process() == false) {
			break;
		}
	}
	
	screen.close();

	return 0;
}