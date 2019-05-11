#pragma once
#include "Particle.h"

namespace pso {
	class Swarm	{ //members are default private in class
	public:
		const static int NPARTICLES = 5000;

	private:
		Particle *m_pParticles;
		int m_elapsed;
	public:
		Swarm();
		virtual ~Swarm();
		void update(int elapsed);
		const Particle * const getParticles() { return m_pParticles; };
	};
} /* namespace pso */
