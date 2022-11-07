#include<iostream>
#include<filesystem>
#include"QuadrupedSim.h"

int main(int argc, char** argv)
{
    std::string path = std::filesystem::current_path().string();
    std::cout << "Current path is : " << path << std::endl;
    QuadrupedSim sim;
    sim.run();
    return 0;
}