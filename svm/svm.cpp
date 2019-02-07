#include<cmath>
#include<fstream>
#include<iostream>
#include <cstdlib>
#include <algorithm>
#include <ctime>
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
    :yv(y),m(sn),C(1),G_vector(sn,0),E_vector(sn,0),alpha(sn,0),b(0),tolerance(0.03)
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
    void validate(vector< vector<int>> &x, vector<int> &y,size_t sn);
    int SVM_Classify(Vector_type instance);
private:    
    void updaetGi(size_t i);
    void updaetEi(size_t i);
    vector<double> G_vector,E_vector,alpha;
    Vector_type w_vector;
    float b,tolerance;
    vector<Vector_type> instances;
    vector<int> yv;    
    int m,C;
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
        cout<<"round "<<passes<<"begin!\n";
        for(size_t i = 0; i < m; i++)
        {
            if( 
                ( yv[i]*E_vector[i] +tolerance < 0 && alpha[i] < C)   
                || 
                ( yv[i]*E_vector[i] > tolerance  && alpha[i] > 0 )  
            )
            {
                std::srand(std::time(nullptr));
                size_t j = ( i + std::rand()%(m-1)+1) % m;
                double alpha_i = alpha[i], alpha_j = alpha[j], L=0,H=C;
                if( yv[i] == yv[j])
                {
                    if(alpha_j+alpha_i - C > 0)L=alpha_j+alpha_i - C;
                    if(alpha_j+alpha_i < C) H=alpha_j+alpha_i;                    
                }
                else
                {
                    if(alpha_j-alpha_i > 0)L=alpha_j-alpha_i;
                    if(C+alpha_j-alpha_i < C) H=C+alpha_j-alpha_i;
                }
                if( L == H)continue;
                double xii=instances[i].dot(instances[i]), xjj=instances[j].dot(instances[j]), xij=instances[i].dot(instances[j]);
                double n = xii+xjj - 2*xij;
                double alpha_j_new = alpha_j + (1.0*yv[j]*(E_vector[i]-E_vector[j]))/n;
                if(alpha_j_new > H )
                alpha_j_new = H;
                else if( alpha_j_new < L )
                alpha_j_new = L;
                double deltaj=alpha_j_new-alpha_j;
                if( std::abs(deltaj)  < 0.00001)
                continue;
                double alpha_i_new = alpha_i - yv[i]*yv[j]*deltaj;
                alpha[i]=alpha_i_new; 
                alpha[j]=alpha_j_new;
                double deltai=alpha[i]-alpha_i;
                double bi=b-E_vector[i]-yv[i]*deltai*xii-yv[j]*deltaj*xij;
                double bj=b-E_vector[j]-yv[i]*deltai*xij-yv[j]*deltaj*xjj;
                if(alpha_i_new > 0 and alpha_i_new < C)
                b=bi;
                else if(alpha_j_new > 0 and alpha_j_new < C)
                b=bj;
                else
                b=(bi+bj)/2.0;
                for(size_t k = 0; k < m;k++)
                {
                    if(k == i || k == j)updaetGi(k);
                    updaetEi(i);
                }
            }
        }
    }      
    //Vector_type sum=Eigen::MatrixXf::Constant(FEATURE,1,0);
    for(size_t j = 0; j < m;j++)
    {
        //sum += (alpha[j]*yv[j]*instances[j]);
        w_vector+= (alpha[j]*yv[j]*instances[j]);
    }
}

void SVM_SMO::validate(vector< vector<int>> &x, vector<int> &y,size_t sn)
{
    vector<Vector_type> instances;
    for(auto v : x)
    {
        Vector_type one = Eigen::MatrixXf::Constant(FEATURE,1,0);
        for(auto e: v)
        one[e]=1;            
        instances.push_back(one);
    }
    vector<int> classify_res;
    for(auto e : instances)
    {
        classify_res.push_back(SVM_Classify(e));
    }
    size_t cnt=0;
    for(size_t i = 0; i < sn;i++)
    {
        if(classify_res[i] != yv[i])
        cnt++;
    }
    cout<<"validate res ,error rate is :"<<cnt*1.0/sn<<std::endl;
}
int SVM_SMO::SVM_Classify(Vector_type instance)
{
    float res = w_vector.dot(instance)+b;
    if(res > 0)
    return 1;
    else if( res < 0)
    return -1;
}
