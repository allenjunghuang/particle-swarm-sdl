#include <SDL.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Screen.h"
#include "Swarm.h"

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

	cout << "Initialize particles and test function" << endl;
	Swarm swarm;
	Himmelblau testfunctin;

	swarm.init(10.0, -10.0, 10.0, -10.0, testfunctin);
	
	int iter = 0;
	while (true) { //game loop runs as long as the game is running, such as draw particles, check events
		
		//int elapsed = SDL_GetTicks();
		//swarm.burst(elapsed);
		
		swarm.optimize(iter, testfunctin);
		if (iter % 10 == 0) {
			cout << "Iteration = " << iter << " best fitness = (" << swarm.m_gbestX << "," << swarm.m_gbestY << ") "<< swarm.m_gbestFitness << endl;
		}
		
		const Particle * const pParticles = swarm.collect();

		for (int i = 0; i < Swarm::NPARTICLES; i++) {
			Particle particle = pParticles[i];

			int x = windowCenterX + (particle.m_x) * Screen::WINDOW_WIDTH / (swarm.m_xUpperBound - swarm.m_xLowerBound) / 2;
			int y = windowCenterY + (particle.m_y) * Screen::WINDOW_HEIGHT / (swarm.m_yUpperBound - swarm.m_yLowerBound) / 2;

			screen.setPixel(x, y, 255, 255, 255);
		}

		screen.boxBlur();

		//draw the screen
		screen.update();
		
		//check event or message
		if (screen.process() == false || iter >= Swarm::MAX_ITERATION) {
			break;
		}
		iter++;
	}
	
	screen.close();
	

	return 0;
}