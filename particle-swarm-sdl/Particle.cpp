#include "Particle.h"


namespace pso {

	Particle::Particle(): m_x(0), m_y(0) {
		m_angle = 2*M_PI*rand() / RAND_MAX;
		m_velocity = 0.0001 * rand() / RAND_MAX;
	}
	
	Particle::~Particle() {
	}

	void Particle::update(int interval) {

		m_xspeed = m_velocity * cos(m_angle);
		m_yspeed = m_velocity * sin(m_angle);

		m_x += m_xspeed * interval;
		m_y += m_yspeed * interval;
	}

} /* namespace pso */
