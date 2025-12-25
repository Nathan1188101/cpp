#include<iostream> 
#include<vector> 
#include<string> 

using namespace std; 

int evalRPN(vector<string>& tokens){

    // iterate through given array 
    // push each time
    // until operand encountered 
    // then pop two most recent nums and perform operation 
    // push result back onto the stack 

    int result = 0; 
    int operation_result = 0; 
    vector<int> stack; 

    for(int i = 0; i < tokens.size(); i++)
    {
        // check if current element is a num 
        // if so -> push onto stack 

        // if not pop last two and do operation
        // then push back 

               
        if(tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "/" || tokens[i] == "*")
        {
            char current_char = tokens[i][0];

            // need to pop two most recent nums from stack here (order matters)
            int first = stack.back();
            stack.pop_back(); // delete

            int second = stack.back(); 
            stack.pop_back(); // delete

            switch(current_char){

                case '+':
                    operation_result = first + second;

                case '-':
                    operation_result = second - first; 
                
                case '*':
                    operation_result = first * second; 

                case '/':
                    operation_result = second / first; 

            }

            stack.push_back(operation_result);

        }else{ // else it's a num

            // gotta figure this out 
            int num = stoi(tokens[i]); 
            stack.push_back(num);

        }

    }

    return stack[0]; 

}

int main(){

    vector<string> tokens = {"2","1","+","3","*"};
    int result_stack = evalRPN(tokens);

    cout << "result: " << result_stack << endl; 

}