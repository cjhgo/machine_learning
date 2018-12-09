#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
using namespace std;

void read_data(string fname, vector< vector<int> > &vv)
{
    ifstream myfile;
    myfile.open(fname);
    string line;
    int number;
    char comma;
    stringstream iss;
    vector<int> v_line;
    while(getline(myfile, line))
    {
        if( line.find("?") != string::npos)
        continue;        
        iss<<line;
        iss>>number;
        while(!iss.eof())
        {
            iss>>comma>>number;
            v_line.push_back(number);
        }
        vv.push_back(v_line);
        v_line.clear();
        iss.clear();
    }
}