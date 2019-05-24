#include "Particle.h"


namespace pso {

	Particle::Particle(): m_x(0), m_y(0) {
		m_angle = 2*M_PI*rand() / RAND_MAX;
		m_velocity = 0.0001 * rand() / RAND_MAX;
	}
	
	Particle::~Particle() {
	}

	void Particle::burst(int interval) {

		m_xspeed = m_velocity * cos(m_angle);
		m_yspeed = m_velocity * sin(m_angle);

		m_x += m_xspeed * interval;
		m_y += m_yspeed * interval;
	}

	void Particle::init(double xUpperBound, double xLowerBound, double yUpperBound, double yLowerBound) {
		m_x = (xUpperBound - xLowerBound) / 2 * ((2.0*rand() / RAND_MAX) - 1) + (xUpperBound + xLowerBound) / 2;
		m_y = (yUpperBound - yLowerBound) / 2 * ((2.0*rand() / RAND_MAX) - 1) + (yUpperBound + yLowerBound) / 2;
		m_xspeed = 0.1*((2.0*rand() / RAND_MAX) - 1);
		m_yspeed = 0.1*((2.0*rand() / RAND_MAX) - 1);
		m_fitness = fit(m_x, m_y);

		m_bestFitness = m_fitness;
		m_bestX = m_x;
		m_bestY = m_y;
	}

	double Particle::fit(double x, double y) {
		return (pow(x, 2) + pow(y, 2));
		//return (pow(x, 2) - (10 * cos(2 * M_PI* x)) + 10) + (pow(y, 2) - (10 * cos(2 * M_PI* y)) + 10);
	}

	void Particle::optimize(double c1, double c2, double gbestX, double gbestY, int interval) {

		m_xspeed = m_xspeed + c1 * (rand() / RAND_MAX)* (m_bestX - m_x) + c2 * (rand() / RAND_MAX)* (gbestX - m_x);
		m_yspeed = m_yspeed + c1 * (rand() / RAND_MAX)* (m_bestY - m_y) + c2 * (rand() / RAND_MAX)* (gbestY - m_y);

		m_x += m_xspeed * interval;
		m_y += m_yspeed * interval;

		m_fitness = fit(m_x, m_y);

		if (m_fitness < this->m_bestFitness) {
			this->m_bestFitness = m_fitness;
			this->m_bestX = m_x;
			this->m_bestY = m_y;
		}
	}

} /* namespace pso */
