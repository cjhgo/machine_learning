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

        cout<<line<<endl;
        if( line.find("?") != string::npos)
        continue;        
        iss<<line;
        iss>>number;
        yv.push_back(number);
        while(iss>>index>>colon>>feature)
        {
            v_line.push_back(index);
            cout<<index<<colon<<feature<<" ";
        }
        cout<<endl;
        vv.push_back(v_line);   
        v_line.clear();
        // iss<<line;
        // cout<<iss.str()<<endl;
        // iss>>number;
        // // cout<<number<<"\t"<<space<<endl<<iss.str()<<endl;
        // yv.push_back(number);
        
        // while(!iss.eof())
        // {
        //     iss>>index>>colon>>feature;
        //     cout<<index<<"#"<<iss.tellp()<<" ";
        //     v_line.push_back(index);
        // }
        // vv.push_back(v_line);
        // v_line.clear();
        iss.str("");
        iss.clear();        
        // cout<<endl<<endl;
    }
    cout<<endl;
    for(auto e:yv)cout<<e<<" ";
    cout<<endl;
    for(auto v:vv)
    {
        for(auto e:v)cout<<e<<" ";
        cout<<endl;
    }
    
}

/**
 * eof 不好使
 * clear 不好使
 * flush 不好使
 * */