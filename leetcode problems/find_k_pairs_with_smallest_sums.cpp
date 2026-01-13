#include<iostream>
#include<vector> 
#include<queue> 

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
        we are also given an integer k 

        we need to define a pair (u, v) which consists of one element from the first array and one from the other 

        we need to return k pairs with the smallest sums 

        possible solutions: 

        I'm wondering if we can use a min_heap in some way to find the min values of each array and then combine them together to get smaller pairs 

        but looking at the example it seems that we take a "control value" from one array and then compare it to every other value in the other array 
    */

    // make a priority queue of ints, stored in a vector, where smallest values go on top (front of line)
    priority_queue<int, vector<int>, greater<int>> pq1; 
    priority_queue<int, vector<int>, greater<int>> pq2; 
    vector<vector<int>> result; 

    for(int i = 0; i < nums1.size(); i++){
        pq1.push(nums1[i]);
    }

    for(int i = 0; i < nums2.size(); i++){
        pq2.push(nums2[i]);
    }


    for(int i = 1; i < k; i++)
    {
        // take the top of each, compare them to see which is smallest. 
        // then use that smaller val as the control value and compare it to the others in the other array? 

        // take the root of each first 
        // then keep going for the rest of k 
        int top1 = pq1.top(); 
        cout << "top1: " << top1 << endl; 
        int top2 = pq2.top(); 
        cout << "top2: " << top2 << endl; 

        result.push_back({top1, top2});


        if(top1 > top2)
        {
            cout << "top1 greater than top2" << endl; 
            cout << "popping: " << pq2.top() << endl; 
            pq2.pop();
            int next_smallest = pq2.top();
            result.push_back({top1, next_smallest}); 
        }
        else if(top2 > top1){
            cout << "top2 greater than top1" << endl; 
            cout << "popping: " << pq1.top() << endl; 
            pq1.pop(); 
            int next_smallest = pq1.top(); 
            result.push_back({top2, next_smallest}); 
        }

    }

    return result; 

}

int main(){

    vector<int> nums1 = {1, 7, 11};
    vector<int> nums2 = {2, 4, 6}; 
    int k = 3; 
    vector<vector<int>> result = kSmallestPairs(nums1, nums2, k); 

    for(int i = 0; i < result.size(); i++)
    {
        for(int j = 0; j < result[i].size(); j++)
        {
            cout << "[" << result[i][0] << ", " << result[i][1] << "]" << endl; 
        }
    }
    

}