// LinkedList ADT
// LinkedList code is provided by the professor, slightly modified

#include "linkedlist.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;

LinkedList :: LinkedList(){
  head = NULL;
}

void LinkedList :: insert(string val, int freq){
  Node *look = this->find(val);
  if (look != NULL){
    look->freq = look->freq + 1;
    return;
  }
  Node *to_add = new Node;
  to_add->data = val;
  to_add->next = head;
  to_add->freq = freq;
  head = to_add;
  return;
}

Node* LinkedList :: find(string val){
  Node *curr = head;
  while (curr != NULL){
    if (curr->data == val){
      return curr;
    }
    curr = curr->next;
  }
  return NULL;
}



Node* LinkedList :: findMax(){
  Node *curr = head;
  Node *max = curr;
  while (curr != NULL){
    if (curr->freq > max->freq || (curr->freq == max->freq && curr->data < max->data) ){
      // switch max with current
      max = curr;
    }
    curr = curr->next;
  }
  return max;
}

Node* LinkedList :: getNode(){
 
  Node *curr = head;
  if (curr != NULL){
    return this->deleteNode(curr->data);
  }
  return NULL;
  
}

Node* LinkedList :: deleteNode(string val){
  Node *prev = NULL;
  Node *curr = head;
  while(curr != NULL){
    if(curr->data == val){
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
  curr->next = NULL;
  return curr;
}

void LinkedList :: deleteAndFreeNode(string val){
  Node* ptr = deleteNode(val);
  if (ptr != NULL){
    ptr->next = NULL;
    delete(ptr);
  }
  return;
}

void LinkedList :: deleteList(){
  Node *curr = head;
  Node *temp = NULL;
  while(curr != NULL){
    temp = curr->next;
    deleteAndFreeNode(curr->data);
    curr = temp;
  }
  head = NULL;
}

string LinkedList :: print(){
  cout << "printing\n";
  string list_str = "";
  Node *curr = head;
  while(curr != NULL){
    list_str = list_str + curr->data + " " + to_string(curr->freq) + " ";
    curr = curr->next;
  }
  if (list_str.length() > 0){
    list_str.pop_back();
  }
  cout << "printing end\n";
  return list_str;
}

int LinkedList :: length(){
  int length = 0;
  Node *curr = head;
  while (curr != NULL){
    length = length + 1;
    curr = curr->next;
  }
  return length;
}