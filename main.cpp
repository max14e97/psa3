#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <assert.h>
#include <cstring>
#include <queue>
#include <functional>
#include <cstring>


#include "ActorGraph.hpp"
#include "ActorGraph.cpp"
#include "ActorNode.hpp"
#include "MovieNode.hpp"

using namespace std;
/*
void findPath(bool weighted, string & start_name, string & find_name, const char* output_filename){
  ActorNode * curr = NULL;

  if(actorMap.count(start_name) != 0){
    curr = actorMap[strat_name];
  }
  else{
    //print empty line onto file?
    return;
  }

  priority_queue<ActorNode*, vector<ActorNode*>, Compare> myQueue;

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
*/
vector<string> loadFromFindFile(const char* in_filename) {
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

int main(int argc, const char ** argv) {

  if(argc != 5){
      cout << "Incorrect number of arguments." << endl;
      //cout << "\t First argument: name of dictionary file." << endl;
      cout << endl;
      exit(-1);
  }

  bool weighted;
  if(string(argv[2]).compare("u") == 0){
    weighted = false;
  }
  else if(string(argv[2]).compare("w") == 0){
    weighted = true;
  }
  else{
    exit(-1);
  }

  string in_filename = argv[1];
  string find_filename = argv[3];
  string output_filename = argv[4];

  ActorGraph myGraph(in_filename.c_str(), weighted);
  vector<string> findArr = loadFromFindFile(find_filename.c_str());

  for(int i = 0; i < findArr.size(); i+=2){
    ActorGraph::findPath(weighted, findArr[i], findArr[i+1], output_filename.c_str());
  }
}
