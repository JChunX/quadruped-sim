#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>
#include <mujoco/mujoco.h>
#include <iostream>

class Input
{
public:
    Input();
    ~Input();

    static Input& get_instance() // Singleton is accessed via get_instance()
    {
        static Input instance; // lazy singleton, instantiated on first use
        return instance;
    }

    void set_mj_variables(mjModel* m, mjData* d, mjvCamera* cam, mjvOption* vopt, mjvScene* scn, mjrContext* con) {
        this->m = m;
        this->d = d;
        this->cam = cam;
        this->vopt = vopt;
        this->scn = scn;
        this->con = con;
    }

    //https://stackoverflow.com/questions/7676971/pointing-to-a-function-that-is-a-class-member-glfw-setkeycallback   
    static void keyboard(GLFWwindow* window, int key, int scancode, int act, int mods) {
        get_instance().keyboard_impl(window, key, scancode, act, mods);
    }
    static void mouse_move(GLFWwindow* window, double xpos, double ypos) {
        get_instance().mouse_move_impl(window, xpos, ypos);
    }
    static void mouse_button(GLFWwindow* window, int button, int act, int mods) {
        get_instance().mouse_button_impl(window, button, act, mods);
    }
    static void scroll(GLFWwindow* window, double xoffset, double yoffset) {
        get_instance().scroll_impl(window, xoffset, yoffset);
    }

private:

    void keyboard_impl(GLFWwindow* window, int key, int scancode, int act, int mods);
    void mouse_move_impl(GLFWwindow* window, double xpos, double ypos);
    void mouse_button_impl(GLFWwindow* window, int button, int act, int mods);
    void scroll_impl(GLFWwindow* window, double xoffset, double yoffset);

    bool button_left = false;
    bool button_middle = false;
    bool button_right = false;
    double lastx = 0;
    double lasty = 0;

    mjModel* m = NULL;
    mjData* d = NULL;
    mjvScene* scn;
    mjvCamera* cam;
    mjvOption* vopt;
    mjrContext* con;
};
#endif // INPUT_H