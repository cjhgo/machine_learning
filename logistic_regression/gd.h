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
    Gradient_descent(vector< vector<int>> &x, vector<int> &y)
    :yv(y), alpha(0.03)
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
    double calc_loss();
    void show_model();
    void show_data();
    void update_grad();
    void validate(vector< vector<int>> &x, vector<int> &y);
    void save(string model_path="logistic.model");
    void load(string mode_path="logistic.model");
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
    double sum = -1*y*std::log(pred)-(1-y)*std::log(1-pred);
    return sum;
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
        sum += (logistic(instances[i])-yv[i])*(instances[i][j]);
    }
    return sum/m;
}
void Gradient_descent::update_grad()
{
    size_t iter_count =0;
    while(iter_count <= 100)
    {
        Vector_type temp;
        for(size_t j = 0; j < 123;j++)
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
    size_t cnt=y.size(), err_cnt;
    assert(cnt==x.size());
    cnt = 20;
    for(size_t i = 0; i < cnt; i++)
    {        
        Vector_type one = Eigen::MatrixXf::Constant(123,1,0);
        for(auto e: x[i])one[e]=1;
        double predit = logistic(instances[i]);
        cout<<predit<<" "<<y[i]<<endl;
    }
}
void Gradient_descent::save(string model_path="logistic.model")
{

}
void Gradient_descent::load(string model_path="logistic.model")
{

}

void Gradient_descent::sgd()
{
}