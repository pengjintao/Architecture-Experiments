#include <iostream>
#include <random>
#include<stdlib.h>
#include<chrono>  
struct timespec ts,te;
using namespace std;

#define likely(x) __builtin_expect(!!(x), 1) //gcc内置函数, 帮助编译器分支优化
#define unlikely(x) __builtin_expect(!!(x), 0)

int main(int argc, char* argv[]){
  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution(0.0,1.0);
    double Hitprobability = 0.0;
    int partitionN = 300;
double x = 0.2;

for (int step = 0;step<partitionN;step++)
{
    clock_gettime(CLOCK_REALTIME, &ts);
    for(int i = 0;i<100000;i++)
    {
        
        double number = distribution(generator);
        if( likely(number < step*(1.0/partitionN)))
        {
            x = x*x;
        }else if(unlikely(number >= step*(1.0/partitionN)))
        {
            x = x*x;
        }
    }
    clock_gettime(CLOCK_REALTIME, &te);
cout << (te.tv_sec - ts.tv_sec)*1000000 + (te.tv_nsec - ts.tv_nsec)/1000<< endl;
 //   cout<<step*(1.0/partitionN)<<endl;
}
    return 0;
}
/*
实验证明在代码中设置静态分支预测是无用的，
有规律的分支预测在CPU中已经做的很好。
*/