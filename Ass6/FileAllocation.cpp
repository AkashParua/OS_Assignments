//Program to implement the Various File Allocation
#include <iostream>
#include <ctime>
#include <chrono>
#include <vector>
#include <string>
using namespace std;
struct fileparts{    //Structure stores information regrading each blcock of files
    int block_no = -1;
    int next_index = -1;
};
struct file_info{    //Structure stores information regrading each file
    string name;
    int size;
    int start_index;
    int end_index;
    vector <int> block_inex; //vector to store the indexes of each file block
};
vector <file_info> file_list;
fileparts memory[1024]; //Memory array to store the fileparts
int hashing(int size){   //hash function assigns value to each file block depending on current time
    const auto now     = std::chrono::system_clock::now();
    const auto epoch   = now.time_since_epoch();
    const auto seconds = std::chrono::duration_cast<std::chrono::seconds>(epoch);
    int time_of_creation = seconds.count();
    int limit = 1024 - size ;
    int hash_value = time_of_creation % (limit);
    if(memory[hash_value].block_no == -1){
        return hash_value;
    }
    else{      //If the block is already occupied, it is searched for the next available block
        for(int i = hash_value; i < limit; i++){
            if(memory[i].block_no == -1){
                return i;
            }
        }
        for(int i = 0; i < hash_value ; i++){
            if(memory[i].block_no == -1){
                return i;
            }
        }
    }
    return hash_value;
}
void ll_fa(string name,int size)
{
    int index = hashing(size);
    file_info file;
    file.name = name;
    file.size = size;
    file.start_index = index;
    file_list.push_back(file);
    fileparts block;
    memory[index] = block;
    memory[index].block_no = 1;
    for(int i = 1;i < size ;i++)
    { 
        memory[index].next_index = hashing(size-i);
        index = memory[index].next_index;
        memory[index].block_no = i+1;
    }
    
}
void i_fa(string name,int size)
{
   file_info file;
    file.name = name;
    file.size = size;
    for(int i = 0; i < size ;i++)
    { 
        int index = hashing(size-i);  //hashing function is called to assign the index to each file block
        file.block_inex.push_back(index); //index is stored in the vector
        fileparts block;  
        memory[index] = block;  //block is stored in the memory array
        memory[index].block_no = i+1; 
    }
    file_list.push_back(file);
}
void c_fa(string name,int size)
{
    int index = hashing(size);
    file_info file;
    file.name = name;
    file.size = size;
    file.start_index = index;
    file.end_index = index + size - 1;
    file_list.push_back(file);
    for(int i=0;i<size;i++)
    {
        fileparts block;
        block.block_no = i+1;
        memory[index+i] = block;
    }
}
void print_file_part_loactions(fileparts part)
{
      int next_index = part.next_index;
      while(part.next_index != -1)
      {
          cout<<part.next_index<<"---->";
          part = memory[part.next_index];
      }
}
int main()
{   
    char c = 'y';
    int k;
    cout<<"1.Conteguous File Allocation\n 2.Linked File Allocation\n 3.Indexed File Allocation\n";
    cin>>k;
    while (true)
    {
        cout<<"Enter name and size of file:"<<endl;
        string name; cin >> name;
        int size; cin >> size;
        if(k==1)
        c_fa(name,size);
        else if(k==2)
        ll_fa(name,size);
        else if(k==3)
        i_fa(name,size);
        cout<<"Do you want to continue?(y/n)"<<endl;
        cin>>c;
        if(c == 'n'){
            break;
        }
    }
    if(k==2){
    for(int i = 0;i<file_list.size();i++){
        cout<<endl<<"___________________________________________________"<<endl;
        cout<<"File name:"<<file_list[i].name<<endl;
        cout<<"File size:"<<file_list[i].size<<endl;
        cout<<"File start index:"<<file_list[i].start_index<<endl;
        cout<<"-------------------------------------------------------"<<endl;
        cout<<"File block locations:"<<endl;
        cout<<file_list[i].start_index<<"---->";
        print_file_part_loactions(memory[file_list[i].start_index]);
    }
    }
    else if(k==1){
    for(int i=0;i<file_list.size();i++)
    {
        cout<<"_____________________________________________________"<<endl;
        cout<<"File name: "<<file_list[i].name<<endl;
        cout<<"Size: "<<file_list[i].size<<endl;
        cout<<"Start index: "<<file_list[i].start_index<<endl;
        cout<<"End index : "<<file_list[i].end_index<<endl;
        cout<<"File parts and respective memory index: "<<endl;
        for(int j= file_list[i].start_index;j<=file_list[i].end_index;j++)
        {
            cout<<memory[j].block_no<<"|"<<j<<endl;
        }
    }
    }
    else if(k==3){
    for(int i=0;i<file_list.size();i++)
    {
        cout<<"__________________________________________"<<endl;
        cout<<"File name: "<<file_list[i].name<<endl;
        cout<<"File size: "<<file_list[i].size<<endl;
        cout<<"File blocks and respective memory index: \n";
        for(int j=0;j<file_list[i].block_inex.size();j++)
        {
            cout<<memory[file_list[i].block_inex[j]].block_no<<"|"<<file_list[i].block_inex[j]<<endl;  //printing the id of each block and its index
        }
    }
    }
    return 0;
}