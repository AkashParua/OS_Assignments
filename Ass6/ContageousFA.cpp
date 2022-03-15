#include <iostream>
#include <ctime>
#include <chrono>
#include <vector>
#include <string>
using namespace std;
struct fileparts{    //Structure stores information regrading each blcock of files
    int block_no = -1;
};
struct file_info{    //Structure stores information regrading each file
    string name;
    int size;
    int start_index; //stores start and end index of the file
    int end_index;
};
fileparts memory[1024]; //Memory array to store the fileparts
vector <file_info> file_list;//vector to store list of files
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
int main()
{
    char c = 'y';
    while(true)
    {
        cout<<"Enter the name of the file and its size: ";
        string name;
        int size;
        cin>>name;cin>>size;
        c_fa(name,size);
        cout<<"Do you want to continue?(y/n):";
        cin>>c;
        if(c == 'n')
            break;
    }
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