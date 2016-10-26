#include <standard_includes.h>
#include <map.h>
#include <log.h>
#include <robot_state.h>
#include <particle_state.h>
#include <sampler.h>
#include <motion_model.h>
#include <sensor_model.h>
#include <chrono>

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
    9. num_particles;
    10. Resampling randomization.
    11. Max range of lidar
    12. Comb sampler distance
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
  int num_particles = (int) params[8];
  double resampling_randomization = params[9];
  double max_range = params[10];
  double comb_dist = params[11];
  //Read Data
  data::Log* log = new data::Log("../data/log/robotdata1.log");
  std::vector<double> time_stamps = log->getTimeStamps();

  //Construct the map
  Map *map = new Map("../data/map/wean.dat", max_range);	
  //Construct the sensor model
  sensor_model::LidarModel* sensor = new sensor_model::LidarModel(
      max_range, sensor_model_std,
      z_hit, z_short, lambda_short, z_max,
      z_rand);
  //Construct the sampler and sample initial points
  sp::Sampler* sp = new sp::Sampler(map, num_particles);
  std::vector<ps::ParticleState> particles;
  sp->sampleUniform(particles);  
  //Visualize the sampled particles
  map->visualizeParticles(&particles, 1);
  //Construct the motion model
  mm::MotionModel *mm = new mm::MotionModel(log, mm_std_xy, mm_std_theta);
  //Delete Later
  printf("Max Range is %d \n", log->getMaxRange());
  //Delete later
  using namespace std::chrono;
  typedef std::chrono::high_resolution_clock Clock;
  typedef std::chrono::duration<double> dsec;

  auto init_start = Clock::now();
  double init_time = 0;
  double sensor_update_time;
  auto sensor_update_start = Clock::now();

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
      sensor_update_start = Clock::now();
      //Do sensor update and importance resampling
      //Candidate for parallelization
      //#pragma omp parallel for  
      for (int i = 0; i < num_particles; i++) {
        map->getIdealLidar(particles[i]);
      }

      for (int i = 0; i < num_particles; i++) {
        sensor->updateWeight(&particles[i], log->getLidar(time));
      }

      /*for(int i = 0; i<num_particles; i++) {
        cout<<"weight is :"<<particles[i].weight()<<endl;
        }
        getchar();*/
      //Now resample the particles
      //Possible speedup : pass a vector to add weights in place
      //sp->importanceResample(particles, resampling_randomization);
       sp->importanceCombResample(particles, comb_dist);
      printf("resampled for iter %d, %zu \n", iter, particles.size());

      //Visualize the resampled particles
      map->visualizeParticles(&particles, 1);

      init_time += duration_cast<dsec>(Clock::now() - init_start).count();
      printf("Time from start: %lf. ", init_time);

      sensor_update_time = duration_cast<dsec>(Clock::now() - sensor_update_start).count();
      printf("Sensor update duration: %lf.\n", sensor_update_time);



      //getchar();
    }

    //Now check if we need to apply motion model
    if(log->isOdom(time)) {
      //Apply motion model based on the current time and next time
      mm->applyMotionModel(particles, time, next_time);
      cout<<"applied motion model"<<endl;
      map->visualizeParticles(&particles, 0);
    }

    //Visualize the new particles

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
