//program to simulate a simple CPU page size 4Kb = 4096 bytes
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
struct page{
    int page_no;     //page number
    int frame_no;   //index of the frame the page is associated with
};
struct frame{
   int process = -1;  //stores the id of the process that is using the frame, -1 for not assigned to any process
   int is_free = -1; //is free -1 for empty frame else 0;
};
struct process{
    int id;
    int size;
    vector <page> pages;  //stores the pages of the process   
};
frame memory[56]; //frame of 56 frames
vector <process> processes; //stores the processes
int return_empty_frame(process p){
    for(int i=0;i<56;i++){
        if(memory[i].is_free == -1){
            memory[i].is_free = 0;
            memory[i].process = p.id;
            return i;
        }
    }
    return -1;
}
void free_memory(process p)       //this clears the frame 
{
    for(int i =0;i<p.pages.size();i++){
        memory[p.pages[i].frame_no].is_free = -1;
        memory[p.pages[i].frame_no].process = -1;
    }
}
void print_memory(){
    for(int i=0;i<56;i++){
        if(memory[i].is_free == -1 )
        cout<<" "<<memory[i].process<<"|";
        else
        cout<<"P"<<memory[i].process<<"|";
    }
    cout<<endl;
}
int main()
{
    int ctr=0;
    while(true)
    {
        print_memory();
        cout<<"1.add process \n2.clear process \n3.exit"<<endl;
        int choice;cin>>choice;
        if(choice == 1)
        {
            process p;
            p.id = ctr;
            cout<<"process id :"<<ctr<<endl;
            cout<<"enter the size of the process in Kb:";
            cin >> p.size;
            int n = p.size/4; //number of pages
            int r = p.size%4; //remainder
            if(r>0)
                n++;
            for(int i=0;i<n;i++) //initializing the pages 
            {
                page pg;
                pg.page_no = i+1;
                pg.frame_no = return_empty_frame(p);
                p.pages.push_back(pg);  //adding the page to the process
            }
            processes.push_back(p); //adding the process to the vector
            ctr++;
        }else if(choice == 2)
        {
            cout<<"enter the process id to be cleared:"<<0<<" to "<<ctr-1<<endl;
            int id;
            cin>>id;
            free_memory(processes[id]);
        }else
        break;
    }
}