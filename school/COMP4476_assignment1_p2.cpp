#include<iostream> 
#include<string> 
#include<vector>
#include<algorithm>
#include<iterator> 

const std::string LETTERS = "abcdefghijklmnopqrstuvwxyz"; 

std::string permutationCipher(std::string& plain_text, const int& m, const std::vector<int>& permutation){

    std::string encrypted_message; 

    // removing the spaces in the message for clean blocks
    plain_text.erase(std::remove(plain_text.begin(), plain_text.end(), ' '), plain_text.end()); 
    
    // string vector for blocks 
    std::vector<std::string> blocks; 
    std::vector<std::string> permutated_blocks; 
    int counter = 1; 
    int current = 0;
    blocks.push_back(""); // starting with 1 empty block we can begin adding to 
    for (int i = 0; i < plain_text.size(); i++) {

        // keep pushing/building a block until counter > m 
        // when counter > m, start building new block  
        if (counter <= m) {

            std::cout << "current char: " << plain_text[i] << std::endl; 

            counter++; 
            blocks[current].push_back(plain_text[i]); 

        } else {
            std::cout << "starting new block." << std::endl; 
            std::cout << "current char: " << plain_text[i] << std::endl; 
            counter = 1; // reset counter  
            current += 1; // incremement to go to that new block
            blocks.push_back(""); // starting new block 
            blocks[current].push_back(plain_text[i]);
            counter++; 
        }
    }

    // need to add padding to non full blocks 
    // if the last string in the blocks vector isn't of size m, add padding. 
    if (blocks.back().size() != m) {

        // get size of block currently 
        int current_size = blocks.back().size(); 

        // find how much padding we need 
        int padding = m - current_size; 

        // using 'x' as padding for now. Could generate random nums and access LETTERS but oh well. 
        for (int i = 0; i < padding; i++) {
            blocks.back().push_back('x');
        }

    }

    // debugging blocks 
    std::cout << "checking blocks: " << std::endl; 
    for (int i = 0; i < blocks.size(); i++) {

        // I want to check that blocks came out right. 

        std::cout << blocks[i] << std::endl; 

    }
    
    // now need to do permutation on blocks 
    for (int i = 0; i < blocks.size(); i++) {

        // go through each block and rearange according to permutation 

        std::string current_block = blocks[i]; 
        permutated_blocks.push_back(""); 

        for (int i = 0; i < current_block.size(); i++) {

            // look up what i should be in permutation 
            int location = permutation[i] - 1; // so if we at 0 -> (2) it will return what user input for front of block 

            // then go to that location in the block 
            permutated_blocks.back().push_back(current_block[location]);

        }
    }
        
    std::cout << "checking permutated blocks: " << std::endl; 
    for (int i = 0; i < permutated_blocks.size(); i++) {

        // I want to check that blocks came out right. 
        std::cout << permutated_blocks[i] << std::endl; 

    }
    


    return encrypted_message;

}

int main(){

    int m; // block size
    int input; // for permutation
    std::vector<int> permutation; // key 
    std::string plain_text; // message 

    std::cout << "enter message: "; 
    std::getline(std::cin, plain_text);
    std::cout << "enter block size (m > 0): "; 
    std::cin >> m; 
    while (m <= 0){
        std::cout << "block size must be greater than 0. Try again: ";
        std::cin >> m; 
    }

    std::cout << "enter permutation from 1 - " << m << std::endl; 

    while (permutation.size() != m) {

        std::cin >> input; 

        if (input > m || input <= 0) {
            std::cout << "only input numbers from 1 - " << m << std::endl; 
        }
        else if (std::find(permutation.begin(), permutation.end(), input) != permutation.end()) {
            // if != .end(), then it already exists. .end() is returned when what you're looking for is not there. 
            std::cout << "Cannot add values already in key... try again." << std::endl; 
        }
        else {
            // only adding if it passes validation 
            permutation.push_back(input); 
        }

    } 

    std::string encrypt = permutationCipher(plain_text, m, permutation); 

}