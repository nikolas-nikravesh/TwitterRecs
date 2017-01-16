/*
 * File: extension.cpp
 * Handles implementation of finding follower recommendations in the PA4
 * extension. Parses command line arguments of graph files, test files, number
 * of recommentations desired, and outfile where output is stored.
 */

#include "TGraph.h"
#include <iostream>
#include <fstream>
#include <string>


using namespace std;

/*
 * Function: main
 * Contains the functionality to find recommended followers using a graph
 */

int main (int argc, char* argv[]){
  
  if(argc != 5){
    cerr << "ERROR: Incorrect number of args" << endl;
    cerr << "USAGE: ./extension [graphfile] [testfile] [# of recs]";
    cerr << " [outfile]" << endl;
    return -1;
  }

  // store arguments from command line into variables
  const char* infile = argv[1];
  string testfile = argv[2];
  int numRecs = stoi(argv[3]);
  string outfile = argv[4];

  TGraph t;
  ifstream test(testfile);
  ofstream out(outfile);

  // use the information provided to create the graph
  t.loadGraph(infile);

  // variable that will store the lines read from the id file
  string line;

  //read in from test file for ids to reccommend
  while(getline(test, line)){
  
    int id = stoi(line);
    vector<pair<int,int>> recs;
    //get reccommendations
    recs = t.getRecs(id, numRecs);
      
    out << "USER ID: " << id << endl;
    out << "TOP " << numRecs << " RECOMMENDATIONS"; 
    if(recs.size() < numRecs) {
      out << " (Max " << recs.size() << " recs available)";
    }
    out << endl;
    out << "\t[ID]\t" << "\t[Number of mutual connections]" << endl;

    // print the ids of recommended users
    for(unsigned int i = 0; i < recs.size(); i++){
      out << "\t" << recs[i].first << "\t" << recs[i].second << endl;
    }
    
    out << endl;

  }
  // close the files
  test.close();
  out.close();

  return 0;

}
