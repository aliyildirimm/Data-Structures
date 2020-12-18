#ifndef STACK
#define STACK

using namespace std;

template <class T>
class Stack
{
public:
	Stack( );
	Stack( const Stack & rhs );
	~Stack( );

	void makeEmpty( );
	bool isEmpty( ) const;

	void pop( );
	void push( const T & x );
	T topAndPop( );
	const T & top( ) const;

	const Stack & operator=( const Stack & rhs );

private:
	struct Node
	{
		T   element;
		Node *next;

		Node( const T & theElement, Node * n = NULL )
			: element( theElement ), next( n ) { }
	};

	Node *topOfStack;  // list itself is the stack
};

template <class T>
Stack<T>::Stack( )
{
	topOfStack = NULL;
}

template <class T>
bool Stack<T>::isEmpty( ) const
{
	return topOfStack == NULL;
}

template <class T>
const T & Stack<T>::top( ) const
{
	return topOfStack->element;
}

template <class T>
void Stack<T>::pop( )
{
	Node *oldTop = topOfStack;
	topOfStack = topOfStack->next;
	delete oldTop;
}

template <class T>
void Stack<T>::push( const T & x )
{
	topOfStack = new Node( x, topOfStack );
}

template <class T>
T Stack<T>::topAndPop( )
{
	T topItem = top( );
	pop( );
	return topItem;
}

template <class T>
void Stack<T>::makeEmpty( )
{
	while ( topOfStack != nullptr )
		pop( );
}

template <class T>
const Stack<T> & Stack<T>::
	operator=( const Stack<T> & rhs )
{
	if ( this != &rhs )
	{
		makeEmpty( );
		if ( rhs.isEmpty( ) )
			return *this;

		Node *rptr = rhs.topOfStack;
		Node *ptr  = new Node( rptr->element );
		topOfStack = ptr;

		for ( rptr = rptr->next; rptr != NULL; rptr = rptr->next )
			ptr = ptr->next = new Node( rptr->element );
	}
	return *this;
}

template <class T>
Stack<T>::Stack( const Stack<T> & rhs )
{
	topOfStack = NULL;
	*this = rhs; // deep copy 
}

template <class T>
Stack<T>::~Stack( )
{
	makeEmpty( );
}

#endif
