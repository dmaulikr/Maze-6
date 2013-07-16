#ifndef Maze_DisjointSet_h
#define Maze_DisjointSet_h

using namespace std;

class DisjointSet{
    int* sets;
    int numSets;
    
public:
    DisjointSet(int size){
        numSets=size;
        sets=new int[size];
        for(int i=0; i<size; i++)
            sets[i]=-1;
    }
    
    ~DisjointSet()
	{
        delete[] sets;
    }
    
    bool isOneSet()
	{
        return numSets == 1;
    }
    
    //finds the parent and performs path compression
	int find(int box)
	{
		if (sets[box] < 0)
		{
			return box;
		}

		sets[box] = find(sets[box]);

		return find(sets[box]);
	}
    
    //unions the two sets by rank, the parent with the larger estimated height becomes the root
	bool unionByRank(int box1, int box2)
	{
		int temp1 = find(box1), temp2 = find(box2);

		if (temp1 == temp2)
			return false;

		if (temp1 < temp2)
		{
			sets[temp2] = temp1;
			sets[temp1]--;
		}

		else
		{
			sets[temp1] = temp2;
			sets[temp2]--;
		}

        numSets--;//only do this if the union succeeds
        return true;
    }
};

#endif
