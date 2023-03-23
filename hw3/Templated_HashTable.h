#ifndef TEMPLATED_HASTABLE_H
#define TEMPLATED_HASTABLE_H
#include <vector>
#include <string>
#include "WordItem.h"
using namespace std;




template <class HashedObj>
class HashTable
{
	public:
		explicit HashTable(  HashedObj & notFound, int size = 101 );
		HashTable(  HashTable & rhs )
                   : ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ),
                     array( rhs.array ), currentSize( rhs.currentSize ) { }

		 HashedObj & find(  HashedObj & x ) ;

		void insert(  HashedObj & x );
		void remove(  HashedObj & x );
		void showLoadFactor();

		 HashTable & operator=(  HashTable & rhs );

		enum EntryType { ACTIVE, EMPTY, DELETED };
          
	private:
		struct HashEntry
		{
			 HashedObj element;
			 EntryType info;

			 HashEntry(  HashedObj & e = HashedObj( ), 
						EntryType i = EMPTY )
					  : element( e ), info( i ) { }
		};
            
		vector<HashEntry> array;
		int currentSize;
		 HashedObj ITEM_NOT_FOUND;

		bool isActive( int currentPos ) const ;
		int findPos(  HashedObj & x ) const;
		void rehash( );
};




		int hashFunction( WordItem & key, int tableSize ) 
		{
			int hashVal = 0;

			
			string keyEle = key.getKey();
			for( int i = 0; i < keyEle.length(); i++ )
				hashVal = hashVal * 37 + keyEle[ i ];

			hashVal = hashVal % tableSize;
			if( hashVal < 0 )
				hashVal = hashVal + tableSize;

			return hashVal;
		}




        /**
         * Internal method to test if a positive number is prime.
         * Not an efficient algorithm.
         */
        bool isPrime( int n )
        {
            if ( n == 2 || n == 3 )
                return true;

            if ( n == 1 || n % 2 == 0 )
                return false;

            for ( int i = 3; i * i <= n; i += 2 )
                 if ( n % i == 0 )
                     return false;

            return true;
        }

	 /**
         * Internal method to return a prime number 
	    * at least as large as n.  Assumes n > 0.
         */
        int nextPrime( int n )
        {
              if ( n % 2 == 0 )
                  n++;

              for ( ; ! isPrime( n ); n += 2 )
                   ;

              return n;
        }








        /**
         * Construct the hash table.
         */
        template <class HashedObj>
        HashTable<HashedObj>::HashTable(  HashedObj & notFound, 
											  int size )
         		 : ITEM_NOT_FOUND( notFound ), array( nextPrime( size ) )
        {
			currentSize = 0;
		}

		

        template <class HashedObj>
        void HashTable<HashedObj>::showLoadFactor()
        {
			cout <<"After preprocessing, the unique word count is " << currentSize << ". current load ratio is " << double(currentSize)/array.size() << endl;
		}

        /**
         * Method that performs quadratic probing resolution.
         * Return the position where the search for x terminates.
         */
        template <class HashedObj>
        int HashTable<HashedObj>::findPos(  HashedObj & x ) const
        {
               int collisionNum = 0;
               int currentPos = hashFunction( x, array.size( ) );

               while ( array[ currentPos ].info != EMPTY && 
				   array[ currentPos ].element != x )
               {
                   currentPos += 2 * ++collisionNum - 1;  // add the difference
                   if ( currentPos >= array.size( ) )             // perform the mod
                       currentPos -= array.size( );               // if necessary
               }
               return currentPos;
        }

       /**
         * Return true if currentPos exists and is active.
         */
        template <class HashedObj>
        bool HashTable<HashedObj>::isActive( int currentPos ) const
        {
              return array[ currentPos ].info == ACTIVE;
        }


        /**
         * Remove item x from the hash table.
         *  x has to be in the table
         */
        template <class HashedObj>
        void HashTable<HashedObj>::remove(  HashedObj & x )
        {
              int currentPos = findPos( x );
              if ( isActive( currentPos ) )
                  array[ currentPos ].info = DELETED;
        }


        /**
         * Find item x in the hash table.
         * Return the matching item, or ITEM_NOT_FOUND, if not found.
         */
        template <class HashedObj>
         HashedObj & HashTable<HashedObj>::find(  HashedObj & x ) 
                                                                                                             
        {
             int currentPos = findPos( x );
             if (isActive( currentPos )) 
                  return array[ currentPos ].element; 
 
             return   ITEM_NOT_FOUND;
        }

       /**
         * Insert item x into the hash table. If the item is
         * already present, then do nothing.
         */
        template <class HashedObj>
        void HashTable<HashedObj>::insert(  HashedObj & x )
        {

             // Insert x as active
             int currentPos = findPos( x );
             if ( isActive( currentPos ) )
                  return;
             array[ currentPos ] = HashEntry( x, ACTIVE );

             // enlarge the hash table if necessary 
	       if ( ++currentSize >= array.size( ) / 1.2 )
                rehash( );
        }


        /**
         * Expand the hash table.
         */
        template <class HashedObj>
        void HashTable<HashedObj>::rehash( )
        {
            vector<HashEntry> oldArray = array;

            // Create new double-sized, empty table
            array.resize( nextPrime( 2 * oldArray.size( ) ) );
            for ( int j = 0; j < array.size( ); j++ )
                 array[ j ].info = EMPTY;

            // Copy table over
            currentSize = 0;
            for ( int i = 0; i < oldArray.size( ); i++ )
                if ( oldArray[ i ].info == ACTIVE )
                     insert( oldArray[ i ].element );

			cout << "rehashed..." << endl;
			cout << "previous table size:" << oldArray.size() << ", new table size: " << array.size() << ", current unique word count: " << currentSize << ", current load factor: " << double(currentSize)/array.size() << endl;
        }





#endif