#ifndef ALASYAM_LIST
#define ALASYAM_LIST
#include <iostream>
#include<fstream>
#include "Node.h"

using namespace std;

template <class T>
class Sequence
{
private:

	// MEMBER DATA.  These are the data items that each sequence object will contain.  For a
	// doubly-linked list, each sequence will have a head and tail pointer, and numElts
	SequenceNode<T> *head;
	SequenceNode<T> *tail;
	int numElts;   // Number of elements in the sequence

public:
    Sequence();
    ~Sequence();
    void AddToFront( T& data );
    void AddToEnd( T& data );
    bool AddAtIndex( T& data, int index);
    void AddBefore( SequenceNode<T>*p,T& data );
    void AddAfter( SequenceNode<T>*p,T& data );
    T RemoveFromFront();
    T RemoveFromEnd();
    void RemoveTheFirst(T& data);
    void RemoveAllOf(T& data);
    T RemoveBefore(SequenceNode<T>* node);
    T RemoveAfter(SequenceNode<T>* node);
    bool ElementExists(T& data);
    SequenceNode<T>* Find(T& data);
    int IndexOf(T& data);
    T RetrieveFront();
    T RetrieveEnd();
    T Retrieve( int index);
    void printList();
    void Empty();
    int Length();
};// End of class Sequence

#endif
