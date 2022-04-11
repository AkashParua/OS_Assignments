#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stack>
using namespace std;
//A consumer-producer program that uses Inter Process Communication (IPC) using Shared Stacks.(Shared memory)
//Stack is a shared memory that is shared by both the consumer and producer processes.
//The producer pushes data into the stack and the consumer pops data from the stack.
int main()
{
    int shmid;
    key_t key;
    int *shm;
    
    
    return 0;
}
