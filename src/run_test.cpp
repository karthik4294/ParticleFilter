#include <iostream>
#include <map_parser.h>

int main(int argc , char *argv[]){

	MapParser *mp = new MapParser("../../data/map/wean.dat");	
 	mp->displayMap();
 	return 0;
}