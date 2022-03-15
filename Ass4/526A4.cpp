#include <iostream>
#include <unistd.h>
#include <time.h>
#include <math.h>
using namespace std;
/*there are five pipes in array fd1 nad five other pipes fd2, each fd1[i] and fd2[i],is a pipe for 0<=i<=4 */
int main()
{
    cout<<"Establishing 2 way communication between parent and child process"<<endl;
    int fd1[5][2];     //fd1[i][1] used to write random numbers in child process and fd1[i][0] used to read random numbers in parent process
    int fd2[5][2];     //fd2[i][1] used to write square of random numbers in parent process and fd2[i][0] used to read square of random numbers in child process
    for(int i =0;i<5;i++)
    {
        pipe(fd1[i]);
        pipe(fd2[i]);
    }
    int id = fork();
    srand(time(NULL));
    if(id == 0)
    {
        //child process use f1[x][0] for writing
        //child process use f2[x][1] for reading
        for(int i =0;i<5;i++)
        {
            //closing the reading end of the pipe f1[i]
            //closing the writing end of the pipe f2[i]
            close(fd1[i][0]);
            close(fd2[i][1]);
            int num = rand()%500+1;
            write(fd1[i][1], &num, sizeof(num));
            int num2;
            read(fd2[i][0], &num2, sizeof(num2));
            cout<<"from PARENT received by CHILD : "<<num2<<"(Squared)"<<endl;
            close(fd1[i][1]);
            close(fd2[i][0]);
        }
        

    }else{
        //parent process use f1[x][1] for reading
        //parent process use f2[x][0] for writing
        for(int i =0;i<5;i++)
        {
            //closing the writing end of the pipe f1[i]
            //closing the reading end of the pipe f2[i]
            close(fd1[i][1]);
            close(fd2[i][0]);
            int num;
            read(fd1[i][0], &num, sizeof(num));
            cout<<"from CHILD received by PARENT : "<<num<<endl;
            int square = num * num;
            write(fd2[i][1], &square, sizeof(square)) ;
            close(fd1[i][0]);
            close(fd2[i][1]);
        }
        
    }

}