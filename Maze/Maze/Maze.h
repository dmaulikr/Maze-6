#ifndef Maze_Maze_h
#define Maze_Maze_h

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <vector>
#include "DisjointSet.h"
using namespace std;

struct mazePiece
{
	bool inPath;
	bool floor;
	bool leftWall;
	bool beenChecked;
};

struct wall
{
	int cell1, cell2;
};

class Maze
{
	DisjointSet* set;
	mazePiece** maze;
	int mazeCols;
	int mazeRows;
	vector<wall> walls;

public:    
	Maze(int rows, int cols){
		mazeCols = cols;
		mazeRows = rows;
		set = new DisjointSet(rows*cols);
		maze = new mazePiece*[rows];
		for(int i=0; i<rows; i++){
			maze[i] = new mazePiece[cols];
			for(int j = 0; j < cols; j++)
			{
				maze[i][j].beenChecked = false;

				wall temp;

				if (j+1 < cols)
				{
					temp.cell1 = getBox(i, j);
					temp.cell2 = getBox(i, j+1);
					walls.push_back(temp);
				}

				if (i+1 < rows)
				{
					temp.cell1 = getBox(i, j);
					temp.cell2 = getBox(i+1, j);
					walls.push_back(temp);
				}

				maze[i][j].floor = true;
				maze[i][j].leftWall = true;
				maze[i][j].inPath = false;
            }
        }
        maze[rows-1][cols-1].floor=false;
        srand(time(NULL));
		carveMaze();
    }
    
    //gets the box number (the box number is the id/index in the set)
    int getBox(int row, int col)
	{
        return (row*mazeCols)+col;
    }
    
    //removes walls to carve out the maze
    //before it removes walls, it should use the set
    //to determine whether the wall can be removed
    //be sure not to remove the leftWall for any cell with col==0
    //or the floor of any cell with row==mazeRows-1
    void carveMaze()
	{
		while (!set->isOneSet())
		{
			int temp = rand()%walls.size();

			if (set->unionByRank(walls[temp].cell1, walls[temp].cell2))
			{
				if (walls[temp].cell1 + 1 == walls[temp].cell2)
				{
					if (walls[temp].cell2 % mazeCols != 0)
						maze[(walls[temp].cell2 / mazeRows)][(walls[temp].cell2 % mazeCols)].leftWall = false;
				}

				else
				{
					if (walls[temp].cell1 / mazeRows != mazeRows - 1)
						maze[walls[temp].cell1 / mazeRows][walls[temp].cell1 % mazeCols].floor = false;
				}
			}

			walls.erase(walls.begin() + temp);
		}
    }
    
    //wrapper for the recursive solve
    //starts solving at the top left corner of the maze
    void solveMaze()
	{
        solveMaze(0, 0);
    }
    
    //should recusively solve the maze
    //it will need to check to see if putting the current cell in the path
    //can create a path to the end
    //don't forget base cases
    //you will need to decide which of the surrounding cells to try next
    //to do this, check which walls exist, and only go if the wall doesn't
    //to mark that a cell is in the path, set inPath to true
    bool solveMaze(int row, int col){
		if (maze[row][col].beenChecked)
		{
			return false;
		}

		if (row == mazeRows - 1 && col == mazeCols - 1)
		{
			maze[row][col].beenChecked = true;
			maze[row][col].inPath = true;
			return true;
		}

		maze[row][col].beenChecked = true;

		bool top = false, bot = false, right = false, left = false;

		if (!maze[row][col].leftWall)
		{
			if (col != 0)
			{
				left = solveMaze(row, col-1);
			}
		}

		if (!maze[row][col].floor)
		{
			if (row != mazeRows - 1)
			{
				bot = solveMaze(row+1, col);
			}
		}

		if (col != mazeCols - 1)
		{
			if (!maze[row][col+1].leftWall)
			{
				right = solveMaze(row, col+1);
			}
		}

		if (row != 0)
		{
			if (!maze[row-1][col].floor)
			{
				top = solveMaze(row-1, col);
			}
		}

		maze[row][col].inPath = right || left || top || bot;
		return right || left || top || bot;
    }
    
    //prints the maze to the screen
    //if showPath is true, then it prints the solution path too
    void printMaze(bool showPath){
        cout<<"+ +";
        for(int j=1; j<mazeCols; j++)
            cout<<"-+";
        cout<<endl;
        for(int i=0; i<mazeRows; i++){
            for(int j=0; j<mazeCols; j++){
                if(maze[i][j].leftWall==true)
                    cout<<"|";
                else
                    cout<<" ";
                if(showPath && maze[i][j].inPath==true)
                    cout<<"*";
                else
                    cout<<" ";
            }
            cout<<"|"<<endl;
            for(int j=0; j<mazeCols; j++){
                if(maze[i][j].floor==true)
                    cout<<"+-";
                else
                    cout<<"+ ";
            }
            cout<<"+"<<endl;
        }
        return;
    }
};
#endif
