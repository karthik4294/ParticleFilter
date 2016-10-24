#include <motion_model.h>

using namespace utils;

namespace mm{

MotionModel::MotionModel()
:
std_dev_(0.1)
{
	utils_ = new UtilFunctions();
}

std::vector<ps::ParticleState> MotionModel::applyMotionModel(std::vector<ps::ParticleState> 
											particles, int iter_num){


	double x0 = 0;
	double y0 = 0;
	double th0 = 1.57;
	double x1 = 100;
	double y1 = 0;
	double th1 = 0;

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

		Eigen::Vector3f s_p_diff = sampleNormalDist(p_diff, theta_diff);

		particles[i].x(particles[i].x() + s_p_diff(0));
		particles[i].y(particles[i].y() + s_p_diff(1));
		particles[i].theta(particles[i].theta() + s_p_diff(2));

	}
	return particles;
}

Eigen::Vector3f MotionModel::sampleNormalDist(Eigen::Vector2f p, double theta){

	std::random_device rd;
    std::mt19937 gen(rd());
 
    std::normal_distribution<> d1(p(0), std_dev_);
    std::normal_distribution<> d2(p(1), std_dev_);
    std::normal_distribution<> d3(theta, std_dev_);

    Eigen::Vector3f norm_p(d1(gen), d2(gen), d3(gen));

    return norm_p;

}

}