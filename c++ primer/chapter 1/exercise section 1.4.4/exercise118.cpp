//compiling and running the program talked about in this section. What hapeens when you only give it equal values? Then do a set of nums where no value is repeated 
#include <iostream>

using namespace std; 

int main(){

    int currVal = 0, val = 0;

    //read first num and ensure that we have data to process 
    if(cin >> currVal){

        int cnt = 1; //to count recurring values 

        //read the remaining numbers 
        while(cin >> val){

            if(val == currVal){
                ++cnt;
            }else{
                cout << currVal << " occurs " << cnt << " times" << endl; 
                currVal = val; //remember the new value 
                cnt = 1; //reset the counter 
                }

        }
        cout << currVal << " occurs " << cnt << " times" << endl; //print the count for the last value in the input 

    }

    return 0;
}