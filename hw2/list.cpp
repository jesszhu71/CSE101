// List Class, linkedlist of nodes
// Taken from code provided by the professor


#include "list.h"
#include "node.h"
#include "cstdlib"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

List :: List(){
  head = NULL;
}

// Insert queen with x, y into linkedlist
void List :: insert(int xcoor, int ycoor){
  if (find(xcoor, ycoor)!= NULL){
    return;
  }
  Node *latest = new Node(xcoor, ycoor);
  latest->next = head;
  head = latest;
  return;
}

// Returns next node in the same column
Node* List :: getNext(Node* prev){

  Node *found = find(prev->x, prev->y);
  if (found == NULL || found->next == NULL){
    return NULL;
  }
  //cout << "original node: " << to_string(found->x) << " " << to_string(found->y)<< "\n";
  //cout << print(" ") << "\n";
  found = found->next;
  //cout << "next node: " << to_string(found->x) << " " << to_string(found->y)<< "\n";
  //cout << print(" ") << "\n";
  if (found->x == prev->x){
    return found;
  }
  return NULL;
}



// finds queen at x, y
Node* List :: find(int xcoor, int ycoor){
  Node *curr = head;
  while (curr != NULL){
    if (curr->x == xcoor && curr->y == ycoor){
      return curr;
    }
    curr = curr->next;
  }
  return NULL;
}


// removes spots from open blocked by x, y queen, returns those spots as a list
List List :: blockList(int x, int y){
  
  List blockout = List();
  Node *curr = head;
  while (curr != NULL){
    if (curr->x == x || curr->y == y || x-curr->x == y-curr->y || x-curr->x == curr->y-y){
      //remove from open space

      blockout.insert(curr->x, curr->y);
      deleteNode(curr->x, curr->y);
    }
    curr = curr->next;
  }
  blockout.insert(x, y);
  return blockout;
}


// gets the most recent available 
Node* List :: getNode(int col){
  Node *curr = head;
  if (col == 0 && curr != NULL){
    return deleteNode(curr->x, curr->y);
  } 
  while (curr != NULL){
    if (curr->x == col){
      return deleteNode(curr->x, curr->y);
    }
    curr = curr->next;
  }
  return NULL;
}

// returns how many items with column number col
int List :: lengthCol (int col){
  int count = 0;
  Node *curr = head;
  while (curr != NULL){

    if (curr->x == col){
      count = count + 1;
    }

    curr = curr->next;
  }
  return count;
}

int List :: length(){
  int length = 0;
  Node *curr = head;
  while (curr != NULL){
    length = length + 1;
    curr = curr->next;
  }
  return length;
}

void List :: insertList(List insertFrom){

  Node *to_add = insertFrom.getNode(0);
  while (to_add != NULL){
    insert(to_add->x, to_add->y);
    to_add = insertFrom.getNode(0);
  }
  return;
}

void List :: sort(){
  Node *curr1 = head, *curr2 = head;
  Node *min;
  int tempx, tempy;
  while (curr1 != NULL){
    curr2 = curr1;
    min = curr2;
    while (curr2 != NULL){
      // if min is greater
      if (min->x > curr2->x || (min->x == curr2->x && min->y > curr2->y)){
        min = curr2;
      }
      curr2 = curr2->next;
    }
    
    tempx = curr1->x;
    tempy = curr1->y;
    curr1->x = min->x;
    curr1->y = min->y;
    min->x = tempx;
    min->y = tempy; 
    
    curr1 = curr1->next;
  }  
}



/*
void List :: removeList(List removeFrom){
  Node *curr = head;
  while (curr != NULL){
    removeFrom.deleteNode(curr->x, curr->y);
    curr = curr->next;
  }
  return;
}
*/

Node* List :: deleteNode(int x, int y){
  Node *prev = NULL;
  Node *curr = head;
  while (curr != NULL){
    if (curr->x == x && curr->y == y){
      break;
    }
    prev = curr;
    curr = curr->next;
  }
  if (curr == NULL){
    return NULL;
  }
  if (prev == NULL){
    head = head->next;
  } else {
    prev->next = curr->next;
  }
  //curr->next = NULL;
  return curr;
}

void List :: deleteList(){
  Node *curr = head;
  if(curr == NULL){
    return;
  }
  while (curr->next != NULL){
    Node *temp = curr->next;
    delete(curr);
    curr = temp;
  }
  delete(curr);
  
}

/*
string List :: print(string delim){
  sort();
  if (head == NULL){
    return "";
  }
  Node *curr = head;
  string output = to_string(curr->x)+ " " +to_string(curr->y);
  curr = curr->next;
  while (curr != NULL){
    output = output + delim + to_string(curr->x) + delim + to_string(curr->y);
    curr = curr->next;
  }
  return output;
}
*/

/*
string List :: print(string delim){
  sort();
  if (head == NULL){
    return "";
  }
  string output = "";
  Node *curr = head;
  while (curr != NULL){
    output = output + delim + "(" + to_string(curr->x) + ", "+ to_string(curr->y) + ")";
    curr = curr->next;
  }
  return output;
}

  */
  
  
  
  
string List :: print(string delim){
  sort();
  if (head == NULL){
    return "";
  }
  string output = "";
  Node *curr = head;
  while (curr != NULL){
    output = output + to_string(curr->x) + delim + to_string(curr->y) + delim;
    curr = curr->next;
  }
  return output;
}


