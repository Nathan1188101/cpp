#include<iostream>
#include<algorithm>

// Problem: 
/*
Q3. Construct Target Array With Multiple Sums

You are given an array target of n integers. From a starting array arr consisting of n 1's, you may perform the following procedure :

let x be the sum of all elements currently in your array.
choose index i, such that 0 <= i < n and set the value of arr at index i to x.
You may repeat this procedure as many times as needed.
Return true if it is possible to construct the target array from arr, otherwise, return false.

 

Example 1:

Input: target = [9,3,5]
Output: true
Explanation: Start with arr = [1, 1, 1] 
[1, 1, 1], sum = 3 choose index 1
[1, 3, 1], sum = 5 choose index 2
[1, 3, 5], sum = 9 choose index 0
[9, 3, 5] Done
Example 2:

Input: target = [1,1,1,2]
Output: false
Explanation: Impossible to create target array from [1,1,1,1].
Example 3:

Input: target = [8,5]
Output: true
*/

/// @brief This function will return x, which is the sum of all elements currently in our arr
/// @param arr pass in the array
/// @return return the sum
int arrSum(std::vector<int>& arr) {

    // always start x at 0 before summing
    int x = 0; 

    for (int i = 0; i < arr.size(); i++) {
        x += arr[i];
    }

    return x; 

}

/// @brief choose an index i, that is within the constraints, and then set the value of arr at index i to x (the sum of arr)
/// @param index_i the index chosen
/// @return 
int setNum(int index_i, std::vector<int>& arr) {

    int x = arrSum(arr); 

    if (index_i < 0 || index_i > arr.size()) {
        std::cout << "Invalid index passed" << std::endl;
        return; // exit immediately
    }

    arr[index_i] = x;

}


bool isPossible(std::vector<int>& target) {

    // std::vector<int> arr;
    // for (int i = 0; i < target.size(); i++ ) {
    //     arr.push_back(1);
    // }

    // I was thinking in the opposite direction of a working solution
    // ask I suspected, my solution was leading down an endless searching sort of path. Just not going to work
    // instead, we should work backwards from what we already have. The target array. 
    // instead of doing a bunch of guessing by summing and placing in random indexes we can work back by always targetting the biggest number in the target array and determining what value it use to be before becoming that number
    // The largest number in this sort of context for the problem will always be the num that changed last and we can work all the way back to 1s from that (if it is even possible in the first place)
    
    // I need to figure out what the condition is to break out and return false that we should be able to tell from early on.
    int largest_num = 0; 

    // get largest value, this returns an iterator (pointer to the element)
    auto it = std::max_element(target.begin(), target.end());

    // deref the iterator 
    if (it != target.end())
        int largest_num = *it;
        
    



    return true; 
}

int main() {

    std::vector<int> target = {9,3,5}; 

    // create arr (same size as target, all elements = 1 to start)
    std::vector<int> arr;
    for (int i = 0; i < target.size(); i++ ) {
        arr.push_back(1);
    }



}