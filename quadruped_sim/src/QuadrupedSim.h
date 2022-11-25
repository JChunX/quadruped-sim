#ifndef QUADRUPED_SIM_H
#define QUADRUPED_SIM_H

#include <GLFW/glfw3.h>
#include <mujoco/mujoco.h>
#include <string>
#include <iostream>
#include "Input.h"
#include "controllers/BaseController.h"
#include "controllers/Controller.h"
#include "controllers/MPCController.h"

class QuadrupedSim
{

public:
    QuadrupedSim(std::string model_path);
    ~QuadrupedSim();
    void step();
    void render();
    void load_model_and_data();

    // MuJoCo data structures
    mjModel* m = NULL;
    mjData* d = NULL;
    // Number of MuJoCo steps to run for every call to step()
    int num_substeps = 35;

    GLFWwindow* window = NULL;
    bool gl_ok() {
        return !glfwWindowShouldClose(window);
    }

private:
    void initialize();
    void shutdown();
    
    mjvCamera cam;
    mjvOption vopt;
    mjvScene scn;
    mjrContext con;

    std::string model_path;
};

#endif // QUADRUPED_SIM_H