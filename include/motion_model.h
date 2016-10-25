#ifndef MOTION_MODEL_H
#define MOTION_MODEL_H

#include <standard_includes.h>
#include <util_functions.h>

#include <robot_state.h>
#include <particle_state.h>
#include <log.h>

namespace mm{

	class MotionModel{

	public:

		MotionModel(data::Log *log);
		std::vector<ps::ParticleState> applyMotionModel(std::vector<ps::ParticleState> particles, int iter_num);
		Eigen::Vector3f sampleNormalDist(Eigen::Vector2f p, double theta);
	private:

		utils::UtilFunctions *utils_;
		data::Log *log_;
		double std_dev_;
	};
};

#endif