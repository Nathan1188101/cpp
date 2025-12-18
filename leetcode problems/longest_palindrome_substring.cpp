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

    int total = given.length();
    int half = total / 2; // returns int (floor)
    cout << "total length of string: " << total << endl; 
    cout << "half of string: " << half << endl; 

    // right 
    for(int i = half; i <= given.length() - 1; i++)
    {
        // left 
        for(int j = half; j >= 0; j--)
        {
            char a = given[i];
            char b = given[j];

            // int distance = (i - j) + 1; 
            // if(a == b){
            //     substring = given.substr(j, distance);
            // }

            // if(substring.length() > final_substring.length())
            // {
            //     final_substring = substring; 
            // }
            while(a == b){
                int distance = (i - j) + 1; 
                substring = given.substr(j, distance);
                if(substring.length() > final_substring.length())
                {
                    final_substring = substring; 
                }
            }
            
            
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

    string s = "abadsefa";

    cout << "longest palindromic substring: " << longestPalindrome(s) << endl; 

}