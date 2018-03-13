#ifndef ACTORNODE_HPP
#define ACTORNODE_HPP

#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <limits>
#include "MovieNode.hpp"
using namespace std;

class MovieNode;

class ActorNode {

public:
  string actorName;

  vector<MovieNode*> movieArr;

  unsigned int dist;
  ActorNode * prev;
  bool done;

  MovieNode * prevM;

  /** Constructor.  Initialize a ActorNode with the given Data item,
   */
  ActorNode(string & in_name) : actorName(in_name) {
    dist = numeric_limits<int>::max();
    done = false;
  }

/*
    bool operator() (ActorNode * n1, ActorNode * n2){
      return ((n1->dist) < (n2->dist));
    }
*/
};
#endif
