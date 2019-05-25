#pragma once
#define _USE_MATH_DEFINES

#include <math.h>
#include <stdlib.h>
#include <limits>
#include "Particle.h"


namespace pso {

	// Test functions
	struct Testfunction {
		virtual double operator()(Particle &particle) = 0;
		virtual ~Testfunction() {}
	};

	struct Rastrigin : public Testfunction {
		double operator()(Particle &particle);
	};

	struct Ackley : public Testfunction {
		double operator()(Particle &particle);
	};

	struct Sphere : public Testfunction {
		double operator()(Particle &particle);
	};

	struct Booth : public Testfunction {
		double operator()(Particle &particle);
	};

	struct Himmelblau : public Testfunction {
		double operator()(Particle &particle);
	};

	// Swarm
	class Swarm	{
	public:
		const static int NPARTICLES = 50;
		const static int MAX_ITERATION = 100;

		double m_gbestX;
		double m_gbestY;
		double m_gbestFitness = DBL_MAX;

		double m_c1 = 1.49445;
		double m_c2 = 1.49445;
		double m_w = 0.729;

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
		void update(int elapsed);
		const Particle * const collect() { return m_pParticles; };

		void init(double xUpperBound, double xLowerBound, double yUpperBound, double yLowerBound, Testfunction &testfunction);
		void optimize(int elapsed, Testfunction &testfunction);
		void fit(Particle &particle, Testfunction &testfunction);
	};

	
} /* namespace pso */
