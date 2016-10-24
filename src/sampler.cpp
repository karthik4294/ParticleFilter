#include <sampler.h>

namespace sp{

Sampler::Sampler(Map *map, int num_particles)
:
map_(map),
num_particles_(num_particles),
ang_res_(5)
{
	free_space_ = map_->getFreeSpace();
	constructFullFreeSpace();
}

void Sampler::constructFullFreeSpace(){

	for(int i = 0; i < free_space_.size(); i++){
		for(int j = 0; j < 360; j+=ang_res_){
			double ang = j*M_PI/180;
			full_free_space_.push_back(std::make_tuple(free_space_[i].first, free_space_[i].second, ang));
		}
	}
}

void Sampler::sampleUniform(std::vector<ps::ParticleState> ps){

	std::default_random_engine gen;
  	std::uniform_int_distribution<int> dist(0, full_free_space_.size());

  	 for (int i = 0; i < num_particles_; i++){
    	
    	int num = dist(gen);
    	ParticleState p_state;
    	p_state.x(std::get<0>(full_free_space_[num]));
    	p_state.y(std::get<1>(full_free_space_[num]));
    	p_state.theta(std::get<2>(full_free_space_[num]));
    	p_state.weight(1.0);

    	ps.push_back(p_state);
  	}
}


}