#include <iostream>
#include <unistd.h>
#include <signal.h>
using namespace std;
int main()
{
    int x = fork();//fork return 0 to child process and process if of child process to the parent
    if (x == 0 )  //that is the process is child process 
    {
        int pid = getpid(); //stroing the parent id of child process 
        int ppid = getppid();  //storing process id of parent process
        cout<<"Parent process id is :"<<ppid<<endl;
        cout<<"Child (Current) process id is"<<pid<<endl;
        for(int i = 0;i<1000;i++)    //printing Hellow World a 100 times with pause 
        {
            cout<<"line "<<i<<"Hellow World"<<endl;
            sleep(1) ; //printing each line with a delay of 1 sec.
           
        }
    }
    else //if the process is parent process i.e x = id of child process
   {    sleep(10);   //sleeping for 10 seconds before termination of child process  
        kill(x,SIGKILL); //killing the child signal by sending its process id
        cout<<"Child process terminated after 10 sec"<<endl;
        cout<<"Value of x from x= fork(),i.e pid of child process"<<x<<endl;
        int p = getpid();
        cout<<"Value of current (Parent) proces:"<<p<<endl;
        exit(0);
    }   
}