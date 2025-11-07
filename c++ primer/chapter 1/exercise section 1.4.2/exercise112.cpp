//what does the following for loop do? 
#include <iostream> 

using namespace std; 

/*
    I ran the program and the sum came out as 0 in the end. 

    if we start the loop at -100, go until 100 and add the i iteration of the loop to the sum we end up adding -100 to 100.
    so we just get 0
*/

int main(){ 

    int sum = 0; 
    for(int i = -100; i <= 100; i++){
        sum += i;
    }
    cout << "Sum: " << sum << endl;

    return 0;


}