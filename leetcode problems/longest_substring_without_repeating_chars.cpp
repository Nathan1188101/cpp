#include <iostream> 
#include <string> 
#include <unordered_map> // this is hash map (dictionary. for us, key is char and value is index (int).

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

    // if given is empty quit out right away 
    if(given.empty())
    {
        return 0; 
    }
    
    // loop through string
    for(int i = 0; i <= given.length() - 1; i++){

        right = i; // update right with each iteration 

        // each interation keep left where it it unless a dupe is found and increment right by 1 
        char current_char = given[i];
        if(hash.find(current_char) == hash.end()) // unordered_map returns end() iterator if whatever is being searched for cannot be found 
        { // if char not found, it's not been seen

            // add it to the hash
            hash[current_char] = i; // add key value pair to the hashmap 

            // record substring 
            int distance = (right - left) + 1; 
            substring = given.substr(left, distance);
            if(substring.length() > final_substring.length())
            {                    
                final_substring = substring; 
            }


        }else if(hash.find(current_char) != hash.end()){
            //if char has been seen 

            // need to get to and past where last dupe was seen (NEED TO MAKE SURE TO NOW ALLOW LEFT TO MOVE BACKWARDS)
            // basically "querying" the hashmap to find the duplicate to current, so we can go to it and use that info to shift left pointer
            if(hash[current_char] + 1 > left)
            { // if shifting the left part of the window doesn't go backwards, proceed

                left = hash[current_char] + 1; 

            } // else do nothing to left
            //or left = hash.find(current_char) -> second //.find() returns an iterator (points to element in bucket if found (element being <key, value> pair, then -> second gives us the value))

            //save substring before moving to next
            int distance = (right - left) + 1; // + 1 to be inclusive, need to account for 
            substring = given.substr(left, distance); //from left forward "length" many indicies 
            if(substring.length() > final_substring.length()){
                final_substring = substring; 
            }
            

            //still need to update hashmap even if we get a dupe (so we can find index of everything) 
            hash[current_char] = i; 

        }

    }

            //if no duplicate every occurs 
    if(final_substring.empty()){
        final_substring = given; 
    }

    return final_substring.length(); 

}

// entry point 
int main(){

    string s = "aaaaaa";

    // pass string into function for testing
    cout << "Longest Substring in " << s << ": " << lengthOfLongestSubstring(s) << endl;

}