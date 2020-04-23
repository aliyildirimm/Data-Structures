#ifndef BinaryHeap_
#define BinaryHeap_
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//Ali Yýldýrým - 23737 - CS300 HW#4 - HEAP

template <class Comparable>
class BinaryHeap
{
public:
	explicit BinaryHeap();

	void insert( const Comparable & x );
	Comparable deleteMin();
	void buildHeap( vector<Comparable> Input);
	Comparable value(int i);
	int findNum(int n);
	bool empty();
	int Size();
	void decrease(int n);

private:
	int currentSize; // Number of elements in heap
	vector<Comparable>array; // The heap array

	void percolateDown( int hole );
};

template <class Comparable>
BinaryHeap<Comparable>::BinaryHeap()
{
	currentSize = 0;
	array.resize(1);
}

template <class Comparable>
Comparable BinaryHeap<Comparable>::value(int i)
{
	return (array[i]);
}

template <class Comparable>
void BinaryHeap<Comparable>::decrease(int n)
{
	Comparable temp; 
	for (int i = 1; i <= currentSize; i++)
	{
		temp = (array[i] - n);
		array[i] = temp;
	}
}

template <class Comparable>
int BinaryHeap<Comparable>::findNum(int n)
{
	int count = 0;
	for(int i =1; i<=currentSize; i++)
	{
		if(array[i] == n)
			count++;
	}
	return count;
}

template <class Comparable>
bool BinaryHeap<Comparable>::empty()
{
	if(currentSize == 0)
		return true;
	return false;
}

template <class Comparable>
int BinaryHeap<Comparable>::Size()
{
	return currentSize;
}

template <class Comparable>
void BinaryHeap<Comparable>::insert( const Comparable & x )
{
	int hole = ++currentSize;
	if(hole > 1)
	{
		array.resize(currentSize+1);

		for (  ; hole >1 && array[ hole / 2 ] > x ; hole /= 2 ){
			array[ hole ] = array[ hole / 2 ];
		}

		array[hole] = x;
		return;
	}
	else if(hole <= 1)
		array.push_back(x);
}

template <class Comparable>
Comparable BinaryHeap<Comparable>::deleteMin()
{
	Comparable minItem;
	minItem = array[ 1 ];
	array[ 1 ] = array[ currentSize-- ];
	array.pop_back();
	if(currentSize != 0)
		percolateDown( 1 );
	return minItem;
}

template <class Comparable>
void BinaryHeap<Comparable>::percolateDown( int hole )
{
	int child;
	Comparable tmp = array[hole];  // tmp is the item that will 
	// be percolated down
	for( ; hole * 2 <= currentSize; hole = child )
	{
		child = hole * 2;
		if ( child != currentSize && array[child + 1] < array[child ] )
			child++;
		if ( tmp > array[child] )
			array[ hole ] = array[ child ];
		else
			break;
	}
	array[ hole ] = tmp;
}

template <class Comparable>
void BinaryHeap<Comparable>::buildHeap( vector<Comparable> Input)
{
	array = Input; // copy input array to private array;
	currentSize = Input.size();
	for ( int i = currentSize / 2; i > 1; i = i-1 )
		percolateDown( i );
}

#endif