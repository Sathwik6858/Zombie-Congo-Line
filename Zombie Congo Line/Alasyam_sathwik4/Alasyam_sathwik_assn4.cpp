#include <iostream>
#include<stdlib.h>
#include<time.h>
#include "Alasyam_list.h"
#include "Node.h"
#include "Zombie.h"

using namespace std;

template <class T>
SequenceNode<T>::SequenceNode() {
    next = NULL;
    prev = NULL;
}

template <class T>
SequenceNode<T>::SequenceNode(T& item) {
    next = NULL;
    prev = NULL;
    elt = item;
}

template <class T>
SequenceNode<T>::~SequenceNode() {};

template <class T>
void SequenceNode<T>::setData(T& item)
{
    elt = item;
}

template <class T>
void SequenceNode<T>::setNext(SequenceNode<T>* n)
{
    next = n;
}

template <class T>
void SequenceNode<T>::setPrev(SequenceNode<T>* p)
{
    prev = p;
}

template <class T>
void SequenceNode<T>::setNextNull()
{
    next = NULL;
}

template <class T>
void SequenceNode<T>::setPrevNull()
{
    prev = NULL;
}

template <class T>
T& SequenceNode<T>::getData ()
{
    return elt;
}

template <class T>
SequenceNode<T>* SequenceNode<T>::getNext()
{
    return next;
}

template <class T>
SequenceNode<T>* SequenceNode<T>::getPrev()
{
    return prev;
}


// Constructor: Sequence -- Initialize an empty sequence of given size
//                          starting from 0.
// Inputs: nothing
template <class T>
Sequence<T>::Sequence(){

    // Initialize head, tail to null and number of elements to zero
    head = NULL;

    tail = NULL;

    numElts = 0;
}


//------------------------------------------------
// Destructor : Sequence - Destroys the Sequence
//------------------------------------------------
template <class T>
Sequence<T>::~Sequence(){}


//--------------------------------------------------------------------
// Function: AddToFront -- Add an element at the front of the sequence.
// Inputs: T data -- element to be added
// Returns: void -- nothing
//----------------------------------------------------------------------
template <class T>
void Sequence<T>::AddToFront( T& data ){

    // create a new sequence node with data

    SequenceNode<T>* firstNode = new SequenceNode<T>(data);
    // If head is null add element at head
    if (head == NULL){

        head = firstNode;

        tail = firstNode;

        numElts ++ ;
    }

    else{
        firstNode->setNext(head);

        head->setPrev(firstNode);

        head = firstNode;

        numElts++;

    }
}

//--------------------------------------------------------------------
// Function: AddToEnd -- Add an element at the end of the sequence.
// Inputs: T data -- element to be added
// Returns: void -- nothing
//----------------------------------------------------------------------
template <class T>
void Sequence<T>::AddToEnd( T& data ){

    // create a new sequence node with data v

    SequenceNode<T>* lastNode = new SequenceNode<T>(data);
    // If head is null add element at head
    if (head == NULL){

        head = lastNode;

        tail = lastNode;

        numElts ++ ;
    }
    // Otherwise point the next of tail to last node
    // point last node to tail
    // Now the new tail is last node so point the tail to it
    // Increment number of elements by 1
    else{
        tail->setNext(lastNode);

        lastNode->setPrev(tail);

        tail = lastNode;

        numElts ++ ;
    }
}

//--------------------------------------------------------------------
// Function: AddAtIndex -- Add an element at the specified index of the sequence.
// Inputs: T data -- element to be added : int index -- position at which value to be added
// Returns: bool -- true for success else false
//----------------------------------------------------------------------
template <class T>
bool Sequence<T>::AddAtIndex( T& data, int index){

    // if index is not in range, throw an exception
    if (index < 0 || index >= numElts){

        return false;
    }


    if (index==0){
        // If p is 0, insert the new node at head.

        SequenceNode<T>* newNode = new SequenceNode<T>(data);

        newNode->setNext(head);

        head->setPrev(newNode);

        head = newNode;

        numElts++;
    }
    else{

        // otherwise traverse to one node before the
        SequenceNode<T>* newNode = new SequenceNode<T>(data);

        SequenceNode<T>* nodePosition = head;  // it will keep track of node position where
                                            // new node to be inserted

        for (int i=0; i<index-1; i++){

            nodePosition = nodePosition->getNext();
        }
        //If the node to be inserted is last node
        // point the tail to new node and make the new node
        // the new tail
        if (nodePosition->getNext()==NULL){

            newNode->setPrev(nodePosition);

            nodePosition->setNext(newNode);

            tail = newNode;

            numElts++;
        }

        // otherwise break the link between iterator and the iterator next
        // node and point both to newNode.
        else{

            newNode->setNext(nodePosition->getNext());

            newNode->getNext()->setPrev(newNode);

            newNode->setPrev(nodePosition);

            nodePosition->setNext(newNode);

            numElts++;
        }
    }
    return true;
}

//--------------------------------------------------------------------
// Function: AddBefore -- Add an element before the given sequence element.
// Inputs: T data -- element to be added
// Returns: void -- nothing
//----------------------------------------------------------------------
template <class T>
void Sequence<T>::AddBefore( SequenceNode<T>*p,T& data ){

    if (head == NULL)
    {
        return;
    }

    SequenceNode<T>* nodePosition = head;

    while (nodePosition!= NULL)
    {
        if (nodePosition == head && nodePosition->getData() == p->getData())
        {
            // create a new sequence node with data
            SequenceNode<T>* newNode = new SequenceNode<T>(data);

            newNode->setNext(head);

            head->setPrev(newNode);

            head = newNode;

            numElts++;

            break;
        }
        else if (nodePosition->getData() == p->getData())
        {
            // create a new sequence node with data
            SequenceNode<T>* newNode = new SequenceNode<T>(data);

            newNode->setNext(nodePosition);
            newNode->setPrev(nodePosition->getPrev());
            nodePosition->getPrev()->setNext(newNode);
            nodePosition->setPrev(newNode);
            numElts++;
            break;
        }

        nodePosition = nodePosition->getNext();
    }
}

//--------------------------------------------------------------------
// Function: AddAfter -- Add an element after the given sequence element.
// Inputs: T data -- element to be added
// Returns: void -- nothing
//----------------------------------------------------------------------
template <class T>
void Sequence<T>::AddAfter( SequenceNode<T>*p,T& data ){

    if (head == NULL)
    {
        return;
    }

    SequenceNode<T>* nodePosition = head;

    while (nodePosition!= NULL)
    {
        if (nodePosition->getData() == p->getData() && nodePosition->getNext() == NULL)
        {
            // create a new sequence node with data
            SequenceNode<T>* newNode = new SequenceNode<T>(data);

            nodePosition->setNext(newNode);

            newNode->setPrev(nodePosition);

            tail = newNode;

            numElts++;

            break;
        }
        else if (nodePosition->getData() == p->getData())
        {
            // create a new sequence node with data
            SequenceNode<T>* newNode = new SequenceNode<T>(data);

            newNode->setNext(nodePosition->getNext());
            nodePosition->getNext()->setPrev(newNode);
            newNode->setPrev(nodePosition);
            nodePosition->setNext(newNode);
            numElts++;
            break;
        }

        nodePosition = nodePosition->getNext();
    }
}

//--------------------------------------------------------------------
// Function: RemoveFromFront -- Remove an element from the front of the sequence.
// Inputs: nothing
// Returns: T -- content of removed item
//----------------------------------------------------------------------
template <class T>
T Sequence<T>::RemoveFromFront(){

    // If head is null , throw an exception
    if (head == NULL){

        throw std::invalid_argument("Error : Unable to pop item. Sequence is already empty ");
    }


    if (head->getNext() == NULL){
        // if next of head is null, that means only one element
        // present in the sequence so delete it and point head and
        //tail to null and no of elements to zero

        SequenceNode<T>* firstNode = head;

        T res = firstNode->getData();

        delete firstNode;

        head = NULL;

        tail = NULL;

        numElts = 0;

        return res;
    }
        // otherwise remove the reference of first node
    else{

        SequenceNode<T>* firstNode = head;

        head = head->getNext();

        head->setPrevNull();

        numElts -- ;

        T res = firstNode->getData();

        delete firstNode;

        return res;
    }
}

//--------------------------------------------------------------------
// Function: RemoveFromEnd -- Remove an element from the end of the sequence.
// Inputs: nothing
// Returns: T --Content of removed node
//----------------------------------------------------------------------
template <class T>
T Sequence<T>::RemoveFromEnd(){

    // If head is null , throw an exception
    if (head == nullptr){

        throw std::invalid_argument("Error : Unable to pop item. Sequence is already empty ");
    }


    if (head->getNext() == NULL){
        // if next of head is null, that means only one element
        // present in the sequence so delete it and point head and
        //tail to null and no of elements to zero

        SequenceNode<T>* lastNode = tail;

        T res = lastNode->getData();

        delete lastNode;

        head = NULL;

        tail = NULL;

        numElts = 0;

        return res;
    }
        // otherwise remove the reference of last node from penultimate node
        // and delete the last node
    else{

        SequenceNode<T>* lastNode = tail;

        tail = tail->getPrev();

        tail->setNextNull();

        numElts -- ;

        T res = lastNode->getData();

        delete lastNode;

        return res;
    }
}


//--------------------------------------------------------------------
// Function: RemoveTheFirst -- find first instance of T data and remove it
// Inputs: T data
// Returns: void -- nothing
//----------------------------------------------------------------------
template <class T>
void Sequence<T>::RemoveTheFirst(T& data){

    // If head is null , throw an exception
    if (head == NULL){

        return;
    }

    SequenceNode<T> * node = head;

    while (node != NULL)
    {
        if (node->getData()==data && node == head){
            // if next of head is null, that means only one element
            // present in the sequence so delete it and point head and
            //tail to null and no of elements to zero
            if (head->getNext() == NULL)
            {
                delete node;

                head = NULL;

                tail = NULL;

                numElts = 0;

            }
            else{
                SequenceNode<T>* temp = head;

                head = head->getNext();

                head->setPrevNull();

                delete temp;

                numElts--;
            }
            return;

        }
        else if (node->getData()==data && node == tail)
        {
            SequenceNode<T>* temp = tail;

            tail = tail->getPrev();

            tail->setNextNull();

            delete temp;

            numElts--;

            return;
        }
        else if (node->getData()==data)
        {
            SequenceNode<T>* temp = node;

            node->getNext()->setPrev(node->getPrev());

            node->getPrev()->setNext(node->getNext());

            delete temp;

            numElts--;

            return;

        }
        node = node->getNext();
    }

}


//--------------------------------------------------------------------
// Function: RemoveAllOf -- find each instance of T data and remove it
// Inputs: T data
// Returns: void -- nothing
//----------------------------------------------------------------------
template <class T>
void Sequence<T>::RemoveAllOf(T& data){

    // If head is null return
    if (head == NULL){

        return;
    }

    SequenceNode<T> *node = head;

    while (node != NULL)
    {
        if (node->getData()==data && node == head){
            // if next of head is null, that means only one element
            // present in the sequence so delete it and point head and
            //tail to null and no of elements to zero
            if (head->getNext() == NULL)
            {

                delete head;

                head = NULL;

                tail = NULL;

                numElts = 0;

                return;

            }
            else{
                node = node->getNext();

                SequenceNode<T>* temp = head;

                head = head->getNext();

                head->setPrevNull();

                delete temp;

                numElts--;
            }

        }
        else if (node->getData()==data && node == tail)
        {
            node = node->getNext();

            SequenceNode<T>* temp = tail;

            tail = tail->getPrev();

            tail->setNextNull();

            delete temp;

            numElts--;

        }
        else if (node->getData()==data)
        {
            SequenceNode<T>* temp = node;

            node = node->getNext();

            temp->getNext()->setPrev(temp->getPrev());

            temp->getPrev()->setNext(temp->getNext());

            delete temp;

            numElts--;

        }
        else
        {
            node = node->getNext();
        }
    }
}

//--------------------------------------------------------------------
// Function: RemoveBefore -- delete the node before a particular node,
// Inputs: SequenceNode<T>* node
// Returns: void -- content of deleted node
//----------------------------------------------------------------------
template <class T>
T Sequence<T>::RemoveBefore(SequenceNode<T>* node){

    // If head is null , throw an exception
    if (head == NULL || node == head){

        throw std::invalid_argument("Error : Unable to remove item. Sequence is already empty ");
    }

    if (node->getPrev()==head)
    {
        SequenceNode<T>* temp = head;

        head = head->getNext();

        head->setPrevNull();

        numElts--;

        T res = temp->getData();

        delete temp;

        return res;
    }

    SequenceNode<T>* temp = node->getPrev();

    temp->getNext()->setPrev(temp->getPrev());

    temp->getPrev()->setNext(temp->getNext());

    T res = temp->getData();

    delete temp;

    return res;

}


//--------------------------------------------------------------------
// Function: RemoveAfter -- delete the node after a particular node,
// Inputs: SequenceNode<T>* node
// Returns: void -- content of deleted node
//----------------------------------------------------------------------
template <class T>
T Sequence<T>::RemoveAfter(SequenceNode<T>* node){

    // If head is null , throw an exception
    if (head == NULL || node == tail){

        throw std::invalid_argument("Error : Unable to remove item. Sequence is already empty ");
    }

    if (node->getNext()==tail)
    {
        SequenceNode<T>* temp = tail;

        tail = tail->getPrev();

        tail->setNextNull();

        numElts--;

        T res = temp->getData();

        delete temp;

        return res;
    }
    SequenceNode<T>* temp = node->getNext();

    temp->getNext()->setPrev(temp->getPrev());

    temp->getPrev()->setNext(temp->getNext());

    T res = temp->getData();

    delete temp;

    return res;

}

//--------------------------------------------------------------------
// Function: ElementExists -- delete the node after a particular node,
// Inputs: T data
// Returns: bool -- Returns a T/F if element exists in list
//----------------------------------------------------------------------
template <class T>
bool Sequence<T>::ElementExists(T& data){

    // If head is null false
    if (head == NULL ){

        return false;
    }

    SequenceNode<T> * node = head;

    while (node != NULL)
    {
        if (data == node->getData())
        {
            return true;
        }
        node = node->getNext();
    }
    return false;

}

//--------------------------------------------------------------------
// Function: Find -- Look for data in the list,
// Inputs: T data
// Returns: SequenceNode<T>* -- return a pointer to its node
//----------------------------------------------------------------------
template <class T>
SequenceNode<T>* Sequence<T>::Find(T& data){

    // If head is null false
    if (head == NULL ){

        return NULL;
    }

    SequenceNode<T> * node = head;

    while (node != NULL)
    {
        if (node->getData()==data)
        {
            return node;
        }
        node = node->getNext();
    }
    return NULL;

}


//--------------------------------------------------------------------
// Function: IndexOf -- Look for data in the list,
// Inputs: T data
// Returns: int -- returns an index of the item in the list (zero-based)
//---------------------------------------------------------------------
template <class T>
int Sequence<T>::IndexOf(T& data){

    // If head is null false
    if (head == NULL ){

        return -1;
    }
    int index = 0;

    SequenceNode<T> * node = head;

    while (node != NULL)
    {
        if (node->getData() == data )
        {
            return index;
        }
        index++;
        node = node->getNext();
    }
    return -1;

}


//--------------------------------------------------------------------
// Function: RetrieveFront -- Finds the data at front i.e head of the sequence
// Inputs:  void -- nothing
// Returns: T  -- returns the data contained in the first node,
//----------------------------------------------------------------------
template <class T>
T Sequence<T>::RetrieveFront(){

    // If head is null then no front exists, so throw an exception
    if (head == NULL){

        throw std::invalid_argument("Error : Unable to find front. Sequence is empty");
    }
    // Otherwise return reference to the first element in sequence
    return head->getData();
}

//--------------------------------------------------------------------
// Function: RetrieveEnd -- Finds the data at end i.e tail of the sequence
// Inputs:  void -- nothing
// Returns: T  -- returns the data contained in the last node,
//----------------------------------------------------------------------
template <class T>
T Sequence<T>::RetrieveEnd(){

    // If head is null then no front exists, so throw an exception
    if (head == NULL){

        throw std::invalid_argument("Error : Unable to find end Sequence is empty");
    }
    // Otherwise return reference to the first element in sequence
    return tail->getData();
}



//--------------------------------------------------------------------
// Function: Retrieve -- Finds the data at front i.e head of the sequence
// Inputs:  int index --
// Returns: T  -- returns the data contained in node # index,
//----------------------------------------------------------------------
template <class T>
T Sequence<T>::Retrieve( int index){

    // if index is not in range, throw an exception
    if (index < 0 || index >= numElts){

        throw std::invalid_argument("Error : Index out of bound");
    }

    if (index==0){
        return head->getData();
    }
    else if(index == numElts-1){
        return tail->getData();
    }
    SequenceNode<T>* node = head;

    for (int i=0; i < index ; i++)
    {
        node = node->getNext();
    }
    return node->getData();
}

//--------------------------------------------------------------------
// Function: printList -- Loop through each node and print the contents of the Node
// Inputs:  void -- nothing
// Returns: vpid  -- nothing
//----------------------------------------------------------------------
template <class T>
void Sequence<T>::printList()
{
    SequenceNode<T>* node = head;

    while (node != NULL)
    {
        cout<<"["<<node->getData()<<"] ";
        node = node->getNext();
    }
    cout<<endl;
}


//--------------------------------------------------------------------
// Function: Empty -- clears the sequence returning it to the empty state
// Returns: void  -- nothing
//----------------------------------------------------------------------
template <class T>
void Sequence<T>::Empty(){
    // Local variables to hold the current and the next sequenceNode
    SequenceNode<T>* current = head;

    SequenceNode<T>* Next = NULL;

    // Repeat until we reach last node
    //delete current node and go to next
    // At last point head to null
    while (current != NULL)
    {
        Next = current->getNext();

        delete current;

        current = Next;
    }


    head = NULL;
    tail = NULL;
    numElts = 0;
}


//--------------------------------------------------------------------
// Function: Length -- How many elements are in the list
// Inputs:  void -- nothing
// Returns: int  -- length of list
//----------------------------------------------------------------------
template <class T>
int Sequence<T>::Length()
{
    if(head == NULL)
    {
        return 0;
    }
    return numElts;
}

Zombie::Zombie(){};

Zombie::Zombie(char t)
{
    type = t;
}

char Zombie::getType()
{
    return type;
}

bool Zombie::operator==(Zombie z)
{
    if (type == z.getType())
        return true;
    return false;
}

ostream& operator<<( ostream& output, Zombie& z){

    output<<z.getType();
    return output;
}



// Function to generate random number
int Randoms(int lower,int upper)
{
    int num = (rand() % (upper - lower + 1)+lower) ;
    return num;
}

class Conga
{
public:
    Sequence<Zombie> congaLine;
    char zombies[6] = {'R','Y','G','B','M','C'};


    Conga()
    {
        rainbowBrains();

        int times = Randoms(2,5);

        for (int j=0; j < times; j++)
        {
            brains();
        }
    }

    void engine()
    {
        Zombie z(zombies[Randoms(0,5)]);
        congaLine.AddToFront(z);
    }

    void caboose()
    {
        Zombie z(zombies[Randoms(0,5)]);
        congaLine.AddToEnd(z);
    }

    void jumpInTheLine()
    {
        Zombie z(zombies[Randoms(0,5)]);
        int pos = Randoms(0,congaLine.Length()-1);
        congaLine.AddAtIndex(z,pos);
    }

    void everyoneOut()
    {
        Zombie z(zombies[Randoms(0,5)]);
        congaLine.RemoveAllOf(z);
    }

    void youreDone()
    {
        Zombie z(zombies[Randoms(0,5)]);
        congaLine.RemoveTheFirst(z);
    }

    void brains()
    {
        int num = Randoms(0,5);
        Zombie z1(zombies[num]);
        Zombie z2(zombies[num]);
        Zombie z3(zombies[num]);

        congaLine.AddToFront(z1);
        congaLine.AddToEnd(z2);
        congaLine.AddAtIndex(z3,congaLine.Length()/2);

    }

    void rainbowBrains()
    {
        int num = Randoms(0,5);
        Zombie z1(zombies[num]);
        congaLine.AddToFront(z1);
        for(int i=0; i < 6; i++)
        {
            Zombie z(zombies[i]);
            congaLine.AddToEnd(z);
        }
    }

    void makingNewFriends()
    {
        Zombie z(zombies[Randoms(0,5)]);
        if (congaLine.ElementExists(z))
        {
            int index = congaLine.IndexOf(z);
            int toss = Randoms(0,1);
            if (toss)
            {
                congaLine.AddAtIndex(z,index-1);
            }
            else{
                congaLine.AddAtIndex(z,index+1);
            }
        }
        else{
            congaLine.AddAtIndex(z,congaLine.Length()-2);
        }

    }

    void unstableZombie()
    {
        Zombie z(zombies[Randoms(0,5)]);
        int indx = 0;
        while (!(congaLine.Retrieve(indx)== z))
        {
            char c = congaLine.Retrieve(indx).getType();
            Zombie z(c);
            congaLine.AddAtIndex(z,indx+1);
            indx+=2;
        }
        congaLine.RemoveTheFirst(z);
    }

    void printConga()
    {
        congaLine.printList();
    }


};

int main()
{
    // Use current time as seed for random generator
    srand(time(0));
   Conga con;

   char choice;
   do
   {
       int rounds;
       int numRounds=0;
       cout<<"Enter number of rounds to run\n\n";
       cin>>rounds;
       cout<<endl;
       for (int i=0; i < rounds; i++)
       {
           if (con.congaLine.Length()==0)
           {
               cout<<"Party is over\n\n";
           }
           if (numRounds == 5)
           {
               con.congaLine.RemoveFromEnd();
               con.congaLine.RemoveFromFront();
               numRounds=0;
           }
           numRounds++;
           int operation = Randoms(0,8);

           cout<<"Round: "<<i<<endl;
           cout<<"The Zombie Party keeps on groaning!\n";
           cout<<"Size: "<<con.congaLine.Length()<<" :: ";
           con.printConga();

           switch (operation)
           {
            case 0:
                cout<<"(Engine)\n";
                con.engine();
                cout<<"The conga line is now:\n";
                cout<<"Size: "<<con.congaLine.Length()<<" :: ";
                con.printConga();
                cout<<"*************************\n\n\n";

                break;
            case 1:
                cout<<"(Caboose)\n";
                con.caboose();
                cout<<"The conga line is now:\n";
                cout<<"Size: "<<con.congaLine.Length()<<" :: ";
                con.printConga();
                cout<<"*************************\n\n\n";
                break;
            case 2:
                cout<<"(Jump in the line)\n";
                con.jumpInTheLine();
                cout<<"The conga line is now:\n";
                cout<<"Size: "<<con.congaLine.Length()<<" :: ";
                con.printConga();
                cout<<"*************************\n\n\n";
                break;
            case 3:
                cout<<"(Everyone Out)\n";
                con.everyoneOut();
                cout<<"The conga line is now:\n";
                cout<<"Size: "<<con.congaLine.Length()<<" :: ";
                con.printConga();
                cout<<"*************************\n\n\n";
                break;
            case 4:
                cout<<"(You are done)\n";
                con.youreDone();
                cout<<"The conga line is now:\n";
                cout<<"Size: "<<con.congaLine.Length()<<" :: ";
                con.printConga();
                cout<<"*************************\n\n\n";
                break;
            case 5:
                cout<<"(Brains)\n";
                con.brains();
                cout<<"The conga line is now:\n";
                cout<<"Size: "<<con.congaLine.Length()<<" :: ";
                con.printConga();
                cout<<"*************************\n\n\n";
                break;
            case 6:
                cout<<"(Rainbow Brains)\n";
                con.rainbowBrains();
                cout<<"The conga line is now:\n";
                cout<<"Size: "<<con.congaLine.Length()<<" :: ";
                con.printConga();
                cout<<"*************************\n\n\n";
                break;
            case 7:
                cout<<"(Making New Friends)\n";
                con.makingNewFriends();
                cout<<"The conga line is now:\n";
                cout<<"Size: "<<con.congaLine.Length()<<" :: ";
                con.printConga();
                cout<<"*************************\n\n\n";
                break;
            case 8:
                cout<<"(Unstable Zombie)\n";
                con.unstableZombie();
                cout<<"The conga line is now:\n";
                cout<<"Size: "<<con.congaLine.Length()<<" :: ";
                con.printConga();
                cout<<"*************************\n\n\n";
                break;
           }

       }

        printf("Press Y to play again and N to exit\n");
        while((getchar()) != '\n');
        scanf("%c",&choice);
   }
   while(choice != 'N');


}
