#include <iostream>
#include <unistd.h>
using namespace std;
void print_fibonacci(int a,int b,int k,int i)
{
    if(i==k)
    return;
    int c = a + b;
    a = b ;
    b = c;
    cout<<c<<",";
    print_fibonacci(a,b,k,i+1);     
}
int main()
{
    fork();
    int pid = getpid();
    cout<<"This is process id:"<<pid<<endl;
    cout<<"Printing first 25 fibonacci numbers"<<endl;
    print_fibonacci(0,1,25,0);
    cout<<endl;
}
