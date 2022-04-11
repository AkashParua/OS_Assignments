#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int done = 0;         //keeps record of the number of processes that are completed
struct process{
    int id;
    int arrival_time;
    int pre_burst_time;
    int io_waiting_time;
    int post_burst_time;
    int total_burst_time;   //pre + post 
    int time_of_completion = 0;  //arrival_time +turn_around_time
    int turn_around_time = 0;   
    int remaining_time;
    int waiting_time = 0;
    vector <int> progress_map; //-1:not strted ,1: pre I/O process, 2: Waiting for I/O, 3: post I/O process
    int index = 0;  //eg. for 3 ,(3,1,2) --> -1,-1,-1,1,2,3,3
    };
bool comperator(process *a, process *b){  //comperator to comapare the respected brust time , used for sorting 
    int x = a->pre_burst_time;
    int y = b->pre_burst_time;
    if(x == 0)
    x = a->post_burst_time;
    if(y == 0)
    y = b->post_burst_time;
    return x <= y;
}
void update_state(process* p,int state)       //updates state, state = 1 then running , state = -1 then pause
{
      if(state == 1 && p->progress_map.at(p->index) == 1)
      {
      p->index ++;
      p->remaining_time -- ;
      p->pre_burst_time --;
      }
      else if(state == 1 && p->progress_map.at(p->index) == 2)
      {
        p->index ++;
        p->remaining_time -- ;
      }
      else if(state == 1 && p->progress_map.at(p->index) == 3)
      {
        p->index ++;
        p->remaining_time -- ;
        p->post_burst_time --;
      }else if(state == 1 && p->progress_map.at(p->index) == -1)
      {
        p->index ++;
        p->remaining_time -- ;
      }else{
          p->waiting_time ++;
      }
      p ->total_burst_time = p->pre_burst_time + p->post_burst_time;
      p->time_of_completion ++;
      if(p->remaining_time == 0){
          done ++;
        }
}
int main()
{
    cout<<"Number of processes :";
    int n; cin >>n;
    vector<process> processes(n);
    cout<<"Enter required details with space in between"<<endl;
    for(int i =0 ;i<n ;i++)
    {   
        cout<<"Process "<<i+1<<"->Arrival time, burst time before IO, IO waiting time, burst time after IO:"<<endl;
        processes.at(i).id = i + 1;
        cin>>processes.at(i).arrival_time;
        cin>>processes.at(i).pre_burst_time;
        cin>>processes.at(i).io_waiting_time;
        cin>>processes.at(i).post_burst_time;
        processes.at(i).total_burst_time = processes.at(i).pre_burst_time + processes.at(i).post_burst_time;
        processes.at(i).remaining_time = processes.at(i).total_burst_time + processes.at(i).io_waiting_time + processes.at(i).arrival_time;
    }
    for(int i = 0 ;i < n;i++)
    {
         for(int j = 0 ;j < processes.at(i).arrival_time ;j++)
        {
            processes.at(i).progress_map.push_back(-1);
        }
        for(int j = 0 ;j < processes.at(i).pre_burst_time;j++)
        {
            processes.at(i).progress_map.push_back(1);
        }
        for(int j = 0 ;j < processes.at(i).io_waiting_time;j++)
        {
            processes.at(i).progress_map.push_back(2);
        }
        for(int j = 0 ;j < processes.at(i).post_burst_time;j++)
        {
            processes.at(i).progress_map.push_back(3);
        }   
    }
    int clock = 0;
    while(clock <1000)
    {
        if(done == n)
        break;
        cout<<"clock:"<<clock<<"-"<<clock + 1<<endl;
        cout<<"--------------------------------------------------------------------------------"<<endl;
        vector <process *> temp;
        for(int i = 0 ;i<n ;i++)
        {
            int k = processes.at(i).index;
            if(processes.at(i).remaining_time == 0 )
            continue;        
            if(processes.at(i).progress_map[k] == -1)  //process not arrived yet
            {  
               cout<<processes.at(i).id<<" not arrived yet"<<endl;
               update_state(&processes.at(i),1);
            }else if(processes.at(i).progress_map[k] == 1 || processes.at(i).progress_map[k] == 3)
            {
                temp.push_back(&processes.at(i));           
            }else if(processes.at(i).progress_map[k] == 2) //processes waiting
            {
                cout<<processes.at(i).id<<" is waiting for I/O"<<endl;
                update_state(&processes.at(i),1);
            }
        }
        sort(temp.begin(),temp.end(),comperator); //the smallest remaining time is at the top
        if(temp.size()!= 0){
        update_state(temp.at(0),1);
        cout<<temp.at(0)->id<<" is running"<<endl;
        }
        for(int i = 1 ;i<temp.size();i++) //rest remain paused (-1 is paused)
        {
            cout<<temp.at(i)->id<<" Waiting"<<endl;
            update_state(temp.at(i),-1);
        }
        clock ++;
        cout<<"--------------------------------------------------------------------------------"<<endl;
    }
    for(int i =0 ;i< n;i++)
    {
        cout<<"Process "<<processes.at(i).id<<" Arrial Time:"<<processes.at(i).arrival_time;
        cout<<" Turn around time:"<<(processes.at(i).time_of_completion - processes.at(i).arrival_time);
        cout<<" Completion Time: "<<processes.at(i).time_of_completion;
        cout<<" Waiting time:"<<processes.at(i).waiting_time + processes.at(i).io_waiting_time<<endl;
    }
}
