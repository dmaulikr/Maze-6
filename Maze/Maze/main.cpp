#include "Maze.h"
using namespace std;


int main(int argc, char *argv[])
{
    Maze myMaze(10, 10);
    myMaze.solveMaze();
    myMaze.printMaze(true);
    
	return 0;
}