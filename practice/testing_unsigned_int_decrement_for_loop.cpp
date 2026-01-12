/*
        Got this idea from c++ primer. 
        they were talking about the behavior of using an unsigned int never going below 0,
        to serve as the exit condtion of a decrementing for loop from 10 to 0. 

        Let me go ahead below so you can see what I'm talking about. 

        SPOILER ALERT: 

            it doesn't work because at one point the for loop will normally decrement 0
            to -1, and then when it comes back around to test i >= 0 it would normally fail
            and the for loop would exit. 

            HOWEVER, if we are using an unsigned int it will wrap around from 0 to 4,294,967,295
            (assuming 32-bit int, but it could be whatever). So, the for loop would never terminate
            as it would wrap around from 0 to 4 mil everytime.
*/
#include<iostream> 

using namespace std; 

int main(){

    // in c++, unsigned int doesn't guarantee a max bit size, only min
    // it is just dependent on your system. 

    // if you want control you should use: 
    // uint32_t

    uint32_t my_int = 10; 
    unsigned int my_other_int = 10; 

    for(unsigned int i = 10; i >= 0; i--)
    {
        cout << i << endl; 
    }

}