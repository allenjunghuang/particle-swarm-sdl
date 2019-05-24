#include "Swarm.h"

namespace pso {

	Swarm::Swarm() : m_elapsed(0) {
		m_pParticles = new Particle[NPARTICLES];
	}

	Swarm::~Swarm() {
		delete [] m_pParticles;
	}

	void Swarm::burst(int elapsed) {
		int interval = elapsed - this->m_elapsed;

		for (int i = 0; i < Swarm::NPARTICLES; i++) {
			m_pParticles[i].burst(interval);

			if (m_pParticles[i].m_x <= m_xLowerBound || m_pParticles[i].m_x >= m_xUpperBound) {
				m_pParticles[i].m_x = 0;
			}
			if (m_pParticles[i].m_y <= m_yLowerBound || m_pParticles[i].m_y >= m_yUpperBound) {
				m_pParticles[i].m_y = 0;
			}
		}
		this->m_elapsed = elapsed;
	}

	void Swarm::init(double xUpperBound, double xLowerBound, double yUpperBound, double yLowerBound) {
		m_xUpperBound = xUpperBound;
		m_xLowerBound = xLowerBound;
		m_yUpperBound = yUpperBound;
		m_yLowerBound = yLowerBound;
		

		for (int i = 0; i < Swarm::NPARTICLES; i++) {
			m_pParticles[i].init(m_xUpperBound, m_xLowerBound, m_yUpperBound, m_yLowerBound);

			if (m_pParticles[i].m_bestFitness < this->m_gbestFitness) {
				this->m_gbestFitness = m_pParticles[i].m_bestFitness;
				this->m_gbestX = m_pParticles[i].m_bestX;
				this->m_gbestY = m_pParticles[i].m_bestY;
			}
		}
	}

	void Swarm::optimize(int elapsed) {
		int interval = elapsed - this->m_elapsed;

		for (int i = 0; i < Swarm::NPARTICLES; i++) {
			m_pParticles[i].optimize(m_c1, m_c2, m_gbestX, m_gbestY, interval);

			if (m_pParticles[i].m_bestFitness < this->m_gbestFitness) {
				this->m_gbestFitness = m_pParticles[i].m_bestFitness;
				this->m_gbestX = m_pParticles[i].m_bestX;
				this->m_gbestY = m_pParticles[i].m_bestY;
			}
		}
		this->m_elapsed = elapsed;
	}

} /* namespace pso */