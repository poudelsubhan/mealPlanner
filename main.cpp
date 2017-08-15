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

void display(const vector<int>& v)
{
  int sum = 0;
  for (int i = 0; i < v.size(); ++i) {
        printf("%d ", v[i]);
	sum += v[i];
  }
  cout << sum;
  printf("\n");
}
 
// A recursive function to print all subsets with the
// help of dp[][]. Vector p[] stores current subset.
void printSubsetsRec(int arr[], int i, int sum, vector<int>& p)
{
    // If we reached end and sum is non-zero. We print
    // p[] only if arr[0] is equal to sum OR dp[0][sum]
    // is true.
    if (i == 1 && sum != 0 && dp[1][sum])
    {
        p.push_back(arr[i]);
        display(p);
        return;
    }
 
    // If sum becomes 0
    if (i == 1 && sum == 0)
    {
        display(p);
        return;
    }
 
    // If given sum can be achieved after ignoring
    // current element.
    if (dp[i-1][sum])
    {
        // Create a new vector to store path
        vector<int> b = p;
        printSubsetsRec(arr, i-1, sum, b);
    }
 
    // If given sum can be achieved after considering
    // current element.
    if (sum >= arr[i] && dp[i-1][sum-arr[i]])
    {
        p.push_back(arr[i]);
        printSubsetsRec(arr, i-1, sum-arr[i], p);
    }
}
 
// Prints all subsets of arr[0..n-1] with sum 0.
void printAllSubsets(int arr[], int n, int sum)
{
    if (n == 0 || sum < 0)
       return;
 
    // Declaring the num of rows in the matrix
    dp = new bool*[n+1];

    for (int i = 0; i <= n; ++i) {
      //declare the num of colums per row in the matrix
      dp[i] = new bool[sum+1];

      //You can create a sum of 0 from the empty subset
      dp[i][0] = true;
    }

    //if the subset is 0 and the sum is greater than 0, then false
    for (int i = 1; i <= sum; ++i) {
      dp[0][i] = false;
    }

    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= sum; ++j) {
	dp[i][j] = dp[i-1][j];
	if (dp[i][j] == false && j >= arr[i-1]) {
	  dp[i][j] = dp[i][j] || dp[i-1][j-arr[i-1]];
	}
      }
    }
    
    if (dp[n][sum] == false) {
        printf("There are no subsets with sum %d. \n", sum);
        return;
    }
 
    // Now recursively traverse dp[][] to find all
    // paths from dp[n-1][sum]
    vector<int> p;
    printSubsetsRec(arr, n, sum, p);
}

int main() {

  bool val = readInFile("food.txt");
  foodList = mergeSort(foodList);
  int n = foodList.size();
  int sum = 500;
  int arr[n];
  for (int i = 0; i < n; ++i) {
    arr[i] = foodList[i].retCal();
    printf ("%4d", arr[i]);
  }
  //printAllSubsets(arr, n, sum);

  /*
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= sum; j++) {
      printf ("%1d", dp[i][j]);
    }
    printf("\n");
  }
  */
  

  
  return 0;
}
