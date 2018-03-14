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

  vector<string> findArr = loadFromFindFile(find_filename.c_str());

    ActorGraph myGraph(in_filename.c_str(), weighted);

  for(int i = 0; i < findArr.size(); i+=2){
    myGraph.findPath(weighted, findArr[i], findArr[i+1], output_filename.c_str());
  }
}
