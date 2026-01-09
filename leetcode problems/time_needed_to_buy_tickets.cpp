#include<iostream> 
#include<vector> 

using namespace std; 

// problem: 
/*
Q2. Time Needed to Buy Tickets
There are n people in a line queuing to buy tickets, where the 0th person is at the front of the line and the (n - 1)th person is at the back of the line.

You are given a 0-indexed integer array tickets of length n where the number of tickets that the ith person would like to buy is tickets[i].

Each person takes exactly 1 second to buy a ticket. A person can only buy 1 ticket at a time and has to go back to the end of the line (which happens instantaneously) in order to buy more tickets. If a person does not have any tickets left to buy, the person will leave the line.

Return the time taken for the person initially at position k (0-indexed) to finish buying tickets.

 

Example 1:

Input: tickets = [2,3,2], k = 2

Output: 6

Explanation:

The queue starts as [2,3,2], where the kth person is underlined.
After the person at the front has bought a ticket, the queue becomes [3,2,1] at 1 second.
Continuing this process, the queue becomes [2,1,2] at 2 seconds.
Continuing this process, the queue becomes [1,2,1] at 3 seconds.
Continuing this process, the queue becomes [2,1] at 4 seconds. Note: the person at the front left the queue.
Continuing this process, the queue becomes [1,1] at 5 seconds.
Continuing this process, the queue becomes [1] at 6 seconds. The kth person has bought all their tickets, so return 6.
Example 2:

Input: tickets = [5,1,1,1], k = 0

Output: 8

Explanation:

The queue starts as [5,1,1,1], where the kth person is underlined.
After the person at the front has bought a ticket, the queue becomes [1,1,1,4] at 1 second.
Continuing this process for 3 seconds, the queue becomes [4] at 4 seconds.
Continuing this process for 4 seconds, the queue becomes [] at 8 seconds. The kth person has bought all their tickets, so return 8.
 

Constraints:

n == tickets.length
1 <= n <= 100
1 <= tickets[i] <= 100
0 <= k < n
*/

int timeRequiredToBuy(vector<int>& tickets, int k){

        // thoughts: 
        /*
            ok so we have a line of people 
            0th person is at the front of the line 

            we are given a 0 indexed array (tickets -> same length as there are people in the line)
            the amount of tickets the ith person in line wants to buy is at tickets[i]

            each person takes 1 sec to buy a ticket 
            only one ticket at a time 
            go back to end of line after getting ticket (if needing more still)

            return the time taken for the person at position k (initially -> the line is going to change but we are talking about from its first state) to finish buying tickets 
            
        */

        // need to identify k
        // take 1 ticket away from each index 1 by 1
        // but have an acc targeted on k, keeping track of how many sec it takes total 

        int kth_person = k; 
        int time = 0; 

        // I need to update position k as it moves around the queue 
        // also need to stop the while loop when k position is 0, don't care about the others 


        while(!tickets.empty())
        {
            cout << "tickets before taking: " << tickets[0] << endl; 

            // take a ticket 
            tickets[0] --;
            cout << "tickets at front now: " << tickets[0] << endl; 

            time++; 

            cout << "k position: " << kth_person << endl; 
            if(kth_person == 0){

                kth_person == tickets.size() - 1; 

            }
            else if(kth_person > 0){

                kth_person --; 

            }
            
            if(tickets[kth_person] == 0){
                break; 
            }


            // if the num of tickets at the front of the line
            if(tickets[0] > 0){
                // take the now decremented amount and put to back of line 
                tickets.push_back(tickets[0]);

                // then delete the copy of it at the front
                tickets.erase(tickets.begin()); 
                cout << "moving front to back" << endl; 
            }
            else if(tickets[0] == 0){
                // else it is 0 
                // remove from queue as it is done 
                tickets.erase(tickets.begin());
                kth_person --; 
                cout << "deletion occured, k now: " << kth_person << endl;  
            }

        }

        return time; 

}

int main(){

    vector<int> tickets = {2,3,2};
    int k = 2; 
    int result = timeRequiredToBuy(tickets, k); 

    cout << "result: " << result << endl; 


}