//Sensor model
#ifndef SENSOR_MODEL_H
#define SENSOR_MODEL_H

#include <standard_includes.h>
#include <map_parser.h>

namespace sensor_model {
	class Lidar {
		//public functions
		Lidar(map::Map* map, int num_rays, double max_range, int n_bins, double min_angle, double max_angle);
		//private variables

		//map
		map::Map* map_;

		//

	};
}

#endif