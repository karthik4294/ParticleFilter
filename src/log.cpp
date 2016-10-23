#include <log.h>

using namespace std;
using namespace cv;

Log::Log(std::string filename) : fin(filename.c_str()) {
}

//void Log::readLog(std::string file) {

//// read every line and put it into a datastructure
//std::ifstream fin(file.c_str());

//std::string line, ch;
//int count = 0;
//char sensor_type;
//double val;

//while (getline(fin, line) && count <1)
//{
//istringstream sin(line);
//std::vector<double> temp_vec;

//sin >> sensor_type;
//log->sensor_type.push_back(sensor_type);
//printf("sensor_type is = %c", sensor_type);


//while (sin >> val)
//{
//temp_vec.push_back(val);
////printf("double value is = %f", val);
//}

////printf("loaded all doubles \n");
//log->sensor_input.push_back(temp_vec);
//count++;
//}

//log->size = count;

//printf("size of log = %d\n\n", log->size);
//}

Mat Log::getNextOdom() {

  Mat odom_reading;

  // loop until we get Odom entry
  while (getline(fin, line)) {
    istringstream sin(line);
    sin >> sensor_type;

    if (sensor_type == 'O') {
      // only read first 3 values, skip the timestamp
      for (int i = 0; i < 3; i++) {
        sin >> val;
        odom_reading.push_back(val);
        //printf("double value is = %f", val);
      }
      break;
    }
  }

  return odom_reading;
  // how do you return empty? TODO
}

Mat Log::getNextLidar() {

  Mat lidar_reading;

  // loop until we get lidar entry
  while (getline(fin, line)) {
    istringstream sin(line);
    sin >> sensor_type;

    if (sensor_type == 'L') {
      // only read first 185 values, skip the timestamp
      for (int i = 0; i < 186; i++) {
        sin >> val;
        lidar_reading.push_back(val);
        // print timestamp
        //if (i == 186)
        //printf("val = %f at count =%d\n", val, i);
      }
      break;
    }
  }

  return lidar_reading;
}
