#include<iostream> 
#include<string> 
#include<vector>

std::string permutationCipher(const std::string& plain_text, const int& m){

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

        

    }


}

int main(){

    std::string plain_text; 
    int m; 

    std::cout << "enter message: "; 
    std::getline(std::cin, plain_text);
    std::cout << "enter block size: "; 
    std::cin >> m; 

    std::string encrypt = permutationCipher(plain_text, m); 

}