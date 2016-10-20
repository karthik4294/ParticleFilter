#include <iostream>
#include <map.h>
#include <particle.h>
#include <log_parser.h>

using namespace std;
using namespace cv;

int main(int argc , char *argv[]){

  //Map *map = new Map("./data/map/test.dat");
  Map *map = new Map("./data/map/wean.dat");
  //map->printMap();
  //map->displayMap();

  Particle *p;
  vector<Particle> *particle_list = new vector<Particle>;

  int x, y, theta;

  int max = 800;
  int min = 0;
    
  for (int i = 0; i < 100; i ++) {

    x = min + rand() % (max - min);
    y = min + rand() % (max - min);

    //printf("Particle %d x=%d y=%d\n", i, x, y);

    p = new Particle(x, y, 0);
    particle_list->push_back(*p);
  }

  map->visualizeParticles(particle_list);

 	return 0;
}
