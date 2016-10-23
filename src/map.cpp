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
    grid.at<double>(temprow, tempcol) = val;
    //printf(" %f ", val);
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
  imshow( "Display window", grid);                   // Show our image inside it.

  waitKey(0);                                          // Wait for a keystroke in the window
}

void Map::visualizeParticles(vector<ParticleState>* particle_list) {

  Mat temp_grid = grid.clone();
  Point pt;
  cv::Scalar red(255, 0, 0);

  for(std::vector<ParticleState>::iterator it = particle_list->begin(); it != particle_list->end(); ++it) {
    pt = Point(int(it->x()/res), int(it->y()/res)); // divided by res as one pixel in visualization = 10 units of distance
    circle(temp_grid, pt, 2, red);
  }

  namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
  imshow( "Display window", temp_grid);                   // Show our image inside it.

  waitKey(0);                                          // Wait for a keystroke in the window
  destroyWindow( "Display window");
}
