#pragma once

namespace pso {

	struct Particle { //members are default public in struct

		double m_x; //let the variable public for the sake of efficiency
		double m_y;
		double m_xspeed;
		double m_yspeed;
		double m_velocity;
		double m_angle;

	public:
		Particle();
		virtual ~Particle();
		void update(int interval);
		void bounce();
	};
} /* namespace pso */