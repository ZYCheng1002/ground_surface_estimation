//
// Created by czy on 23-6-28.
//

#ifndef GROUND_SURFACE_ESTIMATION_GROUND_SURFACE_ESTIMATION_H
#define GROUND_SURFACE_ESTIMATION_GROUND_SURFACE_ESTIMATION_H
#include "algorithm/surface_estimate_base.h"
#include <memory>


class GroundEstimator {
  GroundEstimator(const EstimateParam&);

  virtual ~GroundEstimator() = default;

  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  virtual void Estimate() = 0;

  virtual void AddMeasurements(const Estimator::Measurements&) = 0;

 protected:
  EstimateParam param_;
  std::unique_ptr<Estimator> estimator_ = nullptr;
};

#endif  // GROUND_SURFACE_ESTIMATION_GROUND_SURFACE_ESTIMATION_H
