//
// Created by czy on 2023/6/30.
//

#include "ground_surface_estimation_constant.h"

GroundEstimatorCon::GroundEstimatorCon(const GroundParam& param) : GroundEstimator(param) {}

void GroundEstimatorCon::AddMeasurements(const Measurements& measurements) {
  estimator_->AddMeasurements(measurements);
}

void GroundEstimatorCon::Estimate() {
  for (int i = 0; i < param_.num_iterations; ++i) {
    estimator_->Estimate();
  }
}