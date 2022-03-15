#include <iostream>
#include <unistd.h>
using namespace std;
int main()
{
    int pid = getpid();
    cout<<"The process id of this process is:"<<pid<<endl;
    char *arg[] = {"fibonacci",NULL};
    execv("./fibonacci",arg);
    cout<<"back to exec";
}