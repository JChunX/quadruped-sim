#ifndef QUADRUPED_SIM_H
#define QUADRUPED_SIM_H

#include <GLFW/glfw3.h>
#include <mujoco/mujoco.h>
#include <string>
#include <iostream>

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

private:
    void init();
    void update();
    void render();
    void shutdown();
    void load_model_and_data(std::string model_path);

    static QuadrupedSim getInstance() // Singleton is accessed via getInstance()
    {
        static QuadrupedSim instance; // lazy singleton, instantiated on first use
        return instance;
    }

    //https://stackoverflow.com/questions/7676971/pointing-to-a-function-that-is-a-class-member-glfw-setkeycallback   
    static void keyboard(GLFWwindow* window, int key, int scancode, int act, int mods) {
        getInstance().keyboard_impl(window, key, scancode, act, mods);
    }
    static void mouse_move(GLFWwindow* window, double xpos, double ypos) {
        getInstance().mouse_move_impl(window, xpos, ypos);
    }
    static void mouse_button(GLFWwindow* window, int button, int act, int mods) {
        getInstance().mouse_button_impl(window, button, act, mods);
    }
    static void scroll(GLFWwindow* window, double xoffset, double yoffset) {
        getInstance().scroll_impl(window, xoffset, yoffset);
    }

    void keyboard_impl(GLFWwindow* window, int key, int scancode, int act, int mods);
    void mouse_move_impl(GLFWwindow* window, double xpos, double ypos);
    void mouse_button_impl(GLFWwindow* window, int button, int act, int mods);
    void scroll_impl(GLFWwindow* window, double xoffset, double yoffset);

    bool button_left = false;
    bool button_middle = false;
    bool button_right = false;
    double lastx = 0;
    double lasty = 0;
};

#endif // QUADRUPED_SIM_H