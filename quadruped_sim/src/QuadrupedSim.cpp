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
        std::cout << "======" << std::endl;
        update();
        std::cout << "render" << std::endl;
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

    Input &input = Input::getInstance();
    input.set_mj_variables(m, d, &cam, &vopt, &scn, &con);

    // install GLFW mouse and keyboard callbacks
    glfwSetKeyCallback(window, &Input::keyboard);
    glfwSetCursorPosCallback(window, &Input::mouse_move);
    glfwSetMouseButtonCallback(window, &Input::mouse_button);
    glfwSetScrollCallback(window, &Input::scroll);
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
    mjr_freeContext(&con);

    // free MuJoCo model and data
    mj_deleteData(d);
    mj_deleteModel(m);

//terminate GLFW (crashes with Linux NVidia drivers)

#if defined(__APPLE__) || defined(_WIN32)
  glfwTerminate();
#endif

    return;
}

void QuadrupedSim::load_model_and_data(std::string model_path) {
    std::cout << "Loading model from " << model_path << std::endl;
    // load and compile model
    char error[1000] = "Could not load binary model";
    if (model_path.length()>4 && !std::string(model_path.end()-4, model_path.end()).compare(".mjb")) {
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

