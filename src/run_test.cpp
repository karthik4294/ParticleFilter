#include <standard_includes.h>
#include <map.h>
#include <log.h>
#include <robot_state.h>
#include <particle_state.h>
#include <sampler.h>
#include <motion_model.h>
#include <sensor_model.h>

int main(int argc , char *argv[]){
  //Read Data
  data::Log* log = new data::Log("../data/log/robotdata1.log");
  std::vector<double> time_stamps = log->getTimeStamps();

  //Construct the map
  Map *map = new Map("../data/map/wean.dat");	
  //Construct the sensor model
  sensor_model::LidarModel* sensor = new sensor_model::LidarModel(
                                         log->getMaxRange(), 0.1, 5.0, 2.0, 2.0,
                                         1.5, 0.5);
  //Construct the sampler and sample initial points
  int num_particles = 1;
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
