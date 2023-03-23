#ifndef TEMPLATED_SORTING_H
#define TEMPLATED_SORTING_H
#include "randgen.h"
          /**
         * Standard swap
         */
        template <class Comparable>
        inline void swapFunc( Comparable & obj1, 
									Comparable & obj2 )
        {
              Comparable tmp = obj1;
              obj1 = obj2;
              obj2 = tmp;
        }

template <class Comparable>
void insertionSort (vector <Comparable> & a)
{
	int j;
               // loop over the passes
	for (int p = 1;  p < a.size(); p++)
	{
		Comparable tmp = a[p];
                            // loop over the elements
		for (j = p; j > 0 &&  tmp < a[j-1]; j--)
			a[j] = a[j-1];
		a[j] = tmp;
	}
}


template <class Comparable>
void shellsort (vector <Comparable> & a)
{
	int j;
	// Loop over increments
	for (int gap = a.size()/2;  gap > 0; gap/=2)
		// Loop over elements
		for (int i = gap; i < a.size(); i++)
		{
			Comparable tmp = a[i];
			// Loop over elements that are gap apart
			for (j = i; j >= gap &&  tmp < a[j – gap]; j –= gap)
				a[j] = a[j –gap];
			a[j] = tmp;
		}
}

inline int leftChild( int i )
{
	return 2*i+1;
}

template <class Comparable>
void heapsort(vector<Comparable> & a)
{
	// buildHeap
	for (int i = a.size()/2; i >=0; i--)
		percDown(a, i, a.size());

	// sort
	for (int j = a.size() -1; j >0; j--)
	{
  	     swapFunc(a[0], a[j]);    // swap max to the last pos.
          percDown(a, 0, j); // re-form the heap
	}
}

template <class Comparable>  // for deleteMax
        // a is the array, i is the position to percolate down from
        // n is the logical size of the array
        void percDown( vector<Comparable> & a, int i, int n )
        {
                int child;
                Comparable tmp;

                for (tmp=a[i] ; leftChild(i) < n; i = child )
                {
                     child = leftChild(i);
                     if ( child != n-1 && a[ child  ] < a[ child+1 ] )
                          child++;
                     if ( a[child ] > tmp )
                          a[i] = a[ child ];
                     else
                          break;
               } 
               a[ i ] = tmp;
        }
 

		         /**
         * Mergesort algorithm (driver).
         */
        template <class Comparable>
        void mergeSort( vector<Comparable> & a )
        {
              vector<Comparable> tmpArray( a.size( ) );

              mergeSort( a, tmpArray, 0, a.size( ) - 1 );
        }


        /**
         * Internal method that makes recursive calls.
         * a is an array of Comparable items.
         * tmpArray is an array to place the merged result.
         * left is the left-most index of the subarray.
         * right is the right-most index of the subarray.
         */
        template <class Comparable>
        void mergeSort( vector<Comparable> & a,
             vector<Comparable> & tmpArray, int left, int right )
        {
              if ( left < right )
              {
                    int center = ( left + right ) / 2;
                    mergeSort( a, tmpArray, left, center );
                    mergeSort( a, tmpArray, center + 1, right );
                    merge( a, tmpArray, left, center + 1, right );
              }
        }

		        /**
         * Internal method that merges two sorted halves of a subarray.
         * a is an array of Comparable items.
         * tmpArray is an array to place the merged result.
         * leftPos is the left-most index of the subarray.
         * rightPos is the index of the start of the second half.
         * rightEnd is the right-most index of the subarray.
         */
        template <class Comparable>
        void merge(  vector<Comparable> & a, 
					 vector<Comparable> & tmpArray,
		                  int leftPos, int rightPos, int rightEnd )
        {
               int leftEnd = rightPos - 1;
               int tmpPos = leftPos;
               int numElements = rightEnd - leftPos + 1;
            // Main loop
            while ( leftPos <= leftEnd && rightPos <= rightEnd )
                 if ( a[ leftPos ] <= a[ rightPos ] )
                     tmpArray[ tmpPos++ ] = a[ leftPos++ ];
                 else
                     tmpArray[ tmpPos++ ] = a[ rightPos++ ];

            while ( leftPos <= leftEnd )    // Copy rest of first half
                tmpArray[ tmpPos++ ] = a[ leftPos++ ];

            while ( rightPos <= rightEnd )  // Copy rest of right half
                tmpArray[ tmpPos++ ] = a[ rightPos++ ];

            // Copy tmpArray back
            for ( int i = 0; i < numElements; i++, rightEnd-- )
                a[ rightEnd ] = tmpArray[ rightEnd ];
        }


		 /**
  * Quicksort algorithm (driver).
 */
 template <class Comparable>
 void quicksort( vector<Comparable> & a )
 {
       quicksort( a, 0, a.size( ) - 1 );
 }

            


       /** Return median of left, center, and right.
           *   Order these and hide the pivot.
         */
        template <class Comparable>
        const Comparable & median3( vector<Comparable> & a, 
									       int left, int right )
        {
              int center = ( left + right ) / 2;
              if ( a[ center ] < a[ left ] )
                swapFunc( a[ left ], a[ center ] );
              if ( a[ right ] < a[ left ] )
                swapFunc( a[ left ], a[ right ] );
              if ( a[ right ] < a[ center ] )
                swapFunc( a[ center ], a[ right ] );

              // Place pivot at position right - 1
              swapFunc( a[ center ], a[ right - 1 ] );
              return a[ right - 1 ];
        }


	  /**
         * Internal quicksort method that makes recursive calls.
         * Uses median-of-three partitioning and a cutoff of 10.
         * a is an array of Comparable items.
         * left is the left-most index of the subarray.
         * right is the right-most index of the subarray.
         */
        template <class Comparable>
        void quicksort( vector<Comparable> & a, 
						   int left, int right )
        {
              if ( left + 10 <= right )
              {
                   Comparable pivot = median3( a, left, right );
						// Begin partitioning
                int i = left, j = right - 1;
                for ( ; ; )
                {
                    while ( a[ ++i ] < pivot ) { }

                    while ( pivot < a[ --j ] ) { }

                    if ( i < j )
                          swapFunc( a[ i ], a[ j ] );
                    else
                          break;
                }

                 swapFunc( a[ i ], a[ right - 1 ] );   // Restore pivot

                 quicksort( a, left, i - 1 );       // Sort small elements
                 quicksort( a, i + 1, right );    // Sort large elements
            }
            else  // Do an insertion sort on the subarray
                 insertionSort( a, left, right );
        }

      /**
         * Internal insertion sort routine for subarrays
         * that is used by quicksort.
         * a is an array of Comparable items.
         * left is the left-most index of the subarray.
         * right is the right-most index of the subarray.
         */
        template <class Comparable>
        void insertionSort( vector<Comparable> & a, int left, int right )
        {
             for ( int p = left + 1; p <= right; p++ )
             {
                  Comparable tmp = a[ p ];
                  int j;

                  for ( j = p; j > left && tmp < a[ j - 1 ]; j-- )
                       a[ j ] = a[ j - 1 ];
                  a[ j ] = tmp;
				  
            }
		}	 


 template <class Comparable>
 void quicksortFirst( vector<Comparable> & a )
 {
       quicksortFirst( a, 0, a.size( ) - 1 );
 }

 /*
template <class Comparable>
void quicksortFirst( vector<Comparable> & a, 
						   int left, int right )
{
	if ( left + 10 <= right )
	{
		Comparable pivot = a[left];
		swapFunc(a[left], a[right]);
		// Begin partitioning
		int i = left, j = right;
		for ( ; ; )
		{
			while(i != right)
				while ( a[ ++i ] < pivot ) { }
			while(j != left)
				while ( pivot < a[ --j ] ) { }
			if ( i < j )
				swapFunc( a[ i ], a[ j ] );
			else
				break;
		}

		swapFunc( a[ i ], a[ right ] );   // Restore pivot

		quicksortFirst( a, left, i - 1 );       // Sort small elements
		quicksortFirst( a, i + 1, right );    // Sort large elements
	}

	else  // Do an insertion sort on the subarray
		insertionSort( a, left, right );
}
*/


template <class Comparable>
 void quicksortRandom( vector<Comparable> & a )
 {
       quicksortRandom( a, 0, a.size( ) - 1 );
 }

 /*
template <class Comparable>
        void quicksortRandom( vector<Comparable> & a, 
						   int left, int right )
        {
              if ( left + 10 <= right )
              {
				  RandGen rand;
				  int randomNumber = rand.RandInt(left, right - 1);
                   Comparable pivot = a[randomNumber];
				   swapFunc(a[randomNumber], a[right]);
						// Begin partitioning
                int i = left, j = right;
                for ( ; ; )
                {
                    while ( a[ ++i ] < pivot ) { }

                    while ( pivot < a[ --j ] ) { }

                    if ( i < j )
                          swapFunc( a[ i ], a[ j ] );
                    else
                          break;
                }

                 swapFunc( a[ i ], a[ right - 1 ] );   // Restore pivot

                 quicksortRandom( a, left, i - 1 );       // Sort small elements
                 quicksortRandom( a, i + 1, right );    // Sort large elements
            }
            else  // Do an insertion sort on the subarray
                 insertionSort( a, left, right );
        }
		*/
/*
template <class Comparable>
void quicksortFirst (vector<Comparable> & a )
{
	quicksortFirst(a, 0, a.size() -1);
}

template<class Comparable>
void quicksortFirst(vector<Comparable> & a, int left, int right)
{
	if (left < right)
	{
		int pivot = partitionFirst( a, left, right );

		quicksortFirst( a, left, pivot - 1);
		quicksortFirst(a, pivot + 1, right);
	}
}

template<class Comparable>
int partitionFirst(vector<Comparable> & a, int left, int right)
{
	Comparable pivotItem = a[left];
	int pivotIndex = left;

	for (int idx = left + 1; idx <= right; idx++)
	{
		if (a[idx] < pivotItem) // < operator overloaded for WordItem class
		{
			swapFunc(a[pivotIndex + 1], a[idx]);
			swapFunc(a[pivotIndex], a[pivotIndex + 1]);
			pivotIndex++;
		}
	}
	return pivotIndex;
}
*/


/* This function takes last element as pivot, places 
  the pivot element at its correct position in sorted 
  array, and places all smaller (smaller than pivot) 
  to left of pivot and all greater elements to right 
  of pivot */
template <class Comparable>
int partition(vector<Comparable> & a, int low, int high) 
{ 
    WordItem pivot = a[high]; // pivot 
    int i = (low - 1); // Index of smaller element 
  
    for (int j = low; j <= high - 1; j++) { 
  
        // If current element is smaller than or 
        // equal to pivot 
        if (a[j] <= pivot) { 
  
            i++; // increment index of smaller element 
            swapFunc(a[i], a[j]); 
        }
			
    } 
    swapFunc(a[i + 1], a[high]); 
    return (i + 1); 
} 
  
// Generates Random Pivot, swaps pivot with 
// end element and calls the partition function 
template <class Comparable>
int partition_r(vector<Comparable> & a, int low, int high) 
{ 
    // Generate a random number in between 
    // low .. high 
    srand(time(NULL)); 
    int random = low + rand() % (high - low); 
  
    // Swap A[random] with A[high] 
    swapFunc(a[random], a[high]); 
  
    return partition(a, low, high); 
} 


template <class Comparable>
int partition_1(vector<Comparable> & a, int low, int high) 
{ 

    // Swap A[low] with A[high] 
    swapFunc(a[low], a[high]); 
  
    return partition(a, low, high); 
} 


template <class Comparable>
void quicksortFirst(vector<Comparable> & a, int low, int high) 
{ 
    if (low+10<=high) { 
  
        /* pi is partitioning index, arr[p] is now 
        at right place */
        int pi = partition_1(a, low, high); 
  
        // Separately sort elements before 
        // partition and after partition 
        quicksortFirst(a, low, pi - 1); 
        quicksortFirst(a, pi + 1, high); 
    } 
	else
		insertionSort( a, low, high );
} 
/* The main function that implements QuickSort 
arr[] --> Array to be sorted, 
low --> Starting index, 
high --> Ending index */
template <class Comparable>
void quicksortRandom(vector<Comparable> & a, int low, int high) 
{ 
    if (low+10<=high) { 
  
        /* pi is partitioning index, arr[p] is now 
        at right place */
        int pi = partition_r(a, low, high); 
  
        // Separately sort elements before 
        // partition and after partition 
        quicksortRandom(a, low, pi - 1); 
        quicksortRandom(a, pi + 1, high); 
    } 
	else
		insertionSort( a, low, high );
} 
  
#endif