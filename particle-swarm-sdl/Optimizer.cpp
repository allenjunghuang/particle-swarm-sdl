#include "Optimizer.h"


namespace pso {
	Optimizer::Optimizer() {
	}


	Optimizer::~Optimizer() {
	}

	double Optimizer::fitness(Particle& particle) {
		double distance = sqrt(pow(particle.m_x, 2) + pow(particle.m_y, 2));
		
		return sin(distance) / distance + exp(0.5* cos(2 * M_PI * particle.m_x) + 0.5  * cos(2 * M_PI * particle.m_y)) - 2.71289;
	}
}
