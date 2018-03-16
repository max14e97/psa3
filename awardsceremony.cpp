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


#include "part3Graph.cpp"
#include "ActorNode3.hpp"
#include "MovieNode3.hpp"

using namespace std;
/*
struct Compare : public std::binary_function<resultNode, resultNode, bool>{
    bool operator() (const resultNode & n1, const resultNode & n2) const{
      if(n1.first != n2.first){
        return ((n1.first) < (n2.first));
      }
      else{
	return ((n1.name) > (n2.name));
      }
    }
};
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
            if (!getline( ss, next, '\n' )) break;

            record.push_back( next );
        }
    
        if (record.size() != 1) {
            // we should have exactly 3 columns
            continue;
        }

        string start_name(record[0]);
    
        result.push_back(start_name);
    }

    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return result;
    }
    infile.close();

    return result;
}

int main(int argc, const char ** argv) {

  if(argc != 4){
      cout << "Incorrect number of arguments." << endl;
      //cout << "\t First argument: name of dictionary file." << endl;
      exit(-1);
  }

  string in_filename = argv[1];
  int find_number = atoi(argv[2]);
  string output_filename = argv[3];

  cout << "begin building for find number " << find_number << endl;

  part3Graph myGraph(in_filename.c_str());

  cout << "finished building" << endl;

  ActorNode3 * myActor;
  while(myGraph.actorQueue.top()->numberKnown < find_number){
    myActor = myGraph.actorQueue.top();

    for(auto itr : (myActor->mapKnown)){
      --(itr.second->numberKnown);
    }
    //cout << "Removed " << myActor->actorName << " count " << myActor->numberKnown << endl;

    myGraph.actorQueue.pop();
  }

  ofstream myfile;
  myfile.open(output_filename);
  myfile << "Actor" << "\n";
  vector<string> resultArr;

  cout << "actorQueue size " << myGraph.actorQueue.size() << endl;
  while(myGraph.actorQueue.empty() == false){
    myActor = myGraph.actorQueue.top();
    resultArr.push_back(myActor->actorName);
    myGraph.actorQueue.pop();
  }

  cout << "resultArr size " << resultArr.size() << endl;

  sort(resultArr.begin(), resultArr.end());

  for(int i = 0; i < resultArr.size(); ++i){
    myfile << resultArr[i] << "\n";
  }

  myfile.close();
}
