//take two integers from user input and output the range between the two (using while)
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






