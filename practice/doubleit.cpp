#include<iostream> 

void doubleValues(int* arr, int size) {

    // passing a pointer to the first element of arr (is what we are getting)

    for (int i = 0; i < size; i++) {
        arr[i] = arr[i] * 2; 
    }

}


int main() {

    int arr[] = {1, 2, 3, 4}; 

    doubleValues(arr, 4); 

    std::cout << "Output: ";
    for (int i = 0; i < 4; i++) {
        std::cout << arr[i] << " ";
    } 
    std::cout << std::endl; 

}