//
// Created by czy on 23-6-24.
//



#ifndef GROUND_SURFACE_ESTIMATION_COMMON_PARAM_H
#define GROUND_SURFACE_ESTIMATION_COMMON_PARAM_H
#include <Eigen/Geometry>
#include "common/global_config.h"
struct EstimateParam {
  void Init(){
    auto yaml_io = GlobalConfig::Get();
    plane_normal_x      = yaml_io->GetValue<float>("common", "plane_normal_x");
    plane_normal_y      = yaml_io->GetValue<float>("common", "plane_normal_y");
    plane_normal_z      = yaml_io->GetValue<float>("common", "plane_normal_z");
    plane_offset        = yaml_io->GetValue<float>("common", "plane_offset");
    range_min_x         = yaml_io->GetValue<float>("common", "range_min_x");
    range_min_y         = yaml_io->GetValue<float>("common", "range_min_y");
    range_max_x         = yaml_io->GetValue<float>("common", "range_max_x");
    range_max_y         = yaml_io->GetValue<float>("common", "range_max_y");

    // 通过法向量和一个点初始化超平面
    Eigen::Vector3f normal(plane_normal_x, plane_normal_y, plane_normal_z);
    Eigen::Vector3f point(0.0f, 0.0f, plane_offset);
    plane_initial = Eigen::Hyperplane<float, 3>(normal, point);
    // 初始化包围框
    Eigen::Vector2f min_point(range_min_x, range_min_y);
    Eigen::Vector2f max_point(range_max_x, range_max_y);
    range = Eigen::AlignedBox2f(min_point, max_point);
  }

  float plane_normal_x                  = 0;
  float plane_normal_y                  = 0;
  float plane_normal_z                  = 1;
  float plane_offset                    = 0;
  float range_min_x                     = -50;
  float range_min_y                     = -50;
  float range_max_x                     = 100;
  float range_max_y                     = 50;

  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
  // 超平面(三维平面)
  Eigen::Hyperplane<float, 3> plane_initial{Eigen::Vector3f::UnitZ(), 0};
  // 二维的轴对齐包围框
  Eigen::AlignedBox2f range{Eigen::Vector2f::Constant(-100), Eigen::Vector2f::Constant(100)};
};

#endif  // GROUND_SURFACE_ESTIMATION_COMMON_PARAM_H
