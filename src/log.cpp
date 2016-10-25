#include <log.h>

namespace data {
    
    Log::Log(std::string filename) {
    	std::ifstream fin_(filename);
    	laserCount_ = 0;
    	odomCount_ = 0;
        max_range_ = 0;
        if(fin_.good()) {
        	std::string line_raw;
            while (getline(fin_, line_raw)) {
            	char data_type = line_raw[0];
                char* line = (char*) line_raw.c_str();
                std::istringstream iss(line_raw);
                std::string token;
                iss >> token;
                if (data_type == 'O') {
                    std::vector<std::string> odom_val_string;
                    odom* odom_val = new odom;
                    while(iss >> token) {
                        odom_val_string.push_back(token);
                    }
                    odom_val->x = std::stod(odom_val_string[0]);
                    odom_val->y = std::stod(odom_val_string[1]);
                    odom_val->theta = std::stod(odom_val_string[2]);
                    odom_val->t = std::stod(odom_val_string[3]);
                    //Add it to the map
                    odomVals_[odom_val->t] = odom_val;
                    odomCount_ ++;
                }

                else if (data_type == 'L') {
                    std::vector<std::string> lidar_val_string;
                    lidar* lidar_val = new lidar;
                    while(iss>>token) {
                        lidar_val_string.push_back(token);
                    }
                    lidar_val->t = std::stod(lidar_val_string.back());
                    for(int i = 6; i < lidar_val_string.size()-1; i++) {
                        int range = std::stoi(lidar_val_string[i]);
                        if(range > max_range_) {
                            max_range_ = range;
                        }
                        lidar_val->ranges.push_back
                                         (range);
                    }
                    lidarScans_.push_back(lidar_val);
                    laserCount_ ++;
                }
            }
        }
        printf("Read %d laser scans and %d odom vals \n", laserCount_, odomCount_);
        fin_.close();
    }

    void Log::getLidar (int iter, lidar*& lidar_val) const {
        
        if(iter >= lidarScans_.size()) {
            printf("[ERROR] Wrong access to lidar scans");
            return;
        }
        lidar_val = lidarScans_[iter];
    }

    void Log::getOdom (int iter, std::vector<odom*>& odoms) const {
        odoms.clear();
        for(int i = iter; i < iter + 2; i++) {
            if(i >= lidarScans_.size()) {
                printf("%d [ERROR] Wrong access to lidar scans\n", i);
                return;
            }
            double time_stamp = lidarScans_[i]->t;
            auto it = odomVals_.lower_bound(time_stamp);
            if(it == odomVals_.end()) {
                printf("[ERROR] Cannot find odom.");
                return;
            }
            odoms.push_back(it->second);
        }
    }

}