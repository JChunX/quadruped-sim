#include"QuadrupedSim.h"

/*
Simulator entrypoint
*/

QuadrupedSim::QuadrupedSim() {
    init();
}

QuadrupedSim::~QuadrupedSim() {
    shutdown();
}

void QuadrupedSim::run() {
    while (!glfwWindowShouldClose(window)) {
        update();
        render();
    }
}

void QuadrupedSim::init() {
    load_model_and_data("xml/mini_cheetah.xml");
    if (!glfwInit()) {
        mju_error("Could not initialize GLFW");
    }
    input_controller = InputController();

    // create window, make OpenGL context current, request v-sync
    window = glfwCreateWindow(1200, 900, "Demo", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // initialize visualization data structures
    mjv_defaultCamera(&cam);
    mjv_defaultOption(&opt);
    mjv_defaultScene(&scn);
    mjr_defaultContext(&con);

    // create scene and context
    mjv_makeScene(m, &scn, 2000);
    mjr_makeContext(m, &con, mjFONTSCALE_150);

    // install GLFW mouse and keyboard callbacks
    glfwSetKeyCallback(window, input_controller.keyboard);
    glfwSetCursorPosCallback(window, input_controller.mouse_move);
    glfwSetMouseButtonCallback(window, input_controller.mouse_button);
    glfwSetScrollCallback(window, input_controller.scroll);
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
    mjv_updateScene(m, d, &opt, NULL, &cam, mjCAT_ALL, &scn);
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

  // terminate GLFW (crashes with Linux NVidia drivers)
#if defined(__APPLE__) || defined(_WIN32)
  glfwTerminate();
#endif

    return;
}

void QuadrupedSim::load_model_and_data(std::string model_path) {
    // load and compile model
    char error[1000] = "Could not load binary model";
    if (std::strlen(model_path)>4 && !std::strcmp(model_path+std::strlen(model_path)-4, ".mjb")) {
        m = mj_loadModel(model_path, 0);
    } else {
        m = mj_loadXML(model_path, 0, error, 1000);
    }
    if (!m) {
        mju_error_s("Load model error: %s", error);
    }

    // make data
    d = mj_makeData(m);
}