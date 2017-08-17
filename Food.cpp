//Created by Subhan Poudel

#include <iostream>
#include "Food.h"
using namespace std;

Food::Food() {
  type = 0;
  page = 0;
  name = "";
  cal = 0;
  prot = 0;
  carbs = 0;
  fat = 0;
  time = 0;
}

Food::Food(string a, int b, int c, int d, int e, int f, int g, int h) {
  name = a;
  type = b;
  page = c;
  cal = d;
  prot = e;
  carbs = f;
  fat = g;
  time = h;
}

Food::~Food() {
}

//getters for each private value
string Food::retName() {
  return name;
}

int Food::retType() {
  return type;
}

int Food::retPage() {
  return page;
}

int Food::retCal() {
  return cal;
}

int Food::retProt() {
  return prot;
}

int Food::retCarbs() {
  return carbs;
}

int Food::retFat() {
  return fat;
}

int Food::retTime() {
  return time;
}

//no need for setters
