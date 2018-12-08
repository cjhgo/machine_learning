#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>


void read_data(string fname, vector<int> &xv, vector<double> &yv)
{
    ifstream myfile;
    myfile.open(fname);
    string line;
    int x;
    double y;
    char dot;
    stringstream iss;
    while(getline(myfile, line))
    {    
        iss<<line;
        iss>>x>>dot>>y;
        xv.push_back(x);
        yv.push_back(y);
        iss.clear();
    }
}