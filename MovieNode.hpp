#ifndef MOVIENODE_HPP
#define MOVIENODE_HPP

#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "ActorNode.hpp"

using namespace std;

class ActorNode;

class MovieNode {

public:
  string movieName;
  int movieYear;

  //ActorNode * prevA;

  vector<ActorNode*> actorArr;

  /** Constructor.  Initialize a ActorNode with the given Data item,
   *  no children.
   */
  MovieNode(string & in_name, int in_year) : movieName(in_name) {
    movieYear = in_year;
  }

};
#endif
