#include<iostream>
#include<vector> 
#include<stack> 

using namespace std;

// PROBLEM 
/*
Q2. Daily Temperatures
Given an array of integers temperatures represents the daily temperatures, return an array answer such that answer[i] is the number of days you have to wait after the ith day to get a warmer temperature. If there is no future day for which this is possible, keep answer[i] == 0 instead.


Example 1:

Input: temperatures = [73,74,75,71,69,72,76,73]
Output: [1,1,4,2,1,1,0,0]
Example 2:

Input: temperatures = [30,40,50,60]
Output: [1,1,1,0]
Example 3:

Input: temperatures = [30,60,90]
Output: [1,1,0]
 

Constraints:

1 <= temperatures.length <= 105
30 <= temperatures[i] <= 100
 

*/

vector<int> dailyTemperatures1(vector<int>& temperatures) {

    // THOUGHTS: 
    /*
        given an array -> temperatures -> represents daily temps 

        what we need to do:
            return an array answer
            -> where answer[i] -> the number of days you have to wait after ith day to get a warmer temperature 
            if there is no warmer day, answer[i] == 0.


        ok how are we gonna do this...

        I suppose we could use a nested loop approach like in the previous questions (final price discount),
        and iterate from current i forward to see if we find a warmer day, then note how many iterations forward we took 

        is there a more elegant way? maybe this is fine as is I'm not sure

    */

    vector<int> answers; 
    int current = 0; 
    int days = 0; 

    // need to check if list is duplicates all the way through, redundant to iterate through every thing too many times 


    for(int i = 0; i < temperatures.size(); i++)
    {

        current = temperatures[i];
        bool flag = false; 

        for(int j = i + 1; j < temperatures.size(); j++)
        {
            if(temperatures[j] > current){
                days = j - i; 
                flag = true; 
                break; 
            }
        }
        if(flag == false){
            answers.push_back(0); 
        }
        else{
            answers.push_back(days);             
        }

    }

    return answers; 
        
}

vector<int> dailyTemperatures(vector<int>& temperatures){

    // use a stack approach I think will get us away from O(n) 

    vector<int> answer(temperatures.size(), 0); // creating vector of size temperatures and giving all default values of 0
    stack<int> stack; 

    // need to iterate through and push indicies. 
    // we aren't pusing temps, but "indicies of unresolved days"

    // if stack not empty 
    // before pushing to the waiting pile, see if today answers anyone already waiting 
    
    for(int i = 0; i < temperatures.size(); i++)
    {

        while(!stack.empty() && temperatures[i] > temperatures[stack.top()]){

            // get top value 
            int prev = stack.top();
            // destroy it 
            stack.pop();

            // run calc
            int days = i - prev; 
            // add to answer list 
            answer[prev] = days; 
        }
        stack.push(i); 

    }

    return answer; 

}

// just checking my understanding (writing again from scratch)
vector<int> dailyTemperatures3(vector<int>& temperatures){

    vector<int> answer(temperatures.size()); 
    stack<int> stack; 

    for(int i = 0; i < temperatures.size(); i++)
    {
        while(!stack.empty() && temperatures[i] > temperatures[stack.top()])
        {
            int prev = temperatures[stack.top()];
            stack.pop(); 
            int days = i - prev; 
            answer[prev] = days; 
        }
        stack.push(i);
    }
    return answer; 
}

int main(){
                            //        2           6             6 - 2 = 4 
    vector<int> temperatures = {73,74,75,71,69,72,76,73}; 
    vector<int> answer = dailyTemperatures(temperatures); 

    cout << "answers: "; 
    for(int i = 0; i < answer.size(); i++){
        cout << answer[i];
    }
    cout << endl; 


}