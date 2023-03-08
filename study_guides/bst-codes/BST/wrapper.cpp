// Wrapper

#include <iostream>
#include "bst.h"
#include <stack>
#include <stdexcept>
#include <fstream>
#include <array>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cstring>

using namespace std;


int main(int argc, char** argv){
  if (argc < 3){
    throw std::invalid_argument("Usage ./wordrange <INPUT FILE> <OUTPUT FILE");
  }
  
  ifstream input;
  ofstream output;
  
  input.open(argv[1]);
  output.open(argv[2]);
  
  string command;
  char *com, *valstr, *op;
  //int val = 0;
  
  BST myWords;
  
  while (getline(input, command)){
    if (command.length() == 0)
      continue;
    com = strdup(command.c_str());
    op = strtok(com, " \t");
    
    
    
    valstr = strtok(NULL, " \t");
    /* // I don't think this is necessary bc we dealing with string
    if (valstr != NULL)
      val = strtol (valstr, &dummy, 10);
    */
    
    if (strcmp(op, "i") == 0){
      //cout << "Insert " << valstr << endl;
      // Insert word
      if (myWords.find(valstr) == NULL){
          myWords.insert(valstr);
      }
      //cout << myWords.printInOrder()<< endl;
    }
    
    if (strcmp(op, "r") == 0){
      // count number of strings stored between two strings
      char *valtwo = strtok(NULL, " \t");
      //cout << "Range " << valstr << " and " << valtwo << endl;
      output << myWords.find_range(valstr, valtwo) << endl;
    }
    
    
  }

  
}