#include<cmath>
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
using namespace std;
#include"gd.h"
#include"read_file.h"
int main(int argc, char const *argv[])
{    
    vector<int> xv;
    vector<double> yv;
    read_data("train.csv", xv,yv);
    Gradient_descent gd(xv, yv);
    gd.update_grad();
    return 0;
}