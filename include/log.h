#pragma once
#include <standard_includes.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

class Log{

public:

	int size, count;
  std::string line, ch;
  char sensor_type;
  float val;
  std::ifstream fin;

	Log(std::string filename);

	void displayLog();
	void printLog();
  
  Mat getNextOdom();
  Mat getNextLidar();
  

};
