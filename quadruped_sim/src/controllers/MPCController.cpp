#include "MPCController.h"

/*
Model-Predictive Control for approximated quadruped

Goal:
Find reaction forces given pre-defined contacts and body trajectory
*/

MPCController::MPCController()
    : (N, dt, Q, R)
{
    controller_frequency = 20;
}

MPCController::~MPCController()
{
}

void MPCController::control(const mjModel* m, mjData* d)
{
    std::cout << "MPCController::control" << std::endl;
}