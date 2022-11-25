#ifndef MPCCONTROLLER_H
#define MPCCONTROLLER_H

#include "Controller.h"
#include <drake/solvers/osqp/osqp_solver.h>


class MPCController : public Controller {
public:
    MPCController(int N, double dt, Eigen::MatrixXd Q, Eigen::MatrixXd R);
    ~MPCController();

    void control(const mjModel* m, mjData* d);

    int N;
    double dt;
    Eigen::MatrixXd Q;
    Eigen::MatrixXd R;


private:
    void discrete_time_dynamics(const Eigen::VectorXd& x_ref_k, const Eigen::VectorXd& r_k);

    void add_initial_constraints(Eigen::MatrixXd& x, Eigen::MatrixXd& x_ref);

    void add_final_constraints(Eigen::MatrixXd& x, Eigen::MatrixXd& x_ref);

    Eigen::MatrixXd get_fk(std::vector<int>& indices, Eigen::VectorXd& f);

    void add_dynamic_constraints(Eigen::MatrixXd& x, Eigen::MatrixXd& f, Eigen::MatrixXd& x_ref, Eigen::MatrixXd& r_ref, Eigen::MatrixXd& fsm);

    void add_contact_constraints(Eigen::MatrixXd& f, Eigen::MatrixXd& fsm);

    void add_cost(Eigen::MatrixXd& x, Eigen::MatrixXd& x_ref, Eigen::MatrixXd& f);

    Eigen::MatrixXd compute_mpc(Eigen::MatrixXd& x_ref, Eigen::MatrixXd& r_ref, Eigen::MatrixXd& fsm);

    drake::solvers::MathematicalProgram prog;
};
#endif // MPCCONTROLLER_H