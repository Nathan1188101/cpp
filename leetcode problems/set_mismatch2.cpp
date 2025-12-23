#include<iostream> 
#include<vector> 
#include<unordered_map> 

using namespace std; 

vector<int> findErrorNums(vector<int>& nums){

    unordered_map<int, int> hashmap;
    vector<int> result;
    int current_num = 0; 
    bool flag = false; 

    for(int i = 0; i < nums.size(); i++)
    {
        current_num = nums[i]; 
        if(hashmap.find(current_num) != hashmap.end()) // find will return end iterator if whatever is being searched for cannot be found. 
        {
            // add to hashmap 
            hashmap[current_num] = i; // <current_num, index> 

        }else{
            // dupe found 
            result[0] = current_num;
            flag = true; 
            break; 
        }
        if(flag == true)
            break; 
    }

    return result; 

}

int main(){

}