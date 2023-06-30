//
// Created by czy on 23-6-24.
//

#include "surface_estimate_base.h"

#include <glog/logging.h>

Estimator::Estimator(const EstimateParam& param) : estimate_param_(param) {}

Estimator::~Estimator() = default;

void Estimator::AddMeasurements(const Measurements& measurements) {
  AddMeasurements(measurements, Eigen::VectorXf::Ones(measurements.cols()));
}

void Estimator::AddMeasurements(const Measurements& measurements,
                                const Weights& weights) {
  CHECK_EQ(measurements.cols(), weights.size());
  const auto new_size{measurements_.cols() + measurements.cols()};
  measurements_.conservativeResize(3, new_size);
  measurements_.rightCols(measurements.cols()) = measurements;
  weights_.conservativeResize(new_size);
  weights_.tail(measurements.cols()) = weights;
  AddMeasurements_(measurements.cols());
}

const Measurements& Estimator::GetMeasurements() const {
  return measurements_;
}

const Weights& Estimator::GetWeights() const { return weights_; }

void Estimator::SetWeights(const Weights& weights) {
  CHECK_EQ(weights.size(), weights_.size());
  weights_ = weights;
  SetWeights_();
}

void Estimator::SetParam(const EstimateParam& param) {
  estimate_param_ = param;
  Reset();
}

const EstimateParam& Estimator::GetParameters() const {
  return estimate_param_;
}

bool Estimator::HasMeasurements() const {
  return static_cast<bool>(measurements_.cols());
}

void Estimator::ClearMeasurements() {
  measurements_.resize(3, 0);
  weights_.resize(0);
  ClearMeasurements_();
}

void Estimator::Reset() {}

void Estimator::SetWeights_() {}