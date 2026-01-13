#include<iostream>
#include<vector> 

using namespace std; 

// problems: 
/*
Q2. Find K Pairs with Smallest Sums
You are given two integer arrays nums1 and nums2 sorted in non-decreasing order and an integer k.

Define a pair (u, v) which consists of one element from the first array and one element from the second array.

Return the k pairs (u1, v1), (u2, v2), ..., (uk, vk) with the smallest sums.

 

Example 1:

Input: nums1 = [1,7,11], nums2 = [2,4,6], k = 3
Output: [[1,2],[1,4],[1,6]]
Explanation: The first 3 pairs are returned from the sequence: [1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]
Example 2:

Input: nums1 = [1,1,2], nums2 = [1,2,3], k = 2
Output: [[1,1],[1,1]]
Explanation: The first 2 pairs are returned from the sequence: [1,1],[1,1],[1,2],[2,1],[1,2],[2,2],[1,3],[1,3],[2,3]
 

Constraints:

1 <= nums1.length, nums2.length <= 105
-109 <= nums1[i], nums2[i] <= 109
nums1 and nums2 both are sorted in non-decreasing order.
1 <= k <= 104
k <= nums1.length * nums2.length
*/

vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k){

    // thoughts: 
    /*
        ok we are given two integer arrays 
        nums 1 and nums 2 
        they are sorted in non decreasing order (meaning) -> values never go down, each element is either equal to or greater than the previous one 
        we are also give an integer k 

        we need to define a pair (u, v) which consists of one element from the first array and one from the other 

        we need to return k pairs with the smallest sums 
    */

}

int main(){

    vector<int> nums1 = {1, 7, 11};
    vector<int> nums2 = {2, 4, 6}; 
    int k = 3; 
    vector<vector<int>> result = kSmallestPairs(nums1, nums2, k); 

    cout << "Result: " << result << endl; 

}