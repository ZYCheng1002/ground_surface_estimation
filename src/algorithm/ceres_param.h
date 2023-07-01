//
// Created by czy on 23-7-1.
//

#ifndef GROUND_SURFACE_ESTIMATION_CERES_PARAM_H
#define GROUND_SURFACE_ESTIMATION_CERES_PARAM_H

#include <ceres/problem.h>
#include <ceres/solver.h>
struct CeresParam {
  ceres::Solver::Options solver;
  ceres::Problem::Options problem;
};

#endif  // GROUND_SURFACE_ESTIMATION_CERES_PARAM_H
