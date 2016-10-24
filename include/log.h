#ifndef LOG_H_
#define LOG_H_
#include <standard_includes.h>
namespace data {
    
    struct odom {
        double x;
        double y;
        double theta;
        double t; //time
    };

    struct lidar {
        double t; //time
        std::vector<int> ranges;
    };

    class Log{

    public:
        Log(std::string filename);
        void getLidar(int iter, lidar* lidar_val) const;
        void getOdom(int iter, std::vector<odom*>& odoms) const;
    private:
        std::vector<lidar*> lidarScans_;
        std::map<double, odom*> odomVals_;
    	std::ifstream fin_;

    };
}
#endif