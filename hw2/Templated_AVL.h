#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <vector>
#include <string>

/*
struct DocumentItem {
	std::string documentName;
	int count;
};

struct WordItem {
	string word;
	vector<DocumentItem> list;
	// List of DocumentItemís. In order to keep the documents 
//you can again use the BST that you are going to implement.
};
*/

template <class Comparable>
class AvlNode
{
	Comparable element;
	AvlNode   		*left;
	AvlNode   		*right;
	int        		height;

	AvlNode(  Comparable & theElement, 
		AvlNode *lt, AvlNode *rt, int h = 0 )
			: element( theElement ), left( lt ), right( rt ), height( h ) { }

	template <class Comparable>
	friend class AvlTree;
};
 
template <class Comparable>
class AvlTree
{
	public:
		explicit AvlTree(  Comparable & notFound);
		AvlTree(  AvlTree & rhs );
	    ~AvlTree( );

         Comparable & findMin( ) ;
         Comparable & findMax( ) ;
         Comparable & find(  Comparable & x ) ;
        bool isEmpty( ) ;
        void printTree( ) ;

        void makeEmpty( );
        void insert(  Comparable & x );
        void remove(  Comparable & x );

         AvlTree & operator=(  AvlTree & rhs );
        AvlNode<Comparable> *root;
         Comparable ITEM_NOT_FOUND;

		 Comparable & elementAt( AvlNode<Comparable> *t ) ;

		void insert(  Comparable & x, AvlNode<Comparable> * & t ) ;
        void remove( Comparable & x, AvlNode<Comparable> * & t ) ;

        AvlNode<Comparable> * findMin( AvlNode<Comparable> *t ) ;
        AvlNode<Comparable> * findMax( AvlNode<Comparable> *t ) ;
        AvlNode<Comparable> * find(  Comparable & x, AvlNode<Comparable> *t ) ;
        void makeEmpty( AvlNode<Comparable> * & t ) ;
        void printTree( AvlNode<Comparable> *t ) ;
        AvlNode<Comparable> * clone( AvlNode<Comparable> *t ) ;

            // Avl manipulations
        int height( AvlNode<Comparable> *t ) ;
        int max( int lhs, int rhs ) ;
        void rotateWithLeftChild( AvlNode<Comparable> * & k2 ) ;
        void rotateWithRightChild( AvlNode<Comparable> * & k1 ) ;
        void doubleWithLeftChild( AvlNode<Comparable> * & k3 ) ;
        void doubleWithRightChild( AvlNode<Comparable> * & k1 ) ;
};


template <class Comparable>
AvlTree<Comparable>::
AvlTree( Comparable & notFound ) :
	ITEM_NOT_FOUND( notFound ), root( NULL )
{
}

template <class Comparable>
 Comparable & AvlTree<Comparable>::
elementAt( AvlNode<Comparable> *t ) 
{
	return t == NULL ? ITEM_NOT_FOUND : t->element;
}

template <class Comparable>
 Comparable & AvlTree<Comparable>::
find(  Comparable & x ) 
{
	return elementAt( find( x, root ) );
}

template <class Comparable>
void AvlTree<Comparable>::insert(  Comparable & x )
{
	insert( x, root );
}

template <class Comparable>
AvlNode<Comparable> *
AvlTree<Comparable>::
find(  Comparable & x, AvlNode<Comparable> * t ) 
{
	if ( t == NULL )
		return NULL;
	else if( x < t->element )
		return find( x, t->left );
	else if( t->element < x )
		return find( x, t->right );
	else
		return t;    // Match    
}

template <class Comparable>
 Comparable & AvlTree<Comparable>::findMin( ) 
{
	return elementAt( findMin( root ) );
}

template <class Comparable>
AvlNode<Comparable> *
AvlTree<Comparable>::findMin( AvlNode<Comparable> *t ) 
																	
{
	if( t == NULL )
		return NULL;
	if( t->left == NULL )
		return t;
	return findMin( t->left );
}

template <class Comparable>
 Comparable & AvlTree<Comparable>::findMax( ) 
{
	return elementAt( findMax( root ) );
}

template <class Comparable>
AvlNode<Comparable> *
AvlTree<Comparable>::findMax( AvlNode<Comparable> *t ) 
																	
{
	if( t != NULL )
		while( t->right != NULL )
			t = t->right;
	return t;
}


template <class Comparable>
int AvlTree<Comparable>::height( AvlNode<Comparable> *t ) 
 {
      if (t == NULL)
	return -1;
	
      return t->height;
}

template <class Comparable>
int AvlTree<Comparable>::max( int lhs, int rhs ) 
{
      if (lhs > rhs)
		return lhs;
      return rhs;            
}

template <class Comparable>
 void AvlTree<Comparable>::insert
                     (  Comparable & x, AvlNode<Comparable> * & t ) 
 {
      if ( t == NULL )
           t = new AvlNode<Comparable>( x, NULL, NULL );

      else if ( x < t->element ) {
           // X should be inserted to the left tree!
           insert( x, t->left );
           // Check if the left tree is out of balance (left subtree grew in height!)
           if ( height( t->left ) - height( t->right ) == 2 )
                if ( x < t->left->element )  // X was inserted to the left-left subtree!
                     rotateWithLeftChild( t );
                else			     // X was inserted to the left-right subtree!
                     doubleWithLeftChild( t );
       }
       else if( t->element < x )
       {    // Otherwise X is inserted to the right subtree
            insert( x, t->right );
			if ( height( t->right ) - height( t->left ) == 2 )
		// height of the right subtree increased
               if ( t->right->element < x )
		     // X was inserted to right-right subtree
                       rotateWithRightChild( t );
               else // X was inserted to right-left subtree
                       doubleWithRightChild( t );
            }
            else
                ;  // Duplicate; do nothing
            
	// update the height the node
            t->height = max( height( t->left ), height( t->right ) ) + 1;
}

template <class Comparable>
void AvlTree<Comparable>::rotateWithLeftChild( 
	AvlNode<Comparable> * & k2 ) 
{
       AvlNode<Comparable> *k1 = k2->left;
       k2->left = k1->right;
       k1->right = k2;
       k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
       k1->height = max( height( k1->left ), k2->height ) + 1;
       k2 = k1;
}

template <class Comparable>
void AvlTree<Comparable>::rotateWithRightChild
	( AvlNode<Comparable> * & k1 ) 
{
       AvlNode<Comparable> *k2 = k1->right;
       k1->right = k2->left;
       k2->left = k1;
       k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
       k2->height = max( height( k2->right ), k1->height ) + 1;
       k1 = k2;
}

template <class Comparable>
void AvlTree<Comparable>::doubleWithLeftChild
		( AvlNode<Comparable> * & k3 ) 
{
      rotateWithRightChild( k3->left );
      rotateWithLeftChild( k3 );
}

template <class Comparable>
void AvlTree<Comparable>::doubleWithRightChild
	( AvlNode<Comparable> * & k1 ) 
{
     rotateWithLeftChild( k1->right );
     rotateWithRightChild( k1 );
}

template <class Comparable>
AvlTree<Comparable>::~AvlTree( )
{
	makeEmpty( );
}

template <class Comparable>
void AvlTree<Comparable>::makeEmpty( )
{
	makeEmpty( root );
}


template <class Comparable>
void AvlTree<Comparable>::
makeEmpty( AvlNode<Comparable> * & t ) 
{
	if( t != NULL )
	{
		makeEmpty( t->left );
		makeEmpty( t->right );
		delete t;
	}
	t = NULL;
}

//#include "Templated_AVL.cpp"
#endif