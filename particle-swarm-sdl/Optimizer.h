#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include "Particle.h"

namespace pso {
	class Optimizer
	{
	public:
		Optimizer();
		virtual ~Optimizer();
	    double fitness(Particle& particle);
	};
}