#include<cmath>
#include<iostream>
#include<vector>
using namespace std;
class Gradient_descent
{
public:
    double w,b;
    Gradient_descent(vector<int> &x, vector<double> &y):
    xv(x),yv(y),w(0),b(0),lambda(0.0001)
    {
        m=xv.size();
    }
    double calc_partial_w();
    double calc_partial_b();
    void update_grad();
    void sgd();
private:    
    double calc_loss();
    double lambda;
    int m;
    vector<int> xv;
    vector<double>yv;

};

double Gradient_descent::calc_partial_w()
{
    double sum;
    for(size_t i = 0; i < m; i++)
    {
        sum +=
        (
            xv[i]*(w*xv[i]+b-yv[i])
        );
    }
    return sum/m;
}
double Gradient_descent::calc_partial_b()
{
    double sum;
    for(size_t i = 0; i < m; i++)
    {
        sum +=
        (
            w*xv[i]+b-yv[i]
        );
    }
    return sum/m;
}
void Gradient_descent::update_grad()
{
    size_t i = 0;
    calc_loss();    
    while(true)
    {
        double deltaw = lambda*calc_partial_w();
        double deltab = lambda*calc_partial_b();
        w = w-deltaw;
        b = b-deltab;
        cout<<"iteration "<<i++<<"\t"<<deltaw<<"\t"<<deltab<<endl;
        cout<<"the modle is :w= "<<w<<"\t b="<<b<<endl;
        if( calc_loss() < 0.0001)
            break;        
        cout<<endl<<endl;
    }
    
}
void Gradient_descent::sgd()
{
    size_t iter_cnt=0;
    while(iter_cnt < 100)
    {

        for(size_t j = 0; j < m;j++)
        {
            w=w-lambda*(xv[j]*(w*xv[j]+b)-yv[j])/m;
            b=w-lambda*((w*xv[j]+b)-yv[j])/m;
        }
        cout<<"iteration "<<iter_cnt++<<endl;
        cout<<"the modle is :w= "<<w<<"\t b="<<b<<endl;
        calc_loss();        
    }        
}
double Gradient_descent::calc_loss()
{
    double sum = 0;
    for(size_t i = 0; i < m; i++)
    {
        int xi = xv[i];
        double yi = yv[i];
        double delta = w*xi+b-yi;
        //cout<<w<<"*"<<xi<<"+"<<b<<"-"<<yi<<abs(delta)<<endl;
        sum +=pow(delta, 2);
    }
    sum = sum / (2*m);
    printf("the current value of loss function is %.20f\n",sum);
    return sum;
}