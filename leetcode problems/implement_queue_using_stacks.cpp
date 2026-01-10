#include<iostream>
#include<stack> 

using namespace std; 

// problem 
/*
Q3. Implement Queue using Stacks
Implement a first in first out (FIFO) queue using only two stacks. The implemented queue should support all the functions of a normal queue (push, peek, pop, and empty).

Implement the MyQueue class:

void push(int x) Pushes element x to the back of the queue.
int pop() Removes the element from the front of the queue and returns it.
int peek() Returns the element at the front of the queue.
boolean empty() Returns true if the queue is empty, false otherwise.
Notes:

You must use only standard operations of a stack, which means only push to top, peek/pop from top, size, and is empty operations are valid.
Depending on your language, the stack may not be supported natively. You may simulate a stack using a list or deque (double-ended queue) as long as you use only a stack's standard operations.
 

Example 1:

Input
["MyQueue", "push", "push", "peek", "pop", "empty"]
[[], [1], [2], [], [], []]
Output
[null, null, null, 1, 1, false]

Explanation
MyQueue myQueue = new MyQueue();
myQueue.push(1); // queue is: [1]
myQueue.push(2); // queue is: [1, 2] (leftmost is front of the queue)
myQueue.peek(); // return 1
myQueue.pop(); // return 1, queue is [2]
myQueue.empty(); // return false
 

Constraints:

1 <= x <= 9
At most 100 calls will be made to push, pop, peek, and empty.
All the calls to pop and peek are valid.
 

Follow-up: Can you implement the queue such that each operation is amortized O(1) time complexity? In other words, performing n operations will take overall O(n) time even if one of those operations may take longer.
*/

// class = user defined data type 
// encapsulates data and functions 
class MyQueue {

    // thoughts:
    /*
        need to use two stacks 

    */

    stack<int> stack1; 
    stack<int> stack2; 

    MyQueue(){

    }

    void push(int x){

        // push to back of queue 
        // if the stack isn't empty 
        // push to stack 1
        // if stack 1 is already full -> pop and push each from 1 to 2 -> then push new element to stack 1 -> then push everything back on top 

        if(stack1.empty()){
            stack1.push(x);
        }else{
            // stack1 has elements in it 
            // so while it has elements, pop the top -> push to stack 2 (so top of stack 1 will be at bottom of stack 2, and end of stack 1 will be at top of stack 2)
            while(!stack1.empty()){
                stack2.push(stack1.top());
                stack1.pop(); 
            }

            stack1.push(x);

            while(!stack2.empty()){
                stack1.push(stack2.top());
                stack2.pop();
            }
        }
    }

    int pop(){

    }

    int peek(){

    }

    bool empty(){

    }

};

int main(){

    

}