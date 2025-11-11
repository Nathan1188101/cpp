//revise program I wrote in exercise 1.4.1 that printer a range of numbers so that it handles input in whic hteh first number is smaller than the second 

//--PASTED--
//take two integers from user input and output the range between the two (using while)
//LOL REALIZED I ALREADY DID THIS WHEN I DID THE EXERCISE THE FIRST TIME, DIDN'T KNOW I WAS SUPPOSE TO ASSUME USER GIVES THE ORDER. EITHER WAY I'M GOATED AND ALREADY DONE.
#include <iostream> 

using namespace std; 

int main(){

    //take two ints from user 
    int num_one;
    int num_two; 

    cin >> num_one;
    cin >> num_two;

    //need to figure out which number is larger/smaller
    if(num_one > num_two){
        
        while(num_two <= num_one){
            cout << num_two << endl;
            ++num_two;
        }
    //else num_two > num_one
    }else{
        while(num_one <= num_two){
            cout << num_one << endl;
            ++num_one;
        }
    }

    return 0;
}






