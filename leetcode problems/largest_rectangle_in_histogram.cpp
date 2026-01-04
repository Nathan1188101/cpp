#include<iostream> 
#include<stack> 
#include<vector> 

using namespace std; 

// problem: 
/*
Q3. Largest Rectangle in Histogram
Given an array of integers heights representing the histogram's bar height where the width of each bar is 1,
return the area of the largest rectangle in the histogram.

Example 1:


Input: heights = [2,1,5,6,2,3]
Output: 10
Explanation: The above is a histogram where width of each bar is 1.
The largest rectangle is shown in the red area, which has an area = 10 units.
Example 2:


Input: heights = [2,4]
Output: 4
 

Constraints:

1 <= heights.length <= 105
0 <= heights[i] <= 104
*/

int largestRectangleArea(vector<int>& heights) {
        
    // Thoughts 
    /*
        we are given an array of heights representing a histograms bar height where the width of each bar is 1. 
        we need to return the area of the largest rectanlge in the histogram

        need to clarify a few things: 

        is the width always 1? 
        yes 

        ok so we need to see for each i (bar), how far can we go left and or right where ith height is the limiting height
        IMPORTANT: so the heights don't have to be the same, we just need to see from each index i's height, setting that to the limiting height, how many combine
                   to create the largest rectangle. 

                   example: there could be heights = [1, 2, 3, 4]

                            so the greatest area would be found from focusing on consecutive bars that meet the height requirement (the current i)
                            so from this example: 3 x 2 = 6 would be the greatest not only from [3, 4] which is. 3 x 2, but also from [2, 3, 4] which gives 2 x 3. 

        
        GAME PLAN: 

            need to scan left and right from current i to see how many bars fit in the height requirement,
            then run the calculation. 

            so I know we are going to have to iterate through the list of heights. 
            Then I suppose have pointers going out left and right until a bar falls below the height requirement. 

    */

    int area, final_area = 0;
    int current_height = 0; 
    stack<int> stack; 

    for(int i = 0; i < heights.size(); i++){

        int R_pointer, L_pointer = 0; 
        current_height = heights[i]; 

        while(R_pointer < heights.size() || L_pointer >= 0) // OR will continue as long as at least one condition is true
        {

            // ok so theoretically (I believe) my while loop would keep executing say even if L pointer began going below 0, and R pointer was still valid
            // then when finally both are no longer valid this while would exit.

            R_pointer ++; 
            L_pointer --; 

            if(heights[R_pointer] >= current_height)
            {
                stack.push(heights[R_pointer]); 
            }

            if(heights[L_pointer] >= current_height)
            {
                stack.push(heights[L_pointer]); 
            }
        }
        
        int width = stack.size();
        area = current_height * width; 

        if(area > final_area)
        {
            final_area = area; 
        }


    }


    return final_area; 


}

int main(){

    vector<int> heights = {2,1,5,6,2,3}; 
    int result = largestRectangleArea(heights); 

    cout << "Largest area: " << result << endl; 


}