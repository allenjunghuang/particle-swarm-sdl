#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>

namespace pso {

	struct Particle { //members are default public in struct

		double m_x; //let the variable public for the sake of efficiency
		double m_y;
		double m_xspeed;
		double m_yspeed;
		double m_velocity;
		double m_angle;
		double m_fitness;

		double m_bestX;
		double m_bestY;
		double m_bestFitness;

	public:
		Particle();
		virtual ~Particle();
		void update(int interval);
	};

} /* namespace pso */