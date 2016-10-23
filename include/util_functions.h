#ifndef UTIL_FUNCTIONS_H
#define UTIL_FUNCTIONS_H

#include <standard_includes.h>
#include <eigen3/Eigen/Geometry> 

namespace utils{
	
	Eigen::Matrix3d getRotationMatrix(double roll, double yaw, double pitch){

		Eigen::AngleAxisd rollAngle(roll, Eigen::Vector3d::UnitZ());
		Eigen::AngleAxisd yawAngle(yaw, Eigen::Vector3d::UnitY());
		Eigen::AngleAxisd pitchAngle(pitch, Eigen::Vector3d::UnitX());

		Eigen::Quaternion<double> q = rollAngle * yawAngle * pitchAngle;

		Eigen::Matrix3d rotationMatrix = q.matrix();

		return rotationMatrix;
	}

	Eigen::Vector3d rotateVector(Eigen::Vector3d vec, double yaw){

		double roll = 0;
		double pitch = 0;

		Eigen::AngleAxisd rollAngle(roll, Eigen::Vector3d::UnitZ());
		Eigen::AngleAxisd yawAngle(yaw, Eigen::Vector3d::UnitY());
		Eigen::AngleAxisd pitchAngle(pitch, Eigen::Vector3d::UnitX());

		Eigen::Quaternion<double> q = rollAngle * yawAngle * pitchAngle;

		Eigen::Matrix3d rotationMatrix = q.matrix();

		return rotationMatrix*vec;
	}


} //namespace

#endif