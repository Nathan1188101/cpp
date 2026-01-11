#include<iostream> 
#include<vector> 
#include<queue> // for priority queue 

using namespace std; 

// problem: 
/*
Q1. Last Stone Weight
You are given an array of integers stones where stones[i] is the weight of the ith stone.

We are playing a game with the stones. On each turn, we choose the heaviest two stones and smash them together. Suppose the heaviest two stones have weights x and y with x <= y. The result of this smash is:

If x == y, both stones are destroyed, and
If x != y, the stone of weight x is destroyed, and the stone of weight y has new weight y - x.
At the end of the game, there is at most one stone left.

Return the weight of the last remaining stone. If there are no stones left, return 0.

Example 1:

Input: stones = [2,7,4,1,8,1]
Output: 1
Explanation: 
We combine 7 and 8 to get 1 so the array converts to [2,4,1,1,1] then,
we combine 2 and 4 to get 2 so the array converts to [2,1,1,1] then,
we combine 2 and 1 to get 1 so the array converts to [1,1,1] then,
we combine 1 and 1 to get 0 so the array converts to [1] then that's the value of the last stone.
Example 2:

Input: stones = [1]
Output: 1
 

Constraints:

1 <= stones.length <= 30
1 <= stones[i] <= 1000
*/

int lastStoneWeight(vector<int>& stones){

    // thoughts: 
    /*
        ok we are given an array of stone weights (where stones[i] is the weight of the ith stone)

        game: 
            - each turn we select the two heaviest stones 
            - smash them together 
            - two heaviest stones are x and y 
                - where x <= y
                - so they are either the same, or one is smaller than the other 
            - if x == y, both gone 
            - if x != y, x stone is gone and the weight of stone y is now -> y - x 

            return the weight of the last stone remaining (if there are any left) (will at most be one left)
    */

    while(!stones.empty())
    {
        // need to find max value and then the next max value
        // could be the same as max
        // otherwise we need the next largest 

        // ok I did some research and have learned about:
        // max heap
        // which is good for making priority queues 

        // a max heap: 
        // each nodes value is >= it's children
        // so larger values float to the top 

        // so somehow we use a priority queue to implment a max heap (I think?) 


        // thoughts: 
        /*
            ok I've done some more research 
            a priority queue by defauly in c++ is a max priority queue (max values prioritized)

            looks something like this: 

                priority_queue<int> pq; 

                then, 

                pq.top() = max
                pq.pop() removes max 
                pq.push(x) inserts x while keeping the heap property 

        */
        
        priority_queue<int> pq; 

    }

}

int main(){
    
}