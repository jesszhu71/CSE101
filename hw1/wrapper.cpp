// Main function


#include <iostream>
#include "linkedlist.h"
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
using namespace std;

int main(int argc, char** argv){
  if (argc < 3){
    throw std::invalid_argument("Usage: ./wrapper <INPUT FILE> <OUTPUT FILE>");
  }
  
  ifstream input;
  ifstream shake;
  ofstream output;
  
  input.open(argv[1]);
  output.open(argv[2]);
  
  string word;
  char *word_dup;
  char *word_tok;

  
  
  
  // GET MAX LENGTH OF WORD
  shake.open("shakespeare-cleaned5.txt");
  //shake.open("short-shake.txt");
  int max = 0;
  while (getline(shake, word)){
    if (word.length() == 0)
      continue;
    if (max < (int)word.length()){
      max = word.length();
      }  
  }
  shake.close();
  
  

  
  //READ AND POPULATE WORD FREQUENCY LIST 
  LinkedList shakeList[max+1];
  shake.open("shakespeare-cleaned5.txt");
  //shake.open("short-shake.txt");
  
  while (getline(shake, word)){
    if (word.length() == 0)
      continue;
    word_dup = strdup(word.c_str());
    word_tok = strtok(word_dup, " \t"); //DO I EVEN NEED THIS
		shakeList[word.length()].insert(word_tok);
    //cout << word_tok << word_dup;
  }
  shake.close();
  
  
  
	// LOOP THROUGH EACH LINE OF L, K INPUT
  int l, k;
	string user_input;
  char *copy;
	//char *op;
  
  while (getline(input, user_input)){
    if (user_input.length() == 0)
      continue;
    
    // SET L, K
    //cout << "input: " << user_input << "\n";
    copy = strdup(user_input.c_str());
    l = atoi(strtok(copy, " \t"));
    k = atoi(strtok(NULL, " \t"));

    
    
    if (l > max || shakeList[l].length()<k || shakeList[l].length()<=0){
      // no answer
      output << "-\n";
      continue;
    }
    
    // GET MOST FREQUENT ITEM FROM LINKEDLIST OF L LENGTH K+1 TIMES
    
    // Print out the k'th most frequent words
    LinkedList putback;
    Node *found=NULL;
    // loop through l
    for (int i = 0; i < k + 1; i = i + 1){
      // loop through all words to find most freq
      found = shakeList[l].findMax();
      //******TRIED DELETING/INSERTING NULL NODE
      if (found != NULL){
        shakeList[l].deleteNode(found->data);
        putback.insert(found->data, found->freq);
      } else {
        break;
      }
    }
    
    //we found the k'th most frequent word of length l!
    Node *curr;
    for (int i = 0; i < k + 1; i = i + 1){
      curr = putback.getNode();
      //**** ALSO TRIED INSERTING NULL NODES
      if (curr != NULL){
        shakeList[l].insert(curr->data, curr->freq);
      }
    }
    putback.deleteList();
    if (found != NULL){
      output << found->data << "\n";
    } else {
      output << "-\n";
    }
  }
  
  
  
  for (int i = 0; i < max+1; i = i + 1){
    shakeList[i].deleteList();
  }
  

  input.close();
  output.close();
  return 0;
}