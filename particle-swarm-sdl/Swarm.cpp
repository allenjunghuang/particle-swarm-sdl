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

			if (m_pParticles[i].m_x <= m_xLowerBound || m_pParticles[i].m_x >= m_xUpperBound) {
				m_pParticles[i].m_x = 0;
			}
			if (m_pParticles[i].m_y <= m_yLowerBound || m_pParticles[i].m_y >= m_yUpperBound) {
				m_pParticles[i].m_y = 0;
			}
		}
		this->m_elapsed = elapsed;
	}

	void Swarm::init(double xUpperBound, double xLowerBound, double yUpperBound, double yLowerBound, Testfunction &testfunction) {
		m_xUpperBound = xUpperBound;
		m_xLowerBound = xLowerBound;
		m_yUpperBound = yUpperBound;
		m_yLowerBound = yLowerBound;

		for (int i = 0; i < Swarm::NPARTICLES; i++) {
			m_pParticles[i].m_x = (xUpperBound - xLowerBound) / 2 * ((2.0*rand() / RAND_MAX) - 1) + (xUpperBound + xLowerBound) / 2;
			m_pParticles[i].m_y = (yUpperBound - yLowerBound) / 2 * ((2.0*rand() / RAND_MAX) - 1) + (yUpperBound + yLowerBound) / 2;
			m_pParticles[i].m_xspeed = (xUpperBound - xLowerBound) / 2 *((2.0*rand() / RAND_MAX) - 1);
			m_pParticles[i].m_yspeed = (yUpperBound - yLowerBound) / 2 *((2.0*rand() / RAND_MAX) - 1);
			
			// fit
			fit(m_pParticles[i], testfunction);
			// initial particle best position
			m_pParticles[i].m_bestFitness = m_pParticles[i].m_fitness;
			m_pParticles[i].m_bestX = m_pParticles[i].m_x;
			m_pParticles[i].m_bestY = m_pParticles[i].m_y;

			// update swarm best position
			if (m_pParticles[i].m_bestFitness < this->m_gbestFitness) {
				this->m_gbestFitness = m_pParticles[i].m_bestFitness;
				this->m_gbestX = m_pParticles[i].m_bestX;
				this->m_gbestY = m_pParticles[i].m_bestY;
			}
		}
	}

	void Swarm::optimize(int elapsed, Testfunction &testfunction) {
		int interval = elapsed - this->m_elapsed;

		for (int i = 0; i < Swarm::NPARTICLES; i++) {
			double r1 = (1.0*rand() / RAND_MAX);
			double r2 = (1.0*rand() / RAND_MAX);
			m_pParticles[i].m_xspeed = m_w * m_pParticles[i].m_xspeed + m_c1 * r1 * (m_pParticles[i].m_bestX - m_pParticles[i].m_x) + m_c2 * r2 * (m_gbestX - m_pParticles[i].m_x);
			m_pParticles[i].m_yspeed = m_w * m_pParticles[i].m_yspeed + m_c1 * r1 * (m_pParticles[i].m_bestY - m_pParticles[i].m_y) + m_c2 * r2 * (m_gbestY - m_pParticles[i].m_y);

			m_pParticles[i].m_x += m_pParticles[i].m_xspeed * interval;
			m_pParticles[i].m_y += m_pParticles[i].m_yspeed * interval;

			fit(m_pParticles[i], testfunction);

			// update particle best position
			if (m_pParticles[i].m_fitness < m_pParticles[i].m_bestFitness) {
				m_pParticles[i].m_bestFitness = m_pParticles[i].m_fitness;
				m_pParticles[i].m_bestX = m_pParticles[i].m_x;
				m_pParticles[i].m_bestY = m_pParticles[i].m_y;
			}
			// update swarm best position
			if (m_pParticles[i].m_bestFitness < this->m_gbestFitness) {
				this->m_gbestFitness = m_pParticles[i].m_bestFitness;
				this->m_gbestX = m_pParticles[i].m_bestX;
				this->m_gbestY = m_pParticles[i].m_bestY;
			}
		}
		this->m_elapsed = elapsed;
	}

	void Swarm::fit(Particle &particle, Testfunction &testfunction) { 
		particle.m_fitness = testfunction(particle); 
	}

	double Rastrigin::operator()(Particle &particle) {
		return (pow(particle.m_x, 2) - (10 * cos(2 * M_PI* particle.m_x)) + 10) +
		(pow(particle.m_y, 2) - (10 * cos(2 * M_PI* particle.m_y)) + 10);
	}
	
	double Ackley::operator()(Particle &particle) {
		return -20 * exp(-0.2*sqrt(0.5*(pow(particle.m_x, 2) + pow(particle.m_y, 2))))
			- exp(0.5*(cos(2 * M_PI* particle.m_x) + cos(2 * M_PI* particle.m_y)))
			+ exp(1) + 20;
	}

	double Sphere::operator()(Particle &particle) {
			return (pow(particle.m_x, 2) + pow(particle.m_y, 2));
	}

	double Booth::operator()(Particle &particle) {
		return pow((particle.m_x + particle.m_y - 7), 2)
			+ pow(2 * particle.m_x + particle.m_y - 5, 2);
	}

	double Himmelblau::operator()(Particle &particle) {
		return pow(pow(particle.m_x, 2) + particle.m_y - 11, 2)
			+ pow(particle.m_x + pow(particle.m_y, 2) - 7, 2);
	}

} /* namespace pso */