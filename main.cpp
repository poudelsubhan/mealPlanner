// Code for deciding what food to eat

#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>

using namespace std;

#include "Food.h"

vector<Food> foodList;
// This vector will contain objects of type "Food"

vector<string> split(string line, char c) {
  // The split function that will split the line on the character "c".
  vector<string> retVec;
  stringstream ss(line);
  string token;

  while(getline(ss, token, c)) {
    retVec.push_back(token);
  }

  return retVec;
}

bool readInFile(string filename) {
  string line;
  ifstream file(filename.c_str());
  string delim = ",";
  if (!file.is_open())
    return false;
  while (getline(file, line)) {
    vector<string> sp = split(line, ',');
    
    //adding all of the items, all of these were taken from the book 'The Shredded Chief' by Michael Matthews."
    //order of parameters: name, type, page, calories, protein (g), carbs (g), fat(g), time (min)
    Food item = Food(sp[0], atoi(sp[1].c_str()), atoi(sp[2].c_str()), atoi(sp[3].c_str()), atoi(sp[4].c_str()), atoi(sp[5].c_str()), atoi(sp[6].c_str()), atoi(sp[7].c_str()));
    
    foodList.push_back(item);
    }
  return true;
}


int main() {

  bool val = readInFile("food.txt");
  cout << foodList.size() << endl;
  
}
