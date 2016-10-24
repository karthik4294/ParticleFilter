#include <motion_model.h>

namespace mm{

MotionModel::MotionModel()
:
first_call_(0),
t_init_(0.0)
{

}

void MotionModel::applyMotionModel(std::vector<ps::ParticleState> particles, double timestamp){

	if(first_call_ == 0)
	{
		first_call_++;
		t_init_ = timestamp;
		return;
	}

	// the main loop of the motion model
	for(int i = 0; i < particles_.size(); i++){

		particles_[i];		

	}

}

}