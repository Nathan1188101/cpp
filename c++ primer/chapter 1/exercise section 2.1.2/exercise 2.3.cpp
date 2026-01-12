#include<iostream> 

using namespace std; 

int main(){ 

    // remember: 
    // signed always defaults to unsigned when mixed 

    uint32_t u = 10; 
    uint32_t u2 = 42; 

    //                                       Predictions: 
    cout << "u2 - u = " << u2 - u << endl; // 32
    cout << "u - u2 = " << u - u2 << endl; // 4 mill something...

    int i = 10; 
    int i2 = 42; 

    cout << "i2 - i = " << i2 - i << endl; // 32 
    cout << "i - i2 = " << i - i2 << endl; // -32
    
    cout << "--- now testing unsigned with signed ---" << endl; 
    cout << "i - u = " << i - u << endl; // 0
    cout << "u - i = " << u - i << endl; // 0 

}