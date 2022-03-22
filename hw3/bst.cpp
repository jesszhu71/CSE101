// BST copied from bst example code

#include "bst.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>

using namespace std;

BST :: BST(){
  root = NULL;
}

void BST :: insert(string word){
  Node *to_insert = new Node(word);
  if (root == NULL){
    root = to_insert;
  } else {
    insert(root, to_insert);
  }
}

int BST :: find_range(string str1, string str2){
  //cout << "root subtree size: " << root->subtree << endl;
  return root->subtree - minLeaf(str1, root) - maxLeaf(str2, root);
}


int BST :: minLeaf(string str1, Node* curr){
  
  //cout << "enter minLeaf, curr node is: " << curr->key << endl;
  // leaf node found
  if (curr && curr->left == NULL && curr->right == NULL){
    //cout << "here1\n";
    if (curr->key >= str1){
      //cout <<"here2\n";
      return 0;
    } else {
      //cout << "here3\n";
      return 1;
    }
  }
  

  // is inside
  int remove = 0;
  int output = 0;
  if (curr && curr->key >= str1 && curr->left){
    // go left
    //cout << "current node is inside, so go left\n";
    remove = minLeaf(str1, curr->left);
  } else if (curr && curr->key < str1){
    //cout<< "current node is outside, so go right, rid subtree: " << (curr->left->subtree + 1) << endl;
    int toss = 0;
    if (curr->left){
      toss = curr->left->subtree;
    }
    remove = minLeaf(str1, curr->right) + 1 + toss;
  }
  
  output = output + remove;
  //cout << "end of minLeaf\n";
  return output;
  
}

int BST :: maxLeaf(string str2, Node* curr){
  
  // leaf node found
  if (curr && curr->left == NULL && curr->right == NULL){
    if (curr->key <= str2){
      return 0;
    } else {
      return 1;
    }
  }
  
  // is inside
  int remove = 0;
  int output = 0;
  
  if (curr && curr->key <= str2 && curr->right){
    // go right
    //cout << "current node is inside, so go right\n";
    remove = maxLeaf(str2, curr->right);
  } else if (curr && curr->key > str2) {
    //cout<< "current node is outside, so go right, rid subtree: " << (curr->right->subtree + 1) << endl;
    int toss = 0;
    if (curr->right){
      toss = curr->right->subtree;
    }
    remove = maxLeaf(str2, curr->left) + 1 + toss;
  }
  
  output = output + remove;
  return output;
}




Node* BST :: update(Node* curr, Node* to_insert){
  if (curr == NULL){
    return NULL;
  }
  int left = 0;
  int right = 0;
  int left_childs = 0;
  int right_childs = 0;
  

  if (curr->left){
    left = curr->left->height+1;
    left_childs = curr->left->subtree;
    
  }
  if (curr->right){
    right = curr->right->height+1;
    right_childs = curr->right->subtree;
  }
  
  curr->subtree = left_childs + right_childs + 1;
  curr->height = max(left, right);
  
  // check height difference
  int diff = left - right;
  
  // evaluate heigh difference
  if (diff > 1){
    // left is higher
    if (curr->left->key < to_insert->key){
      // left right case
      rLeft(curr->left);
    }
    return rRight(curr);
  } else if (diff < -1){
    // right is higher
    if (curr->right->key > to_insert->key){
      // right left case
      rRight(curr->right);
    }
    return rLeft(curr);
  }

  return curr;
}

void BST :: insert(Node* start, Node* to_insert){
  //cout << "subtree of " << start->key << " " << start->subtree << endl;
  if (start == NULL){
    return;
  }
  
  if (to_insert->key <= start->key){
    // go left
    if (start->left == NULL){
      start->left = to_insert;
      to_insert->parent = start;
    } else{
      insert(start->left, to_insert);
    }
    // update here!
    start = update(start, to_insert);
    return;
  } else {
    // go right
    if (start->right == NULL){
      start->right = to_insert;
      to_insert->parent = start;
    } else{
      insert(start->right, to_insert);
    }
    // update here!
    start = update(start, to_insert);
    return;
  }
}

/*
int BST :: range(string str1, string str2, Node* start){
  // if current node is less than str 1, go left
  // if current node is greater than str 2, go right
  // if current node is leaf and in between str1 and 2, increment counter

  if (start == NULL){
    return 0;
  }
  
  // recurse left and right
  int l = 0;
  int r = 0;
  int output = 0;
  
  
  if (start->key <= str2 && start->key >= str1){
    // current key is between the two strings
    output = 1;
    l = range(str1, str2, start->left);
    r = range(str1, str2, start->right);
  } else if (start->key <= str1){
    r = range(str1, str2, start->right);
  } else if (start->key >= str2){
    l = range(str1, str2, start->left);
  }

  
  // counter increment
  output = output + l + r;
  return output; 
}
*/


// int BST :: range(string str1, string str2, Node* start){
//   if (start == NULL){
//     return 0;
//   }
  
//   // recurse left and right
//   int l = 0;
//   int r = 0;
//   int output = 0;
  
  
//   if (start->key <= str2 && start->key >= str1){
//     // current key is between the two strings
//     output = 1;
//     l = range(str1, str2, start->left);
//     r = range(str1, str2, start->right);
//   } else if (start->key <= str1){
//     r = range(str1, str2, start->right);
//   } else if (start->key >= str2){
//     l = range(str1, str2, start->left);
//   }

  
//   // counter increment
//   output = output + l + r;
//   return output; 
// }

// counter clockwise
Node* BST :: rLeft(Node* old){
  // find new root of rotation, set new root's parent
  Node *new_root = old->right;
  new_root->parent = old->parent; // 
  
  // attach new root to rest of tree
  if(old->key != root->key && old->parent->left && old->parent->left->key == old->key){
    old->parent->left = new_root;
  }
  if(old->key != root->key && old->parent->right && old->parent->right->key == old->key){
    old->parent->right = new_root;
  }
  
  // transplanted branch temp
  Node *temp = new_root->left;
  
  // if root of tree, set new root
  if (old->key == root->key){
    root = new_root;
  }
  
  // left part of new root
  new_root->left = old;
  old->parent = new_root; //
  
  // transplant of temp
  old->right = temp;
  if (temp){
    temp->parent = old;
  }
  
  // update new heights
  int x = 0;
  int y = 0;
  int x_subtree = 0;
  int y_subtree = 0;
  
  if (old->left){
    x = old->left->height + 1;
    x_subtree = old->left->subtree;
  }
  if (temp){
    y = temp->height + 1;
    y_subtree = temp->subtree;
  }
  
  // old's height
  old->height = max(x, y);
  old->subtree = x_subtree + y_subtree + 1;
  
  x = 0;
  y = 0;
  x_subtree = 0;
  y_subtree = 0;
  
  if (new_root->left){
    x = new_root->left->height + 1;
    x_subtree = new_root->left->subtree;
  }
  if (new_root->right){
    y = new_root->right->height + 1;
    y_subtree = new_root->right->subtree;
  }
  
  // new's height
  new_root->height = max(x, y);
  new_root->subtree = x_subtree + y_subtree + 1;
  return new_root;
  
}

// clockwise
Node* BST :: rRight(Node* old){
  // logic same as rLeft
  
  Node *new_root = old->left;
  new_root->parent = old->parent; //
  if(old->key != root->key && old->parent->left && old->parent->left->key == old->key){
    old->parent->left = new_root;
  } 
  
  if(old->key != root->key && old->parent->right && old->parent->right->key == old->key){
    old->parent->right = new_root;
  } 
  
  Node *temp = new_root->right;
  
  if (old->key == root->key){
    root = new_root;
  }
  
  new_root->right = old;
  old->parent = new_root;
  
  old->left = temp;
  if (temp){
    temp->parent = old;
  }
  

  int x = 0;
  int y = 0;
  int x_subtree = 0;
  int y_subtree = 0;
  
  if (temp){
    x = temp->height + 1;
    x_subtree = temp->subtree;
  }
  if (old->right){
    y = old->right->height + 1;
    y_subtree = old->right->subtree;
  }

  old->height = max(x, y);
  old->subtree = x_subtree + y_subtree + 1;
  
  x = 0;
  y = 0;
  x_subtree = 0;
  y_subtree = 0;

  if (new_root->left){
    x = new_root->left->height + 1;
    x_subtree = new_root->left->subtree;
    
  }
  if (new_root->right){
    y = new_root->right->height + 1;
    y_subtree = new_root->right->subtree;
  }

  new_root->height = max(x, y);
  new_root->subtree = x_subtree + y_subtree + 1;
  
  return new_root;
}



Node* BST :: find(string word){
  return find(root, word);
}


Node* BST :: find(Node* start, string word){
  if (start == NULL || start->key == word){
    return start;
  }
  if (word < start->key){
    return find(start->left, word);
  } else {
    return find(start->right, word);
  }
}


Node *BST :: minNode(Node* start){
  if (start == NULL){
    return NULL;
  }
  if (start->left == NULL){
    return start;
  } else {
    return minNode(start->left);
  }
}


Node* BST :: maxNode(Node* start){
  if(start == NULL){
    return NULL;
  }
  if (start->right == NULL){
    return start;
  } else {
    return maxNode(start->right);
  }
}

Node* BST :: deleteKey(string word){
  return deleteNode(find(word));
}


Node* BST :: deleteNode(Node *to_delete){
  if (to_delete == NULL){
    return NULL;
  }
  bool isRoot = (to_delete == root) ? true : false;
  bool isLeftChild = false;
  if (!isRoot){
    isLeftChild = (to_delete->parent->left == to_delete) ? true : false;
  }
  bool isDeleted = false;
  
  if (to_delete->left == NULL){
    if (isRoot){
      root = to_delete->right;
      if (root != NULL){
        root->parent = NULL;
      }
    } else {
      if (isLeftChild){
        to_delete->parent->left = to_delete->right;
      } else {
        to_delete->parent->right = to_delete->right;
      }
      if(to_delete->right != NULL){
        to_delete->right->parent = to_delete->parent;
      }
      isDeleted = true;
    }
  }
  
  
  if (!isDeleted && to_delete->right == NULL){
    if (isRoot){
      root = to_delete->left;
      if(root !=NULL){
        root->parent = NULL;
      } 
    } else {
        if (isLeftChild){
          to_delete->parent->left = to_delete->left;
        } else {
          to_delete->parent->right = to_delete->left;
        }
        if (to_delete->left != NULL){
          to_delete->left->parent = to_delete->parent;
        }
      }
      isDeleted = true;
      
    }
  if (isDeleted){
    to_delete->left = to_delete->right = NULL;
    return to_delete;
  }

  Node* succ = minNode(to_delete->right);
  to_delete->key = succ->key;
  return deleteNode(succ); 
}

void BST :: deleteBST(){
  deleteBST(root);
}

void BST :: deleteBST(Node* start){
  if (start == NULL){
    return;
  }
  deleteBST(start->left);
  deleteBST(start->right);
  delete(start);
}

string BST :: printInOrder(){
  return printInOrder(root);
}

string BST :: printPreOrder(){
  return printPreOrder(root);
}

string BST :: printPostOrder(){
  return printPostOrder(root);
}

string BST :: printInOrder(Node* start){
  if (start == NULL){
    return "";
  }
  string leftpart = printInOrder(start->left);
  string rightpart = printInOrder(start->right);
  string output = start->key;
  if(leftpart.length() != 0){
    output = leftpart + " " + output;
  }
  if (rightpart.length() != 0){
    output = output + " " + rightpart;
  }
  return output;
}

string BST :: printPreOrder(Node* start){
  if (start == NULL){
    return "";
  }
  string leftpart = printPreOrder(start->left);
  string rightpart = printPreOrder(start->right);
  string output = start->key;
  if(leftpart.length() != 0){
    output = output + " " + leftpart;
  }
  if (rightpart.length() != 0){
    output = output + " " + rightpart;
  }
  return output;
}

string BST :: printPostOrder(Node* start){
  if (start == NULL){
    return "";
  }
  string leftpart = printPostOrder(start->left);
  string rightpart = printPostOrder(start->right);
  string output = start->key;
  if(leftpart.length() != 0){
    output = rightpart + " " + output;
  }
  if (rightpart.length() != 0){
    output = leftpart + " " + output;
  }
  return output;
}