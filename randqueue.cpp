#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <algorithm>


template <typename T>
class RandomizedQueue
{
	T* arr;
	T* permute;
	long long capacity;
	long long length;

	public:
		//initiate a random queue of zero size
		RandomizedQueue(long long = 1);

		//check if queue is empty
		bool isEmpty();

		//return the size of the queue
		int size();

		//add something to the back of the queue
		void enqueue(T);

		//take something off the fron of the queue
		T dequeue();

		//returns a random element in the queue
		T sample();
		
		//return the capacity (test function)
		int cap();

		//iterator class
		class iterator
		{
			T* ptr;

			public:
				explicit iterator() : ptr(nullptr) {}
				explicit iterator(T* p) : ptr(p) {}
				bool operator ==(const iterator& rhs) const
				{
					return ptr == rhs.ptr;
				}
				bool operator!=(const iterator& rhs) const
				{
					return !(*this == rhs);
				}
				T operator*() const
				{
					return *ptr;
				}
				iterator& operator++()
				{
					++ptr;
					return *this;
				}
				iterator operator++(int)
				{
					iterator temp(*this);
					++*this;
					return temp;
				}
		};
		iterator begin();

		iterator end();
};


template <typename T>
RandomizedQueue<T>::RandomizedQueue(long long n)
	: capacity(n), arr(new T[n]), length(0)
{
}
template <typename T> 
typename RandomizedQueue<T>::iterator  
                      RandomizedQueue<T>::begin()
{
	permute = new T[length];
	std::copy(arr, arr+ length, permute);

	std::random_shuffle(&permute[0],&permute[length]);

	return iterator(permute);
}

template <typename T>
typename RandomizedQueue<T>::iterator
			RandomizedQueue<T>::end()
{
	return iterator(permute + length);
}

template <typename T>
int RandomizedQueue<T>::cap()
{
	return( capacity );
}

template <typename T>
bool RandomizedQueue<T>::isEmpty()
{
	return( length == 0 );
}

template <typename T>
int RandomizedQueue<T>::size()
{
	return( size );
}

template <typename T>
void RandomizedQueue<T>::enqueue(T newthing)
{

	//check if the item added is larger than the end if so double queue size
	if( capacity == length )
	{
		T* old = arr;
		arr = new T[capacity = capacity * 2];
		std::copy( old, old + length, arr);
		delete[] old;
	}

	//add element to the end
	arr[length++] = newthing;
}

template <typename T>
T RandomizedQueue<T>::dequeue()
{
	//check if queue is 4x bigger than size, if so decrease allocated size
	if( length ==  capacity / 4)
	{
		T* old = arr;
		arr = new T[capacity = capacity / 2];
		std::copy(old, old + length, arr);
		delete[] old;
	}

	//take the first element and save it
	T front = arr[0];
	//shift the whole array

	for(int i = 1; i < length; i++)
		arr[(i-1)] = arr[i];
	length--;
	//return the saved first element
	return front;
}

template <typename T>
T RandomizedQueue<T>::sample()
{

	//pick a random index from 0 to n-1 queue size
	int index = rand() % length;

	//return random indexed element in queue
	return( arr[index] );
}

int main()
{

	//random seed
	srand(time(NULL));
	RandomizedQueue<int> q;
	RandomizedQueue<int>::iterator it;

	for(int i = 0; i<5; i++)
		q.enqueue(i);

	for(int i = 0; i < 5; i ++)
		std::cout << q.sample() << "\n";

	std::cout << "Using the iterator" << "\n";

	for(it = q.begin(); it != q.end(); ++it)
		std::cout << *it  << "\n";

	for(int i = 0; i < 5; i++)
		std::cout << q.dequeue() << "\n";
	return 0;
}
