#include<cmath>
#include<tuple>
#include<map>
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
using namespace std;
#include"read_file.h"
#include"gd.h"
int main(int argc, char const *argv[])
{   
    string fname="./uci/adult/adult.1.train";
    vector<int> yv;
    vector< vector<int> > instances;
    read_data(fname, yv, instances);
    Gradient_descent gd(instances, yv);
    gd.show_data();
    return 0;
}