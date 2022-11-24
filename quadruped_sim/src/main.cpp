#include<iostream>
#include<filesystem>
#include"QuadrupedSim.h"

int main(int argc, char** argv) {

    // print pwd
    std::cout << "pwd:" << std::filesystem::current_path() << std::endl;

    QuadrupedSim sim;
    
    sim.run();

    return 0;
}