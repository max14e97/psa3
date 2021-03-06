/*
 * ActorGraph.hpp
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP

#include <iostream>
#include <unordered_map>
#include "ActorNode.hpp"
#include "MovieNode.hpp"

// Maybe include some data structures here

using namespace std;

class ActorGraph {
protected:
  
    // Maybe add class data structure(s) here

public:
    //vector<ActorNode*> nodeArr;
    //vector<MovieNode*> movieNodeArr;
    unordered_map<string, ActorNode*> actorMap;
    unordered_map<string, MovieNode*> movieMap;

    ActorGraph(const char* in_filename, bool use_weighted_edges);

    ~ActorGraph(){
      for(auto itr : actorMap){
        delete(itr.second);
      }

      for(auto itr : movieMap){
        delete(itr.second);
      }
    }

    // Maybe add some more methods here
  
    /** You can modify this method definition as you wish
     *
     * Load the graph from a tab-delimited file of actor->movie relationships.
     *
     * in_filename - input filename
     * use_weighted_edges - if true, compute edge weights as 1 + (2018 - movie_year), otherwise all edge weights will be 1
     *
     * return true if file was loaded sucessfully, false otherwise
     */
    bool loadFromFile(const char* in_filename, bool use_weighted_edges);
    
    string findPath(bool weighted, string & start_name, string & find_name, const char* output_filename);

    //vector<string> loadFromFindFile(const char* in_filename);
};


#endif // ACTORGRAPH_HPP
