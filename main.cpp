// Code for deciding what food to eat

#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <boost/algorithm/string.hpp>

using namespace std;

#include "Food.h"

vector<Food> foodList;

bool readInFile(string filename) {
  string line;
  vector<string> fields;
  ifstream file(filename.c_str());
  if (!file.is_open())
    return false;
  while (getline(file, line)) {
    split(fields, line, is_any_of(","));
    print fields;
  }
  file.close();
  return true;
}


int main() {

  //adding all of the items, all of these were taken from the book 'The Shredded Chief' by Michael Matthews."
  //order of parameters: name, type, page, calories, protein (g), carbs (g), fat(g), time (min)
  bool val = readInFile("food.txt");
  
}
