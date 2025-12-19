#include<iostream> 
#include<string> 
#include<vector> 

using namespace std; 

/*
5. Longest Palindromic Substring
Hint: 
Given a string s, return the longest palindromic substring in s.

Example 1:

Input: s = "babad"
Output: "bab"
Explanation: "aba" is also a valid answer.

Example 2:

Input: s = "cbbd"
Output: "bb"

Constraints:

1 <= s.length <= 1000
s consist of only digits and English letters.
*/

string longestPalindrome(string s) {
        
    string given = s; 
    string substring; 
    string final_substring; 
    int R, L = 0; 

    /*
        How to find palindrome: 
        - has to be same sequence of letters forwards and backwards 
        - sliding window? 
        - 

        aba
        bb
        racecar
    */
        // expand from middle 
        // use L and R pointers 
        // as soon as L and R don't match, no longer palindromic 
        // conditions: 
        // L >= 0 and R < n (n size of string), and L == R

        // find middle of string 
        // count total length
        // divide by 2 
        // if even, round down? 

    // iterate through each char in the string, and at each char treat it as the center and expand out. Do this at every char 
    for(int i = 0; i <= given.length() - 1; i++)
    {

        // odd 
        L = i; 
        R = i; 
        while(L >= 0 && R <= given.length() - 1 && given[L] == given[R])
        {
            // expand outward
            L--; // left
            R++; // right 
            int distance = (R - L - 1); 
            substring = given.substr(L + 1, distance); 
        }
        if(substring.length() > final_substring.length())
        {
            final_substring = substring; 
        }

        // even (resetting them)
        L = i; 
        R = i + 1;
        while(L >= 0 && R <= given.length() - 1 && given[L] == given[R])
        {
            L--; 
            R++; 
            int distance = (R - L - 1); 
            substring = given.substr(L + 1, distance);
        }
        if(substring.length() > final_substring.length())
        {
            final_substring = substring; 
        }

    }

    return final_substring; 
}

int main(){

    vector<string> tests = {
        "racecar",
        "bb",
        "aba",
        "abcdefg",
        "sefabahhfe",
    };

    for(int i = 0; i < tests.size(); i++)
    {
        cout << "for: " << tests[i] << " output: " << longestPalindrome(tests[i]) << endl; 
    }

}