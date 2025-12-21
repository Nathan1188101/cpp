#include<iostream>
#include<vector> 

using namespace std; 

/*
Q3. Max Consecutive Ones
Given a binary array nums, return the maximum number of consecutive 1's in the array.

Example 1:

Input: nums = [1,1,0,1,1,1]
Output: 3
Explanation: The first two digits or the last three digits are consecutive 1s. The maximum number of consecutive 1s is 3.
Example 2:

Input: nums = [1,0,1,1,0,1]
Output: 2
 
Constraints:

1 <= nums.length <= 105
nums[i] is either 0 or 1.
*/

int findMaxConsecutiveOnes(vector<int>& nums) {

    // use a temp val and a counter? 
    // compare temp val to next val?
    // increment counter when hitting ones, but set to 0 when encountering a 0 
    int counter = 0;
    int R = 0; 
    int final_count = 0; 

    // iterate through the binary array 
    for(int i = 0; i < nums.size(); i++)
    {

        // this implementation at the moment has a flaw.
        // it is doing redundant checks. 
        // if we find consecutive 1's, and then exit while loop, then iterate one from for loop, we just redundantly check ones we've already gone over 
        // need to skip to the last 1 before encountering a 0 
        // this redundancy makes our time complexity O(n^2) because worst case is we visit every index more than once, the last index will get visited the most because every iteration up to and including it will scan it. Waste of time. 

        // ADDED THIS TO FIX THE ABOVE DESCRIBED REDUNDANCY 
        if(counter > 0){
            i  = R;
        }

        R = i; 
        counter = 0; 
        while(R < nums.size() && nums[R] == 1)
        {
            // expand forward from current iteration 
            R++; 
            counter++; 
        }

        // update final count if counter is greater after each check 
        if(counter > final_count)
        {
            final_count = counter; 
        }
    }

    return final_count; 
        
}

int main(){

    vector<int> nums = {1,1,0,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1};
    int result = findMaxConsecutiveOnes(nums);

    cout << "nums: "; 
    for(int i = 0; i < nums.size(); i++)
    {
        cout << nums[i]; 
    }
    cout << endl; 

    cout << "longest consecutive 1's: " << result << endl; 


}