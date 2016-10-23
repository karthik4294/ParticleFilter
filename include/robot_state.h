#ifndef ROBOT_STATE_H
#define ROBOT_STATE_H

#include <standard_includes.h>
#include <util_functions.h>

namespace rs{

	class RobotState{

	public:

		RobotState(){}
		RobotState(double x, double y, double theta);
		
		void setX(double x);
		void setY(double y);
		void setTheta(double theta);
		double getX();
		double getY();
		double getTheta();
		
		RobotState *rotateVector(double theta);

	private:

		// coordinates in odom frame
		double x_;
		double y_;
		double theta_;

	};

} //namespace

#endif