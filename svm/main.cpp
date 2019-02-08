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
#include"svm.cpp"
int main(int argc, char const *argv[])
{   
    string fname="./uci/adult/adult.train";
    vector<int> yv, yv_test;
    vector< vector<int> > instances, instances_test;
    read_data(fname, yv, instances);
    read_data("./uci/adult/adult.test", yv_test, instances_test);
    assert(yv.size() == instances.size());
    SVM_SMO svm(instances, yv, instances.size(),std::atoi(argv[1]));
    svm.SMO();
    svm.validate(instances_test, yv_test, instances_test.size());
    return 0;
}