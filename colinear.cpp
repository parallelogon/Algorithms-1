#include "sort.h"
#include <math.h>


struct Point
{
	float x;
	float y;
};


int main()
{
	srand (time(NULL));


	//make a vector for points
	std::vector<Point>  points;

	//make a vector for slopes
	std::vector<float> slopes;

	//pick a max x/y coordinate and a number of points
	int max = 5;
	int nPoints = 10;


	//randomly generate a bunch of points
	points.resize(nPoints);
	for(int i = 0; i < nPoints; i++)
	{
		points[i].x = rand() % max + 1;//(float(rand())/float((RAND_MAX)) * max ) * pow( -1, rand() % 2 );	
		points[i].y = rand() % max + 1;//(float(rand())/float((RAND_MAX)) * max ) * pow( -1, rand() % 2 );
	}
	

	//calculate a slope for each point

	std::vector<std::vector<int> >colinear;

	slopes.resize(nPoints);
	for(int i = 0; i < nPoints; i++)
	{
		for(int j = 0; j < nPoints; j++)
		{
			if(j == i)
				slopes[j] = 0;
			else
				slopes[j] = (points[j].y - points[i].y)/(points[j].x - points[i].x);
		}
		shellSort(slopes);

		std::vector<int> line;
		for(int k = 1; k < nPoints; k++)
		{
			if( slopes [k-1] == slopes[k] )
			{	
				for(int l = k-1; l < nPoints-1; l++)
				{
					if( slopes[l] == slopes[l+1])
						line.push_back(l);
					else
					{
						//line.push_back(l);
						k = l+1;
						break;
					}
				}
				
				line.push_back(k-1);
			}
		}
		colinear.push_back(line);
		for(int i = 0; i < nPoints; i++)
			std::cout << slopes[i] << " ";
		
		std::cout << "Colinear: ";
		for(int i = 0; i < line.size();i++)
			std::cout << line[i] << " ";

		std::cout << "\n";
	}
	
	return 0;
}
