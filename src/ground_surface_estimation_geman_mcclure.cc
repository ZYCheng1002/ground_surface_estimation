//
// Created by idriver-czy on 2023/6/29.
//

#include "ground_surface_estimation_geman_mcclure.h"

GroundEstimatorGM::GroundEstimatorGM(const GroundParam& ground_param)
    : GroundEstimator(ground_param) {

}

void GroundEstimatorGM::AddMeasurements(const Measurements& measurements) {
  estimator_->AddMeasurements(measurements);
}

void GroundEstimatorGM::Estimate() {
  mu_ = param_.mu;
  for (int i = 0; i < param_.num_iterations; ++i) {
    //TODO: LOG
    estimator_->Estimate();
    mu_ /= 1.4;
    // todo: estimator_->SetWeights();
  }
}