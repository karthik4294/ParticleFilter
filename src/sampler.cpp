#include <sampler.h>

namespace sp{

Sampler::Sampler(Map *map, int num_particles)
:
map_(map),
num_particles_(num_particles)
{
	free_space_ = map_->getFreeSpace();
	constructFullFreeSpace();
}

void Sampler::constructFullFreeSpace(){

	for(int i = 0; i < free_space_.size(); i++){

		
	}
}


void Sampler::sampleUniform(std::vector<ps::ParticleState> ps){

	map_->displayMap();
	
	std::cout << free_space_.size() << std::endl;



}


}