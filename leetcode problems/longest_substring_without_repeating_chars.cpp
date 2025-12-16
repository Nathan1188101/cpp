#include <iostream> 
#include <string> 
#include <unordered_map> // this is hash map (dictionary, for us key is char, and value is index (int)

using namespace std; 

// Problem: 
/*
Given a string s, find the length of the longest substring without duplicate characters.

Example 1:

Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3. Note that "bca" and "cab" are also correct answers.
Example 2:

Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
Example 3:

Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
*/

// Thoughts: 
/*
    "sliding window problem"

    use vars to keep track of current substring, where it STARTS and ENDS (pointers)
    use a hashmap to keep track of characters we've seen 
    if we encounter a repeat we adjust the window and keep looking for something longer 

    hashmap is to keep track of each chars index. (so the hash map stores a chars most recent index)
        if the next char is not in the dict -> expand window 
        if the next char is already in the list -> we've found a dupe -> shift window up to last seen index of the dupe and + 1 (to go past it)


*/

int lengthOfLongestSubstring(string s) {

    // pointers, start at 0 (left most side)
    int left = 0;
    int right = 0;  
    string given = s; 
    unordered_map<char, int> hash; 
    string substring; 
    string final_substring; 

        
    // loop through string
    for(int i = 0; i <= given.length() - 1; i++){

        // each interation keep left where it it unless a dupe is found and increment right by 1 
        char current_char = given[i];
        if(hash.find(current_char) == hash.end()) // unordered_map returns end() iterator if whatever is being searched for cannot be found 
        { // if char not found, it's not been seen

            // add it to the hash
            hash[current_char] = i; // add key value pair to the hashmap 
            right = i; // update right with each iteration 

        }else if(hash.find(current_char) != hash.end()){
            //if char has been seen 

            //save substring before moving to next
            substring = given.substr(left, right);
            if(substring.length() > final_substring.length()){
                final_substring = substring; 
            }
            
            //don't add to hashmap and shift window from left up to and past that (current) position 
            left = i + 1; 

        }

    }
    return final_substring.length(); 

}

// entry point 
int main(){

    string s = "abcabcbb";

    // pass string into function for testing
    cout << lengthOfLongestSubstring(s) << endl;

}