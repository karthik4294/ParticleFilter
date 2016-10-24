#include <util_functions.h>

namespace utils{

UtilFunctions::UtilFunctions()
{

}

Eigen::Matrix3d UtilFunctions::getRotationMatrix(double roll, double yaw, double pitch){

	Eigen::AngleAxisd rollAngle(roll, Eigen::Vector3d::UnitZ());
	Eigen::AngleAxisd yawAngle(yaw, Eigen::Vector3d::UnitY());
	Eigen::AngleAxisd pitchAngle(pitch, Eigen::Vector3d::UnitX());

	Eigen::Quaternion<double> q = rollAngle * yawAngle * pitchAngle;

	Eigen::Matrix3d rotationMatrix = q.matrix();

	return rotationMatrix;
}

Eigen::Vector3d UtilFunctions::rotateVector(Eigen::Vector3d vec, double yaw){

	double roll = 0.0;
	double pitch = 0.0;

	Eigen::AngleAxisd rollAngle(roll, Eigen::Vector3d::UnitZ());
	Eigen::AngleAxisd yawAngle(yaw, Eigen::Vector3d::UnitY());
	Eigen::AngleAxisd pitchAngle(pitch, Eigen::Vector3d::UnitX());

	Eigen::Quaternion<double> q = rollAngle * yawAngle * pitchAngle;

	Eigen::Matrix3d rotationMatrix = q.matrix();

	return rotationMatrix*vec;
}

Eigen::Vector3d UtilFunctions::tranformVector(Eigen::Vector3d vec, double x, double y, double yaw){

	double roll = 0.0;
	double pitch = 0.0;

	Eigen::AngleAxisd rollAngle(roll, Eigen::Vector3d::UnitZ());
	Eigen::AngleAxisd yawAngle(yaw, Eigen::Vector3d::UnitY());
	Eigen::AngleAxisd pitchAngle(pitch, Eigen::Vector3d::UnitX());

	Eigen::Quaternion<double> q = rollAngle * yawAngle * pitchAngle;

	Eigen::Vector3d trans(x, y, 0.0);

	Eigen::Matrix3d r = q.matrix();

	Eigen::Affine3d t(Eigen::Translation3d(Eigen::Vector3d(x, y, 0.0)));

	return (r*vec) + trans;
}

}