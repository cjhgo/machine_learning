#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
using namespace std;

void read_data(string fname, vector<int> &yv, vector< vector<int> > &vv)
{
    ifstream myfile;
    myfile.open(fname);
    string line;
    int number,index,feature;
    char space,colon;
    stringstream iss;
    vector<int> v_line;

    while(getline(myfile, line))
    {
        if( line.find("?") != string::npos)
        continue;        
        iss<<line;
        iss>>number;
        if( number == -1) number = 0;
        yv.push_back(number);
        v_line.push_back(0);
        while(iss>>index>>colon>>feature)
        {
            v_line.push_back(index);
        }
        vv.push_back(v_line);   
        v_line.clear();
        iss.str(std::string());
        iss.clear();        
    }
    /*output read result from the line
    for(auto e:yv)cout<<e<<" ";
    cout<<endl;
    for(auto v:vv)
    {
        for(auto e:v)cout<<e<<" ";
        cout<<endl;
    }
    */    
}