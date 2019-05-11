#include "Swarm.h"


namespace pso {

	Swarm::Swarm() : m_elapsed(0) {
		m_pParticles = new Particle[NPARTICLES];
	}

	Swarm::~Swarm() {
		delete [] m_pParticles;
	}

	void Swarm::update(int elapsed) {
		int interval = elapsed - this->m_elapsed;

		for (int i = 0; i < Swarm::NPARTICLES; i++) {
			m_pParticles[i].update(interval);
		}
		this->m_elapsed = elapsed;
	}

} /* namespace pso */