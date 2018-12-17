#include<cmath>
#include<iostream>
#include<vector>
#include <Eigen/Dense>

typedef Eigen::Matrix< float , 123, 1> Vector_type;
typedef Eigen::Matrix< float , 123, 1> Weight_type;
using namespace std;
class Gradient_descent
{
public:
    Gradient_descent(vector< vector<int>> &x, vector<int> &y):yv(y)
    {
        m = x.size();
        w_vector = Eigen::MatrixXf::Constant(123,1,0.6);
        for(auto v : x)
        {
            Vector_type one = Eigen::MatrixXf::Constant(123,1,0);
            for(auto e: v)
            one[e]=1;
            instances.push_back(one);
        }
    }
    double sigmod(double x);
    void show_model();
    void show_data();
    void update_grad();
    void sgd();
private:    
    double calc_loss();
    Vector_type w_vector;
    vector<Vector_type> instances;
    vector<int> yv;    
    int m;
};

double Gradient_descent::sigmod(double x)
{
    return 1.0/(1.0 + exp(-x));
}
void Gradient_descent::show_model()
{
    cout<<"the model of logistic regression is :\n";
    cout<<w_vector.transpose()<<endl<<endl;
}
void Gradient_descent::show_data()
{
    show_model();        
    for(size_t i = 0; i < m;i++)
    {
        auto e = instances[i];
        cout<<e.transpose()<<"\t"<<sigmod(e.dot(w_vector))<<"vs"<<yv[i]<<endl;
    }
}
void Gradient_descent::update_grad()
{
    
}
void Gradient_descent::sgd()
{
}
double Gradient_descent::calc_loss()
{
    return 0;
}