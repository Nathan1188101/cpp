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

int largestRectangleArea1(vector<int>& heights) {
        
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

    int area = 0;
    int final_area = 0;
    int current_height = 0; 
    stack<int> stack; 
    bool R_flag = false; 
    bool L_flag = false; 
  

    if(heights.size() == 1){
        final_area = 1 * heights[0]; 
    }

    for(int i = 0; i < heights.size(); i++){

        int R_pointer = i + 1; 
        int L_pointer = i - 1; 
        current_height = heights[i];
        int width = 0; 
        R_flag = false;  
        L_flag = false;


        stack.push(current_height);

        while((R_pointer < heights.size() || L_pointer >= 0) && (R_flag == false || L_flag == false)) // OR will continue as long as at least one condition is true
        {
            
            if(R_pointer < heights.size() && heights[R_pointer] >= current_height && R_flag == false)
            {
                stack.push(heights[R_pointer]); 
                R_pointer ++; 
            }else{
                R_flag = true;
            }
            
            if(L_pointer >= 0 && heights[L_pointer] >= current_height && L_flag == false)
            {
                stack.push(heights[L_pointer]); 
                L_pointer --; 
            }else{
                L_flag = true;
            }

        }
        
        width = stack.size();
        area = current_height * width; 

        // then clear the stack for next run 
        while(!stack.empty()){
            stack.pop(); 
        }

        if(area > final_area)
        {
            final_area = area; 
        }


    }


    return final_area; 


}

// OK TURNS OUT THIS APPROACH IF FUNDAMENTALLY FLAWED, MOVING ON AND TRYING ANOTHER BELOW
int largestRectangleArea2(vector<int>& heights){

    stack<int> stack; 
    int width = 0; 
    int area = 0; 
    int final_area = 0;
    int height = 0;  
    int acc = 0; 


    for(int i = 0; i < heights.size(); i++)
    {
        int current_height = heights[i];
        acc = 0;  

        if(stack.empty())
        {
            stack.push(i);
            cout << "stack was empty so " << i << " was pushed" << endl; 
        }
        else if(current_height >= heights[stack.top()]){ // so our stack will have increasing order 
            stack.push(i);
            cout << "found a bar within params: " << i << " was pushed" << endl; 
        }
        else if(current_height < heights[stack.top()]){ 
            cout << "encountered smaller bar, being popping" << endl; 

            while(!stack.empty()){

                // need to count the number of items popped from the list 
                acc += 1; 
                stack.pop(); 
                cout << "pop" << endl; 

                if(stack.size() == 1)
                    height = heights[stack.top()]; 
                    cout << "stack has 1 element left, so OG height was: " << height << endl;

            }

            area = acc * height; 
            cout << "calcultion ran: " << acc << " * " << height << endl; 
            cout << "area = " << area << endl; 

            if(area > final_area)
                final_area = area; 
                cout << "area was found to be greater, final area = " << final_area << endl; 
        }

        if(!stack.empty())
        {
            while(!stack.empty()){


                if(stack.size() == 1)
                    height = heights[stack.top()]; 
                    cout << "stack has 1 element left, so OG height was: " << height << endl; 

                // need to count the number of items popped from the list 
                acc += 1; 
                stack.pop(); 
                cout << "pop" << endl; 


            }

            area = acc * height; 
            cout << "calcultion ran: " << acc << " * " << height << endl; 
            cout << "area = " << area << endl; 

            if(area > final_area)
                final_area = area; 
                cout << "area was found to be greater, final area = " << final_area << endl; 
        }
    }

    return final_area; 

}

// new approach 
int largestRectangleArea(vector<int>& heights){

    stack<int> stack; 
    int area = 0; 
    int final_area = 0;
    int width = 0; 
    int height = 0; 
    int current_height = 0;  

    for(int i = 0; i < heights.size(); i++)
    {

        current_height = heights[i]; 

        if(stack.empty())
        {
            // push the index 
            stack.push(i); 
        }
        else if(heights[i] >= heights[stack.top()])
        {
            stack.push(i); 
        }
        else if(heights[i] < heights[stack.top()])
        {
            // encountered a shorter bar 

            // we pop one bar at a time 
            // right bound is the index of the smaller bar we just encountered 
            // after each pop, we look to see what is at the top of the stack now 
            // that bar is probably shorter (could be equal height but idk)
            // that is the left boundary now 
            // stack.top() (after popping) should be the first bar to the LEFT that is shorter 
            // i is where we hit a shorter bar on the RIGHT 
            // so width = R_bound - L_bound - 1 (-1 exlusive because we don't want to include the outer bounds, only what is within)


            while(!stack.empty() && heights[stack.top()] > current_height){

                int poppedIndex = stack.top(); 
                stack.pop(); 

                height = heights[poppedIndex]; 
                if(stack.empty()){
                    width = i; // why?
                }else{
                    width = i - stack.top() - 1; 
                }

                area = height * width; 
                if(area > final_area)
                {
                    final_area = area; 
                }

            }

            stack.push(i);

        }

        // if we reach the end of the array, and the stack still has bars in it
        // we need to pop them and run the calculations 

    }

    return final_area; 

}

int main(){

    //vector<int> heights = {2,1,5,6,2,3}; 
    // vector<int> heights = {1}; 
    vector<int> heights = {1, 1}; // 2 
    int result = largestRectangleArea(heights); 

    cout << "Largest area: " << result << endl; 


}