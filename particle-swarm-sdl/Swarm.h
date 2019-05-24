#pragma once
#define _USE_MATH_DEFINES

#include <math.h>
#include <stdlib.h>
#include <limits>
#include "Particle.h"


namespace pso {
	class Swarm	{ //members are default private in class
	public:
		const static int NPARTICLES = 50;
		const static int MAX_ITERATION = 512;

		double m_gbestX;
		double m_gbestY;
		double m_gbestFitness = DBL_MAX;

		double m_c1 = 1.49445;
		double m_c2 = 1.49445;

		double m_xUpperBound = 1.0;
		double m_xLowerBound = -1.0;
		double m_yUpperBound = 1.0;
		double m_yLowerBound = -1.0;

	private:
		Particle *m_pParticles;
		int m_elapsed;

	public:
		Swarm();
		virtual ~Swarm();
		void burst(int elapsed);
		void init(double xUpperBound, double xLowerBound, double yUpperBound, double yLowerBound);
		void optimize(int elapsed);
		const Particle * const collect() { return m_pParticles; };
	};

	
} /* namespace pso */
