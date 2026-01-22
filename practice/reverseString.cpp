#include <stdlib.h>
#include <string>
#include <iostream> 

//reverse string implementation
using namespace std; 

int main(){

    //input string 
    std::string input; 
    
    //output 
    std::string output; 

    std::cout << "input string: ";
    getline(cin, input);
    //std::cin >> input; 

    //starting from last index of string, decrement until at index 0
    for(int i = input.length() - 1; i >= 0; i--){

        //take current input index and add to new output string
        output += input[i]; 

    }

    //output results 
    std::cout << "reversed string: " << output << std::endl;


    return 0; 


}