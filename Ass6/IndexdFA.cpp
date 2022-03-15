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
    vector <int> block_inex; //vector to store the indexes of each file block
    int size;
    int start_index;
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
int main()
{
    char c = 'y';
    while(c == 'y')
    {
        string name;
        int size;
        cout<<"Enter the name of the file and its size: ";
        cin>>name;cin>>size;
        i_fa(name,size);
        cout<<"Do you want to enter more files? (y/n):";
        cin>>c;
        if(c=='n')
            break;
    }
    for(int i=0;i<file_list.size();i++)
    {
        cout<<"__________________________________________"<<endl;
        cout<<"File name: "<<file_list[i].name<<endl;
        cout<<"File size: "<<file_list[i].size<<endl;
        cout<<"File blocks and respective memory index: ";
        cout<<"----------------------------------------"<<endl;
        for(int j=0;j<file_list[i].block_inex.size();j++)
        {
            cout<<memory[file_list[i].block_inex[j]].block_no<<"|"<<file_list[i].block_inex[j]<<endl;  //printing the id of each block and its index
        }
    }
}