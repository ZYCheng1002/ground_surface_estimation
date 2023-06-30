//
// Created by czy on 2023/6/29.
//

#ifndef GROUND_SURFACE_ESTIMATION_GROUND_PARAMTERS_H
#define GROUND_SURFACE_ESTIMATION_GROUND_PARAMTERS_H
#include "algorithm/base_param.h"
#include "algorithm/sac_param.h"
#include "common/system_common.h"

struct GroundParam {
  void Init() {
    auto yaml_io = GlobalConfig::Get();
    method              = static_cast<SurfaceMethod>(yaml_io->GetValue<int>("ground_surface_estimation", "method"));
    num_iterations      = yaml_io->GetValue<int>("ground_surface_estimation", "num_iterations");
    distance_threshold  = yaml_io->GetValue<float>("ground_surface_estimation", "distance_threshold");
    mu                  = yaml_io->GetValue<int>("ground_surface_estimation", "mu");
    asymmetry_ratio     = yaml_io->GetValue<int>("ground_surface_estimation", "asymmetry_ratio");

    estimate_param.Init();
    sac_param.Init();
  }

  EstimateParam estimate_param;
  SacParam sac_param;
  SurfaceMethod method      = SurfaceMethod::plane_sac;
  int num_iterations        = 3;
  float distance_threshold  = 1;
  float mu                  = 1;
  float asymmetry_ratio     = 1;


};

#endif  // GROUND_SURFACE_ESTIMATION_GROUND_PARAMTERS_H
