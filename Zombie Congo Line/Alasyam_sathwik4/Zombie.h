#ifndef ZOMBIE
#define ZOMBIE
#include <iostream>
#include<fstream>

using namespace std;

class Zombie
{
private:
    char type;
public:
    Zombie();
    Zombie(char t);
    char getType();
    bool operator==(Zombie z);
    friend ostream& operator<<( ostream& output, Zombie& z);

};// End of class Zombie

#endif
