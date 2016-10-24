#ifndef MOTION_MODEL_H
#define MOTION_MODEL_H

#include <standard_includes.h>
#include <util_functions.h>

#include <robot_state.h>
#include <particle_state.h>

namespace mm{

	class MotionModel{

	public:

		MotionModel();
		void applyModel(std::vector<ps::ParticleState> particles, double timestamp);

	private:

	};
};

#endif