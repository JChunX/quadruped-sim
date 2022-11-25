#include"QuadrupedSim.h"

QuadrupedSim::QuadrupedSim(std::string model_path)
 : model_path(model_path){
    initialize();
}

QuadrupedSim::~QuadrupedSim() 
{
    
}

void QuadrupedSim::initialize() 
{
    load_model_and_data();
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

    Input &input = Input::get_instance();
    input.set_mj_variables(m, d, &cam, &vopt, &scn, &con);

    // install GLFW mouse and keyboard callbacks
    glfwSetKeyCallback(window, &Input::keyboard);
    glfwSetCursorPosCallback(window, &Input::mouse_move);
    glfwSetMouseButtonCallback(window, &Input::mouse_button);
    glfwSetScrollCallback(window, &Input::scroll);

    BaseController &base_controller = BaseController::get_instance();
    base_controller.add_controller();
    mjcb_control = &BaseController::controller;
}

void QuadrupedSim::step() 
{
    for (int i=0; i<num_substeps; i++)
    {
        mj_step(m, d);
    }
}

void QuadrupedSim::render() 
{
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

void QuadrupedSim::shutdown() 
{
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

void QuadrupedSim::load_model_and_data() 
{
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

