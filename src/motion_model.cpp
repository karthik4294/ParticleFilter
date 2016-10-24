#include <motion_model.h>

using namespace utils;

namespace mm{

MotionModel::MotionModel()
{
	utils_ = new UtilFunctions();
}

std::vector<ps::ParticleState> MotionModel::applyMotionModel(std::vector<ps::ParticleState> 
											particles, int iter_num){


	double x0 = 0;
	double y0 = 0;
	double th0 = 0;
	double x1 = 100;
	double y1 = 0;
	double th1 = 1.57;

	// Change
	double x_diff = x1 - x0;
	double y_diff = y1 - y0;
	double theta_diff = th1 - th0;

	Eigen::Vector2f diff_vec(x_diff, y_diff);

	Eigen::Vector2f robot_diff_vec = utils_->rotateVector(diff_vec, -th0); //check the angle of rotation

	// the main loop of the motion model
	for(int i = 0; i < particles.size(); i++){
				
		double rot = particles[i].theta();
		Eigen::Vector2f p_diff = utils_->rotateVector(robot_diff_vec, rot);

		// Eigen::Vector2f s_p_diff = sampleNormalDist(p_diff, theta_diff);

		particles[i].x(particles[i].x() + p_diff(0));
		particles[i].y(particles[i].y() + p_diff(1));
		particles[i].theta(theta_diff);

	}

	return particles;

}

Eigen::Vector2f sampleNormalDist(Eigen::Vector2f p, double theta){




}

}