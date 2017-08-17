//created by Subhan Poudel, header file for object food

#ifndef FOOD_H
#define FOOD_H

#include <iostream>
#include <string>


using namespace std;

class Food {
public:
    Food();                 // Default Constructor
    Food(string a, int b, int c, int d, int e, int f, int g, int h);
    ~Food();                //Destructor
    string retName();
    int retType();
    int retPage();
    int retCal();
    int retProt();
    int retCarbs();
    int retFat();
    int retTime();
private:
    //attributes of each food
    string name;
    int type;
    int page;
    int cal;
    int prot;
    int carbs;
    int fat;
    int time;
};

#endif
