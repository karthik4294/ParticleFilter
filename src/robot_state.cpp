#include <robot_state.h>

namespace rs{

RobotState::RobotState(double x, double y, double theta)
:
x_(x),
y_(y),
theta_(theta)
{

}

void RobotState::setX(double x){
	x_ = x;
}

void RobotState::setY(double y){
	y_ = y;
}

void RobotState::setTheta(double theta){
	theta_ = theta;
}

double RobotState::getX(){
	return x_;
}

double RobotState::getY(){
	return y_;
}

double RobotState::getTheta(){
	return theta_;
}

RobotState* RobotState::rotateVector(double theta){

	RobotState* trans_state = new RobotState;
	
	Eigen::Vector3d vec(x_, y_, 0);	
	Eigen::Vector3d trans_vec = utils::rotateVector(vec, theta);

	trans_state->setX(trans_vec[0]);
	trans_state->setX(trans_vec[1]);
	trans_state->setX(trans_vec[2]);

	return trans_state;
}

} //namepsace