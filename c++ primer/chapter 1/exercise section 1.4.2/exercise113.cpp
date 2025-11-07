//redoing the exercises from section 1.4.1 that used while with for
#include <iostream>

using namespace std; 

int main(){

    //previously: used a 'while' to sum the nums from 50 to 100
    
    int sum = 0; //remember Initialize to avoid garbage values 

    for(int i = 50; i <= 100; i++){
        sum += i; 
    }

    cout << "sum: " << sum << endl; //sum = 3825

    return 0; 

}