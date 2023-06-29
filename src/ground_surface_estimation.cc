//
// Created by czy on 23-6-28.
//

#include "ground_surface_estimation.h"
#include "algorithm/surface_estimate_sac.h"

GroundEstimator::GroundEstimator(const GroundParam& param) {
  /// 测试: sac
  estimator_ = std::make_unique<SurfaceEstimateSac>(param.sac_param, param.estimate_param);
  param_ = param;
}
