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
#include<iterator> 

const std::string KEY_SPACE = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ,.";

// encryption
std::string substitutionCipherEncryption(const std::string& plain_text, const std::vector<int>& key){

    std::string formatted_string; 
    std::vector<int> plain_text_ints; 
    std::vector<int> substitution; 
    std::string encrypted;

    // convert to upper 
    for (int i = 0; i < plain_text.size(); i++) {
        auto current_char = toupper(plain_text[i]); 
        formatted_string.push_back(current_char); 
    }

    // convert plain text chars to plain text ints 
    for (int i = 0; i < formatted_string.size(); i++) {

        // get current char 
        char current_char = formatted_string[i]; 

        // search for it in space 
        size_t index = KEY_SPACE.find(current_char);

        // if number found 
        if (index != std::string::npos) { // char found in keyspace 
            plain_text_ints.push_back(index); 
        }

    }


    // converting plain text ints to cipher text ints 
    for (int i = 0; i < plain_text_ints.size(); i++) {

        // current num 
        int current_num = plain_text_ints[i]; 

        // so go to index denoted by current num in permutation list
        int replace = key[current_num]; 

        substitution.push_back(replace);

    }

    for (int i = 0; i < substitution.size(); i++) {

        int current_num = substitution[i]; 

        char search = KEY_SPACE[current_num]; 

        encrypted.push_back(search); 

    }

    return encrypted; 

}

// decryption 
std::string substitutionCipherDecryption(const std::string& cipher_text, const std::vector<int>& key){

    /*
        to decrypt 

        capture cipher text 
        convert to nums using KEY_SPACE 
        then search for each num in permutation -> wherever that num is, take it's index (that's the original plain text number)
        convert new nums to plain text
        boom done. 

    */

    std::vector<int> cipher_text_ints;
    std::vector<int> decrypted_ints;  
    std::string decryption; 

    // convert to nums using Z29 (KEY_SPACE) 
    for (int i = 0; i < cipher_text.size(); i++) {

        char current_char = cipher_text[i]; 
        size_t index = KEY_SPACE.find(current_char);
        
        if (index != std::string::npos) {
            // exists
            cipher_text_ints.push_back(index); 
        }

    }

    // then apply inverse/reverse mapping 
    for (int i = 0; i < cipher_text_ints.size(); i++) {

        // search for each of these nums in the permutation 
        // take the index of where it is and that's the num we need. 
        auto plain_text_int = std::find(key.begin(), key.end(), cipher_text_ints[i]);

        if (plain_text_int != key.end()) {
            int index = std::distance(key.begin(), plain_text_int);
            decrypted_ints.push_back(index); 
        }

    }

    // convert decrypted nums to original plain text 
    for (int i = 0; i < decrypted_ints.size(); i++) {

        int current_num = decrypted_ints[i]; 

        char map_to = KEY_SPACE[current_num]; 

        decryption.push_back(map_to);

    }

    return decryption; 

}

int main(){

    std::string plain_text; 
    std::vector<int> key;  
    int input; 

    // NOTE: pre made permutation key so you don't have to enter in the values (will skip while loop below)
    key = {22, 28, 8, 23, 20, 6, 4, 24, 14, 21, 5, 15, 10, 7, 18, 3, 1, 0, 13, 12, 26, 16, 27, 9, 25, 19, 11, 2, 17}; 

    std::cout << "input plain text (message): "; 
    std::getline(std::cin, plain_text); 

    // NOTE: this will get skipped when using pre made permutation. 
    std::cout << "input (from 0-28) 29 values for key: " << std::endl;
    while (key.size() != 29) {

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

    std::string result = substitutionCipherEncryption(plain_text, key); 

    std::cout << "result: " << result << std::endl; 

    std::string cipher_text = result; 
    std::string decrypt = substitutionCipherDecryption(cipher_text, key);
    
    std::cout << "decryption: " << decrypt << std::endl; 

}
