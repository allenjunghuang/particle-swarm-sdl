#include "Optimizer.h"


namespace pso {
	Optimizer::Optimizer() : m_elapsed(0) {
		m_pParticles = new Particle[NPARTICLES];
	}

	Optimizer::~Optimizer() {
		delete[] m_pParticles;
	}

	void Optimizer::update(int elapsed) {
		int interval = elapsed - this->m_elapsed;

		for (int i = 0; i < Optimizer::NPARTICLES; i++) {
			m_pParticles[i].update(interval);
		}
		this->m_elapsed = elapsed;
	}

}
