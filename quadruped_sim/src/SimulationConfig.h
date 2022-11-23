#ifndef SIMULATION_CONFIG_H
#define SIMULATION_CONFIG_H

#include <string>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>

/* 
Configuration data and parser for the simulation.
*/

struct SimulationConfig {
    // Simulation configuration data
    std::string simulation_name;
    std::string model_name;
    std::string controller;
}