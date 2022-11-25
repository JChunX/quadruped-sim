#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <mujoco/mujoco.h>
#include <drake/solvers/mathematical_program.h>
#include <Eigen/Dense>
#include <Eigen/Sparse>

class Controller {
public:
    Controller();
    ~Controller();

    virtual void control(const mjModel* m, mjData* d) = 0;

    int controller_frequency = 100;
};

#endif // CONTROLLER_H