#ifndef QUADRUPEDCONTROLLER_H
#define QUADRUPEDCONTROLLER_H

#include "BaseController.h"
#include "TrajectoryGenerator.h"
#include "MPCController.h"
#include "ContactScheduler.h"
#include <Eigen/Dense>
#include <math.h>

/*
QuadrupedController is the entrypoint for all downstream quadruped controllers.
*/

class QuadrupedController : public BaseController
{
public:
    QuadrupedController();
    ~QuadrupedController();

private:
    void controller_impl(const mjModel* m, mjData* d);

    eigen::MatrixXd shoulder_positions = eigen::MatrixXd::Zero(4, 3);

    eigen::VectorXd body_cmd_vel = eigen::VectorXd::Zero(2);

    double omega = M_PI / 20;
    int N = 20;
    double dt = 0.1;
    eigen::MatrixXd x_ref = eigen::MatrixXd::Zero(N, 12);

    TrajectoryGenerator traj_gen;
    MPCController mpc_controller;
    ContactScheduler contact_scheduler;
};

#endif // QUADRUPEDCONTROLLER_H