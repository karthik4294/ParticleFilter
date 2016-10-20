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


void Particle::move(float x_disp, float y_disp, float theta_disp) {
     x += x_disp;
     y += y_disp;
     //theta_noise = theta_val;
     // TODO FIX -- add new function applytransform
}
