#include "Percolation.h"
#include <math.h>
#include <string>
#include <iostream>

class PercolationStats
{
	double mean = 0.0;
	double stdev = 0.0;
	int N;
	int T;

	public:
		PercolationStats(int,int);
		double getMean();
		double getStdev();
		double confidenceLo();
		double confidenceHi();
};

PercolationStats::PercolationStats(int n, int trials)
{
	N = n;
	T = trials;
	int i;
	int j;
	double x;

	srand (time(NULL));

	for(int t = 0; t < T; t++)
	{
		Percolation trial(n);
		while(trial.percolates() == 0)
		{
			i = rand() % n;
			j = rand() % n;

			trial.open(i,j);
		}

		x = trial.numberOfOpenSites()/pow(n,2);
		mean += x;
		stdev += pow(x,2);
	}

	mean = mean/T;
	stdev = pow((T/(T-1))*(stdev/T - pow(mean,2)),0.5);
}

double PercolationStats::getMean()
{
	return mean;
}

double PercolationStats::getStdev()
{
	return stdev;
}

double PercolationStats::confidenceLo()
{
	return (mean - 1.96*stdev/sqrt(T));
}

double PercolationStats::confidenceHi()
{
	return (mean + 1.96*stdev/sqrt(T));
}

int main(int argc, char** argv)
{
	int N = std::stoi(argv[1]);
	int Trials = std::stoi(argv[2]);

	PercolationStats perc(N, Trials);

	std::cout << perc.getMean() << " " << perc.getStdev() << "\n";
	std::cout << "[ " << perc.confidenceLo() << " , " << perc.confidenceHi() << " ] " << "\n";

	return 0;
}
