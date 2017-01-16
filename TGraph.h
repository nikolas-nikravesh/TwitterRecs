/*
 * File: TGraph.cpp
 * Contains the method and variable declarations for TGraph, along with
 * priority queue operations that are overwritten for the purposes of
 * this program
 */

#include "TUser.h" 
#include <unordered_map>
#include <string>

class pairCmp {

  public:
    // override the operator to compare numbers of mutual connections
    bool operator()(pair<int,int> lhs, pair<int,int> rhs) const {
      
      return lhs.second < rhs.second;
    
    }

};


class TGraph {

  protected:
    // the actual graph itself
    unordered_map<int, TUser*> userGraph;
    // list of all the people that are followed by the people that the user
    // follows
    unordered_map<int, int> recs;
  
  
  public:
    // construct the graph
    bool loadGraph(const char* in_filename);
    // sorts the people in recs based on number of mutual connections, from
    // most to least
    vector<pair<int,int>> getRecs(int id, int num);

    ~TGraph();



};
