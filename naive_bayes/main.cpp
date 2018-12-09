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
typedef  tuple<int,int,int> key_type;
typedef  tuple<int,int> key2_type;
typedef map<key_type, double> ptable_type;

int main(int argc, char const *argv[])
{   
    string fname="./uci/breast-cancer-wisconsin/breast-cancer-wisconsin.data";
    vector< vector<int> > v5;
    read_data(fname, v5);
    int len = v5.size()*0.8;
    vector< vector<int> > v4(v5.begin(), v5.begin()+len),
    v1(v5.begin()+len, v5.end());
    printf("%d\t%d\t%d\n", v5.size(), v4.size(), v1.size());
    ptable_type ptable;
    map<key2_type,int> YxTable;
    map<int, double> ytable;
    for(auto v: v4)
    {
        int y = v[9];
        ytable[y]++;
        for(size_t i = 0; i < 9;i++)
        {
            ptable[make_tuple(y,i,v[i]) ]++;
        }
    }
    for(auto& e : ptable)
    {
        int y=std::get<0>(e.first);
        int x=std::get<1>(e.first);
        cout<<y<<"\t"<<x<<"\t"<<std::get<2>(e.first)<<"\t"<<e.second<<endl;
        YxTable[ make_tuple(y,x) ] += e.second;
    }
    cout<<"--------------\n";
    for(auto& e : ptable)
    {
        int y=std::get<0>(e.first);
        int x=std::get<1>(e.first);
        e.second /= YxTable[ make_tuple(y,x) ];
        cout<<y<<"\t"<<x<<"\t"<<std::get<2>(e.first)<<"\t"<<e.second<<"\t"<<endl;
    }
    for(auto& e:ytable)
    {
        e.second /= v4.size();
        cout<<e.first<<"\t"<<e.second<<endl;
    }
    size_t err_cnt=0;
    for(auto& e:v1 )
    {
        double y2 = ytable[2], y4 = ytable[4];
        for(size_t i = 0; i <9;i++)
        {
            y2 *= ptable[make_tuple(2,i,e[i])];
            y4 *= ptable[make_tuple(4,i,e[i])];        
        }
        int type;
        if( y2 > y4) type = 2;
        else type =4;
        if(type != e[9])err_cnt++;
        printf("%.20f\t %.20f\t%d\t%d\n",y2,y4,type, e[9]);
    }
    cout<<"the error rate of classify is "<<(float)err_cnt/v1.size()<<endl;
    return 0;
}