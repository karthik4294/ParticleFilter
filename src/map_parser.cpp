#include <map_parser.h>

MapParser::MapParser(std::string filename)
{	
	map_ = new Map;

	// Defining certain constants instead of reading from file
	map_->size_x = 8000;
	map_->size_y = 8000;
	map_->res = 10;

	// initialize
	map_->grid_size = 0;
	map_->grid.resize(1000);

	// parse the map from dat file
	readMap(filename);
}

void MapParser::readMap(std::string file){

	std::ifstream fin(file.c_str());

	std::string line, ch;
	int count = 0;

    while (std::getline(fin, line)){

    	count++;

    	if(count < 8)
    		continue;

    	std::stringstream ss(line);
		while(ss){ 
			
			if(!std::getline(ss, ch, ' '))
				break;
 			
 			map_->grid[map_->grid_size].push_back(atof(ch.c_str()));

 		}
 		map_->grid_size++;
	}

	map_->grid.resize(map_->grid_size);
}

void MapParser::printMap(){

	printf("\nSize x : %d\n", map_->size_x);
	printf("\nSize y : %d\n", map_->size_y);
	printf("\nResolution : %d\n", map_->res);
	printf("\nMap size : %d\n", map_->grid_size);

	printf("\nMap : \n");

	for(int i = 0; i < map_->grid.size(); i++){
		for(int j = 0; j < map_->grid[i].size(); j++){

			std::cout << map_->grid[i][j] << " " ;
		}
		std::cout << std::endl;
	}
}

void MapParser::displayMap(){

	cv::Mat image = cv::Mat::zeros(map_->grid_size, map_->grid_size, CV_32FC1);

	for(int i = 0; i < image.rows; i++){
		for(int j = 0; j < image.cols; j++){

			if(map_->grid[i][j] > 0){
				image.at<float>(i,j) = map_->grid[i][j];
			}
		}
	}

	cv::imshow("Map", image);
	cv::waitKey(0);
}

void MapParser::getMap(Map *map){

	map = map_;
}