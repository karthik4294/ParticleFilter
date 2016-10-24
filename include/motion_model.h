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
		std::vector<ps::ParticleState> applyMotionModel(std::vector<ps::ParticleState> particles, int iter_num);
		Eigen::Vector2f sampleNormalDist(Eigen::Vector2f p, double theta);
	private:

		utils::UtilFunctions *utils_ = new utils::UtilFunctions();
	};
};

#endif