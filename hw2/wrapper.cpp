// Wrapper file

#include <iostream>
#include "list.h"
#include <stack>
#include <stdexcept>
#include <fstream>
#include <array>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
using namespace std;

class Pair{
  public:
    Node *queen;
    List blockout;
};

List find_queens(string user_input){
  // generate the possible queen spots
  stack<class Pair> queenStack; //holds all me added queens
  
  char *dup, *tok, *temp;
  
  dup = strdup(user_input.c_str());
  tok = strtok(dup, " \t");
  
  //Read size of board, populate whole empty board
  int size;
  size = strtol(tok, &temp, 10);
  List open; // list of linked list of all open spots
  List queens; // all queens and location queen[x-1] = y
  int queens_status[size]; // 0 if not filled, 1 if input queen, 2 if queen put there, master list
  
  for (int i = 1; i < size + 1; i = i + 1){
    for (int j = 1; j < size + 1; j = j + 1){
      open.insert(i, j);
      queens_status[i] = 0;
    }
  }
  
  //Read all default queens
  int x, y;
  char *x_tok, *y_tok;
  x_tok = strtok(NULL, " \t");
  y_tok = strtok(NULL, " \t");
  //int input_size = 0;
  //cout << "board size " << to_string(size) << " ";

  while (x_tok != NULL && y_tok != NULL){
    Pair init;
    x = strtol(x_tok, &temp, 10);
    y = strtol(y_tok, &temp, 10);
    //cout << "queen input at: "<< x_tok << ", " <<y_tok;
    //input_size = input_size + 1;
    
    if (open.find(x,y) == NULL){
      //conflict, cannot add
      //cout << "conflict\n";
      List empty;
      return empty;
    }
    
    //Add queen to stack, block out stuff
    // WAIT DONT NEED to stack initial queens
    queens.insert(x, y);
    queens_status[x-1] = 1;
    open.blockList(x, y);
    
    // tok the next queen
    x_tok = strtok(NULL, " \t");
    y_tok = strtok(NULL, " \t");
  }
  //cout << "\n";
  // Find all remaining spots for queens
  int curr_col = 1;
  open.sort();
  //cout << open.print(" ") << "\n";
  while (curr_col <= size){
    //cout << "column #: " << to_string(curr_col) << " ";
    //cout << open.print(" ") << "\n";
    
    if (queens_status[curr_col-1]==1){
      // ALREADY HAS DEFAULT QUEEN
      //cout << "curr_col has default queen at " << to_string(curr_col) << "\n";
      curr_col = curr_col + 1;
    } else if (open.lengthCol(curr_col) == 0){
      //cout << "No open spots, backtrack\n";
      // NEED TO BACKTRACK, POP 
      Pair to_add;
      bool yes_found = false;
      while (yes_found == false){
        // pop and put back open options
        Pair removed = queenStack.top();
        //cout << "popped node: " << to_string(removed.queen->x) << " " << to_string(removed.queen->y) << "\n";
        //cout << "before everything put back" << open.print(" ") << "\n";
        
        //cout << "HERE\n" ;
        open.insertList(removed.blockout);
        
        open.sort();
        //cout << "HERE\n" ;
        
        //cout << "after everything put back" << open.print(" ") << "\n";
        
        // find next open spot
        curr_col = removed.queen->x;
        queens_status[curr_col-1] = 0;
        
        //cout << "HERE\n" ;
        to_add.queen = open.getNext(removed.queen); //next open spot
        //cout << "HERE\n" ;
        
        queenStack.pop();
        if (to_add.queen != NULL){
          // getNext actually returned something
          to_add.blockout = open.blockList(to_add.queen->x, to_add.queen->y);
          queens_status[curr_col-1] = 2;
          queenStack.push(to_add);
          //curr_col = curr_col + 1;
          //cout << "adding queen at: " << to_add.queen->x << " " << to_add.queen->y << "\n";
          yes_found = true;
        }
        
        if (queenStack.size() == 0){
          //cout <<"HERE\n";
          return List();  //no answer
        }
      }
      curr_col = curr_col + 1;
      
    } else {
      // NOTHING IN COLUMN, GET FIRST OPEN SPOT IN COLUMN
      Pair to_add;
      to_add.queen = open.getNode(curr_col);
      //cout << "adding queen at: " << to_add.queen->x << " " << to_add.queen->y << "\n";
      to_add.blockout = open.blockList((to_add.queen)->x, (to_add.queen)->y);
      //cout << "blocked out spaces " << to_add.blockout.print(" ") << "\n";
      queenStack.push(to_add);
      queens_status[curr_col-1] = 2;
      curr_col = curr_col + 1;
    }
  }
  //cout << "outside while loop\n";
  open.sort();
  //cout << "stack size: " << queenStack.size() << " board size: " << size << "\n";
  while (queenStack.size()>0){
    Node *removed = queenStack.top().queen;
    queenStack.pop();
    queens.insert(removed->x, removed->y);
  }
  return queens;
}

// return list of blocked out spots when queen is put at x, y


int main(int argc, char** argv){
  if (argc < 3){
    throw std::invalid_argument("Usage: ./hello <INPUT FILE> OUTPUT FILE>");
  }
  
  ifstream input;
  ofstream output;
  
  input.open(argv[1]);
  output.open(argv[2]);
 
  string user_input;
  
  while (getline(input, user_input)){
    // loop though all lines of input
    if (user_input.length() == 0)
      continue;
    //cout << "input: "<<user_input <<"\n";
    

    List queen_list = find_queens(user_input);
    
    if (queen_list.length() == 0){
      output << "No solution\n"; // make output later
    } else{
      output << queen_list.print(" ") << endl; //make output later
    }
    
    queen_list.deleteList();
    
  }
  input.close();
  output.close();
  
  
  
}