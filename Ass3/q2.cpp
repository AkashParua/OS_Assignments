
 #include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::chrono;
using namespace std;
long int osum=0;
long int esum=0;
void sum(int a,int b, int k)
{
    if(a%2==k)
    a++;
    long int s = 0;
    for(int i=a;i<=b;i+=2)
        s+=(long int)i;
    if(k==1)
    esum = s;
    else
    osum = s;
    
}
int main()
{
    cout<<"enter the range of numbers :";
    int a,b;
    cin>>a>>b;
    auto start = high_resolution_clock::now();
    thread t1(sum,a,b,1);//thread 1 calculates the odd numbers inbetween
    thread t2(sum,a,b,0);//thread 2 calculates the even numbers inbetween
    auto end   = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    t1.join();
    t2.join();
    cout<<"even sum:"<<esum<<endl<<"odd sum "<<osum<<endl;
    cout<<"Diffrence :"<<osum - esum;
    cout<<" time taken in microseconds:"<<duration.count();
    return 0;
}
