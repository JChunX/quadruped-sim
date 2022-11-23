#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

#include <GLFW/glfw3.h>

class InputController
{
public:
    InputController();
    ~InputController();

    void keyboard(GLFWwindow* window, mjModel* m, mjData* d, int key, int scancode, int action, int mods);

    void mouse_button(GLFWwindow* window, int button, int action, int mods);

    void mouse_move(GLFWwindow* window, mjModel* m, mjvScene* scn, mjvCamera* cam, double xpos, double ypos);

    void scroll(GLFWwindow* window, mjModel* m, mjvScene* scn, mjvCamera* cam, double xoffset, double yoffset);

    bool button_left = false;
    bool button_middle = false;
    bool button_right = false;
    double lastx = 0;
    double lasty = 0;
};
