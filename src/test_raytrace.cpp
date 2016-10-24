#include <standard_includes.h>
#include <map.h>
#include <log.h>
#include <robot_state.h>
#include <particle_state.h>
#include <sampler.h>
#include <motion_model.h>

int main(int argc , char *argv[]){

  Map *map = new Map("../data/map/wean.dat");	
  ps::ParticleState new_particle(3650.0, 3000.0, 0, 5.0);
  map->raytrace(new_particle);

  return 0;
}
