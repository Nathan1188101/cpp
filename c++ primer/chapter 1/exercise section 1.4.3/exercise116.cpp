//making my own program that reads a set of values from cin and sums that 
#include <iostream> 

using namespace std; 

int main(){

    //sum and value
    int sum = 0; 
    int value = 0; 

    while(cin >> value)
        sum += value;

    cout << "sum: " << sum << endl; 

    return 0;
}