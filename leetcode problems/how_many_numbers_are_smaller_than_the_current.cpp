#include<iostream> 
#include<vector> 
#include<algorithm> 
#include<unordered_map> 

using namespace std; 

// problem: 
/*
Q2. How Many Numbers Are Smaller Than the Current Number
Easy
Topics
premium lock icon
Companies
Hint
Given the array nums, for each nums[i] find out how many numbers in the array are smaller than it. That is, for each nums[i] you have to count the number of valid j's such that j != i and nums[j] < nums[i].

Return the answer in an array.

 

Example 1:

Input: nums = [8,1,2,2,3]
Output: [4,0,1,1,3]
Explanation: 
For nums[0]=8 there exist four smaller numbers than it (1, 2, 2 and 3). 
For nums[1]=1 does not exist any smaller number than it.
For nums[2]=2 there exist one smaller number than it (1). 
For nums[3]=2 there exist one smaller number than it (1). 
For nums[4]=3 there exist three smaller numbers than it (1, 2 and 2).
Example 2:

Input: nums = [6,5,4,8]
Output: [2,1,0,3]
Example 3:

Input: nums = [7,7,7,7]
Output: [0,0,0,0]
 

Constraints:

2 <= nums.length <= 500
0 <= nums[i] <= 100
*/

vector<int> smallerNumbersThanCurrent(vector<int>& nums) {

    // vars 
    unordered_map<int, int> hashmap; 
    vector<int> result(nums.size()); 

    // make copy of nums 
    vector<int> copy = nums; 
 
    // sort nums in ascending order 
    sort(copy.begin(), copy.end());


    for(int i = 0; i < copy.size(); i++)
    {

        if(hashmap.find(copy[i]) == hashmap.end()) // .end() iterator is returned if find fails
        {
            // current num hasn't been seen yet 
            // so the count for this val is it's current index
            // and add to the hasmap 
            hashmap[copy[i]] = i; // saved <value, index>, access index to get saved count. 


        }else{
            // use saved count 
            // skip it 
        }
    }

    for(int i = 0; i < nums.size(); i++)
    {
       auto find = hashmap.find(nums[i]); // search for the num at OG index
       if(find != hashmap.end())
       {
            // if has been found 
            int count = find->second; // accessing the stored count
            result[i] = count;
       }

    }
    return result; 
}

int main(){

    vector<int> nums = {8,1,2,2,3};
    vector<int> result = smallerNumbersThanCurrent(nums); 

    cout << "count: "; 
    for(int i = 0; i < result.size(); i++)
    {
        cout << result[i]; 
    }
    cout << endl; 

}