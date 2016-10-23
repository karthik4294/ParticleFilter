#include <standard_includes.h>
#include <map.h>
#include <robot_state.h>
#include <particle_state.h>

int main(int argc , char *argv[]){

  Map *map = new Map("../data/map/wean.dat");	
  //map->displayMap();

  ps::ParticleState particle_state(2.0, 3.0, 0.0, 5.0);

  ps::ParticleState news = particle_state.rotate(M_PI);

  printf("New state %f %f %f\n", news.x(), news.y(), news.theta());

  vector<ParticleState> *particle_list = new vector<ParticleState>;

  particle_list->push_back(particle_state);
  map->visualizeParticles(particle_list);

  particle_list->clear();
  ps::ParticleState new_particle(200.0, 300.0, 0.0, 5.0);
  particle_list->push_back(new_particle);
  map->visualizeParticles(particle_list);

  return 0;
}
