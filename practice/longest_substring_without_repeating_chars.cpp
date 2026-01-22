#include<iostream>
#include<string> 
#include<unordered_map> // hashmap 
#include<vector> // dynamic array for string test cases

using namespace std; 

int lengthOfLongestSubstring(string s){

    // pointers 
    int left = 0; 
    int right = 0; 

    // substring vars 
    string substring; 
    string final_substring; 

    // hashmap for tracking chars and their index 
    unordered_map<char, int> map; 

    // handle empty string 
    if(s.empty())
        return 0; 

    for(int i = 0; i <= s.length() - 1; i++)
    {
        right = i; // update right pointer with each iteration 

        // current char 
        char current_char = s[i];

        // new char branch 
        if(map.find(current_char) == map.end())
        {
            // add char to map 
            map[current_char] = i; // adds the char and the index (making the key value pair)
            
            // record substring
            int length = (right - left) + 1; //inclusive
            substring = s.substr(left, length); 
            if(substring.length() > final_substring.length())
            {
                final_substring = substring; 
            }
            
        }
        // dupe found branch 
        else if(map.find(current_char) != map.end())
        {
            // adjust window, then take substring 
            if(map[current_char] + 1 > left) // only shift left if it is going forward 
            {
                left = map[current_char] + 1; // up to dupe and past it 
            }

            //get substring (basically starting new one now I suppose)
            int length = (right - left) + 1; 
            substring = s.substr(left, length); 
            if(substring.length() > final_substring.length())
            {
                final_substring = substring; 
            }

            // update hashmap 
            map[current_char] = i; 

        }

    }
    if(final_substring.empty())
        final_substring = s; 

    return final_substring.length();

}

int main(){ 

    vector<string> strings = 
    {
        "abcdefg", // 7
        "aaaaaa",  // 1
        "andhsa",  // 5
        "",        // 0
        "abcdab",  // 4
    }; 

    for(int i = 0; i <= strings.size() -1; i++)
    {
        cout << "longest substring in " << strings[i] << ": " << lengthOfLongestSubstring(strings[i]) << endl;
    }


}
