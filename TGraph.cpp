/*
 * File: TGraph.cpp
 * Contains implementation of building and traversing through the graph to get
 * Twitter follower recommendations, given a file of user ids that indicate
 * relationships of one user following another
 */

#include "TGraph.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <fstream>

/*
 * Function: loadGraph
 * Reads in the file containing graph information and creates a graph of users
 */
bool TGraph::loadGraph(const char* in_filename) {
    // Initialize the file stream
    ifstream infile(in_filename);
    
    // keep reading lines until the end of file is reached
    while (infile) {
        string s;
    
        // get the next line
        if (!getline( infile, s )) break;

        istringstream ss( s );
        vector <string> record;

        while (ss) {
            string next;
      
            // get the next string before hitting a space and put it 
            // in 'next'
            if (!getline( ss, next, ' ' )) break;

            record.push_back(next);
        }
    
        if (record.size() != 2) {
            // we should have exactly 2 columns
            continue;
        }

        int firstID = stoi(record[0]);
        int secondID = stoi(record[1]);

         
        //if ID1 is not in map, insert the new ID  
        if(userGraph.find(firstID) == userGraph.end()){
         
          TUser* user = new TUser(firstID);
          userGraph.insert(make_pair(firstID,user));
         
        }

        //if ID2 is not in map, insert the new ID  
        if(userGraph.find(secondID) == userGraph.end()){
         
          TUser* user = new TUser(secondID);
          userGraph.insert(make_pair(secondID,user));
         
        }

        //add a directed edge from user 1 to user 2
        TUser* user1 = userGraph[firstID];
        TUser* user2 = userGraph[secondID];

        user1->connections.push_back(user2->id);

    }

/*    for(auto it = userGraph.begin(); it != userGraph.end(); ++it){
  

      // delete the TUser object
      TUser* user = it->second;
      cout << "User: " << user->id <<endl;

      for(unsigned int i = 0; i < user->connections.size(); i++){
        
        cout << user->connections[i] << endl;
      
      }
      
      cout << endl;
    
  
    }
*/
    
    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    return true;
}

/*
 * Function: getRecs
 * Return a vector of follow recommendations and the number of connections
 * in common that they have
 */
vector<pair<int,int>> TGraph::getRecs(int id, int num) {

  vector<pair<int,int>> finalrecs;
  recs.clear();

  // check if the id exists in the graph, if not return an empty vector
  if(userGraph.find(id) == userGraph.end()){
    return finalrecs;
  }
  
  // if the num provided is less than 1, don't bother w/ rest of function
  if(num < 1){
    return finalrecs;
  }

  //get the user to reccommend
  TUser* user = userGraph[id];
  vector<int> following1 = user->connections;

  //traverse through every user the user follows
  for(int i: following1){
  
    //get the info from following vector ids
    TUser* followed_user = userGraph[i];
    vector<int> following2 = followed_user->connections;
  
    //traverse the vectors of the followed_user
    for(int j: following2){

      // if the user is already in recs map, increment the count
      if (recs.find(j) != recs.end()) {
        recs[j]++;
      }
      // else add the user to the recs map
      else {
        recs.insert(make_pair(j, 1));
      }
    }
  
  
  }

  //sort the reccommendations based on frequency of appearence using pq
  priority_queue<pair<int,int>, vector<pair<int, int>>, pairCmp> pq;
  
  
  //add all the nodes from the recs map to the pq
  for (auto it = recs.begin(); it != recs.end(); it++) {
    pq.push(*it);
  }
  
  //get num recs from pq

  if(pq.size() < num){
    num = pq.size();
  }
  
  for (int i = 0; i < num; i++){
  
    pair<int, int> p = pq.top();
    pq.pop();
    finalrecs.push_back(p);

  }

  return finalrecs;
}

/*
 * TGraph destructor
 * Make sure we delete all elements within the object that were on heap
 */
TGraph::~TGraph(){

  for(auto it = userGraph.begin(); it != userGraph.end(); ++it){
  
    // delete the TUser object
    delete it->second;
  
  }


}
