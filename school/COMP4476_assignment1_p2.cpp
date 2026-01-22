#include<iostream> 
#include<string> 
#include<vector>
#include<algorithm>
#include<iterator> 

std::string permutationCipher(const std::string& plain_text, const int& m, const std::vector<int>& permutation){

    // we split plain text up into m sized blocks 
    // then make permutations of each block 
    
    // maybe use a vector of strings. 
    std::vector<std::string> blocks; 
    int counter = 0; 
    int current = 0;
    for (int i = 0; i < plain_text.size(); i++) {

        // keep pushing/building a block until counter == m 
        // when counter == m, start building new block  
        if (counter != m) {

            counter++; 
            blocks[current].push_back(plain_text[i]); 

        }
        else{
            counter = 0; 
            current += 1; 
        }

    }
    
    for (int i = 0; i < blocks.size(); i++) {

        // something here

    }


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
        std::cout << "block size must be greater than 0. Try again:";
        std::cin >> m; 
    }

    std::cout << "enter permutation from 1 - " << m; 

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