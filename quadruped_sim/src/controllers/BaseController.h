#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H

#include <mujoco/mujoco.h>
#include <vector>
#include "Controller.h"

/*
BaseController's child classes (eg. QuadrupedController) acts as the entrypoint for all downstream controllers.
*/


class BaseController
{

public:
    BaseController();
    ~BaseController();

    static BaseController& get_instance()
    {
        static BaseController instance;
        return instance;
    }

    static void controller(const mjModel* m, mjData* d) {
        get_instance().controller_impl(m, d);
    }

    void add_controller();

    std::vector<Controller> controllers;

private:

    void controller_impl(const mjModel* m, mjData* d);

};

#endif // BASECONTROLLER_H