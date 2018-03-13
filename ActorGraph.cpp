/*
 * ActorGraph.cpp
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */
 
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <functional>
#include "ActorGraph.hpp"

#include "ActorNode.hpp"
#include "MovieNode.hpp"

using namespace std;

struct Compare : public std::binary_function<ActorNode*, ActorNode*, bool>{
    bool operator() (const ActorNode * n1, const ActorNode * n2) const{
      return ((n1->dist) < (n2->dist));
    }
};


ActorGraph::ActorGraph(const char* in_filename, bool use_weighted_edges) {
  loadFromFile(in_filename, use_weighted_edges);
}

bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges) {
    // Initialize the file stream
    ifstream infile(in_filename);

    bool have_header = false;
  
    // keep reading lines until the end of file is reached
    while (infile) {
        string s;
    
        // get the next line
        if (!getline( infile, s )) break;

        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }

        istringstream ss( s );
        vector <string> record;

        while (ss) {
            string next;
      
            // get the next string before hitting a tab character and put it in 'next'
            if (!getline( ss, next, '\t' )) break;

            record.push_back( next );
        }
    
        if (record.size() != 3) {
            // we should have exactly 3 columns
            continue;
        }

        string actor_name(record[0]);
        string movie_title(record[1]);
        int movie_year = stoi(record[2]);
    
        // we have an actor/movie relationship, now what?
        /*
        if(use_weighted_edges == false){
          movie_year = 2018;
        }
        */
        //movie_title += "$";
        //movie_title += to_string(movie_year);

          MovieNode *myMovie = new MovieNode(movie_title, movie_year);
          ActorNode *myActor = new ActorNode(actor_name);

        if(movieMap.count(movie_title) == 0){
          movieMap[movie_title] = myMovie;

        }
        else{
          //free delete?
          myMovie = (movieMap[movie_title]);
        }

        if(actorMap.count(actor_name) == 0){
          actorMap[actor_name] = myActor;

        }
        else{
          myActor = (actorMap[actor_name]);

        }

        myActor->movieArr.push_back(myMovie);
        myMovie->actorArr.push_back(myActor);

/*
        nodeArr.push_back(myActor);
        movieNodeArr.push_back(myMovie);

        myActor->movieArr.push_back(myMovie);
        myMovie->actorArr.push_back(myActor);
*/
    }

    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    return true;
}

/*
vector<string> ActorGraph::loadFromFindFile(const char* in_filename) {
    // Initialize the file stream
    ifstream infile(in_filename);

    bool have_header = false;
    vector<string> result;
  
    // keep reading lines until the end of file is reached
    while (infile) {
        string s;
    
        // get the next line
        if (!getline( infile, s )) break;

        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }

        istringstream ss( s );
        vector <string> record;

        while (ss) {
            string next;
      
            // get the next string before hitting a tab character and put it in 'next'
            if (!getline( ss, next, '\t' )) break;

            record.push_back( next );
        }
    
        if (record.size() != 2) {
            // we should have exactly 3 columns
            continue;
        }

        string start_name(record[0]);
        string find_name(record[1]);
    
        result.push_back(start_name);
        result.push_back(find_name);
    }

    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return result;
    }
    infile.close();
   
    return result;
}
*/

void ActorGraph::findPath(bool weighted, string & start_name, string & find_name, const char* output_filename){
  priority_queue<ActorNode*, vector<ActorNode*>, Compare> myQueue;
  ActorNode * curr = NULL;
/*
  for(int i = 0; i < nodeArr.size(); ++i){
    if(nodeArr[i]->actorName == start_name){
      curr = nodeArr[i];
    }
  }
*/
  if(curr == NULL){
    //print empty line onto file?
    return;
  }

  curr->dist = 0;
  myQueue.push(curr);
  string result;
  ofstream myfile;
  myfile.open(output_filename);
  
  while(myQueue.empty() == false){
    curr = myQueue.top();
    myQueue.pop();
    if(curr->done == false){
      curr->done = true;

      result = "(" + result + curr->actorName + ")--[" + curr->prevM->movieName + "#@" + to_string(curr->prevM->movieYear) + "]";

      if(curr->actorName == find_name){
        //write to new line of file
        myfile << result << "\n";
        myfile.close();
        return;
      }
      else{
        result += "-->";
      }

      for(int index = 0; index < curr->movieArr.size(); ++index){
        int c = curr->dist + 1 + (2018 - curr->movieArr[index]->movieYear);
        if(c < curr->dist){
          for(int j = 0; j < curr->movieArr[index]->actorArr.size(); ++j){
            if(curr->movieArr[index]->actorArr[j]->actorName != curr->actorName){
              curr->movieArr[index]->actorArr[j]->prev = curr;
              curr->movieArr[index]->actorArr[j]->dist = c;
              curr->movieArr[index]->actorArr[j]->prevM = curr->movieArr[index];
              myQueue.push(curr->movieArr[index]->actorArr[j]);
              break;
            }
          }
        }
      }
    }
  }

  //write empty line to file
  myfile << "\n";
  myfile.close();
}
