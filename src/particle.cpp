#include <particle.h>


using namespace cv;

Particle::Particle()
{	
}


void Particle::set_pose(float x_val, float y_val, float theta_val) {
     x = x_val;
     y = y_val;
     theta = theta_val;
}

void Particle::set_noise(float x_val, float y_val, float theta_val) {
     x_noise = x_val;
     y_noise = y_val;
     theta_noise = theta_val;
}
