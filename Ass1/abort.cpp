#include <iostream>
#include <unistd.h>
using namespace std;
int main()
{
    for(int i = 0 ;i<10;i++)
    {
        cout<<"hellow world !"<<endl;
        if(i==5)
        abort();
    }
}