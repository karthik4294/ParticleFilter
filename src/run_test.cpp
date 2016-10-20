#include <iostream>
#include <map.h>
#include <particle.h>
#include <log.h>

using namespace std;
using namespace cv;

int main(int argc , char *argv[]){

  //Map *map = new Map("./data/map/wean.dat");

  //Particle *p;
  //vector<Particle> *particle_list = new vector<Particle>;

  //int x, y, theta;

  //int max = 800;
  //int min = 0;
    
  //for (int i = 0; i < 100; i ++) {
    //x = min + rand() % (max - min);
    //y = min + rand() % (max - min);

    //p = new Particle(x, y, 0);
    //particle_list->push_back(*p);
  //}
  //map->visualizeParticles(particle_list);

  //for(std::vector<Particle>::iterator it = particle_list->begin(); it != particle_list->end(); ++it) {
    //it->move(2.0,2.0, 0.0);
  //}
  //map->visualizeParticles(particle_list);
  //
  Mat a;
  Log *log = new Log("./data/log/robotdata1.log");
  a = log->getNextOdom();
  a = log->getNextLidar();
  a = log->getNextLidar();

 	return 0;
}
