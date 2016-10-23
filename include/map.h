#pragma once
#include <standard_includes.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <particle_state.h>

using namespace cv;
using namespace std;
using namespace ps;


class Map{

public:

	Map(std::string filename);

	int size_x;
	int size_y;
	int res;
	int grid_size;
	Mat grid;

	void readMap(std::string file);
	void printMap();
	void displayMap();
	void getMap(Map* map);

  void visualizeParticles(vector<ParticleState>* particle_list);
  void visualizePoints(vector<Mat>* points_list);
};
