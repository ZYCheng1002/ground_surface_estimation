//
// Created by czy on 23-6-24.
//

#include <Eigen/Geometry>

#ifndef GROUND_SURFACE_ESTIMATION_COMMON_PARAM_H
#define GROUND_SURFACE_ESTIMATION_COMMON_PARAM_H

struct EstimateParam {
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  Eigen::Hyperplane<float, 3> plane_initial{Eigen::Vector3f::UnitZ(), 0};
  Eigen::AlignedBox2f range{Eigen::Vector2f::Constant(-100), Eigen::Vector2f::Constant(100)};
};

#endif  // GROUND_SURFACE_ESTIMATION_COMMON_PARAM_H
