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
		void burst(int interval);

		void init(double xUpperBound, double xLowerBound, double yUpperBound, double yLowerBound);
		void optimize(double c1, double c2, double xbest, double ybest, int interval);
		double fit(double x, double y);
	};
} /* namespace pso */