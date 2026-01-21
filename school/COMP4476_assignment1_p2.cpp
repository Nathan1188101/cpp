#include<iostream> 
#include<string> 
#include<vector>

std::string permutationCipher(const std::string& plain_text, const int& m){

    // we split plain text up into m sized blocks 
    // then make permutations of each block 



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