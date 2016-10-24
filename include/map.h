#pragma once
#include <standard_includes.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


#include <particle_state.h>

using namespace cv;
using namespace std;
using namespace ps;

class Map{

public:

	Map(std::string filename);

	void readMap(std::string file);
	void printMap();
	void displayMap();
	Map *getMap(){
		return this;
	}
	Mat getGrid(){
		return grid;
	}
	std::vector<std::pair<double, double>> getFreeSpace(){
		return free_space_;
	}
	
	void visualizeParticles(vector<ParticleState>* particle_list);
  	void visualizePoints(vector<Mat>* points_list);

private:

	int size_x;
	int size_y;
	int res;
	int grid_size;
	Mat grid;
	Mat grid_disp_;
	std::vector<std::pair<double, double>> free_space_;
};
