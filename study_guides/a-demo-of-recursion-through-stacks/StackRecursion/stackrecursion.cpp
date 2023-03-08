// Filename: stackrecursion.cpp
//
// The file basically contains two functions that generate all subsequences of an input string. One function is the (standard) recursive method,
// while the other is non-recursive and uses a stack. Both these functions have an identical output, and create a (linked) list of strings as their output.
// 
// The code uses the List data structure used in a number of CSE101 assignments and tests.
// 
// USAGE:  (the executable is generated by a Makefile)
//     ./stackrecursion <INPUT FILE> <OUTPUT FILE>
// 
//     Only the first line of <INPUT FILE> is read, as a string. <OUTPUT FILE> contains all subsequences, each in a separate line.
// 
// 
// C. Seshadhri, Jan 2020, Oct 2020

#include <iostream>
#include "list.h"
#include <stack>
#include <stdexcept>
#include <fstream>
#include <array>
#include <vector> 
#include <algorithm>
#include <sstream>
#include <string>
using namespace std;


// This class keeps pairs of string. This is useful for simulating the recursion through as stack.
class Pair
{
    public:
        string in_str;
        string fixed_str;
};


// PRACTICE TEST STUFF
List allAnagrams(string input)
{
    List final_output;
    stack <class Pair> anaStack;
    Pair init, stacktop;
    init.in_str = input;
    init.fixed_str = "";
    anaStack.push(init);
    
    while(!anaStack.empty()){
        stacktop = anaStack.top();
        anaStack.pop();
        if(stacktop.in_str.length() == stacktop.fixed_str.length()){
            if (final_output.find(stacktop.fixed_str) == NULL){
                final_output.insert(stacktop.fixed_str);
            }
            continue;
        }
        int first = stacktop.fixed_str.length();
        char old_first = stacktop.in_str[first];
        cout << "here\n";
        for (int i = 0; i < (int)stacktop.in_str.length()-(int)stacktop.fixed_str.length(); i = i + 1){
            // swap every non-fixed index with the first non-fixed index
            //first = stacktop.fixed_str.length;
            int swap_spot = first + i;
            Pair to_push;
            to_push.fixed_str = stacktop.fixed_str + stacktop.in_str[swap_spot];
            char new_first = stacktop.in_str[swap_spot];
            string temp = stacktop.in_str;
            string s1(1, new_first);
            temp.replace(first, 1, s1);
            //temp[first] = new_first;
            string s2(1, old_first);
            temp.replace(swap_spot, 1, s2);
            //temp[swap_spot] = old_first;
            to_push.in_str = temp;
            anaStack.push(to_push);
        }
        
    }
    return final_output;
}

List stretch(string input, int k)
{
    List final_output;
    stack <class Pair> anaStack;
    Pair init, stacktop;
    init.in_str = "";
    init.fixed_str = input;
    
    for (int i = 0; i < k-1; i = i + 1){
        init.in_str = init.in_str + input;
    }
    
    anaStack.push(init);
    
    while(!anaStack.empty()){
        stacktop = anaStack.top();
        anaStack.pop();
        if (final_output.find(stacktop.fixed_str) == NULL){
                final_output.insert(stacktop.fixed_str);
        }
        if(stacktop.in_str.length() == 0){
            continue;
        } 
        
        Pair take;
        Pair no_take;
        
        char popped = stacktop.in_str.back();
        stacktop.in_str.pop_back();
        
        take.in_str = stacktop.in_str;
        no_take.in_str = stacktop.in_str;
        no_take.fixed_str = stacktop.fixed_str;
        
        int insert_index = stacktop.fixed_str.find(popped);
        string s2(1, popped);
        stacktop.fixed_str.insert(insert_index, s2);
        take.fixed_str = stacktop.fixed_str;
        
        anaStack.push(take);
        anaStack.push(no_take);    
    }
    return final_output;
}

List swap(string input)
{
    List final_output;
    stack <class Pair> anaStack;
    Pair init, stacktop;
    init.in_str = input;
    init.fixed_str = "";
    anaStack.push(init);
    
    while(!anaStack.empty()){
        stacktop = anaStack.top();
        anaStack.pop();
        if (stacktop.fixed_str.length() == stacktop.in_str.length()-1){
                final_output.insert(stacktop.in_str);
                continue;
        } 
        
        Pair swap;
        Pair no_swap;
        
        
        int curr_index = stacktop.fixed_str.length();
        string s0(1, stacktop.in_str[curr_index+1]);
        string s1(1, stacktop.in_str[curr_index]);
        
        swap.fixed_str = stacktop.fixed_str + s0;
        no_swap.fixed_str = stacktop.fixed_str + s1;
        no_swap.in_str = stacktop.in_str;
        
        string s2(1, stacktop.in_str[curr_index]);
        string s3(1, stacktop.in_str[curr_index+1]);
        stacktop.in_str.replace(curr_index, 1, s3);
        stacktop.in_str.replace(curr_index+1, 1, s2);
        
        swap.in_str = stacktop.in_str;    
        
        anaStack.push(swap);
        anaStack.push(no_swap);
        
    }
    return final_output;
}

List language(string input, int k)
{
    List final_output;
    stack <class Pair> anaStack;
    Pair init, stacktop;
    init.in_str = input;
    init.fixed_str = "";
    anaStack.push(init);
    
    while(!anaStack.empty()){
        stacktop = anaStack.top();
        anaStack.pop();
        
        if (final_output.find(stacktop.fixed_str) == NULL){
            final_output.insert(stacktop.fixed_str);
        }
        if ((int)stacktop.fixed_str.length() == k){
            continue;
        }

        int first = stacktop.fixed_str.length();
        char old_first = stacktop.in_str[first];
        for (int i = 0; i < (int)stacktop.in_str.length()-(int)stacktop.fixed_str.length(); i = i + 1){
            // swap every non-fixed index with the first non-fixed index
            //first = stacktop.fixed_str.length;
            int swap_spot = first + i;
            Pair to_push;
            to_push.fixed_str = stacktop.fixed_str + stacktop.in_str[swap_spot];
            char new_first = stacktop.in_str[swap_spot];
            string temp = stacktop.in_str;
            string s1(1, new_first);
            temp.replace(first, 1, s1);
            //temp[first] = new_first;
            string s2(1, old_first);
            temp.replace(swap_spot, 1, s2);
            //temp[swap_spot] = old_first;
            to_push.in_str = temp;
            anaStack.push(to_push);
        }
        
    }
    return final_output;
}

/*
// NOT DONE
List stretch(string input, int k)
{
    List final_output;
    stack <class Pair> anaStack;
    Pair init, stacktop;
    init.in_str = "";
    init.fixed_str = "";
    for (int i = 0; i < (int)input.length(); i = i + 1){
        for (int j = 0; j < k; j = j + 1){
            init.in_str = init.in_str + input[i];
        }
    }
    anaStack.push(init);
    
    while(!anaStack.empty()) // while the stack is non-empty
    {
        stacktop = anaStack.top();// get the top pair in stack 
        anaStack.pop(); // remove the top element of stack
        if (stacktop.in_str.length() == 0) // input string is empty, so this is base case
        {
            final_output.insert(stacktop.fixed_str); // insert the fixed string onto list
            continue; // pop the next element of stack 
            
        }
        char last = stacktop.in_str.back(); // get last element of in_str
        stacktop.in_str.pop_back(); // remove last element of stack
        Pair to_push; // setting up elements to push onto stack
        to_push.in_str = stacktop.in_str;
        to_push.fixed_str = stacktop.fixed_str; 
        anaStack.push(to_push); // this is for one recursive call
        to_push.fixed_str = last + stacktop.fixed_str; // this is for next recursive call
        anaStack.push(to_push);
    }
    return final_output;
}
*/



// This function generates all subsequences of the input input_str, and outputs them as a list. This function does not use recursion.
// Input: string input_str
// Output: list of all subsequences of input_str
// 
List allSubSeqStack(string input_str)
{
    List final_output; // generate empty list
    stack<class Pair> recurStack; // empty stack that performs the recursion
    Pair init, stacktop; // create a pair to push, to start the stac
    init.in_str = input_str; // put the initial string
    init.fixed_str = ""; // this is the fixed string, initially empty
    recurStack.push(init); // push this pair onto the top

    while(!recurStack.empty()) // while the stack is non-empty
    {
        stacktop = recurStack.top();// get the top pair in stack 
        recurStack.pop(); // remove the top element of stack
        if (stacktop.in_str.length() == 0) // input string is empty, so this is base case
        {
            final_output.insert(stacktop.fixed_str); // insert the fixed string onto list
            continue; // pop the next element of stack
        }
        char last = stacktop.in_str.back(); // get last element of in_str
        stacktop.in_str.pop_back(); // remove last element of stack
        Pair to_push; // setting up elements to push onto stack
        to_push.in_str = stacktop.in_str;
        to_push.fixed_str = stacktop.fixed_str; 
        recurStack.push(to_push); // this is for one recursive call
        to_push.fixed_str = last + stacktop.fixed_str; // this is for next recursive call
        recurStack.push(to_push);
    }
    return final_output;
}

// This recursive function generates all subsequences of the input in_str *appended* to the fixed_str, and outputs them in the list provided as an argument
// Input: string fixed_str, string in_str, pointer to list list_ptr
// Output: void, but list referenced by list_ptr is modified
// 
void allSubSeqRec(string in_str, string fixed_str, List *list_ptr)
{
    if (in_str.length() == 0) // base case
    {
        list_ptr->insert(fixed_str); // insert the fixed string into list
        return;
    }
    char top = in_str.back(); // get the last element of the string
    in_str.pop_back(); // delete last element of in_str
    allSubSeqRec(in_str, fixed_str, list_ptr); // recursive call for subsequences without top
    allSubSeqRec(in_str, top+fixed_str, list_ptr); //  recursive call for subsequences with top
    return;
}

// This function generates all subsequences of the input in_str, and outputs them as a list. This is the recursive version
// Input: string in_str
// Output: list of all subsequences of in_str
// 
List allSubSeq(string in_str)
{
    List *final_output = new List(); // generate empty list
    allSubSeqRec(in_str,"",final_output); // populate list with output
    return *final_output;
}


int main(int argc, char** argv)
{
    if (argc < 3) // must provide two arguments as input
    {
        throw std::invalid_argument("Usage: ./hello <INPUT FILE> <OUTPUT FILE>"); // throw error
    }

    ifstream input; // stream for input file
    ofstream output; // stream for output file

    input.open(argv[1]); // open input file
    output.open(argv[2]); // open output file

    string in_str; // to store the input string from the file


    getline(input, in_str); // get the single string from the input file
    
    List myList = swap(in_str); // initializing the linked list

    myList.sort(); // sort the list
    
    output << myList.print("\n") << endl;  // print the list, using a new line as delimiter between items of the list
    
    myList.deleteList(); // free all the memory of this list

    input.close();
    output.close();
}
