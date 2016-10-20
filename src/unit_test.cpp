#include <iostream>
#include <map.h>
#include <particle.h>
#include <log.h>

using namespace std;
using namespace cv;

int main(int argc , char *argv[]){

  Mat a;
  Log *log = new Log("./data/log/robotdata1.log");
  a = log->getNextOdom();
  a = log->getNextLidar();
  a = log->getNextLidar();

 	return 0;
}
