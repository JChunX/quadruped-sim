#include "BaseController.h"
#include <iostream>

BaseController::BaseController()
{
}

BaseController::~BaseController()
{
}

void BaseController::add_controller(Controller& controller)
{
    controllers.push_back(controller);
}

void BaseController::controller_impl(const mjModel* m, mjData* d)
{
    std::cout << "BaseController::controller_impl" << std::endl;

    // get time
    double t = d->time;

    // for all controllers, call control at specified frequency
    for (int i = 0; i < controllers.size(); i++) {
        int controller_frequency = controllers[i].controller_frequency;
        if (t * controller_frequency - (int)(t * controller_frequency) < 1e-6) {
            controllers[i].control(m, d);
        }
    }

    for (int i = 0; i < m->nu; i++) {
        d->ctrl[i] = 10;
    }
}