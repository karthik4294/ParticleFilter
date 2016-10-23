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

	void readMap(std::string file);
	void printMap();
	void displayMap();
	Map *getMap(){
		return this;
	}
	Mat getGrid(){
		return grid;
	}
	std::vector<std::pair<int, int>> getFreeSpace(){
		return free_space_;
	}

private:

	int size_x;
	int size_y;
	int res;
	int grid_size;
	Mat grid;
	std::vector<std::pair<int, int>> free_space_;


	void visualizeParticles(vector<ParticleState>* particle_list);
};
