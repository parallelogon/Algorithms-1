#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <time.h>
#include <stdlib.h>

/* A class to be used in a larger program to solve 8-puzzle problems this class
'Board' and it's associated methods will make an nxn game board*/
class Board
{
	std::vector< std::vector< int > > tiles;
	int dim;

	public:
		//Creates a board form an n-by-n array
		Board(std::vector< std::vector<int> >);

		//returns the board a string
		std::string toString();

		//yields the dimension of the board
		int dimension();

		//calculates and returns the hamming weight (# out of place tiles)
		int hamming();

		//calculates and sumes the manhattan distance from tiles and their goal
		int manhattan();

		//checks if solution is found
		bool isGoal();

		//checks if two boards are equal
		bool equals(Board);

		//returns the twin of a board, twins are obtained by exchanging any two tiles
		Board twin();

		int atIJ(int,int);

		//switches the pieces at i,j with a,b
		void slide(int, int, int, int);

		class iterator
		{
        		Board * p;

        		public:
                		iterator(Board * x) : p(x) {}
                		iterator(const iterator& myitr) : p(myitr.p) {}
                		iterator& operator++() {p = p->next; return *this;}
                		//bool operator== (const iterator& rhs) const {return *p.equals(rhs.p);}
                		//bool operator!= (const iterator& rhs) const {return rhs.p.equals(this);}
                		Board operator*() const {return *p;}
		};


};

Board::Board(std::vector< std::vector<int> > config)
{
	dim = config.size();

	tiles.resize(dim, std::vector<int>(dim));

	for(int i=0; i < dim; i++)
	{
		for(int j = 0; j < dim; j++)
			tiles[i][j] = config[i][j];
	}
}

std::string Board::toString()
{
	std::string asString;

	asString.append(std::to_string(dim));
	asString.append("\n");

	for(int i= 0; i < dim; i++)
	{
		for(int j = 0; j < dim; j++)
			asString.append(std::to_string(tiles[i][j]));
		asString.append("\n");
	}

	return asString;
}

int Board::dimension()
{
	return dim;
}

int Board::hamming()
{
	int weight = 0;
	for(int i = 0; i < dim; i++)
	{
		for(int j = 0; j < dim; j ++)
		{
			if( tiles[i][j] !=  (dim*i + j+1)%(dim*dim) && tiles[i][j] != 0)
				weight++;
		}
	}

	return weight;
}

int Board::manhattan()
{
	//to store the total manhattan distance
	int totalManhattan = 0;

	//to store the value of the tile temporarily
	int t = 0;

	//to store the correct i value
	int ic = 0;

	//to store the correct j value
	int jc = 0;
	for(int i = 0; i < dim; i++)
	{
		for(int j = 0; j < dim; j++)
		{
			t = tiles[i][j];
			if(t != 0)
			{
				jc = (t-1)%dim;
				ic = (t-1-jc)/dim;

				totalManhattan += std::abs(j - jc) + std::abs(i - ic);
			}
		}
	}
	return totalManhattan;
}

int Board::atIJ(int i, int j)
{
	return(tiles[i][j]);
}

bool Board::equals(Board b2)
{
	for(int i = 0; i < dim; i ++)
	{
		for(int j = 0; j < dim; j++)
		{
			if(tiles[i][j] != b2.atIJ(i,j))
				return 0;
		}
	}

	return 1;
}

Board Board::twin()
{
	//pick two random indices
	int i1 = rand() % dim;
	int i2 = rand() % dim;
	int j1 = rand() % dim;
	int j2 = rand() % dim;


	//switch them in the tiles 2d vector
	slide(i1,j1,i2,j2);

	//make a twin board
	Board b2(tiles);

	//switch them back
	slide(i1,j1,i2,j2);

	return b2;
}


void Board::slide(int i, int j, int a, int b)
{
	int tmp = tiles[i][j];
	tiles[i][j] = tiles[a][b];
	tiles[a][b] = tmp;
}


int main()
{
	int d = 3;
	std::vector< std::vector<int> > tile(d, std::vector<int>(d) );
	srand (time(NULL));

	std::vector< std::vector<int> > tile2{ {8, 1, 3},{4, 0, 2}, {7, 6, 5} };

	for(int i = 0; i <d; i++)
	{
		for(int j = 0; j < d; j++)
			tile[i][j] = rand() % d*d; //(d*i + j+1)%(d*d);
	}

	Board gameboard(tile2);
	Board goalboard(tile);

	
	std::string gamestring = gameboard.toString();

	for(int i = 0; i < gamestring.size(); i++)
		std::cout << gamestring[i];

	std::cout << gameboard.hamming() << " " << gameboard.manhattan() << "\n";
	std::cout << gameboard.equals(goalboard) << "\n";

	std::cout << gameboard.twin().toString() << gameboard.toString();
	
	return 0;
}
