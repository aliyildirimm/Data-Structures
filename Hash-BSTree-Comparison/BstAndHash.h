#ifndef BstAndHash
#define BstAndHash
#include <string>
#include <vector>
using namespace std;

template<class HashedObj>
struct Node
{
	HashedObj element;
	HashedObj translate;
	Node *next;
	Node(const HashedObj & theElement ="",  const HashedObj & theTranslation="", Node *ch=nullptr)
		: element( theElement ), translate(theTranslation), next( ch )
	{}
};


template <class Comparable>
class BinarySearchTree;

template <class Comparable>
class BinaryNode
{
	Comparable element;
	Comparable translate;
	BinaryNode  *left;
	BinaryNode  *right;

	BinaryNode( const Comparable & theElement,  const Comparable & theTranslation,
		BinaryNode *lt, BinaryNode *rt)
		: element( theElement ), translate(theTranslation), left( lt ), right( rt ) { }

	friend class BinarySearchTree<Comparable>;
};

template <class Comparable>
class BinarySearchTree
{
public:
	explicit BinarySearchTree( const Comparable & notFound );
	/*BinarySearchTree( const BinarySearchTree & rhs );*/
	~BinarySearchTree( );

	const Comparable & findMin( ) const;
	const Comparable & findMax( ) const;
	const Comparable & find( const Comparable & x ) const;
	bool isEmpty( ) const;

	const Comparable & Translate(  const Comparable & x  ) const;
	void Update(const Comparable & x, const Comparable & y);

	void makeEmpty( );
	void insert( const Comparable & x, const Comparable & y );

private:
	BinaryNode<Comparable> *root;
	const Comparable ITEM_NOT_FOUND;

	const Comparable & elementAt( BinaryNode<Comparable> *t ) const;

	void insert( const Comparable & x, const Comparable & y, BinaryNode<Comparable> * & t ) const;
	BinaryNode<Comparable> * findMin( BinaryNode<Comparable> *t ) const;
	BinaryNode<Comparable> * findMax( BinaryNode<Comparable> *t ) const;
	BinaryNode<Comparable> * find( const Comparable & x, BinaryNode<Comparable> *t ) const;
	void makeEmpty( BinaryNode<Comparable> * & t ) const;
};

static int a = 0;
template <class Comparable>
BinarySearchTree<Comparable>::
	BinarySearchTree(const Comparable & notFound ) :
	ITEM_NOT_FOUND( notFound ), root( NULL )
{}

template <class Comparable>
void BinarySearchTree<Comparable>::
	Update(const Comparable & x, const Comparable & y ) 
{
	Comparable str = find(x,root)->translate;
	str = str + ", " + y;
	find(x,root)->translate = str;
	cout << "***UPDATED***" << endl;
}

template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::
	Translate( const Comparable & x  ) const
{
	return (find(x,root)->translate);
}


template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::
	elementAt( BinaryNode<Comparable> *t ) const
{
	return t == NULL ? ITEM_NOT_FOUND : t->translate;
}

template <class Comparable>
bool BinarySearchTree<Comparable>::isEmpty() const
{
	if(root == nullptr)
		return true;
	else
		return false;

}
template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::
	find( const Comparable & x ) const
{
	return elementAt( find( x, root ) );
}

template <class Comparable>
BinaryNode<Comparable> *
	BinarySearchTree<Comparable>::
	find( const Comparable & x, BinaryNode<Comparable> * t ) const
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
const Comparable & BinarySearchTree<Comparable>::findMin( ) const
{
	return elementAt( findMin( root ) );
}


template <class Comparable>
BinaryNode<Comparable> *
	BinarySearchTree<Comparable>::findMin( BinaryNode<Comparable> *t ) 
	const
{
	if( t == NULL )
		return NULL;
	if( t->left == NULL )
		return t;
	return findMin( t->left );
}

template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::findMax( ) const
{
	return elementAt( findMax( root ) );
}


template <class Comparable>
BinaryNode<Comparable> *
	BinarySearchTree<Comparable>::findMax( BinaryNode<Comparable> *t ) 
	const
{
	if( t != NULL )
		while( t->right != NULL )
			t = t->right;
	return t;
}

template <class Comparable>
void BinarySearchTree<Comparable>::insert( const Comparable &x, const Comparable &y ) 
{
	insert( x, y, root );
}

template <class Comparable>
void BinarySearchTree<Comparable>::
	insert( const Comparable & x, const Comparable & y, BinaryNode<Comparable> * &t ) const
{
	if( t == NULL ) //  create a new node at the right place
		t = new BinaryNode<Comparable>( x, y, NULL, NULL );
	else if( x < t->element )
		insert( x,y, t->left );  // insert at the left or 
	else if( t->element < x )
		insert( x,y, t->right );  // right subtree
	else{
		if(t->translate != y){
			t->translate = t->translate +", " + y;
		}
	}

}     


template <class Comparable>
void BinarySearchTree<Comparable>::makeEmpty( )
{
	makeEmpty( root );
}


template <class Comparable>
void BinarySearchTree<Comparable>::
	makeEmpty( BinaryNode<Comparable> * & t ) const
{
	if( t != NULL )
	{
		makeEmpty( t->left );
		makeEmpty( t->right );
		delete t;
	}
	t = NULL;
}


template <class Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree( )
{
	makeEmpty( );
}

template <class HashedObj>
class HashTable
{
public:
	HashTable( const HashedObj & notFound, int size = 53 );
	HashTable( const HashTable & rhs )
		: ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ), 
		theLists( rhs.theLists ) { }

	const HashedObj & find( const HashedObj & x );

	void makeEmpty( );
	void insert( const HashedObj & x,  const HashedObj & y );
	int hash( const string & key, int tableSize );

	int nextPrime(int n);
	bool isPrime(int n);
	void rehash( );
	const HashTable & operator=( const HashTable & rhs);
	int Size() const ;
	int TableSize() const;

private:
	vector<Node<HashedObj> > theLists;   
	// The array of Lists
	
	const HashedObj ITEM_NOT_FOUND;
	int currentSize;

};



template <class HashedObj>
HashTable<HashedObj>::HashTable( 
	const HashedObj & notFound, int size )
	: ITEM_NOT_FOUND( notFound ), theLists( nextPrime( size ) )
{
	currentSize = 0;
}

template <class HashedObj>
int HashTable<HashedObj>::Size( ) const
{return currentSize;}

template <class HashedObj>
int HashTable<HashedObj>::TableSize( ) const
{return theLists.size();}

template <class HashedObj>
int HashTable<HashedObj>::hash( const string & key, int tableSize )
{
      int hashVal = 0;
  
    for (int i = 0; i < key.length();i++) 
	  hashVal = 37 * hashVal + key[ i ];

    hashVal = hashVal % tableSize;

    if (hashVal < 0) 
	  hashVal = hashVal + tableSize;

   return(hashVal);

}

template <class HashedObj>
bool HashTable<HashedObj>:: isPrime( int n )
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

template <class HashedObj>
int HashTable<HashedObj>:: nextPrime( int n )
{
	if ( n % 2 == 0 )
		n++;

	for ( ; ! isPrime( n ); n += 2 )
		;

	return n;
}


template <class HashedObj>
void HashTable<HashedObj>::makeEmpty( )
{
	for( int i = 0; i < theLists.size( ); i++ ){
		theLists[i].next = nullptr;
	}
}

template <class HashedObj>
void HashTable<HashedObj>::insert( const HashedObj & x, const HashedObj & y )
{
	int index = hash(x,theLists.size());
	Node<HashedObj> *ptr = new Node<HashedObj>(x, y);
	Node<HashedObj> *hold = &theLists[index];
	Node<HashedObj> *temp = hold;
	if(theLists[index].next == nullptr)
	{
		theLists[index].next = ptr;
	}
	else{
		bool check = true;
		while(temp->next != nullptr && check){
			if(temp->element != x)
				temp = temp->next;
			else{
				if(temp->translate.find(y) == string::npos){
					temp->translate += ", " + y;
				}
				check = false;
			}
		}

		if(temp->element != x)
			 temp->next = ptr;
		else{
			if(temp->translate.find(y) == string::npos){
				temp->translate += ", " + y;
			}
		}
	}
	if ( ++currentSize > theLists.size( ) / 2 )
		rehash( );
}


template <class HashedObj>
 const HashedObj & HashTable<HashedObj>::
	find( const HashedObj & x )
{
   int index = hash( x, theLists.size( ) );
   Node<HashedObj> *current = theLists[index].next;
   while(current != nullptr){
	   if(current->element == x)
		   return current->translate;

	   current = current->next;
   }
   return ITEM_NOT_FOUND;
}

 template <class HashedObj>
 void HashTable<HashedObj>::rehash( )
 {
	 vector<Node<HashedObj>> oldArray = theLists;

	 makeEmpty();
	 theLists.resize( nextPrime( 2 * oldArray.size( ) ) );

	cout << "rehashed... " <<endl;
	cout << "previous table size: " << oldArray.size() <<  ", new table size: " << theLists.size() << 
		", current unique word count " << currentSize << ", current load factor: " ;
	int size = theLists.size();
	double ratio = (double) (currentSize-1)/size;
	cout << ratio << endl; 

	 currentSize = 0;
	 for ( int i = 0; i < oldArray.size( ); i++ ){
		 Node<HashedObj> *ptr = oldArray[i].next;
		 while(ptr != nullptr){
			 if(ptr->element != ITEM_NOT_FOUND){
				 insert(ptr->element , ptr->translate);
			 }
			 ptr = ptr->next;
		 }
	 }
 }

#endif