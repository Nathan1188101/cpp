//count how many vowels in a string. 
#include <iostream>
#include <string>

using namespace std; 

int main(){

    //something to contain vowel ref
    char vowels[6] = {'a', 'e', 'i', 'o', 'u', 'y'};
    int size = (sizeof(vowels) / sizeof(vowels[0])); //length of array = total size of array in bytes / size of single element in bytes
    string input;
    int count = 0; //always initialize your variables (int count; was uninitialized and will just fill with garbage i.e whatever values were in the register last time it was used)

    getline(cin, input);

    //normalize the string to lowercase first 
    for(int l = 0; l < input.length(); l++){
        input[l] = tolower(input[l]);
    }

    //loop through input string
    for(int i = 0; i < input.length(); i++){

        char current_char = input[i];
        for(int j = 0; j < size; j++){

            //compare current char in outter loop to each vowel in vowel array 
            if(current_char == vowels[j]){
                count ++; //increase count if vowel found
            }

        }

    }

    cout << "total vowels: " << count << endl; 

    return 0;
}