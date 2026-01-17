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
#include<algorithm>

std::string subsitutionCipherEncryption(std::string plainText, std::vector<int> key){

    std::string key_space = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ,."; 

    // map message to keyspace (before permutation)
    /*
        thinking through this: 

        so when we encounter a char, we need to check what it's value is. 
            like if we find a H -> 7
            
            example: "hello" -> 7, 4, 11, 11, 14

            so we need a way to iterate through the plain text -> match the current char to it's value -> then put it in some output vector or something 


    */

    for (int i = 0; i < plainText.size(); i++) {

        // identify current char
        // find it in keyspace 
        // get index -> boom done 

        // get current char 
        char current_char = plainText[i]; 

        // search for it in space 
        size_t index = key_space.find(current_char);

        if (index != std::string::npos) {
            // if char/index is found 
            
        }


    }

}


int main(){

    std::string plain_text; 
    std::vector<int> key;  
    int input; 

    std::cout << "input plain text (message): "; 
    std::cin >> plain_text; 

    std::cout << "input (from 0-28) 28 values for key: ";
    while (key.size() != 28) {

        std::cin >> input;

        // needs to be within the range 
        if (input > 28 || input < 0) {
            std::cout << "only values within the range of 0 - 28" << std::endl;
        }
        // cannot already exist in the list 
        else if (std::find(key.begin(), key.end(), input) != key.end()) {
            std::cout << "already input this value, try another." << std::endl; 
        }
        else {
            // only add value if it passes validation 
            key.push_back(input); 
        }

    }

    std::string result = subsitutionCipherEncryption(plain_text, key); 

    std::cout << "result: " << result << std::endl; 

}