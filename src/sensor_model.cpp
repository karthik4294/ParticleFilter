//Sensor Model source
#include <sensor_model.h>

namespace sensor_model {

	LidarModel::LidarModel(double max_range, double std_dev, double z_hit,
			       double z_short, double lambda_short, double z_max,
			       double z_rand) {
		
		max_range_ = max_range;
		std_dev_ = std_dev;
		z_hit_ = z_hit;
		z_short_ = z_short;
		lambda_short_ = lambda_short;
		z_max_ = z_max;
		z_rand_ = z_rand;
		//Delete Later
		printf("standard dev for sensor is %f \n", std_dev_);
		//Delete Later
		//Normalize
		
		double sum = z_hit_ + z_short_ + z_max_ + z_rand_;
		z_hit_ = z_hit_ / sum;
		z_short_ = z_short_ / sum;
		z_max_ = z_max_ / sum;
		z_rand_ = z_rand_ / sum;
	}

	void LidarModel::updateWeight(ps::ParticleState* particle,
	                              data::lidar* lidar) {
		//Re-initialize weight to 1
		particle->weight(1.0);

		std::vector<int>* lidar_ranges = lidar->ranges;
		std::vector<int>* ideal_ranges = particle->ranges();
		
		//Sanity check
		if(ideal_ranges->size() != lidar_ranges->size()) {
			printf("[SENSOR_MODEL_ERROR] Lidar range and ideal range size" 
				    "mismatch %zu, %zu \n", ideal_ranges->size(),
				  lidar_ranges->size());
			return;
		}
		/*printf("************* \n");
		printf("New Particle \n");
		printf("************* \n");*/
		for(int i = 0; i < lidar_ranges->size(); i++) {

			//Get the ray-casted range
			int ideal_range = ideal_ranges->at(i);

			//Get the measured range
			int lidar_range = lidar_ranges->at(i);
			//printf("\t Lidar range: %d, Ideal range: %d \n", ideal_range, lidar_range);
			//Calcualate p_hit
			double p_hit = getPHit(ideal_range, lidar_range);

			//Calculate p_short;
			double p_short = getPShort(ideal_range, lidar_range);

			//Calculate p_max
			double p_max = getPMax(lidar_range);

			//Calculate p_rand
			double p_rand = getPRand(lidar_range);

			//Find the total weighted probability
			double p = z_hit_*p_hit + z_short_*p_short + z_max_*p_max
			           + z_rand_*p_rand;
			//printf("Probability is %f \n", p);  
			//Update the particle weight
			particle->weight(particle->weight()*p);
		}
		if(particle->weight() > 0.001) {
			//printf("weight for particle %f \n", particle->weight());
			//getchar();
		}
		
	}

	//Function to get the p_hit according to gaussian
	double LidarModel::getPHit(int ideal_range, int lidar_range) {
		//Transform lidar_range to a normal distribution variable
		//z = x - mu / sigma
		//Integrate over the density function to get the probability
		double sum_res = 0.01; //Discretization for calculating sum
		double probability = 0.0;
		for (double i = lidar_range - 0.5; i < lidar_range + 0.5;
		     i += sum_res) {
			double norm_var = (i - ideal_range)/std_dev_;	
			double probability_density = 
			               (exp(-0.5*norm_var*norm_var)/sqrt(2*PI))/std_dev_;
			probability += probability_density*sum_res;
		}
		return (probability);
	}

	//Function to get p_short
	double LidarModel::getPShort(int ideal_range, int lidar_range) {
		
		//Check if eligible
		if(lidar_range < 0 || lidar_range > ideal_range) {
			return 0.0;
		}

		//Now calculate non-zero probability
		
		//Calculate normalizer
		double eta = 1/(1 - exp(-lambda_short_*ideal_range));

		//Calculate the probability
		double sum_res = 0.01; //Discretization for calculating sum
		double probability = 0.0;
		for (double i = lidar_range - 0.5; i < lidar_range + 0.5;
		     i += sum_res) {
			double norm_var = (lidar_range - ideal_range)/std_dev_;	
			double probability_density = 
			                         eta*lambda_short_*exp(-lambda_short_*i);
			probability += probability_density*sum_res;
		}
		return (probability);
	}

	//Function to get p_max
	double LidarModel::getPMax(int lidar_range) {
		
		if(lidar_range == max_range_) {
			return 1.0;
		}
		else {
			return 0.0;
		}
	}

	//Function to get p_rand
	double LidarModel::getPRand(int lidar_range) {
		
		if(lidar_range < 0 || lidar_range > max_range_) {
			return 0.0;
		}
		else {
			return (1/max_range_);
		}
	}
}
