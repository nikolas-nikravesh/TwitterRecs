/*
 * File: TUser.cpp
 * Contains the method and variable declarations for TUser
 */

#include <vector>

using namespace std; 

class TUser {

  public:
    int id;
    // list of all the people that the user follows
    vector<int> connections;
    
    // constructor
    TUser(int n): id(n) {}

};
