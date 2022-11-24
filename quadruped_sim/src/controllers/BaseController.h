#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <mujoco/mujoco.h>

class BaseController
{
/*
Base controller class
*/

public:
    Controller();
    ~Controller();

    static BaseController& getInstance()
    {
        static BaseController instance;
        return instance;
    }

    static void controller(const mjModel* m, mjData* d) {
        getInstance().controller_impl(m, d);
    }

private:

    void controller_impl(const mjModel* m, mjData* d);

};

#endif // CONTROLLER_H