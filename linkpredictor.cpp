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

class resultNode{
public:
  int first;
  int second;
  string name;

  resultNode(int in1, int in2, string in3){
    first = in1;
    second = in2;
    name = in3;
  }
};
/*
struct Compare : public std::binary_function<pair<int,int>, pair<int,int>, bool>{
    bool operator() (const pair<int,int> n1, const pair<int,int> n2) const{
      if(n1.first != n2.first){
        return ((n1.first) < (n2.first));
      }
      else{
      }
    }
};
*/
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
      exit(-1);
  }

  string in_filename = argv[1];
  string find_filename = argv[2];
  string outputOne_filename = argv[3];
  string output_filename = argv[4];

  vector<string> findArr = loadFromFindFile(find_filename.c_str());

  //cout << "begin building" << endl;

  linkGraph myGraph(in_filename.c_str());

  //cout << "finished building" << endl;

  ofstream myfile;
  myfile.open(outputOne_filename);
  myfile << "Actor1,Actor2,Actor3,Actor4" << "\n";

  ofstream myfile2;
  myfile2.open(output_filename);
  myfile2 << "Actor1,Actor2,Actor3,Actor4" << "\n";

  for(int i = 0; i < findArr.size(); ++i){
    //cout << "begin writing for " << findArr[i] << endl;
    //get the index in the matrix of the query name
    int findIndex = myGraph.actorMap[findArr[i]]->index;

    //extract that one row of vector from matrix
    vector<int> findVector = myGraph.adjMatrix[findIndex];
    vector<vector<int>> inputVector;
    inputVector.push_back(findVector);

    MatrixOperations<int> myMultiply(inputVector, myGraph.adjMatrix);
    vector<vector<int>> resultMatrix = myMultiply.matrixMultiply();

    vector<int> resultArr = resultMatrix[0];
/*
    for(int j = 0; j < resultArr.size(); ++j){
      cout << resultArr[j] << "-";
      cout << myGraph.paraArr[j] << " ";
    }
    cout << "\n" << endl;
*/
    //priority_queue<pair<int,int>, vector<pair<int,int>>, Compare> maxQueue;
    priority_queue<resultNode, vector<resultNode>, Compare> whatQueue;
    for(int j = 0; j < resultArr.size(); ++j){
      //maxQueue.push(make_pair(resultArr[j],j));
      resultNode thisNode(resultArr[j],j,myGraph.paraArr[j]);
      whatQueue.push(thisNode);
    }

    vector<string> resultZero;
    vector<string> resultOne;

    while((resultZero.size() < 4) || (resultOne.size() < 4)){
      //int foundFreq = maxQueue.top().first;
      //int foundIndex = maxQueue.top().second;
      //cout << maxQueue.top().first << "-" << myGraph.paraArr[foundIndex] << " ";
      //maxQueue.pop();
      int foundFreq = whatQueue.top().first;
      int foundIndex = whatQueue.top().second;
      
      //keep finding items following it until first is not the same
      //#1 top pop push
      //#2 loop to find everything and put into a vector
     if(foundIndex == findIndex){
        whatQueue.pop();
        continue;
      }
      else if((myGraph.adjMatrix[foundIndex][findIndex] == 0) && (resultZero.size() < 4)){
        resultZero.push_back(myGraph.paraArr[foundIndex]);

/*
        vector<int> temp;
        while(maxQueue.top().first == foundFreq){
          temp.push_back(maxQueue.top().second);
          maxQueue.pop();
        }

        vector<string> tempName;
        for(int x = 0; x < temp.size(); ++x){
          tempName.push_back(myGraph.paraArr[temp[x]]);
          sort(tempName.begin(), tempName.end());
        }

        if(tempName.size() == 0){
          resultZero.push_back(myGraph.paraArr[foundIndex]);
        }
        else{
          resultZero.push_back(tempName[0]);
        }
*/      
      }
      else if((myGraph.adjMatrix[foundIndex][findIndex] == 1) && (resultOne.size() < 4)){
        //cout << "pushed! ";
        resultOne.push_back(myGraph.paraArr[foundIndex]);

/*
        vector<int> temp;
        while(maxQueue.top().first == foundFreq){
          temp.push_back(maxQueue.top().second);
          maxQueue.pop();
        }

        vector<string> tempName;
        for(int x = 0; x < temp.size(); ++x){
          tempName.push_back(myGraph.paraArr[temp[x]]);
          sort(tempName.begin(), tempName.end());
        }

        if(tempName.size() == 0){
          resultOne.push_back(myGraph.paraArr[foundIndex]);
        }
        else{
          resultOne.push_back(tempName[0]);
        }
*/      
      }

      whatQueue.pop();
    }

    myfile << resultOne[0] << "\t";
    myfile << resultOne[1] << "\t";
    myfile << resultOne[2] << "\t";
    myfile << resultOne[3] << "\n";

    myfile2 << resultZero[0] << "\t";
    myfile2 << resultZero[1] << "\t";
    myfile2 << resultZero[2] << "\t";
    myfile2 << resultZero[3] << "\n";

    //cout << "finished writing for " << findArr[i] << endl;

    //string result = myGraph.findPath(weighted, findArr[i], findArr[i+1], output_filename.c_str());

    //write to new line of file
    //myfile << result << "\n";
  }

  myfile.close();
  myfile2.close();
}
