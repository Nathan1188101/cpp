#include<iostream> 
#include<vector> 
#include<unordered_map> 

using namespace std; 

/*
Q3. Find All Numbers Disappeared in an Array

Given an array nums of n integers where nums[i] is in the range [1, n], return an array of all the integers in the range [1, n] that do not appear in nums.

 
Example 1:

Input: nums = [4,3,2,7,8,2,3,1]
Output: [5,6]
Example 2:

Input: nums = [1,1]
Output: [2]


Constraints:

n == nums.length
1 <= n <= 105
1 <= nums[i] <= n


Follow up: Could you do it without extra space and in O(n) runtime? You may assume the returned list does not count as extra space.
*/

vector<int> findDisappearedNumbers(vector<int>& nums) {

    unordered_map<int, int> map; 
    vector<int> result; 

    // fill the map with seen values 
    for(int i = 0; i < nums.size(); i++)
    {
        map[nums[i]] = i; // <value, index> 
    }

    // all nums inside nums are in range of 1 to n
    // return another array of "the holes", or rather, the numbers that do not appear 
    for(int i = 1; i <= nums.size(); i++)
    {
        // from 1 to n
        // search for each number 
        // if NOT present (i.e returns .end(), then put in result array)
        if(map.find(i) == map.end())
        { // .end() returned if NOT found 
            result.push_back(i); 
        }
    }

    return result; 

}

int main(){
    vector<int> nums = {1,1}; 
    vector<int> result = findDisappearedNumbers(nums);

    cout << "missing nums: "; 
    for(int i = 0; i < result.size(); i++)
    {
        cout << result[i];  
    }
    cout << endl; 

}