#ifndef ACTORNODE3_HPP
#define ACTORNODE3_HPP

#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <limits>
#include <unordered_map>
#include "MovieNode3.hpp"
using namespace std;

class MovieNode3;

class ActorNode3 {

public:
  string actorName;

  vector<MovieNode3*> movieArr;

  unordered_map<string,ActorNode3*> mapKnown;

  int numberKnown = 0;

  /** Constructor.  Initialize a ActorNode with the given Data item,
   */
  ActorNode3(string & in_name) : actorName(in_name) {
  }

};
#endif
