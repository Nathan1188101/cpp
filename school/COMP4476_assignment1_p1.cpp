/*
                                                    COMP4476 Cryptography
                                                        Assignment 1 


Problem 1. 

    Write a program for the SUBSTITUTION CIPHER 
    based on Z 29
    corresponds to 26 alphabetic characters (0 - 25) 
    - " " is 26
    - "," is 27
    - "." is 28 

    I need to make encryption and decryption code 

    For the encryption, the plaintext and the key need to be input. The
    encryption algorithm will ask the use to choose and input a random order of the
    numbers 0, 1, . . . , 28 as a key
                            
    for the encryption algorithm the plain text and the key are the input 
        - so I suppose the key would be the random ordering (permutation) of nums 0 through 28, and the user inputs that? 


*/

#include<iostream>
#include<vector> 
#include<string>

std::string subsitutionCipherEncryption(std::string plainText, std::vector<int> key){

    std::string keySpace = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ,."; 

    // need to take user input for plain text
    // need to take user input for key 


    // then map the letters to the numbers 
    // then shuffle the numbers around the match the key



}


int main(){

    std::string plainText; 
    std::vector<int> key;  
    int input; 

    std::cout << "input plain text (message): "; 
    std::cin >> plainText; 

    std::cout << "input 28 values for key: ";
    for (int i = 0; i < 28; i++) {
        std::cin >> input;
        key.push_back(input); 
    }

    std::string result = subsitutionCipherEncryption(plainText, key); 

    std::cout << "result: " << result << std::endl; 

}