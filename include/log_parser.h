#pragma once
#include <standard_includes.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

struct Log{

	int size;
	std::vector<char> sensor_type;
	std::vector<std::vector<double>> sensor_input;

  int max_x, min_x, max_y, min_y;
};

class LogParser{

public:

	LogParser(std::string filename);
	void readLog(std::string file);
	void displayLog();
	void printLog();
	//void getMap(Map* map);

private:

	Log *log;

};
