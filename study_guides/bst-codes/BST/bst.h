#ifndef BST_H
#define BST_H

#include <string>

using namespace std;

class Node{
  public: 
    string key;
    int height;
    int subtree;
    Node *left, *right, *parent;
    Node (){
      left = NULL;
      right = NULL;
      parent = NULL;
    }
    Node (string val){
      key = val;
      left = NULL;
      right = NULL;
      parent = NULL;
      height = 0;
      subtree = 1;
    }
};

class BST {
  private:
    Node *root;
  public: 
    BST();
    void insert(string);
    void insert(Node*, Node*);
    Node* find(string);
    Node* find(Node*, string);
    int find_range(string, string);
    //int range(string, string, Node*);
    int minLeaf(string, Node*);
    int maxLeaf(string, Node*);
    Node* rLeft(Node*);
    Node* rRight(Node*);
    Node* update(Node*, Node*);
    Node* minNode(Node*);
    Node* maxNode(Node*);
    Node* deleteKey(string);
    Node* deleteNode(Node*);
    void deleteBST();
    void deleteBST(Node* start);
    string printInOrder();
    string printInOrder(Node* start);
    string printPreOrder();
    string printPreOrder(Node* start);
    string printPostOrder();
    string printPostOrder(Node* start);
    
  /*
    Node* lca(int, int);
    Node* lca(Node*, int, int);
    */
};



#endif