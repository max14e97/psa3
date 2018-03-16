#ifndef part3GRAPH_HPP
#define part3RAPH_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <functional>

#include <unordered_map>
#include "ActorNode3.hpp"
#include "MovieNode3.hpp"

using namespace std;

struct Compare : public std::binary_function<ActorNode3*, ActorNode3*, bool>{
    bool operator() (const ActorNode3 * n1, const ActorNode3 * n2) const{
      return ((n1->numberKnown) > (n2->numberKnown));
    }
};

/*
bool comparison(const ActorNode3 * n1, const ActorNode3 * n2){
  return ((n1->numberKnown) < (n2->numberKnown));
}
*/

class part3Graph {
public:
    unordered_map<string, ActorNode3*> actorMap;
    unordered_map<string, MovieNode3*> movieMap;

    priority_queue<ActorNode3*, vector<ActorNode3*>, Compare> actorQueue;

    part3Graph(const char* in_filename){
      loadFromFile(in_filename);

      ActorNode3 * myActor;

      for(auto itr : movieMap){
        for(int i = 0; i < itr.second->actorArr.size(); ++i){
            myActor = itr.second->actorArr[i];

            ActorNode3 * currActor;
            for(int j = i+1; j < itr.second->actorArr.size(); ++j){
              currActor = itr.second->actorArr[j];

              if(myActor->actorName != currActor->actorName){
              if(myActor->mapKnown.count(currActor->actorName) == 0){
                myActor->mapKnown[currActor->actorName] = currActor;
              }
              if(currActor->mapKnown.count(myActor->actorName) == 0){
                currActor->mapKnown[myActor->actorName] = myActor;
              }
              }
            }
          //cout << myActor->actorName << " knows " << myActor->numberKnown << endl;
        }
      }

      for(auto itr : actorMap){
        itr.second->numberKnown = itr.second->mapKnown.size();
        actorQueue.push(itr.second);

        //cout << itr.second->actorName << " knows " << itr.second->numberKnown << endl;
      }

      cout << "actor map node number " << actorMap.size() << endl;
      cout << "pQueue size " << actorQueue.size() << endl;

    }

    ~part3Graph(){
      for(auto itr : actorMap){
        delete(itr.second);
      }

      for(auto itr : movieMap){
        delete(itr.second);
      }
    }


bool loadFromFile(const char* in_filename) {
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

        MovieNode3 *myMovie = new MovieNode3(movie_title);
        ActorNode3 *myActor = new ActorNode3(actor_name);

        if(actorMap.count(actor_name) == 0){
          actorMap[actor_name] = myActor;
        }
        else{
          delete(myActor);
          myActor = (actorMap[actor_name]);
        }

        if(movieMap.count(movie_title) == 0){
          movieMap[movie_title] = myMovie;
        }
        else{
          //free delete?
          delete(myMovie);
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

};
#endif
