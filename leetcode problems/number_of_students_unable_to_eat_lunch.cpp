#include<iostream>
#include<vector>

using namespace std; 

// problem: 
/*
Q1. Number of Students Unable to Eat Lunch
The school cafeteria offers circular and square sandwiches at lunch break, referred to by numbers 0 and 1 respectively. All students stand in a queue. Each student either prefers square or circular sandwiches.

The number of sandwiches in the cafeteria is equal to the number of students. The sandwiches are placed in a stack. At each step:

If the student at the front of the queue prefers the sandwich on the top of the stack, they will take it and leave the queue.
Otherwise, they will leave it and go to the queue's end.
This continues until none of the queue students want to take the top sandwich and are thus unable to eat.

You are given two integer arrays students and sandwiches where sandwiches[i] is the type of the i​​​​​​th sandwich in the stack (i = 0 is the top of the stack) and students[j] is the preference of the j​​​​​​th student in the initial queue (j = 0 is the front of the queue). Return the number of students that are unable to eat.


Example 1:

Input: students = [1,1,0,0], sandwiches = [0,1,0,1]
Output: 0 
Explanation:
- Front student leaves the top sandwich and returns to the end of the line making students = [1,0,0,1].
- Front student leaves the top sandwich and returns to the end of the line making students = [0,0,1,1].
- Front student takes the top sandwich and leaves the line making students = [0,1,1] and sandwiches = [1,0,1].
- Front student leaves the top sandwich and returns to the end of the line making students = [1,1,0].
- Front student takes the top sandwich and leaves the line making students = [1,0] and sandwiches = [0,1].
- Front student leaves the top sandwich and returns to the end of the line making students = [0,1].
- Front student takes the top sandwich and leaves the line making students = [1] and sandwiches = [1].
- Front student takes the top sandwich and leaves the line making students = [] and sandwiches = [].
Hence all students are able to eat.
Example 2:

Input: students = [1,1,1,0,0,1], sandwiches = [1,0,0,0,1,1]
Output: 3
 

Constraints:

1 <= students.length, sandwiches.length <= 100
students.length == sandwiches.length
sandwiches[i] is 0 or 1.
students[i] is 0 or 1.
*/

int countStudents(vector<int>& students, vector<int>& sandwiches){

    // Thoughts: 
    /*
        ok so we are given to arrays (but they are suppose to be a queue and a stack)
        - so students array is the QUEUE (students[0] = front of the queue)
        - sandwiches array is the STACK (sandwiches[0] = top of stack)

        when the student at the front of the queue, doesn't like the sandwhich on top of the stack -> they go back of the queue
        if the student at front of queue likes the sandwhich on top of stack -> pop sandwhich and student 
        
        the "simulation" stops when no student in the queue will take the top sandwich, count how many students left that "can't eat lunch" at that point. 

    */

    // myVector.erase(myVector.begin + offset if I need it)

    // iterate through students? 
    // check if index 0 of students matches index 0 (top of stack) of sandwiches 
    // if student does not match stack.top() then move student to back of students and continue 
    // if student does match stack.top() then remove both top of sandwiches and front of student queue 

    // count for students left 
    int student_count = 0; 
    bool flag = false; 

    while(!students.empty()){

        if(students[0] == sandwiches[0])
        {
            // if they match 
            // remove student from front of queue 
            // and remove sandwiches from top of stack 
            students.erase(students.begin()); 
            sandwiches.erase(sandwiches.begin()); 
           
            flag = false; 

            cout << "found match" << endl; 
        }
        else{
            // no match 
            // move student to back of student queue
            students.push_back(students[0]); // move to back
            students.erase(students.begin()); // then erase 

            cout << "found mismatch, moving " << students[0] << " to back of line" << endl;  

            flag = true; 
        }

        if(flag = true)
            break;

    }

    student_count = students.size(); 

    return student_count; 


}

int main(){

    vector<int> students = {1,1,1,0,0,1}; 
    vector<int> sandwiches = {1,0,0,0,1,1}; 
    int result = countStudents(students, sandwiches); 

    cout << "students unable to eat lunch: " << result << endl; 

}