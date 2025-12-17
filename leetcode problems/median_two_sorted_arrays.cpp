/*
4. Median of Two Sorted Arrays
Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.

The overall run time complexity should be O(log (m+n)).

 

Example 1:

Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
Explanation: merged array = [1,2,3] and median is 2.
Example 2:

Input: nums1 = [1,2], nums2 = [3,4]
Output: 2.50000
Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.
*/
#include<iostream> 
#include<vector> 
#include<climits> 

using namespace std; 

// thoughts 
/*
    can't acutally merge them, goes against time complexity requirement 
    to SIMULATE the merge behavior we make L and R partitions in both arrays 
    then look at the four "seam" values around the cuts 

    if we have an even total of elements (combined) we have to take the max of the left most partition,
    and the minimum of the rightmost partition, then average them like you normally would. 

*/

// given function starter 
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        
    // find total elements (combined) and half 
    // use pointers L and R on one of the arrays, find middle with these 
    // m = middle 
    // left partition include m   
    // we know we've found the corrent partitions when comparing both partitions from each array with each other's opposite partition 

    // following video: 
    vector<int> A, B = nums1, nums2;
    int total = A.size() + B.size(); // total elements 
    int half = total / 2; // half will tell us total elements in Left partition 

    // if B is bigger than A, swap them 
    if(B.size() < A.size())
    {
        A, B = B, A; 
    }

    // with the condition above, we will always have A being smaller. It has been handled
    // run Binary Search on A because it is smaller 
    // L and R pointers of A 
    int L = 0;
    int R = A.size() - 1; 

    while (true){
        
        int i = (L + R) / 2; // compute middle val of array A 
        int j = half - i - 2; // pointer for B (not sure why -2)
        
        int Aleft = (i >= 0) ? A[i] : INT_MIN; // INT_MIN is the minium value a INT can be in C++
        int Aright = A[i + 1]; 
        int Bleft = (j >= 0) ? B[j] : INT_MIN; 
        int Bright = B[j + 1]; 

    }



}

int main(){ 

}


