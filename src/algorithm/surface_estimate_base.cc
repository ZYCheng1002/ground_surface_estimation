//
// Created by czy on 23-6-24.
//

#include "surface_estimate_base.h"

#include <glog/logging.h>

Estimator::Estimator(const EstimateParam& param): estimate_param_(param) {}

void Estimator::AddMeasurements(const Measurements& measurements) {
  AddMeasurements(measurements, Eigen::VectorXf::Ones(measurements.cols()));
}

void Estimator::AddMeasurements(const Estimator::Measurements& measurements, const Estimator::Weights& weights) {
  CHECK_EQ(measurements.cols(), weights.size());
  const auto new_size{measurements_.cols() + measurements.cols()};
  measurements_.conservativeResize(3, new_size);
  measurements_.rightCols(measurements.cols()) = measurements;
  weights_.conservativeResize(new_size);
  weights_.tail(measurements.cols()) = weights;
  // addMeasurements_(measurements.cols());
}