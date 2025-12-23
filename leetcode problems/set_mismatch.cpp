#include<iostream>
#include<vector> 
#include<algorithm> // for min and max 

using namespace std; 

/*
Q1. Set Mismatch
You have a set of integers s, which originally contains all the numbers from 1 to n. Unfortunately, due to some error,
one of the numbers in s got duplicated to another number in the set, which results in repetition of one number and 
loss of another number.

You are given an integer array nums representing the data status of this set after the error.

Find the number that occurs twice and the number that is missing and return them in the form of an array.


Example 1:

Input: nums = [1,2,2,4]
Output: [2,3]

Example 2:

Input: nums = [1,1]
Output: [1,2]
 

Constraints:

2 <= nums.length <= 104
1 <= nums[i] <= 104
*/

// I know my solution is pretty slow (O(n^2)), 

vector<int> findErrorNums(vector<int>& nums){

    // result needs to be returned in an array of size 2 where (dupe, missing)
    vector<int> result(2);

    int pointer = 0; 
    int current = 0; 
    bool flag = false; 
    int sum = 0; 
    int err_sum = 0;

    for(int i = 0; i < nums.size(); i++)
    {
        pointer = i; // to scan through, starting point is always current iteration of for loop
        current = nums[i]; // holder for dupe search
        
        // while the pointer is within the bounds of the array 
        while(pointer < nums.size())
        {
            pointer++; // increment 
            if(pointer > nums.size() - 1) // if going out of bounds, stop. 
            {
             break; 
            }
        
            // dupe check
            if(nums[pointer] == current)
            {
                flag = true; 
                cout << "dupe found: " << current << endl; 
                result[0] = current; // put the dupe at 0 index 
                break;
            }
        }
        if(flag == 1)
            break; 

    }

    if(nums.size() > 2){
        // need to sum what real sum of array should be 
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
        int delta = sum - delta_dupe; 
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
    auto min_array = min_element(nums.begin(), nums.end()); 
    auto max_array = max_element(nums.begin(), nums.end()); 

    // NOTE: 
    /*
    NOTE: 
        min and max_element() return iterators (a pointer to the location), so we need to dereference it (means accessing the actual value it points too (opposite of this is using & to get the address)). 
        reference: a pointer/iterator that refers points (refers) to a memory location 
        de- = prefix for remove or reverse 
        dereferncing = removing the reference layer to access what it points to 
        that's why it's called that^

        example of dereferencing below: 
    */  
    // cout << "min: " << *min_array << endl; 
    // cout << "max: " << *max_array << endl; 

    vector<int> result = findErrorNums(nums); 
    cout << "result: "; 
    for(int i = 0; i < result.size(); i++)
    {
        cout << result[i] << ",";  
    }
    cout << endl; 


}