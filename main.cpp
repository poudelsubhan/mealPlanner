// Created by Subhan Poudel
// Code for deciding what food to eat
// Merge sort algorithm is based on the article on wikipedia
// subset sum algorithm found in wikipedia, geek for geeks and tutorial horizon

#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <math.h>

using namespace std;

#include "Food.h"

vector<Food> foodList;
// This vector will contain objects of type "Food"


vector<string> split(string line, char c) {
  // The split function that will split the line on the character "c".
  // returns a vector of strings where each element is a string before the character "c"
  vector<string> retVec;
  stringstream ss(line);
  string token;

  //splits each line on the character "c" and puts it in the vector
  while(getline(ss, token, c)) {
    retVec.push_back(token);
  }

  return retVec;
}

bool readInFile(string filename) {
  //reads in the file, creates Food object from each line in file and pushes that object to the vector of type Food
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
//sorting is not necessary for the subset sum algorithm to work
//you can find mergesort on wikipedia, adapted for vector of type Food
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

//2-D array that solves the subset sum problem
bool **ansArr;

//this vector will store indices of all possible answers, thus is the first solution vector
vector< vector<int> > solList;

//prints the solutions
void display(vector< vector<int> > &v) {
  int sum = 0;
  int num = v.size();
  for (int i = 0; i < num; ++i) {
    for (int j = 0; j < v[i].size(); ++j) {
      printf("%s, ", foodList[v[i][j]].retName().c_str());
      sum += foodList[v[i][j]].retCal();
    }
    cout << sum;
    sum = 0;
    printf("\n");
  }
}

 
// Prints all subsets by traversing the 2-D array dp
void printSubsetsRec(int arr[], int i, int sum, vector<int>& p)
{
    // If we reached end and sum is non-zero. We print
    // p[] only if arr[0] is equal to sum OR dp[0][sum]
    // is true.
    if (i == 1 && sum != 0 && ansArr[1][sum])
    {
        p.push_back(i-1);
        solList.push_back(p);
        return;
    }
 
    // If sum becomes 0
    if (i == 1 && sum == 0)
    {
        solList.push_back(p);
        return;
    }
 
    // If given sum can be achieved after ignoring
    // current element.
    if (ansArr[i-1][sum])
    {
        // Create a new vector to store path
        vector<int> b = p;
        printSubsetsRec(arr, i-1, sum, b);
    }
 
    // If given sum can be achieved after considering
    // current element.
    if (sum >= arr[i] && ansArr[i-1][sum-arr[i]])
    {
        p.push_back(i);
        printSubsetsRec(arr, i-1, sum-arr[i], p);
    }
}
 
//assigns the bool values to ansArr
void printAllSubsets(int arr[], int n, int sum)
{
    if (n == 0 || sum < 0)
       return;
 
    // Declaring the num of rows in the matrix
    ansArr = new bool*[n+1];

    for (int i = 0; i <= n; ++i) {
      //declare the num of colums per row in the matrix
      ansArr[i] = new bool[sum+1];

      //You can create a sum of 0 from the empty subset
      ansArr[i][0] = true;
    }

    //if the subset is 0 and the sum is greater than 0, then false
    for (int i = 1; i <= sum; ++i) {
      ansArr[0][i] = false;
    }

    //fills in the rest of the cells for ansArr
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= sum; ++j) {
	ansArr[i][j] = ansArr[i-1][j];
	if (ansArr[i][j] == false && j >= arr[i-1]) {
	  ansArr[i][j] = ansArr[i][j] || ansArr[i-1][j-arr[i-1]];
	}
      }
    }

    //if the bottom right most cell is not 1, there are no subsets for the given sum
    if (ansArr[n][sum] == false) {
        printf("There are no subsets with sum %d. \n", sum);
        return;
    }
 
    // traverses ansArr to find all solutions
    vector<int> p;
    printSubsetsRec(arr, n, sum, p);
}


//this vector will store all the subsets with optimal prot, carbs and fat balance
vector< vector<int> > optimalAns;

void optimalMeals(vector< vector<int> > &v, int cal, int op, int bodFat, int gen, int weight) {
  float opProt, opCarbs, opFat;
  
  //optimal for weight loss and maintenece
  if (op == 1 || op == 3) {
    opProt = weight; // obese or overweight for protein
    opFat = 0.2 * weight;
    //normal body fat range for protein
    if ( (gen == 1 && bodFat <= 20) || (gen == 2 && bodFat <= 30) )
      opProt = 1.2 * weight;
    opCarbs = (cal - (opProt * 4) - (opFat * 9))/4.0;
  }

  //optimal for muscle gain
  else {
    opProt = weight;
    opFat = 0.3 * weight;
    opCarbs = (cal - (opProt * 4) - (opFat * 9))/4.0;
  }

  float minProt, maxProt, minCarbs, maxCarbs, minFat, maxFat;
  minProt = 0.9*opProt;
  maxProt = 1.1*opProt;
  minCarbs = 0.9*opCarbs;
  maxCarbs = 1.1*opCarbs;
  minFat = 0.9*opFat;
  maxFat = 1.1*opFat;

  //goes through and finds the optimal combinations
  int num = v.size();
  int prot, carbs, fat;
  for (int i = 0; i < num; ++i) {
    prot = 0; carbs = 0; fat = 0;
    //add up the macro value for each subset
    for (int j = 0; j < v[i].size(); ++j) {
      prot += foodList[v[i][j]].retProt();
      carbs += foodList[v[i][j]].retCarbs();
      fat += foodList[v[i][j]].retFat();
    }
    //compare macro value to optimum and add to optimum list only if it matches
    if ( (prot >= minProt && prot <= maxProt) && (carbs >= minCarbs && carbs <= maxCarbs) && (fat >= minFat && fat <= maxFat) )
      optimalAns.push_back(v[i]);
  }

  if (optimalAns.size() == 0) {
    cout << "None of the subsets are optimal in terms of macroneutrient balance.";
  }
  cout << endl;
  
  else
    display(optimalAns);
}

//calculates the calories you should eat, 
int calcCal(int w, int f, int a, int b) {
  double lean = (1 - f/100.0) * w;
  double BMR = 370 + (21.6 * (lean / 2.2));

  int cal = round(BMR);
  cout << endl;
  printf("Your daily caloric expenditure is %d. \n", cal);
  
  switch(a) {
    case 1:
      BMR = BMR;
      break;
    case 2:
      BMR = BMR * 1.2;
      break;
    case 3:
      BMR = BMR * 1.35;
      break;
    case 4:
      BMR = BMR * 1.5;
      break;
  }

  cal = round(BMR);
  printf("Given your exercise level, your caloric needs are %d. \n", cal);

  switch(b) {
    case 1:
      BMR = BMR * .8;
      break;
    case 2:
      BMR = BMR * 1.1;
      break;
    case 3:
      BMR = BMR;
      break;
  }

  cal = round(BMR);
  cal = ((cal + 50) / 100) * 100;
  printf("Given your goal, this is the amount of calories you should eat daily: %d. \n", cal);

  int ans = -10;
  while (ans < 1) {
    cout << "Please choose one of the options:" << endl;
    printf(" [1] if you want %d to be your caloric value or \n [any integer value] that you want as your caloric value, value will be rounded to the nearest 100 \n", cal);
    cin >> ans;
  }
  
  if (ans != 1)
    cal = ((ans + 50) / 100) * 100;
  
  return cal;
}

vector<int> basicCalculations() {
  vector<int> values;
  int gen = 10;
  while (gen < 1 || gen > 2) {
    cout << "Please choose one of the options:" << endl;
    cout << " [1] for male \n [2] for female" << endl;
    cin >> gen;
  }
  
  int ans = 10;
  while (ans < 1 || ans > 3) {
    cout << "Please choose one of the options:" << endl;
    cout << " [1] for weight loss \n [2] for muscle gain \n [3] for maintenence" << endl;
    cin >> ans;
  }

  int weight, bodyFat;
  cout << "What is your weight in pounds?" << endl;
  cin >> weight;
  cout << "What is your body fat in %?" << endl;
  cin >> bodyFat;
  
  
  int typ = 10;
  while (typ < 1 || typ > 4) {
    cout << "Please choose one of the options:" << endl;
    cout << " [1] if you do not exercise \n [2] if you exercise 1 to 3 hours a week \n [3] if you exercise 4 to 6 hours a week \n [4] if you exercise vigorously for 6 or more hours a week" << endl;
    cin >> typ;
  }
  values.push_back(calcCal(weight, bodyFat, typ, ans));
  values.push_back(ans);
  values.push_back(bodyFat);
  values.push_back(gen);
  values.push_back(weight);
  return values;
}

//main function
int main() {
  //puts items into the vector foodList
  bool val = readInFile("food.txt");
  //sorting the list, this step is not necessary for the algorithm to work
  foodList = mergeSort(foodList);

  vector<int> userInList = basicCalculations();
  
  int n = foodList.size();    
  int arr[n];        // array of ints for caloric values of each item in foodList
  for (int i = 0; i < n; ++i) {
    arr[i] = foodList[i].retCal();
  }

  //calling the algorithm on arr
  printAllSubsets(arr, n, userInList[0]);
  optimalMeals(solList, userInList[0], userInList[1], userInList[2], userInList[3], userInList[4]);
  
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
