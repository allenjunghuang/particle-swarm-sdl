#include "Optimizer.h"


namespace pso {
	Optimizer::Optimizer() : m_elapsed(0) {
		m_pParticles = new Particle[NPARTICLES];
	}

	Optimizer::~Optimizer() {
		delete[] m_pParticles;
	}


}
