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
  int num_threads = thread::hardware_concurrency();
  clock_t start = clock();
  
  clock_t end = clock();
  cout<<"Generated thread pool in "<<(double)(end-start)/CLOCKS_PER_SEC<<" s"<<endl;
  //Read config params
  cout<<"small value is "<<SMALL_VALUE<<endl;
  cout<<"large negative is "<<LARGE_NEGATIVE<<endl;
  //getchar();
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
    12. Comb dist
  */
  std::vector<double> params;
  std::ifstream config_reader(filename);
  
  if(config_reader.good()) {
    std::string config_line;
    while(std::getline(config_reader, config_line)) {
        if(!isalpha(config_line[0])) {
            cout<<config_line<<endl;
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
  double bracket = params[12];
  //Read Data
  //data::Log* log = new data::Log("../data/log/robotdata1.log");
  data::Log* log = new data::Log("../data/log/ascii-robotdata4.log");
  std::vector<double> time_stamps = log->getTimeStamps();

  //Construct the map
  Map *map = new Map("../data/map/wean.dat", max_range);	
  //Construct the sensor model
  sensor_model::LidarModel* sensor = new sensor_model::LidarModel(
                                         max_range, sensor_model_std,
                                         z_hit, z_short, lambda_short, z_max,
                                         z_rand, bracket);
  //Construct the sampler and sample initial points
  num_particles = 1;
  sp::Sampler* sp = new sp::Sampler(map, num_particles);
  std::vector<ps::ParticleState> particles;
  ps::ParticleState p;
  p.x(4000);
  p.y(4100);
  p.theta(-1.57);
  p.setRanges();
  p.setRayTips(max_range);
  particles.push_back(p);
  //sp->sampleUniform(particles, max_range);  
  //Visualize the sampled particles
  //map->visualizeParticles(&particles, 1);
  
  //Construct the motion model
  mm::MotionModel *mm = new mm::MotionModel(log, mm_std_xy, mm_std_theta);
  //Delete Later
  printf("Max Range is %d \n", log->getMaxRange());
  //Delete later
  //Now run the particle filter
  cout<<"Now beginning"<<endl;
  //getchar();
  auto begin = std::chrono::system_clock::now();
  for(int iter = 0; iter < time_stamps.size(); iter++) {
    ctpl::thread_pool pool1(num_threads);
    auto start = std::chrono::system_clock::now();
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
      //#pragma omp parallel for  
      for (int i = 0; i < num_particles; i++) {
        //clock_t first = clock();
        //Map* map_temp = new Map(map);
        data::lidar* lidar = log->getLidar(time);
        map->getIdealLidarVis(&particles[i], lidar);
        //pool1.push(std::bind(&Map::getIdealLidar, map,&particles[i]));
        //clock_t second = clock();
        //cout<<"get ideal lidar took "<<(double)(second-first)/CLOCKS_PER_SEC<<" s"<<endl;
      }
      //Wait for all the threads to finish and then stop
      pool1.stop(true);
      ctpl::thread_pool pool2(num_threads);
      for(int i = 0; i < num_particles; i++) {
        //clock_t second = clock();
        //ps::ParticleState particle = particles[i];
        //ps::ParticleState* particle_ptr = &particle;
        data::lidar* lidar = log->getLidar(time);
        sensor->updateWeight(&particles[i], lidar);
        //pool2.push(std::bind(&sensor_model::LidarModel::updateWeight,
        //                   sensor, &particles[i], lidar));
        //clock_t third = clock();
        //cout<<"update weights took "<<(double)(third - second)/CLOCKS_PER_SEC<<" s"<<endl;
      }
      pool2.stop(true);
      /*for(int i = 0; i<num_particles; i++) {
            cout<<"weight is :"<<particles[i].weight()<<endl;
        }
      getchar();*/
      //Now resample the particles
      //Possible speedup : pass a vector to add weights in place
      //map->visualizeParticles(&particles, 1);
      //getchar();
      //sp->importanceResample(particles, resampling_randomization);
      // sp->importanceCombResample(particles, comb_dist);
      //sp->importanceResample(particles, resampling_randomization);
      //printf("resampled for iter %d, %zu \n", iter, particles.size());
      //Visualize the resampled particles
      //map->visualizeParticles(&particles, 1);

      //getchar();
    }

    //Now check if we need to apply motion model
    if(log->isOdom(time)) {
      //Apply motion model based on the current time and next time
      mm->applyMotionModel(particles, time, next_time);
      //cout<<"applied motion model"<<endl;
      //map->visualizeParticles(&particles, 0);
    }
    auto end = std::chrono::system_clock::now();
    //Visualize the new particles
  auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
  auto total_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin);
   //cout<<"Iteration number "<<(iter+1)<<" took "<<elapsed.count()<<" ms"<<endl;
   //cout<<(iter+1)<<" iterations done in "<<total_elapsed.count()<<" ms"<<" ,average time is "
                                     //<<total_elapsed.count()/(iter+1)<<" ms/iter"<<endl;                                      
   //getchar();
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
