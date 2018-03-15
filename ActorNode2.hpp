#ifndef ACTORNODE2_HPP
#define ACTORNODE2_HPP

#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <limits>
#include "MovieNode2.hpp"
using namespace std;

class MovieNode2;

class ActorNode2 {

public:
  string actorName;

  vector<MovieNode2*> movieArr;

  int index = -1;

  /** Constructor.  Initialize a ActorNode with the given Data item,
   */
  ActorNode2(string & in_name) : actorName(in_name) {
  }

};
#endif
