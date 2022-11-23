#ifndef QUADRUPED_SIM_H
#define QUADRUPED_SIM_H

#include <GLFW/glfw3.h>
#include <mujoco/mujoco.h>
#include <string.h>

class QuadrupedSim
{

public:
    QuadrupedSim();
    ~QuadrupedSim();
    void run();

    // MuJoCo data structures
    mjModel* m = NULL;
    mjData* d = NULL;
    mjvCamera cam;
    mjvOption vopt;
    mjvScene scn;
    mjrContext con;

    GLFWwindow* window = NULL;

    InputController input_controller;

private:
    void init();
    void update();
    void render();
    void shutdown();
    void load_model_and_data(std::string model_path);
};