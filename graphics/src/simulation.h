#pragma once 
#include"CircleManager.h" 

class Simulation {
    public: 
        Simulation(CircleManager& manager);                     // constructor 

        void BirthDeath(); 
        

    private: 
        CircleManager& manager;                                 // store the reference 

};