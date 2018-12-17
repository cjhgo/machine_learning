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
    vector<int> yv, yv_test;
    vector< vector<int> > instances, instances_test;
    read_data(fname, yv, instances);
    read_data("./uci/adult/adult.test", yv_test, instances_test);
    assert(yv.size() == instances.size());
    Gradient_descent gd(instances, yv);
    if( not gd.load())
    {
        gd.update_grad();
    }
    //gd.show_data();
    gd.show_model();
    gd.save();
    gd.validate(instances_test, yv_test);
    return 0;
}