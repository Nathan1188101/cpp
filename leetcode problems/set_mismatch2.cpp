#include<iostream> 
#include<vector> 
#include<unordered_map> 
#include<cmath> 

using namespace std; 

vector<int> findErrorNums(vector<int>& nums){

    unordered_map<int, int> hashmap;
    vector<int> result (2);
    int current_num = 0; 
    bool flag = false; 
    int sum = 0; 
    int err_sum = 0; 

    for(int i = 0; i < nums.size(); i++)
    {
        current_num = nums[i];                       
        if(hashmap.find(current_num) == hashmap.end()) //.end() means cannot be found  
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

    if(nums.size() > 2){
        // real sum
        for(int i = 1; i <= nums.size(); i++)
        {
            sum += i; 
        }

        // sum error-ed array 
        for(int i = 0; i < nums.size(); i++)
        {
            err_sum += nums[i]; 
        }

        // calculate missing value 
        int delta_dupe = err_sum - result[0]; // now we have removed the dupe value from the error-ed sum, and can find the detla between the actual sum and the sum missing a value
        int delta = abs(sum - delta_dupe); // take absolute to ensure not negative 
        result[1] = delta; 

    }else{
        if(result[0] == 1)
        {
            result[1] = result[0] + 1;
        }else{
            result[1] = result[0] - 1; 
        }
        
    }

    return result; 

}

int main(){

    vector<int> nums = {4,5,6,7,4,9}; 
    vector<int> result = findErrorNums(nums); 
    cout << "result: "; 
    for(int i = 0; i < result.size(); i++)
    {
        cout << result[i] << ",";  
    }
    cout << endl; 

}