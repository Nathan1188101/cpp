#include<iostream> 
#include<vector> 

using namespace std; 

vector<int> exclusiveTime(int n, vector<string>& logs) {

    string action; 
    vector<int> result(n); 
    vector<int> stack; 
    int current_time, prev_time, acc_time = 0;

    for(int i = 0; i < logs.size(); i++){

        // get action 
        int delimiter = logs[i].find(":"); // find first occurance 
        int end_delimiter = logs[i].rfind(":"); // last occurance 
        action = logs[i].substr(delimiter + 1, end_delimiter - delimiter - 1);

        // func_id 
        int func_id = stoi(logs[i].substr(0, delimiter));
        int time_stamp = stoi(logs[i].substr(end_delimiter + 1, logs[i].size() - end_delimiter - 1));
        current_time = time_stamp;  

        cout << "action: " << action << endl; 

        if(action == "start"){

            // push if start

            cout << "func id: " << func_id << endl; 

            // check if another function is running (check if stack is not empty)
            if(!stack.empty()){

                // if not empty 
                // calc time for who was running 
                acc_time = current_time - prev_time; 
                result[stack.back()] += acc_time; 

            }
            // then push (still always need to push) -> just need to run calc above it not so we can account for interruptions 
            stack.push_back(func_id);
            prev_time = current_time;
                
                
        }
        else if(action == "end"){

            // pop if end 
            acc_time = current_time - prev_time + 1; 
            result[stack.back()] += acc_time; 
            stack.pop_back(); // then pop 
            prev_time = current_time + 1; 

            // NOTE: (about inclusive for END (+1), but exlusive for start) 
            /*
                END calculations are inclusive. 

                end, ends at that timestamp, example -> 1:start:2, 1:end:5 -> 2, 3, 4, 5 -> 4 time units 
                calculation = 5 - 2 + 1 = 4 

                Why is there no +1 for the start? 

                when calculating between two starts, i.e -> 0:start:0, 1:start:2, 0 starts at beginning of 0, 
                                                                                  1 starts at beginning of 2. 
                calculation = 2 - 0 = 2
                for handling interruptions, start to start, just subtract.

                for start to end do +1 because it ENDS AT x, it's inclusive. 
            */            
        }

    }

    return result; 

}

int main(){ 

    int n = 2;
    vector<string> logs = {"0:start:0","1:start:2","1:end:5","0:end:6"}; 
    vector<int> result = exclusiveTime(n, logs); 

    cout << "result: "; 
    for(int i = 0; i < result.size(); i++)
    {
        cout << result[i];
    }
    cout << endl; 

}