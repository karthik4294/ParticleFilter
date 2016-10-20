#include <iostream>
#include <map.h>
#include <particle.h>
#include <log_parser.h>

int main(int argc , char *argv[]){

  //Map *map = new Map("./data/map/test.dat");
  Map *map = new Map("./data/map/wean.dat");
  //map->printMap();
  map->displayMap();

  Particle *p1 = new Particle();
  vector<Particle> *particle_list;
  map->visualizeParticles(particle_list);
 	return 0;
}
