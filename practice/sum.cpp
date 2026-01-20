#include<iostream> 


// Time Complexity: O(n)
int sum(int n){

    int sum = 0; 
    for (int i = 0; i <= n; i++) {

        sum += i; 

    }

    return sum; 

}


// Time Complexity: O(1)
int sumFaster(int n){

    int sum = n * (1 + n) / 2; 
    return sum; 

}

// therefore, sumFaster is better as it runs in O(1) (which is lower/faster than O(N))
//  sumFaster will always run in a set number of steps (3) where regualr sum's runtime will grow with the size of the input n

int main(){

    int n = 0; 

    std::cout << "for exit, enter: 6767" << std::endl; 

    while(true){

        std::cout << "input number: ";
        std::cin >> n;

        if (n == 6767) {
            break; 
        }

        int result = sumFaster(n);         

        std::cout << "sum = " << result << std::endl; 
    }


}