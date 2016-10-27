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

void Sampler::sampleUniform(std::vector<ps::ParticleState>& ps, double max_range){

	std::random_device rd;
  std::mt19937 gen(rd());

	std::uniform_int_distribution<int> dist(0, full_free_space_.size());

	for (int i = 0; i < num_particles_; i++){	
  	int num = dist(gen);
  	ParticleState p_state;
  	p_state.x(std::get<0>(full_free_space_[num]));
  	p_state.y(std::get<1>(full_free_space_[num]));
  	p_state.theta(std::get<2>(full_free_space_[num]));
    p_state.setRanges();
    p_state.setRayTips(max_range);
    // std::cout << "Sampled point " << p_state.x() << " " << p_state.y() << " " << p_state.theta() << std::endl; 

  	p_state.weight(1.0);

  	ps.push_back(p_state);
	}
}

void Sampler::importanceResample(std::vector<ps::ParticleState> &ps, double resampling_randomization)
{

    std::vector <double> input_weights;

    for(std::vector<ps::ParticleState>::iterator it = ps.begin(); it != ps.end(); ++it) {
      input_weights.push_back(it->weight());
    }
    /*double min_weight = *std::min_element(input_weights.begin(), input_weights.end());
    for(int i = 0; i <input_weights.size(); i++) {
      input_weights[i] += abs(min_weight);
      //cout<<"Modded weight: "<<input_weights[i]<<endl;
    }*/
    std::random_device rd;
    std::mt19937 gen(rd());

    std::discrete_distribution<> d(input_weights.begin(), input_weights.end());

    std::vector<ps::ParticleState> resampled_particles;

    for(int n=0; n < ps.size(); ++n) {
      ps::ParticleState particle = ps[d(gen)];
      double random = (double)rand() / (double)RAND_MAX;
      particle.x((1 + resampling_randomization*(random-0.5))*particle.x());
      particle.y((1 + resampling_randomization*(random-0.5))*particle.y());
      particle.theta((1 + resampling_randomization*(random-0.5))*particle.theta());
      particle.weight(1.0); 
      resampled_particles.push_back(particle);   
    }
    ps = resampled_particles;
}


void Sampler::importanceCombResample(std::vector<ps::ParticleState> &ps, int comb_dist) 
{
    std::vector <double> input_weights;
    std::vector <double> comb_weights;

    for(std::vector<ps::ParticleState>::iterator it = ps.begin(); it != ps.end(); ++it) {
      input_weights.push_back(it->weight());
    }

    double min_weight = *std::min_element(input_weights.begin(), input_weights.end());
    for(int i = 0; i <input_weights.size(); i++) {
      input_weights[i] += abs(min_weight);
      //cout<<"Modded weight: "<<input_weights[i]<<endl;
    }

    std::stable_sort(input_weights.begin(), input_weights.end());
    std::reverse(input_weights.begin(), input_weights.end());
    
    for(int i = 0; i < input_weights.size(); i++){
      if(i % comb_dist == 0)
        comb_weights.push_back(input_weights[i]);
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    std::discrete_distribution<> d(comb_weights.begin(), comb_weights.end());

    std::vector<ps::ParticleState> resampled_particles;

    for(int n=0; n < ps.size(); ++n) {
      resampled_particles.push_back(ps[d(gen)]);
    }
    ps = resampled_particles;
}

void Sampler::lowVarianceResample(std::vector<ps::ParticleState> &ps, int comb_dist) 
{

  std::vector <double> input_weights;
  double wt = 0;

  for(std::vector<ps::ParticleState>::iterator it = ps.begin(); it != ps.end(); ++it) {
    input_weights.push_back(it->weight());
    wt += it->weight();
  }

  std::transform (input_weights.begin (), input_weights.end (), input_weights.begin (),
                 std::bind1st (std::multiplies <double> () , 1/wt)) ;

  std::vector<ps::ParticleState> resampled_particles;

  int s = ps.size();
  double max_r = 1/s;

  double r = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX/max_r));

  int i = 0;

  double w = input_weights[i];

  for(int m = 1; m <= s; m++){

      double u = r + (i - 1)/m;
      while(u > w){
        i++;
        w += input_weights[i];
      }

      resampled_particles.push_back(ps[i]);
  }

  ps = resampled_particles;

}

}
