#ifndef MOVIENODE3_HPP
#define MOVIENODE3_HPP

#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "ActorNode3.hpp"

using namespace std;

class ActorNode3;

class MovieNode3 {

public:
  string movieName;

  vector<ActorNode3*> actorArr;

  /** Constructor.  Initialize a ActorNode with the given Data item,
   *  no children.
   */
  MovieNode3(string & in_name) : movieName(in_name) {
  }

};
#endif
