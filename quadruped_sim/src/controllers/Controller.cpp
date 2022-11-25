#include "Controller.h"
#include <iostream>

Controller::Controller()
{
}

Controller::~Controller()
{
}

void Controller::control(const mjModel* m, mjData* d)
{
    std::cout << "Controller::control" << std::endl;
}