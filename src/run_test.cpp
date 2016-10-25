#include <standard_includes.h>
#include <map.h>
#include <log.h>
#include <robot_state.h>
#include <particle_state.h>
#include <sampler.h>
#include <motion_model.h>
#include <sensor_model.h>

int main(int argc , char *argv[]){
  std::string filename = argv[1];
  //Read config params
  
  /*Params is a vector of the form
    1. mm_std_xy
    2. mm_std_theta
    3. sensor_model_std
    4. z_hit
    5. z_short
    6. lambda_short
    7. z_max
    8. z_rand
  */
  std::vector<double> params;
  std::ifstream config_reader(filename);
  
  if(config_reader.good()) {
    std::string config_line;
    while(std::getline(config_reader, config_line)) {
        if(!isalpha(config_line[0])) {
            params.push_back(std::stod(config_line));
        }
    }
  }
    
  double mm_std_xy = params[0];
  double mm_std_theta = params[1];
  double sensor_model_std = params[2];
  double z_hit = params[3];
  double z_short = params[4];
  double lambda_short = params[5];
  double z_max = params[6];
  double z_rand = params[7];

  //Read Data
  data::Log* log = new data::Log("../data/log/robotdata1.log");
  std::vector<double> time_stamps = log->getTimeStamps();

  //Construct the map
  Map *map = new Map("../data/map/wean.dat");	
  //Construct the sensor model
  sensor_model::LidarModel* sensor = new sensor_model::LidarModel(
                                         log->getMaxRange(), sensor_model_std,
                                         z_hit, z_short, lambda_short, z_max,
                                         z_rand);
  //Construct the sampler and sample initial points
  int num_particles = 100;
  sp::Sampler* sp = new sp::Sampler(map, num_particles);
  std::vector<ps::ParticleState> particles;
  sp->sampleUniform(particles);  
  //Visualize the sampled particles
  map->visualizeParticles(&particles);
  //Construct the motion model
  mm::MotionModel *mm = new mm::MotionModel(log);
  
  //Now run the particle filter
  for(int iter = 0; iter < time_stamps.size(); iter++) {
    double time = time_stamps[iter];
    double next_time = time;
    //If the next time exists, set it to that
    if(iter < time_stamps.size() -1) {
      next_time = time_stamps[iter + 1];
    }

    //Now check if we need to do a sensor update
    if(log->isLidar(time)) {
      //Do sensor update and importance resampling
      //Candidate for parallelization
      for (int i = 0; i < num_particles; i++) {
        map->getIdealLidar(particles[i]);
        sensor->updateWeight(&particles[i], log->getLidar(time));
      }
      //Now resample the particles
      //sp->importanceResample(particles);

      //Visualize the resampled particles
      map->visualizeParticles(&particles);
    }

    //Now check if we need to apply motion model
    if(log->isOdom(time)) {
      //Apply motion model based on the current time and next time
      mm->applyMotionModel(particles, time, next_time);
    }

    //Visualize the new particles
    map->visualizeParticles(&particles);
  }




/*  std::vector<ps::ParticleState> new_particles;

  std::vector<ps::ParticleState> set;

  for(int i = 0; i < log->laserCount() - 1; i++){
	new_particles = mm->applyMotionModel(particles, i);
	particles = new_particles;
	set.insert(set.end(), new_particles.begin(), new_particles.end());
  }

  map->visualizeParticles(&set);*/


  return 0;
}
