#include <standard_includes.h>
#include <map.h>
#include <log.h>
#include <robot_state.h>
#include <particle_state.h>
#include <sampler.h>
#include <motion_model.h>
#include <sensor_model.h>

int main(int argc , char *argv[]){
  data::Log* log = new data::Log("../data/log/robotdata1.log");
  Map *map = new Map("../data/map/wean.dat");	
  //Construct the sensor model
  sensor_model::LidarModel* sensor = new sensor_model::LidarModel(
                                         log->getMaxRange(), 0.1, 5.0, 2.0, 2.0,
                                         1.5, 0.5);
  //Testing if the file loaded ok
  for (int i = 0; i < log->laserCount(); i++) {
    data::lidar* lidar_val;
    log->getLidar(i, lidar_val);
    std::vector<int> ranges = lidar_val->ranges;
    printf("%zu\n", ranges.size());
  } 
  
  //map->displayMap();

  //ps::ParticleState particle_state(2.0, 3.0, 0.0, 5.0);

  // ps::ParticleState news = particle_state.rotate(M_PI);

  // vector<ParticleState> *particle_list = new vector<ParticleState>;

  // particle_list->push_back(particle_state);
  // map->visualizeParticles(particle_list);

  // particle_list->clear();
  // ps::ParticleState new_particle(200.0, 300.0, 0.0, 5.0);
  // particle_list->push_back(new_particle);
  // map->visualizeParticles(particle_list);

  int num_particles = 1;

  sp::Sampler* sp = new sp::Sampler(map, num_particles);
  
  mm::MotionModel *mm = new mm::MotionModel();

  std::vector<ps::ParticleState> particles;
  sp->sampleUniform(particles);  

  map->visualizeParticles(&particles);

  std::vector<ps::ParticleState> new_particles;

  new_particles = mm->applyMotionModel(particles, 0);

  map->visualizeParticles(&new_particles);

  new_particles = mm->applyMotionModel(new_particles, 0);

  map->visualizeParticles(&new_particles);

  return 0;
}
