#include<iostream> 

int* findMax(int* arr, int size) {

    // return pointer to largest element 

    int* result; 

    int temp = -1;
    int index;  
    for (int i = 0; i < size; i++) {

        if (arr[i] > temp) {
            temp = arr[i]; 
            index = i; 
        }
    }

    result = &arr[index];

    return result; 
}

 
int main() {

    int arr[] = {4, 9, 1, 20, 7};

    int* max = findMax(arr, 5); 

    std::cout << "max: " << *max << std::endl; 

}