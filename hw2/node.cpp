// Node Class, contains queen coordinates
// Taken from code provided by Professor (with preference modifications)

#include "node.h"
#include <cstdlib>
#include <string>
using namespace std;


Node :: Node(){
  x = 0;
  y = 0;
  next = NULL;
}


//Constructor
Node :: Node(int xcoor, int ycoor){
  x = xcoor;
  y = ycoor;
  next = NULL;
}


