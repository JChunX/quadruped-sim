#include"QuadrupedSim.h"

/*
Simulator entrypoint
*/

QuadrupedSim::QuadrupedSim() {
    init();
}

QuadrupedSim::~QuadrupedSim() {
    
}

void QuadrupedSim::run() {
    while (!glfwWindowShouldClose(window)) {
        update();
        render();
    }
    shutdown();
}

void QuadrupedSim::init() {
    load_model_and_data("models/xml/mini_cheetah.xml");
    if (!glfwInit()) {
        mju_error("Could not initialize GLFW");
    }

    // create window, make OpenGL context current, request v-sync
    window = glfwCreateWindow(1200, 900, "Demo", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // initialize visualization data structures
    mjv_defaultCamera(&cam);
    mjv_defaultOption(&vopt);
    mjv_defaultScene(&scn);
    mjr_defaultContext(&con);

    // create scene and context
    mjv_makeScene(m, &scn, 2000);
    mjr_makeContext(m, &con, mjFONTSCALE_150);

    // install GLFW mouse and keyboard callbacks
    glfwSetKeyCallback(window, &QuadrupedSim::keyboard);
    glfwSetCursorPosCallback(window, &QuadrupedSim::mouse_move);
    glfwSetMouseButtonCallback(window, &QuadrupedSim::mouse_button);
    glfwSetScrollCallback(window, &QuadrupedSim::scroll);
}

void QuadrupedSim::update() {
    mjtNum simstart = d->time;
    while (d->time - simstart < 0.01) {
        mj_step(m, d);
    }
}

void QuadrupedSim::render() {
    // get framebuffer viewport
    mjrRect viewport = {0, 0, 0, 0};
    glfwGetFramebufferSize(window, &viewport.width, &viewport.height);

    // update scene and render
    mjv_updateScene(m, d, &vopt, NULL, &cam, mjCAT_ALL, &scn);
    mjr_render(viewport, &scn, &con);

    // swap OpenGL buffers (blocking call due to v-sync)
    glfwSwapBuffers(window);

    // process pending GUI events, call GLFW callbacks
    glfwPollEvents();
}

void QuadrupedSim::shutdown() {
  //free visualization storage
  mjv_freeScene(&scn);
  //mjr_freeContext(&con);

  // free MuJoCo model and data
  //mj_deleteData(d);
  //mj_deleteModel(m);

  // terminate GLFW (crashes with Linux NVidia drivers)
//#if defined(__APPLE__) || defined(_WIN32)
  //glfwTerminate();
//#endif

    return;
}

void QuadrupedSim::load_model_and_data(std::string model_path) {
    // load and compile model
    char error[1000] = "Could not load binary model";
    if (model_path.length()>4 && !std::strcmp(model_path.c_str() + model_path.length() - 4, ".mjb")) {
        m = mj_loadModel(model_path.c_str(), 0);
    } else {
        m = mj_loadXML(model_path.c_str(), 0, error, 1000);
    }
    if (!m) {
        mju_error_s("Load model error: %s", error);
    }

    // make data
    d = mj_makeData(m);
}

void QuadrupedSim::keyboard_impl(GLFWwindow* window, int key, int scancode, int act, int mods) {
      // backspace: reset simulation
    if (act==GLFW_PRESS && key==GLFW_KEY_BACKSPACE) {
        mj_resetData(m, d);
        mj_forward(m, d);
    }
}

void QuadrupedSim::mouse_button_impl(GLFWwindow* window, int button, int act, int mods) {
  // update button state
  button_left = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)==GLFW_PRESS);
  button_middle = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE)==GLFW_PRESS);
  button_right = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT)==GLFW_PRESS);

  // update mouse position
  glfwGetCursorPos(window, &lastx, &lasty);
}

void QuadrupedSim::mouse_move_impl(GLFWwindow* window, double xpos, double ypos) {
    // no buttons down: nothing to do
    if (!button_left && !button_middle && !button_right) {
        return;
    }

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
    mjv_moveCamera(m, act, dx/height, dy/height, &scn, &cam);
}

void QuadrupedSim::scroll_impl(GLFWwindow* window, double xoffset, double yoffset) {
    // emulate vertical mouse motion = 5% of window height
    mjv_moveCamera(m, mjMOUSE_ZOOM, 0, -0.05*yoffset, &scn, &cam);
}