#include<cmath>
#include<fstream>
#include<iostream>
#include<vector>
#include <Eigen/Dense>
#define FEATURE 123
typedef Eigen::Matrix< float , FEATURE, 1> Vector_type;
typedef Eigen::Matrix< float , FEATURE, 1> Weight_type;
using namespace std;
class SVM_SMO
{
public:
    SVM_SMO(vector< vector<int>> &x, vector<int> &y,size_t  sn)
    :yv(y),m(sn),G_vector(sn,0),E_vector(sn,0),alpha(sn,0),b(0)
    {
        w_vector = Eigen::MatrixXf::Constant(FEATURE,1,0);
        for(auto v : x)
        {
            Vector_type one = Eigen::MatrixXf::Constant(FEATURE,1,0);
            for(auto e: v)
            one[e]=1;            
            instances.push_back(one);
        }
        for(size_t i = 0; i < m;i++)
        {
            updaetGi(i);
            updaetEi(i);
        }
    }    

    void SMO();

private:    
    void updaetGi(size_t i);
    void updaetEi(size_t i);
    vector<double> G_vector,E_vector,alpha;
    Vector_type w_vector;
    float b;
    vector<Vector_type> instances;
    vector<int> yv;    
    int m;
};
void SVM_SMO::updaetGi(size_t i)
{
    float sum=0;
    for(size_t j = 0; j < m;j++)
    {
        sum += (alpha[j]*yv[j]*instances[j].dot(instances[i]));
    }
    G_vector[i] = sum;
}
void SVM_SMO::updaetEi(size_t i)
{
    E_vector[i] = G_vector[i]+b-yv[i];
}


void SVM_SMO::SMO()
{
    size_t passes = 0;
    while(passes < 100)
    {
        for(size_t i = 0; i < m; i++)
        {
            
        }
    }
}