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

vector<Food> merge(vector<Food> left, vector<Food> right) {
  vector<Food> answer;

  while ((left.size() != 0) && right.size() != 0) {
    if (left[0].retCal() <= right[0].retCal()) {
      answer.push_back(left[0]);
      left.erase(left.begin());
    } else {
      answer.push_back(right[0]);
      right.erase(right.begin());
    }
  }

  while (left.size() != 0) {
    answer.push_back(left[0])
  }


}
//
vector<Food> mergeSort(vector<Food> items) {
  int len = items.size()
  if (len <= 1)
    return items;

  vector<Food> left;
  vector<Food> right;
  for (i = 0; i < len; i++) {
    if (i < (len/2))
      left.push_back(items[i]);
    else
      right.push_back(items[i]);
  }

  left = mergeSort(left);
  right = mergeSort(right);

  return merge(left, right);

}

int main() {

  bool val = readInFile("food.txt");
  
  
}
