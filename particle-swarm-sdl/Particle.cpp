#define _USE_MATH_DEFINES
#include "Particle.h"
#include <stdlib.h>
#include <math.h>

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

	void Particle::bounce() {
		m_x += m_xspeed;
		m_y += m_yspeed;

		if (m_x <= -1.0 || m_x >= 1.0) {
			m_xspeed = -m_xspeed;
		}
		if (m_y <= -1.0 || m_y >= 1.0) {
			m_yspeed = -m_yspeed;
		}
	}
} /* namespace pso */
