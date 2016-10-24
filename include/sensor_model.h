//Sensor model
#ifndef SENSOR_MODEL_H
#define SENSOR_MODEL_H

#include <standard_includes.h>
#include <map.h>

namespace sensor_model {
	class LidarModel {

		public:
		//public functions
		
		LidarModel(double max_range, double std_dev, double z_hit,
			       double z_short, double lambda_short, double z_max,
			       double z_rand);
		
		void updateWeight(ps::ParticleState* particle,
						  const std::vector<double>* lidar_ranges);

		private:

		//Private variables

		//Maximum range of the sensor
		double max_range_;

		//Standard deviation of the measurements
		double std_dev_;

		//Weight for correct hits
		double z_hit_;

		//Weight for transient obstacles and the intrinsic parameter to tune
		//it
		double z_short_;
		double lambda_short_;

		//Weight for max_range readings
		double z_max_;

		//Weight for random issues
		double z_rand_;

		//Private functions

		//get p_hit
		double getPHit(double ideal_range, double lidar_range);

		//get p_short
		double getPShort(double ideal_range, double lidar_range);

		//get p_max
		double getPMax(double lidar_range);

		//get p_rand
		double getPRand(double lidar_range);

	};
}

#endif
