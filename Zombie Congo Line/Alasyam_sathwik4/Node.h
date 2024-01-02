#ifndef NODE
#define NODE
#include <iostream>
#include<fstream>

using namespace std;

template <class T>
class SequenceNode {
private:
    SequenceNode<T> *next;
    SequenceNode<T> *prev;
    T elt;
public:
    SequenceNode();
    SequenceNode(T& item);
    ~SequenceNode();
    void setData(T& item);
    void setNext(SequenceNode<T>* n);
    void setPrev(SequenceNode<T>* p);
    void setNextNull();
    void setPrevNull();
    T& getData ();
    SequenceNode<T> *getNext();
    SequenceNode<T> *getPrev();
};// End of class SequenceNode

#endif
