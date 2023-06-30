//
// Created by czy on 23-6-24.
//

#ifndef GROUND_SURFACE_ESTIMATION_SAC_PARAM_H
#define GROUND_SURFACE_ESTIMATION_SAC_PARAM_H
#include "common/global_config.h"

struct SacParam {
  void Init(){
    auto yaml_io = GlobalConfig::Get();

    optimize_coefficients     = yaml_io->GetValue<bool>("sac", "optimize_coefficients");
    inlier_threshold          = yaml_io->GetValue<float>("sac", "inlier_threshold");
    eps_angle                 = yaml_io->GetValue<float>("sac", "eps_angle");
    max_iterations            = yaml_io->GetValue<int>("sac", "eps_angle");
    probability               = yaml_io->GetValue<float>("sac", "probability");
  }
  bool optimize_coefficients       = true;
  float inlier_threshold           = 0.2;
  float eps_angle                  = 0.01;
  size_t max_iterations            = 20;
    float probability              = 0.99;
};

#endif  // GROUND_SURFACE_ESTIMATION_SAC_PARAM_H
