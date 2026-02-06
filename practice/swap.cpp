#include<iostream> 

void swapWithPointers(int* a, int* b) {

    // swap with pointers 
    // so swap the ints at each pointer? 
    
    // get copy of val they are pointing too
    // int temp = *a; 
    // int temp2 = *b; 

    // // then reassign 
    // *a = temp2; 
    // *b = temp; 

    // or simpler 
    int temp = *a;
    *a = *b; 
    *b = temp; 

}

void swapWithReferences(int& a, int& b) {

    int temp = a; 
    std::cout << "Temp: " << temp << std::endl; 
    a = b; 
    b = temp; 

}

int main() {

    // variable 
    int x = 1; 
    int y = 2; 

    // create pointer and assign to address of  
    int* a = &x;
    int* b = &y;

    // std::cout << *a << std::endl; 
    // std::cout << *b << std::endl; 


    //swapWithPointers(a, b);
    swapWithReferences(x, y); 

    // std::cout << *a << std::endl; 
    // std::cout << *b << std::endl;
    
    std::cout << x << std::endl; 
    std::cout << y << std::endl; 

}