#include <particle_state.h>

using namespace rs;

namespace ps{

ParticleState::ParticleState(RobotState robot_state, double weight)
:
x_(robot_state.x()),
y_(robot_state.y()),
theta_(robot_state.theta()),
robot_state_(robot_state),
weight_(weight)
{
	utils_ = new utils::UtilFunctions();
}

ParticleState::ParticleState(double x, double y, double theta, double weight)
:
x_(x),
y_(y),
theta_(theta),
weight_(weight)
{
	utils_ = new utils::UtilFunctions();

	robot_state_.x(x_);
	robot_state_.y(y_);
	robot_state_.theta(theta_);
}

void ParticleState::x(double x){
	x_ = x;
}

void ParticleState::y(double y){
	y_ = y;
}

void ParticleState::theta(double theta){
	theta_ = theta;
}

void ParticleState::robot_state(RobotState robot_state){
	robot_state_ = robot_state;
	x_ = robot_state.x();
	y_ = robot_state.y();
	theta_ = robot_state.theta();
}

void ParticleState::weight(double weight){
	weight_ = weight;
}

double ParticleState::x(){
	return x_;
}

double ParticleState::y(){
	return y_;
}

double ParticleState::theta(){
	return theta_;
}

RobotState ParticleState::robot_state(){
	return robot_state_;
}

double ParticleState::weight(){
	return weight_;
}

ParticleState ParticleState::rotate(double theta){

	ParticleState trans_state;
	trans_state.robot_state(robot_state_.rotate(theta));
	trans_state.weight(weight_);

	return trans_state;	

}

} //namepsace