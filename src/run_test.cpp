#include <standard_includes.h>
#include <map_parser.h>
#include <robot_state.h>

int main(int argc , char *argv[]){

	map::MapParser *mp = new map::MapParser("../../data/map/wean.dat");	
 	mp->displayMap();

 	rs::RobotState* robot_state = new rs::RobotState(2.0, 3.0, 0.0);

 	rs::RobotState* news = robot_state->rotate(M_PI);

 	printf("New state %f %f %f\n", news->x(), news->y(), news->theta());

 	return 0;
}