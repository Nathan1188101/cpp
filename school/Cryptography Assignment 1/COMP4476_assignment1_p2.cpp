#include<iostream> 
#include<string> 
#include<vector>
#include<algorithm>
#include<iterator> 

// PERMUTATION ENCRYPTION. (uses 'x' for padding)
std::string permutationCipher(std::string& plain_text, const int& m, const std::vector<int>& permutation){

    std::string encrypted_message; 

    // removing the spaces in the message for clean blocks
    plain_text.erase(std::remove(plain_text.begin(), plain_text.end(), ' '), plain_text.end()); 

    // string vector for blocks 
    std::vector<std::string> blocks; 
    for (int i = 0; i < plain_text.size(); i++) {
        if (i % m == 0) {
            blocks.push_back(""); // start new block 
        }
        blocks.back().push_back(plain_text[i]);
    }
    // need to add padding to non full blocks 
    // if the last string in the blocks vector isn't of size m, add padding 
    if (blocks.back().size() != m) {

        // get size of block currently 
        int current_size = blocks.back().size(); 

        // find how much padding we need 
        int padding = m - current_size; 

        for (int i = 0; i < padding; i++) {
            blocks.back().push_back('x');
        }

    }

    // DEBUGGING: showing plain blocks 
    /*
    std::cout << "checking blocks: " << std::endl; 
    for (int i = 0; i < blocks.size(); i++) {
        // I want to check that blocks came out right. 
        std::cout << blocks[i] << std::endl; 
    }
    */
    
    // doing user defined permutation on blocks  
    std::vector<std::string> permuted_blocks; 
    for (int i = 0; i < blocks.size(); i++) {

        std::string current_block = blocks[i]; 
        permuted_blocks.push_back(""); // creating an empty block 

        for (int i = 0; i < current_block.size(); i++) {

            // look up what i should be in permutation 
            int index = permutation[i] - 1; // need to - 1 because of 0 based counting 

            // then go to that location in the block and add that char to the new block
            permuted_blocks.back().push_back(current_block[index]); // build new permuted block into empty block

        }
    }
        
    // DEBUGGING: showing permuted blocks 
    /*
    std::cout << "checking permuted blocks: " << std::endl; 
    for (int i = 0; i < permuted_blocks.size(); i++) {
        // I want to check that blocks came out right
        std::cout << permuted_blocks[i] << std::endl; 
    }
    */

    // then combine all these blocks into one string 
    for (int i = 0; i < permuted_blocks.size(); i++) {
        encrypted_message.append(permuted_blocks[i]);
    }
    
    return encrypted_message;

}

std::string permutationCipherDecryption(std::string& cipher_text, const int& m, const std::vector<int>& permutation){

    std::string plain_text; // for final output 

    // need to split the cipher text into m sized blocks 
    std::vector<std::string> permuted_blocks;  
    for (int i = 0; i < cipher_text.size(); i++) {
        if (i % m == 0) {
            permuted_blocks.push_back(""); // start new block 
        }
        permuted_blocks.back().push_back(cipher_text[i]); 
    }

    // get inverse of permutation 
    std::vector<int> inverse_permutation;
    for (int i = 0; i < permutation.size(); i++) {

        // find num in permutation 
        auto num = std::find(permutation.begin(), permutation.end(), i + 1); 

        // get index 
        int index = std::distance(permutation.begin(), num); 

        inverse_permutation.push_back(index + 1); 

    }

    // now we have permuted blocks 
    // need to revert them using inverse permutation  
    std::vector<std::string> blocks; 
    for (int i = 0; i < permuted_blocks.size(); i++) {

        std::string current_block = permuted_blocks[i];
        blocks.push_back("");  

        for (int i = 0; i < current_block.size(); i++) {
            // look up what i should be in permutation 
            int index = inverse_permutation[i] - 1; // need to - 1 because of 0 based counting 

            // then go to that location in the block and add that char to the new block
            blocks.back().push_back(current_block[index]); // build new permuted block into empty block
        }

    }

    // putting it all together 
    for (int i = 0; i < blocks.size(); i++) {
        plain_text.append(blocks[i]); 
    }

    return plain_text;

}

int main(){

    int m; // block size
    int input; // for permutation
    std::vector<int> permutation; // key 
    std::string plain_text; // message 

    // test cases if you want them 
    // int m = 3;
    // permutation = {2, 1, 3};
    // plain_text = "hello there"

    std::cout << "enter message: "; 
    std::getline(std::cin, plain_text);
    std::cout << "enter block size (m > 0): "; 
    std::cin >> m; 
    while (m <= 0){
        std::cout << "block size must be greater than 0. Try again: ";
        std::cin >> m; 
    }

    std::cout << "enter permutation from 1 - " << m << std::endl; 
    // taking input for permutation
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
    std::cout << "encrypted message: " << encrypt << std::endl;
    
    std::cout << "--------" << std::endl; 

    // decryption 
    std::string decrypt = permutationCipherDecryption(encrypt, m, permutation); 
    std::cout << "decrypted message: " << decrypt << std::endl; 

}