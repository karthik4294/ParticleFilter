#include <map.h>
#include <particle_state.h>

using namespace cv;
using namespace ps;

Map::Map(std::string filename)
{	

  // Defining certain constants instead of reading from file
  size_x = 800;
  size_y = 800;
  res = 10;

  // initialize
  grid = Mat::zeros(size_x, size_y, CV_64FC1);
  grid_disp_ = Mat::zeros(size_x, size_y, CV_8UC3);
  // parse the map from dat file
  readMap(filename);
}

void Map::readMap(std::string file){

  std::ifstream fin(file);

  if (! fin.good())
  {
    printf("Bad File Path!\n");
    exit(EXIT_FAILURE);
  }

  std::string line, ch;
  int count = 0;
  double val;

  while (std::getline(fin, line)){

    count++;

    // skip first 7 lines
    if(count == 7)
      break;
  }

  count = 0;
  while ( fin >> val){
    int temprow = count / size_x;
    int tempcol = count % size_x;
    grid.at<double>((size_y - 1) - tempcol, temprow) = val;
    if(val == -1) {
      grid_disp_.at<Vec3b>((size_y - 1) - tempcol, temprow, 0) = Vec3b(0,0,0);
    }
    else {
      int b = (val)*255;
      int g = (val)*255;
      int r = (val)*255;
      grid_disp_.at<Vec3b>((size_y - 1) - tempcol, temprow, 0) = Vec3b(b,g,r);
    }
    //printf(" %f ", val);
    if (val == 1.0){
      double x = (size_y - 1) - tempcol;
      double y = temprow;
      for(double j = 1; j < res; j++)
        free_space_.push_back(std::make_pair((x*res) + j, (y*res) + j));
    }
    count++;
  }
}

void Map::printMap(){

  cv::Size s = grid.size();

  printf("\nSize x : %d\n", size_x);
  printf("\nSize y : %d\n", size_y);
  printf("\nResolution : %d\n", res);
  printf("\nMap size : %d\n", grid_size);

  printf("\nMap : \n");

  for(int i = 0; i < s.height; i++){
    for(int j = 0; j < s.width; j++){

      std::cout << grid.at<double>(i,j) << " " ;
    }
    std::cout << std::endl;
  }
}

void Map::displayMap(){

  namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
  imshow( "Display window", grid_disp_);                   // Show our image inside it.
  waitKey(0);                                          // Wait for a keystroke in the window
}

void Map::visualizeParticles(vector<ParticleState>* particle_list) {

  Mat grid_rgb = grid_disp_.clone();//(temp_grid.size(), CV_8UC3);
  //cvtColor(temp_grid, grid_rgb, CV_GRAY2RGB);

  Point pt;
  cv::Scalar red(0, 0, 255);
  printf("Particle list size is %zu \n", particle_list->size());
  for(std::vector<ParticleState>::iterator it = particle_list->begin(); it != particle_list->end(); ++it) {
    //std::cout << int(it->x()/res) << int(it->y()/res) << std::endl;  
    pt = Point(int(it->y()/res), int(it->x()/res)); // divided by res as one pixel in visualization = 10 units of distance
    circle(grid_rgb, pt, 2, red);

  }

  namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
  imshow( "Display window", grid_rgb);                   // Show our image inside it.

  waitKey(0);                                          // Wait for a keystroke in the window
  destroyWindow( "Display window");
}

void Map::visualizePoints(vector<pair<int,int>>* points_list) {

  Mat grid_rgb = grid_disp_.clone();//(temp_grid.size(), CV_8UC3);

  Point pt;
  cv::Scalar color(255, 0, 0);

  for(std::vector<pair<int,int>>::iterator it = points_list->begin(); it != points_list->end(); ++it) {
    pt = Point(it->first, it->second);
    circle(grid_rgb, pt, 1, color);
  }

  namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
  imshow( "Display window", grid_rgb);                   // Show our image inside it.

  waitKey(0);                                          // Wait for a keystroke in the window
  destroyWindow( "Display window");
}


vector<pair<int,int>> Map::interpolate(int x0, int y0, int x1, int y1) {

  vector<pair<int, int>> result;

  float dx = abs(x1 - x0);
  float dy = abs(y1 - y0);

  float dist = max(dx, dy);
  printf("max dist=%f\n", dist);

  float t;
  int x, y;

  for (int step = 0; step <= dist ; step++) {
    if (dist == 0)
      t = 0.0;
    else t = step / dist;

    x = round(x0 + t*(x1-x0));
    y = round(y0 + t*(y1-y0));

    //printf("at step = %d points are x=%d y=%d t=%f", step,  x, y, t);
    //printf("grid value is =%f\n", grid.at<double>(x,y));

    if (grid.at<double>(x,y) >= 1) {
    //// collided with obstacle
      //break;
      printf("FUCK");
    }

    result.push_back(make_pair(x,y));
  }

  return result;
}

vector<int> Map::raytrace(ParticleState p) {

  float theta;
  float rangemax = 100;
  int x0 = (int) p.x() / res, y0 = (int) p.y() / res;
  double theta0 = p.theta();
  int x1, y1, tx, ty;
  printf("x0=%d, y0=%d theta0=%f\n", x0, y0, theta0);

  vector<pair<int,int>> single_ray;
  vector<pair<int,int>> all_rays;

  for (theta = 90; theta >= -90; theta--){
  //{
  //theta = 0;

    x1 = rangemax * cos(theta * PI/180);
    y1 = rangemax * sin(theta * PI/180);


    Eigen::Vector2d point(x1, y1);
    Eigen::Rotation2Dd t(theta0);
    t.toRotationMatrix();

    Eigen::Vector2d new_point = t * point;

    tx = new_point(0) + x0;
    ty = new_point(1) + y0;

    printf("tx=%d, ty=%d\n", tx, ty);
    printf("x1=%d, y1=%d\n", x1, y1);

    single_ray = interpolate(x0, y0, tx, ty);
    all_rays.insert(all_rays.end(), single_ray.begin(), single_ray.end());
  }

    visualizePoints(&all_rays);
  //
  vector<int> result;
  return result;

}
