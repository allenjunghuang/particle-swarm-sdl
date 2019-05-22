#pragma once

#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <math.h>
#include "Particle.h"

namespace pso {
	class Optimizer
	{
	public:
		const static int NPARTICLES = 500;
		static double m_xgbest;
		static double m_ygbest;
		static double m_gfitness;
	private:
		Particle * m_pParticles;
		int m_elapsed;
	public:
		Optimizer();
		virtual ~Optimizer();
		virtual void init(Particle& particle) = 0;
	};

	class Sphere : public Optimizer {
		// Sphere function, search domain [-inf; inf], global min f(0) = 0
	public:
		void init(Particle& particle) {
			particle.m_x = 10*(2.0*rand() / RAND_MAX) - 1; // (-10, 10)
			particle.m_y = 10*(2.0*rand() / RAND_MAX) - 1;
			particle.m_xspeed = 0.5*((2.0*rand() / RAND_MAX) - 1); // (-0.5, 0.5)
			particle.m_yspeed = 0.5*((2.0*rand() / RAND_MAX) - 1);
		}

		double fit(const Particle& particle) {
			return sqrt(pow(particle.m_x, 2) + pow(particle.m_y, 2));
		
		}
	};

	class Ackley : public Optimizer {
		// Ackley function, search domain [-5; 5], global min f(0) = 0
	public:
		void init(Particle& particle) {
			particle.m_x = 5*(2.0*rand() / RAND_MAX) - 1; // (-5, 5)
			particle.m_y = 5*(2.0*rand() / RAND_MAX) - 1;
			particle.m_xspeed = 0.5*((2.0*rand() / RAND_MAX) - 1); // (-0.5, 0.5)
			particle.m_yspeed = 0.5*((2.0*rand() / RAND_MAX) - 1);
			particle.m_pfitness = fit(particle);
		}

		double fit(const Particle& particle) {
			double dist = sqrt(pow(particle.m_x, 2) + pow(particle.m_y, 2));

			return sin(dist) / dist + exp(0.5* cos(2 * M_PI * particle.m_x) + 0.5  * cos(2 * M_PI * particle.m_y)) - exp(1);
		}
	};

	class Rastrigin {
		// Rastrigin function, search domain [-5.12, 5.12], global min f(0) = 0
	public:
		void init(Particle& particle) {
			particle.m_x = 5.12*(2.0*rand() / RAND_MAX) - 1; // (-5.12, 5.12)
			particle.m_y = 5.12*(2.0*rand() / RAND_MAX) - 1;
			particle.m_xspeed = 0.5*((2.0*rand() / RAND_MAX) - 1); // (-0.5, 0.5)
			particle.m_yspeed = 0.5*((2.0*rand() / RAND_MAX) - 1);
		}

		double fit(const Particle& particle) {
			return (pow(particle.m_x, 2) - (10 * cos(2 * M_PI* particle.m_x)) + 10) +
				(pow(particle.m_y, 2) - (10 * cos(2 * M_PI* particle.m_y)) + 10);
		}
	};

}