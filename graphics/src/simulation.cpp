#include"simulation.h"
#include<iostream> 

// constructor 
Simulation::Simulation(CircleManager& manager) : manager(manager) {

}

/*
    Need to switch to the moran process doing birth death or death birth

    BD (birth death):
        - choose a random node to reproduce (prob of being chosen is proportional to it's fitness)
        - randomly pick one of it's neighbors 
        - replace that neighbor with the offspring of the chosen reproductive node (offspring will be same type)

    DB (death birth):
        - randomly choose a node to die 
        - look at it's neighbors 
        - pick one neighbor to reproduce and replace this dead spot (weighted by fitness)
        - replace 

*/
void Simulation::BirthDeath() {

    // choose a node for reproduciton 
    // so find the node with the best fitness? or choose a random one but give nodes with higher fitness a slightly better chance of being chosen 
    // choose a random number between 1 and n - 1 (n = # of nodes)
    // 

    srand(time(0)); // might need to call this only once somewhere else, for now I will keep it here

    int total_nodes = manager.getNodes().size(); 

    int random_node = rand() % total_nodes; 

    // now get a ref to that node 
    auto& nodes = manager.getNodes(); 
    auto& chosen_node = nodes[random_node]; // ref to random node 
 
    auto& neighbors = chosen_node->getNeighbors(); 
    int random_neighbor = rand() % neighbors.size(); 
    auto& chosen_neighbor = neighbors[random_neighbor]; 

    


}