#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>


/*A percolation class keeps track of all of the open/closed nodes 
in an NxN grid and can check if a given configuration percolates.
Along with the grid itself a vector to keep track of the shared roots of
the tree of connections along with with the size of each tree is initialized*/

class Percolation
{
	//Three vectors
	//one 2d to keep track of the grid
	std::vector<std::vector<int>> grid;
	
	//one to keep track of the roots of the nodes
	std::vector<int> id;

	//one to keep track of the size of each of the trees
	std::vector<int> sz;

	public:
		Percolation(int); //constructor initializes all three private arrays
		void open(int, int); //opens a node
		bool isOpen(int, int); //checks for open nodes
		bool isFull(int, int); //checks if an open site can be connected to the top of the grid
		int numberOfOpenSites(); //returns the total number of open sites
		bool percolates(); //checks if the virtual top site and bottom site are connected
		int root(int); //finds the root in the list 'id'
		void unionWQU(int, int);
		void printPerc();
		~Percolation();
};

Percolation::Percolation(int N)
{
	grid.resize(N,std::vector<int>(N));

	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			grid[i][j] = 0;
		}
	}

	//the arrays for id and size are 2 larger because of two virtual sites placed
	//at the top and the bottom of the grid
	id.resize(N*N+2);
	for(int i = 0; i < N*N+2; i ++)
	{
		id[i] = i;
	}

	sz.resize(N*N+2);
	for(int i = 0; i < N*N+2; i++)
	{
		sz[i] = 1;
	}
}

Percolation::~Percolation()
{
	delete[] grid;
	delete[] id;
	delete[] sz;
}

//Finds the root of a given node
int Percolation::root(int p)
{
	while(id[p] != p)
	{
		p = id[p];
	}

	return p;
}


//opens a node and then connects all nodes around it
void Percolation::open(int p, int q)
{
	grid[p][q] = 1;

	int L = grid.size();
	//forms a union with all the adjacent cells first checking top or bottom row

	//edge case, at the top set the root to zero (virtual node) and connect to all adjacent nodes in a T pattern
	if (p == 0)
	{
		id[p*L+q+1] = 0;
		sz[0] +=1;
		if(isOpen(p+1,q))
			unionWQU(p*L+q+1,(p+1)*L+q+1);
		for(int j = -1; j < 2; j+=2)
		{
			if(isOpen(p,q+j))
				unionWQU(p*L+q+1, p*L+q+j+1);
		}
	}

	//edge case, at the bottom set the root to N^2 + 2 and connect all adjacent nodes in an upside down T pattern.
	else if (p == L-1)
	{
		id[p*L+q+1] = L*L+1;
		sz[L*L+1] +=1;

		if(isOpen(p-1,q))
			unionWQU(p*L+q+1,(p-1)*L+q+1);

		for(int j = -1; j < 2; j = j+2)
		{
			if(isOpen(p,q+j))
				unionWQU(p*L+q+1, p*L + q + j+1);
		}
	}

	//standard case, after opening a node checks all surrounding nodes for connecitons
	else
	{
		for(int i = -1; i <2; i = i + 2)
		{
			if(isOpen(p+i,q))
				unionWQU(p*L+q+1,(p+i)*L+q+1);
		}

		for(int j = -1; j < 2; j++)
		{
			if(isOpen(p,q+j))
				unionWQU(p*L+q+1,p*L+q+j+1);
		}
	}
}

//does a weighted union by size between two trees, note that the list 'id' has a special zero and end node, so all p and q have to increase by one when calling
//for regular nodes
void Percolation::unionWQU(int p, int q)
{
	
	int i = root(p);
	int j = root(q);

	if(i == j)
		return;

	if (sz[i] < sz[j])
	{
		id[i] = j;
		sz[j] += sz[i];
	}
	else
	{
		id[j] = i;
		sz[i] += sz[j];
	}
}

//checks if both a node is open and in bounds
bool Percolation::isOpen(int p, int q)
{
	int L = grid.size();
	if(p < 0 || p >= L)
		return 0;

	if(q<0 || q >= L)
		return 0;

	return grid[p][q];
}


//checks if the node is connected to the top node
bool Percolation::isFull(int p, int q)
{
	int L = grid.size();
	if(root(p*L + q + 1)==root(0))
		return 1;

	return 0;
}

//Counts all open sites on the grid
int Percolation::numberOfOpenSites()
{
	int count = 0;
	int L = grid.size();
	for(int i = 0; i < L; i++)
	{
		for(int j = 0; j < L; j++)
		{
			count += grid[i][j];
		}
	}
	return count;
}


//Similar to full but for the bottom node, checks if the bottom is connected to the top
bool Percolation::percolates()
{
	int L = grid.size();
	return(root(L*L+1)==root(0));
}



//for debugging and visualization, prints the full grid
void Percolation::printPerc()
{
	int L = grid.size();

	for(int i = 0; i <L; i++)
	{
		for(int j = 0; j <L; j++)
		{
			std::cout << grid[i][j] << " ";
			if(j == L-1)
				std::cout << "\n";
		}
	}

	/*
	std::cout << "\n\n";
	for(int i = 0; i < L*L+2; i++)
		std::cout << id[i];

	std::cout << "\n\n";
	*/
}
