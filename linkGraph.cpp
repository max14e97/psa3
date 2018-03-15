#ifndef LINKGRAPH_HPP
#define LINKGRAPH_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <functional>

#include <unordered_map>
#include "ActorNode2.hpp"
#include "MovieNode2.hpp"
#include "ActorGraph.hpp"

using namespace std;
class linkGraph {
public:
    unordered_map<string, ActorNode2*> actorMap;
    unordered_map<string, MovieNode2*> movieMap;

    vector<vector<int>> adjMatrix;
    vector<string> paraArr;

    linkGraph(const char* in_filename){
      loadFromFile(in_filename);

      for(int i = 0; i < actorMap.size(); ++i){
        vector<int> subVector(actorMap.size(), 0);
        adjMatrix.push_back(subVector);
      }

      ActorNode2 * myActor;
      int counter = 0;
      for(auto itr : movieMap){
        for(int i = 0; i < itr.second->actorArr.size(); ++i){
            myActor = itr.second->actorArr[i];
	    if(myActor->index == -1){
              //myMovie->actorArr[i];
              paraArr.push_back(myActor->actorName);
              myActor->index = paraArr.size() - 1;
              //for(int i = 0; i < adjMatrix.size(); ++i)
            }

            for(int j = i+1; j < itr.second->actorArr.size(); ++j){
              if(itr.second->actorArr[j]->index == -1){
                paraArr.push_back(itr.second->actorArr[j]->actorName);
                itr.second->actorArr[j]->index = paraArr.size() - 1;
              }

              adjMatrix[myActor->index][itr.second->actorArr[j]->index] = 1;
              adjMatrix[itr.second->actorArr[j]->index][myActor->index] = 1;
            }
        }
      }

    }

    bool loadFromFile(const char* in_filename);
};

#endif

bool linkGraph::loadFromFile(const char* in_filename) {
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
        movie_title += "$$";
        movie_title += to_string(movie_year);

        MovieNode2 *myMovie = new MovieNode2(movie_title);
        ActorNode2 *myActor = new ActorNode2(actor_name);

        if(actorMap.count(actor_name) == 0){
          actorMap[actor_name] = myActor;
        }
        else{
          myActor = (actorMap[actor_name]);
        }

        if(movieMap.count(movie_title) == 0){
          movieMap[movie_title] = myMovie;
        }
        else{
          //free delete?
          myMovie = (movieMap[movie_title]);
        }

        myActor->movieArr.push_back(myMovie);
        myMovie->actorArr.push_back(myActor);
    }

    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    return true;
}

