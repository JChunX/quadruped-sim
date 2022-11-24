#include "Input.h"

Input::Input() {

}

Input::~Input() {

}

void Input::keyboard_impl(GLFWwindow* window, int key, int scancode, int act, int mods) {
    std::cout << "key: " << key << std::endl;
      // backspace: reset simulation
    if (act==GLFW_PRESS && key==GLFW_KEY_BACKSPACE) {
        mj_resetData(m, d);
        mj_forward(m, d);
    }
}

void Input::mouse_button_impl(GLFWwindow* window, int button, int act, int mods) {
    std::cout << "mouse button: " << button << std::endl;
    // update button state
    button_left = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)==GLFW_PRESS);
    button_middle = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE)==GLFW_PRESS);
    button_right = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT)==GLFW_PRESS);

    // update mouse position
    glfwGetCursorPos(window, &lastx, &lasty);
}

void Input::mouse_move_impl(GLFWwindow* window, double xpos, double ypos) {
    std::cout << "mouse move: " << xpos << ", " << ypos << std::endl;
    // no buttons down: nothing to do
    if (!button_left && !button_middle && !button_right) {
        return;
    }

    std::cout << "mouse has button down" << std::endl;
    // compute mouse displacement, save
    double dx = xpos - lastx;
    double dy = ypos - lasty;
    lastx = xpos;
    lasty = ypos;

    // get current window size
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    // get shift key state
    bool mod_shift = (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)       
                    ==GLFW_PRESS ||
                    glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)==GLFW_PRESS);

    // determine act based on mouse button
    mjtMouse act;
    if (button_right) {
        act = mod_shift ? mjMOUSE_MOVE_H : mjMOUSE_MOVE_V;
    } else if (button_left) {
        act = mod_shift ? mjMOUSE_ROTATE_H : mjMOUSE_ROTATE_V;
    } else {
        act = mjMOUSE_ZOOM;
    }

    // move camera
    mjv_moveCamera(m, act, dx/height, dy/height, scn, cam);
}

void Input::scroll_impl(GLFWwindow* window, double xoffset, double yoffset) {
    std::cout << "scroll: " << xoffset << ", " << yoffset << std::endl;
    // emulate vertical mouse motion = 5% of window height
    mjv_moveCamera(m, mjMOUSE_ZOOM, 0, -0.05*yoffset, scn, cam);
}