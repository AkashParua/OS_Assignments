#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
using namespace std;
int main()
{
   system("echo 'LIST OF INPUT DEVICES --->'");
   system("xinput list");
   system("echo 'LIST OF OUTPUT DEVICES --->'");
   system("lspci");
  
}
