//Sensor Model source
#include <sensor_model.h>

namespace sensor_model {

	LidarModel::LidarModel(double max_range, double std_dev, double z_hit,
			       double z_short, double z_max, double z_rand) {
		
		max_range_ = max_range;
		std_dev_ = std_dev;
		z_hit_ = z_hit;
		z_short_ = z_short;
		z_max_ = z_max;
		z_rand_ = z_rand;
	}

	LidarModel::updateWeight(ps::ParticleState* particle) {
		double particle-> = 0; //This is the initial weight of the particle
	}
}
