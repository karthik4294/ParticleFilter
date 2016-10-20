#include <iostream>
#include <map_parser.h>
#include <log_parser.h>

int main(int argc , char *argv[]){

	MapParser *mp = new MapParser("./data/map/wean.dat");	
   //mp->displayMap();

	LogParser *lp = new LogParser("./data/log/robotdata1.log");	
 	lp->displayLog();
 	return 0;
}
