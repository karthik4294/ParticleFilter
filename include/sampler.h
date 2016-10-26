#ifndef SAMPLER_H
#define SAMPLER_H

#include <standard_includes.h>
#include <util_functions.h>
#include <map.h>
#include <particle_state.h>

namespace sp{

	class Sampler{

	public:

		Sampler(Map *map, int num_particles);
		void sampleUniform(std::vector<ps::ParticleState>& ps);
		void constructFullFreeSpace();
		void importanceResample(std::vector<ps::ParticleState> &ps,
								double resampling_randomization);

	private:

		int ang_res_;

		Map *map_;
		int num_particles_;
		std::vector<std::pair<double, double>> free_space_;
		std::vector<std::tuple<double, double , double>> full_free_space_;

	};

} // namespace

#endif