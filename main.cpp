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

//merge algorithm that sorts elements from least cal to highest cal
vector<Food> merge(vector<Food> left, vector<Food> right) {
  vector<Food> answer;

  while ((left.size() != 0) && right.size() != 0) {
    if (left[0].retCal() <= right[0].retCal()) {
      answer.push_back(left[0]);
      left.erase(left.begin());
      //the erase operation is extremely inefficient on a vector
      //but won't matter for a vector this small
    } else {
      answer.push_back(right[0]);
      right.erase(right.begin());
    }
  }

  if (left.size() != 0) {
    for (int i = 0; i < left.size(); i++) {
      answer.push_back(left[i]);
    }
    left.clear();
  }

  if (right.size() != 0) {
    for (int i = 0; i < right.size(); i++) {
      answer.push_back(right[i]);
    }
  }
  
  return answer;


}
//mergesort algorithm that recursively breaks elements to half their size
vector<Food> mergeSort(vector<Food> items) {
  int len = items.size();
  if (len <= 1)
    return items;

  vector<Food> left;
  vector<Food> right;
  for (int i = 0; i < len; i++) {
    if (i < (len/2))
      left.push_back(items[i]);
    else
      right.push_back(items[i]);
  }

  left = mergeSort(left);
  right = mergeSort(right);

  return merge(left, right);

}

bool **dp;

void display(vector<Food> &s) {
  for (int i = 0; i < s.size(); ++i)
    printf("%d ", s[i].retCal());
  printf("\n");
}

void printSub(vector<Food> arr, int i, int sum, vector<Food>& p) {

  if (i == 0 && sum != 0 && dp[0][sum]) {
    p.push_back(arr[i]);
    display(p);
    return;
  }

  if (i == 0 && sum == 0) {
    display(p);
    return;
  }

  if (dp[i-1][sum]) {
    vector<Food> b = p;
    printSub(arr, i-1, sum, b);
  }

  if (sum >= arr[i].retCal() && dp[i-1][sum-arr[i].retCal()]) {
    p.push_back(arr[i]);
    printSub(arr, i-1, sum-arr[i].retCal(), p);
  }
}

void printAll(vector<Food> arr, int n, int sum) {

  if (n == 0 || sum < 0)
    return;

  dp = new bool*[n];
  for (int i = 0; i < n; ++i) {
    dp[i] = new bool[sum + 1];
    dp[i][0] = true;
  }

  if (arr[0].retCal() <= sum)
    dp[0][arr[0].retCal()] = true;

  for (int i = 1; i < n; ++i)
    for (int j = 0; j < sum + 1; ++j)
      dp[i][j] = (arr[i].retCal() <= j) ? dp[i-1][j] || dp[i-1][j-arr[i].retCal()] : dp[i - 1][j];

  if (dp[n-1][sum] == false) {
    printf("There are no sumbsets with sum %dn", sum);
    return;
  }

  vector<Food> p;
  printSub(arr, n-1, sum, p);
}

int main() {

  bool val = readInFile("food.txt");
  foodList = mergeSort(foodList);

  int n = foodList.size();
  int sum = 2000;
  printAll(foodList, n, sum);
  return 0;
}
