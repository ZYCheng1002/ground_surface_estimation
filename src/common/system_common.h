//
// Created by idriver-czy on 2023/6/30.
//

#ifndef GROUND_SURFACE_ESTIMATION_SYSTEM_COMMON_H
#define GROUND_SURFACE_ESTIMATION_SYSTEM_COMMON_H
enum class SurfaceMethod {
  plane_ceres             = 0,
  plane_sac               = 1,
  uniform_b_spline_ceres  = 2,
  uniform_b_spline_eigen  = 3,
  polynomial_ceres        = 4,
  none
};

enum class GroundMethod {
  constant                = 0,
  geman_mcclure           = 1,
  truncated_least_squares = 2
};

/// 多项式形式的平面参数
template <typename T>
using Representation = Eigen::Matrix<T, 8, 1>;

/// 点到平面的平面参数 Ax + By + Cz + D = 0
template <typename T>
using Plane = Eigen::Matrix<T, 4, 1>;


#endif  // GROUND_SURFACE_ESTIMATION_SYSTEM_COMMON_H
