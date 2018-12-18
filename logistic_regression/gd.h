#include<cmath>
#include<fstream>
#include<iostream>
#include<vector>
#include <Eigen/Dense>
#define FEATURE 124
typedef Eigen::Matrix< float , FEATURE, 1> Vector_type;
typedef Eigen::Matrix< float , FEATURE, 1> Weight_type;
using namespace std;
class Gradient_descent
{
public:
    Gradient_descent(vector< vector<int>> &x, vector<int> &y, double arg=0.099)
    :yv(y), alpha(arg)
    {
        m = x.size();
        w_vector = Eigen::MatrixXf::Constant(FEATURE,1,0.55);
        for(auto v : x)
        {
            Vector_type one = Eigen::MatrixXf::Constant(FEATURE,1,0);
            for(auto e: v)
            one[e]=1;            
            instances.push_back(one);
        }
    }    
    double calc_loss();
    void show_model();
    void show_data();
    void update_grad();
    void validate(vector< vector<int>> &x, vector<int> &y);
    void save(string model_path="logistic.model");
    bool load(string mode_path="logistic.model");
    void sgd();
private:    
    double alpha;
    double sigmod(double x);
    double logistic(Vector_type v);
    double cost_at_v(Vector_type v, int y);
    double calc_grad(size_t j);
    Vector_type w_vector;
    vector<Vector_type> instances;
    vector<int> yv;    
    int m;
};

double Gradient_descent::sigmod(double x)
{
    return 1.0/(1.0 + exp(-x));
}
double Gradient_descent::logistic(Vector_type v)
{
    return sigmod(v.dot(w_vector));
}

double Gradient_descent::cost_at_v(Vector_type v, int y)
{
    double pred = logistic(v);
    if(y == 1)
    return -1*std::log(pred); 
    else if(y == 0)
    return -1*std::log(1-pred);
}
double Gradient_descent::calc_loss()
{
    double sum = 0;
    for(size_t i = 0; i < m ; i++)
    {
        sum += cost_at_v(instances[i], yv[i]);
    }
    sum /= m;
    cout<<"the current loss is : "<<sum<<endl;
    return sum;
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
        cout<<e.transpose()<<"\t"<< logistic(e)<<"vs"<<yv[i]<<endl;
    }
}

double Gradient_descent::calc_grad(size_t j)
{
    double sum = 0;
    for(size_t i = 0; i < m; i++)
    {
        double pred = logistic(instances[i]);
        sum += (pred - yv[i])*(instances[i][j]);
    }
    return sum/m;
}
void Gradient_descent::update_grad()
{
    size_t iter_count =0;
    while(1 or iter_count <= 100)
    {
        Vector_type temp;
        for(size_t j = 0; j < FEATURE;j++)
        {
            double delta = alpha*calc_grad(j);
            w_vector[j] = w_vector[j] - delta;
            temp[j] = delta;
        }
        cout<<"at iteration "<<iter_count<<endl;
        double loss = calc_loss();
        if( std::abs(loss) < 0.05)
        break;
        show_model();
        cout<<temp.transpose()<<endl<<endl;
        iter_count++;
    }
}
void Gradient_descent::validate(vector< vector<int>> &x, vector<int> &y)
{   
    size_t cnt=y.size(), err_cnt=0;
    assert(cnt==x.size());
    
    double sum = 0;    
    for(size_t i = 0; i < cnt; i++)
    {        
        Vector_type one = Eigen::MatrixXf::Constant(FEATURE,1,0);
        for(auto e: x[i])one[e]=1;
        sum += cost_at_v(one, y[i]);
        int end_pred = logistic(one) > 0.5 ? 1 :0;
        if( end_pred != y[i] ) err_cnt++;
    }
    cout<<"the loss at test set: "<< sum/cnt<<endl<<err_cnt*1.0/cnt;
}
void Gradient_descent::save(string model_path)
{
    ofstream out(model_path);
    out<<w_vector.transpose();
    out.close();
}
bool Gradient_descent::load(string model_path)
{
    ifstream in(model_path);
    if( in.good())
    {
        double number;
        size_t cnt=0;
        while(in>>number)w_vector[cnt++]=number;
        return true;
    }
    else
        return false;        
}
void Gradient_descent::sgd()
{
}