#ifndef MOVIENODE2_HPP
#define MOVIENODE2_HPP

#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "ActorNode2.hpp"

using namespace std;

class ActorNode2;

class MovieNode2 {

public:
  string movieName;

  vector<ActorNode2*> actorArr;

  /** Constructor.  Initialize a ActorNode with the given Data item,
   *  no children.
   */
  MovieNode2(string & in_name) : movieName(in_name) {
  }

};
#endif
