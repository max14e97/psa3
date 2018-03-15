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


#include "linkGraph.cpp"
#include "ActorNode2.hpp"
#include "MovieNode2.hpp"
#include "MatrixMultiply.hpp"

using namespace std;

struct Compare : public std::binary_function<pair<int,int>, pair<int,int>, bool>{
    bool operator() (const pair<int,int> n1, const pair<int,int> n2) const{
      return ((n1.first) < (n2.first));
    }
};

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

  linkGraph myGraph(in_filename.c_str());


  ofstream myfile;
  myfile.open(output_filename);
  myfile << "(actor)--[movie#@year]-->(actor)--..." << "\n";

  for(int i = 0; i < findArr.size(); ++i){

    int findIndex = myGraph.actorMap[findArr[i]]->index;
    vector<int> findVector = myGraph.adjMatrix[findIndex];
    vector<vector<int>> inputVector;
    inputVector.push_back(findVector);
    MatrixOperations<int> myMultiply(inputVector, myGraph.adjMatrix);
    vector<vector<int>> resultMatrix = myMultiply.matrixMultiply();

    vector<int> resultArr = resultMatrix[0];

    priority_queue<pair<int,int>> maxIndexArr;
    priority_queue<pair<int,int>, vector<pair<int,int>>, Compare> maxQueue;
    for(int j = 0; j < resultArr.size(); ++j){
      maxQueue.push(make_pair(resultArr[j],j));
    }

    vector<string> resultZero;
    vector<string> resultOne;

    while((resultZero.size() <= 4) || (resultOne.size() <= 4)){
      int foundIndex = maxQueue.top().second;
      if((myGraph.adjMatrix[foundIndex][findIndex] == 0) && (resultZero.size() <= 4)){
        resultZero.push_back(myGraph.paraArr[foundIndex]);
      }
      else if((myGraph.adjMatrix[foundIndex][findIndex] == 1) && (resultZero.size() <= 4)){
        resultOne.push_back(myGraph.paraArr[foundIndex]);
      }
      maxQueue.pop();
    }

    //string result = myGraph.findPath(weighted, findArr[i], findArr[i+1], output_filename.c_str());

    //write to new line of file
    //myfile << result << "\n";
  }

  myfile.close();
}
