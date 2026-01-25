#include<iostream> 
#include<string> 
#include<vector>
#include<algorithm>
#include<iterator> 

std::string permutationCipher(std::string& plain_text, const int& m, const std::vector<int>& permutation){

    std::string encrypted_message; 

    // removing the spaces in the message for clean blocks
    plain_text.erase(std::remove(plain_text.begin(), plain_text.end(), ' '), plain_text.end()); 
    
    // string vector for blocks 
    std::vector<std::string> blocks;  
    for (int i = 0; i < plain_text.size(); i++) {
        if (i % m == 0) {
            blocks.push_back(""); 
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

    // then combine all these blocks into one string 
    for (int i = 0; i < permuted_blocks.size(); i++) {
        encrypted_message.append(permuted_blocks[i]);
    }
    
    return encrypted_message;

}

// I will use a struct to define what is being returned by the attacker function 
struct AttackResult {
    int m; // size of block 
    std::vector<int> key; // permutation/key  
};

AttackResult plainTextAttack(std::string& plain_text, const std::string& cipher_text) {

    AttackResult result; 

    // THOUGHTS: 
    /*
    // base case m = 2
    // this is like swap position or not 

    // I need to be looking at positions 
    // across blocks, which plaintext position j could consistently land in ciphertext position i
    
    // so iteratively go through different block sizes for plain and cipher text 
    // analyze positions in plain and cipher blocks
    // we're looking to see 

    // whenever we find the permutation, whatever block size was used to find that will be m 
    */
    
    // removing the spaces in the message for clean blocks
    plain_text.erase(std::remove(plain_text.begin(), plain_text.end(), ' '), plain_text.end()); 

    bool m_found = false; 
    int m = 2;
    while (m_found == false) {

        std::cout << "current m = " << m << std::endl; 

        // PLAIN TEXT BLOCKS 
        std::cout << "building plain text blocks..." << std::endl; 
        std::vector<std::string> blocks;  
        for (int i = 0; i < plain_text.size(); i++) {
            // everytime i is a multiple of m create a new block. Otherwise keep adding to the current one. 
            if (i % m == 0) {
                blocks.push_back("");
            }
            blocks.back().push_back(plain_text[i]);
        }
        // add padding 
        if (blocks.back().size() != m) {
            int current_size = blocks.back().size(); 
            int padding = m - current_size; 
            for (int i = 0; i < padding; i++) {
                    blocks.back().push_back('x');
            }
        }
        
        // CIPHER TEXT BLOCKS 
        std::cout << "building cipher blocks..." << std::endl; 
        std::vector<std::string> permuted_blocks;  
        for (int i = 0; i < cipher_text.size(); i++) {
            if (i % m == 0) {
                permuted_blocks.push_back(""); 
            }
            permuted_blocks.back().push_back(cipher_text[i]); 
        }


        // building candidate key.  
        std::cout << "building candidate key..." << std::endl; 
        std::vector<int> candidate_key; 
        std::vector<bool> used(m, false); 
        for (int i = 0; i < permuted_blocks[0].size(); i++) {

            char target = permuted_blocks[0][i]; 

            // go through OG block 
            for (int j = 0; j < blocks[0].size(); j++) {
                if (blocks[0][j] == target && used[j] == false) {
                    candidate_key.push_back(j + 1); 
                    used[j] = true; 
                    break; // break, outter iterates and we begin looking for next char 
                }
            }

        }


        std::cout << "candidate key size: " << candidate_key.size() << std::endl; 
        if (candidate_key.size() != m) {
            std::cout << "key size does not match m, testing next block size." << std::endl;  
            m++;
            continue; 
        }
        if (m == 10) {
            std::cout << "At m=10:" << std::endl;
            std::cout << "blocks[0]: '" << blocks[0] << "'" << std::endl;
            std::cout << "permuted_blocks[0]: '" << permuted_blocks[0] << "'" << std::endl;
            std::cout << "candidate_key: ";
            for (int k : candidate_key) std::cout << k << " ";
            std::cout << std::endl;
        }

        std::cout << "testing candidate key with the existing blocks" << std::endl; 
        // now that we have a temp key 
        // test it with the rest of the blocks by making the permutation with the regular block and comparing it to the 
        int counter = 1; // block 0 already been checked. so counter at 1
        for (int i = 1; i < blocks.size(); i++) { // block 0 already checked so i = 1 to skip first block 

            std::string temp_permuted_block; 
            // go through and apply permutation to build a temp block for comparison to real permuted block 
            for (int j = 0; j < blocks[i].size(); j++) {
                int position = candidate_key[j] - 1;
                temp_permuted_block.push_back(blocks[i][position]); 
            }

            // compare to real corresponding permuted block 
            if (temp_permuted_block != permuted_blocks[i]) {
                // wrong 
                // increment m and try again
                temp_permuted_block.clear(); 
                m++;
                break;
            } else {
                counter += 1; 
            }

        }
        if (counter == permuted_blocks.size()) {
            result.key = candidate_key; 
            result.m = m; 
            m_found = true; 
        }

    }

    return result; 

}

int main(){

    // my algo breaks for longer messages like this with duplicate chars 
    std::string message = "hello there my name is nathan and I am the best in the game"; 
    int m = 10; 
    std::vector<int> key = {2, 3, 1, 4, 5, 7, 10, 9, 8, 6}; 

    // works great for stuff like this though lol
    // std::string message = "abcdefghi";
    // int m = 3;
    // std::vector<int> key = {2, 3, 1}; 

    // encrypt 
    std::string encrypted_message = permutationCipher(message, m, key); 
    std::cout << "message before: " << message << std::endl; 
    std::cout << "encrypted message: " << encrypted_message << std::endl; 

    // attack
    std::string plain_copy = message; 
    AttackResult result = plainTextAttack(plain_copy, encrypted_message); 

    std::cout << "Found m: " << result.m << std::endl; 
    std::cout << "Found key: "; 
    for (int i = 0; i < result.key.size(); i++) {
        std::cout << result.key[i]; 
    }
    std::cout << std::endl; 

}