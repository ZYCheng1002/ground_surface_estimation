//
// Created by czy on 2023/6/29.
//

#ifndef GROUND_SURFACE_ESTIMATION_GROUND_PARAMTERS_H
#define GROUND_SURFACE_ESTIMATION_GROUND_PARAMTERS_H
#include "algorithm/sac_param.h"
#include "algorithm/base_param.h"

struct GroundParam {
  EstimateParam estimate_param;
  SacParam sac_param;
};

#endif  // GROUND_SURFACE_ESTIMATION_GROUND_PARAMTERS_H
