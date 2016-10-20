#pragma once
#include <standard_includes.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;


class Particle{

public:

	float x, y, theta;
  float x_noise, y_noise, theta_noise;

	Particle();
	Particle(float x_val, float y_val, float theta_val) :
    x(x_val), y(y_val), theta(theta_val){}

  void set_pose(float x_val, float y_val, float theta_val);

  void set_noise(float x_val, float y_val, float theta_val);

  void move(float x_disp, float y_disp, float theta_disp);

};
