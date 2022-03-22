//LinkedLink Header
// Code provided by professor, modified

#ifndef LIST_H
#define LIST_H

#include <string>

using namespace std;

struct Node{
  string data;
  int freq;
  Node *next;
};

class LinkedList{
  private:
    Node *head;
  public:
    LinkedList();
    void insert(string, int freq = 1);
    Node* find(string);
    Node* findMax();
    Node* getNode();
    Node* deleteNode(string);
    void deleteAndFreeNode(string);
    void deleteList();
    string print();
    int length();
};


#endif