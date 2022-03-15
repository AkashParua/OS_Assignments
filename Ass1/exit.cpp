#include <iostream>
#include <unistd.h>
using namespace std;
void pattern()
{
    for(int i = 0;i<10;i++){
    for(int j = 0;j<=i;j++){
    cout<<"*";}
    cout<<'\n';}
}
int main()
{
    atexit(pattern);
    cout<<"Hellow World"<<endl;
    exit(0);
}
