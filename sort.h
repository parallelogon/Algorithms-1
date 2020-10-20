#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

template <typename T>
void insertionSort(std::vector<T> &vect);

template <typename T>
void shellSort(std::vector<T> &vect);

template <typename T>
void mergeSort(std::vector<T> &vect, int lo, int hi);


//here we define less than so that we can modify it for strange datatypes
template <typename T>
bool lessthan(const T &a, const T &b);

//exchange as well, modifiable to different datatypes
template <typename T>
void exch(std::vector<T> &vect, int lo, int hi);

//merge portion of mergesort
template <typename T>
void mergeSortMerge(std::vector<T> &vect, std::vector<T> &aux, int lo, int mid, int hi);


template<typename T>
bool lessthan(const T &a,const T &b)
{
	return (a < b);
}

template<typename T>
void exch(std::vector<T> &vect, int lo, int hi)
{
	T tmp = vect[lo];
	vect[lo] = vect[hi];
	vect[hi] = tmp;
}


template <typename T>
void insertionSort(std::vector<T> &vect)
{
	
	//loop through the array
	for(int i = 0; i < vect.size(); i++)
	{
		//for every index travel backwards
		for(int j = i+1; j>0; j--)
		{
			//switch with anything less in the sorted (left) part of the vector
			if( lessthan( vect[j], vect[j-1] ) )
			{
				exch( vect, j, j-1 );
			}
			//if it's impossible, break and start with next item
			else
				break;
		}
	}
}

template <typename T>
void shellSort(std::vector<T> &vect)
{

	//define the size of the array
	int N = vect.size();

	//make the highest element in the sequence to sort by
	int h = 1;
	while (h < N/3)
		h = 3*h + 1;

	
	//h - sort the array
	while (h >= 1)
	{
		for(int i = h; i <N; i++)
		{
			//perform a type o insertion sort
			for(int j = i; j >= h; j -= h)
			{
				if( lessthan( vect[j], vect[j-h] ) )
					exch(vect,j,j-h);
				else
					break;
			}
		}

		//modify h until it reaches 1 to fully sort
		h = h/3;
	}
}

template <typename T>
void mergeSortMerge(std::vector<T> &vect, std::vector<T> &aux,int lo, int mid, int hi )
{

	//keep track of indices as begining of first list and beginning of second list
	int i = lo;
	int j = mid + 1;


	for(int l = lo; l <= hi; l++)
		aux[l] = vect[l];

	//go through each element of vect modifying it to contain the sorted elements from the working vector aux (contains the initial ordering of vect)
	for(int k = lo; k <= hi; k++)
	{
	//If the value of i has incremented past mid then j must be the what needs to be added to the array
	if( i > mid)
		vect[k] = aux[j++];

	//the converse is true for j
	else if ( j > hi)
		vect[k] = aux[i++];

	//if the current value on the right is lower than the current value on the left than put it to the left
	else if ( lessthan(aux[j], aux[i] ) )
		vect[k] = aux[j++];
	//if none of the above are true, the value on the left must be lower
	else
		vect[k] = aux[i++];
	}
}


template <typename T>
void mergeSort(std::vector<T> &vect, std::vector<T> &aux, int lo, int hi)
{
	//returns no value if the indices are the same (single element array cannot be sorted)
	if(hi <= lo)
		return;

	//find the midpoint
	int mid = lo + (hi - lo)/2;

	//sort the lower half
	mergeSort(vect, aux, lo, mid);

	//sort the higher half
	mergeSort(vect,aux, mid+1, hi);

	//merge the two halves
	mergeSortMerge(vect,aux,lo,mid,hi);
}
