//Sensor model
#pragma once
#include <standard_includes.h>
#include <map_parser.h>

namespace sensor_model {
	class Lidar {
		//public functions
		Lidar(map::Map* map);
		//private variables

		//map
		map::Map* map_;

		//

	};
}