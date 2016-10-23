#ifndef UTIL_FUNCTIONS_H
#define UTIL_FUNCTIONS_H

#include <standard_includes.h>
#include <eigen3/Eigen/Geometry> 

namespace utils{
	
	class UtilFunctions{
		
		public:

			UtilFunctions();
			Eigen::Matrix3d getRotationMatrix(double roll, double yaw, double pitch);
			Eigen::Vector3d rotateVector(Eigen::Vector3d vec, double yaw);

	};


} //namespace

#endif