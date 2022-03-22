// Wrapper

#include <iostream>
#include <stack>
#include <stdexcept>
#include <fstream>
#include <array>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cstring>
#include <set>
#include <unordered_map>
#include <bits/stdc++.h>
#include <stdbool.h>
#include <queue>

using namespace std;

class Pair{
    public:
        string name;
        string movie;
};


int main(int argc, char** argv){
    if (argc < 3){
        throw std::invalid_argument("Usage ./sixdegrees <INPUT FILE> <OUTPUT FILE>");
    }

    ifstream input;
    ofstream output;
    ifstream movies;

    input.open(argv[1]);
    output.open(argv[2]);
    movies.open("cleaned_movielist.txt");

    string command;
    char *com, *act1, *act2, *movie;


   
    unordered_map<string, set <string>> actor_map; // holds all actors and everyone related to that actor
    unordered_map<string, bool> visited; // boool map of which actors are visited
    map<vector <string>, string> movie_map;
  
    
    
    
    // READ THE LIST OF MOVIES AND CREATE MAP OF RELATIONS
    while (getline(movies, command)){
        if (command.length() == 0){
            continue;
        }
        
        com = strdup(command.c_str());
        movie = strtok(com, " \t");

        // Adds actors of current movie to a set
        act1 = strtok(NULL, " \t");
        set <string> this_movie;

        while (act1 != NULL){ 
      // ADD act1 TO THINGS
            this_movie.insert(act1);
            act1 = strtok(NULL, " \t");
        }
    
        for (set <string>::iterator i = this_movie.begin(); i != this_movie.end(); ++i){
            string curr = *i;
            //visited[curr] = false; 
            for (set <string>::iterator j = this_movie.begin(); j != this_movie.end(); ++j){
                actor_map[curr].insert(*j); 
                vector<string> v{curr, *j};
                movie_map[v] = movie;   
            }
       
        }
    }
  
  // READ EACH PAIR IN INPUT AND DO STUFF
    while (getline(input, command)){
        //cout << command << endl;
        if (command.length() == 0)
            continue;
        com = strdup(command.c_str());
        act1 = strtok(com, " \t");
        act2 = strtok(NULL, " \t");
    
        if (act1 == NULL || act2 == NULL){
            cout << "invalid input\n";
            continue;
        }
        
        if (actor_map.find(act1) == actor_map.end() || actor_map.find(act2) == actor_map.end()){
            output << "Not present\n";
            continue;
        }  
        if (strcmp(act1, act2) == 0){
            output << act1 << endl;
            continue;
        }
        
        queue<string> q;
        vector<string> path;
        unordered_map <string, string> p;

        bool finished = false;
        for (unordered_map<string, set<string>>::iterator i = actor_map.begin(); i != actor_map.end(); ++i){
            visited[i->first] = false;
        }

        string start = act1;
        
        q.push(start);
        visited[act1] = true;
        
        while (!q.empty() && finished == false){
            start = q.front();
            q.pop();
            for (set <string>::iterator i = actor_map[start].begin(); i != actor_map[start].end(); ++i){
                if (visited[*i] == false){
                    visited[*i] = true;
                    p[*i] = start; 
                    q.push(*i); 
                    
                    if (*i == act2){
                        // FOUND PATH!
                        finished = true;
                        //string curr = act2; 
                        string curr = act2;
                        path.push_back(act2);
                        while (p.find(curr) != p.end()){
                            path.push_back(p[curr]);
                            curr = p[curr];
                        }
                        //cout << "does reach here\n";
                        for (int i = 1; i < (int)path.size(); i = i + 1){
                            string curr_path = path[(int)path.size() - i];
                            string path_next = path[(int)path.size() - i - 1];
                            output << curr_path;
                            vector<string> v{curr_path, path_next};
                            output << " -(" << movie_map[v] << ")- ";
                        }

                        output << act2 << endl;         
                        break;
                    } 
                }
            }   
        }

        if (finished == false){
            // no path found
            //cout << "here\n";
            output << "Not present\n";
        } 
    
  }

  
}