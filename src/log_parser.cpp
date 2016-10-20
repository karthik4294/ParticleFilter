#include <log_parser.h>

using namespace std;

LogParser::LogParser(std::string filename)
{
  log = new Log;
  readLog(filename);

  max_x = INT_MAX;
  max_y = INT_MAX;

  min_x = INT_MIN;
  min_y = INT_MIN;
}

void LogParser::readLog(std::string file) {

  // read every line and put it into a datastructure

  std::ifstream fin(file.c_str());

  std::string line, ch;
  int count = 0;
  char sensor_type;
  double val;

  while (getline(fin, line) && count <1)
  {
    istringstream sin(line);
    std::vector<double> temp_vec;

    sin >> sensor_type;
    log->sensor_type.push_back(sensor_type);
    printf("sensor_type is = %c", sensor_type);


    while (sin >> val)
    {
      temp_vec.push_back(val);
      //printf("double value is = %f", val);
    }

    //printf("loaded all doubles \n");
    log->sensor_input.push_back(temp_vec);
    count++;
  }

log->size = count;

printf("size of log = %d\n\n", log->size);
}

void LogParser::printLog() {
}

void LogParser::displayLog() {

	cv::Mat image = cv::Mat::zeros(map_->grid_size, map_->grid_size, CV_32FC1);

	for(int i = 0; i < image.rows; i++){
		for(int j = 0; j < image.cols; j++){

			if(map_->grid[i][j] > 0){
				image.at<float>(i,j) = map_->grid[i][j];
			}
		}
	}

	cv::imshow("Map", image);
	cv::waitKey(0);
}


