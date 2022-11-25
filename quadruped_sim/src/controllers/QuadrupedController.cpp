#include "QuadrupedController.h"

QuadrupedController::QuadrupedController()
{
    std::cout << "QuadrupedController::QuadrupedController" << std::endl;
}

QuadrupedController::~QuadrupedController()
{
}

void QuadrupedController::controller_impl(const mjModel* m, mjData* d)
{
    std::cout << "QuadrupedController::controller_impl" << std::endl;
}