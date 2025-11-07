//exercise section 1.4.1 
//while related practice 
#include <iostream>

using namespace std; 

int count(){

    int count = 50;
    int sum = 0;

    while(count <= 100){
        sum += count;
        ++count;
    }
    
    cout << "count: " << sum << endl;

    return sum;
}

int main(){

    count();

    return 0;
}



