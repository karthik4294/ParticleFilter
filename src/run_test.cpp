#include <iostream>
#include <map_parser.h>

using namespace map;

int main(int argc , char *argv[]){

	map::MapParser *mp = new map::MapParser("../../data/map/wean.dat");	
 	mp->displayMap();
 	return 0;
}