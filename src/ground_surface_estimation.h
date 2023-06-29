//
// Created by czy on 23-6-28.
//

#ifndef GROUND_SURFACE_ESTIMATION_GROUND_SURFACE_ESTIMATION_H
#define GROUND_SURFACE_ESTIMATION_GROUND_SURFACE_ESTIMATION_H
#include <memory>

#include "algorithm/surface_estimate_base.h"
#include "ground_paramters.h"

class GroundEstimator {
 public:
  GroundEstimator(const GroundParam&);

  virtual ~GroundEstimator() = default;

  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  virtual void Estimate() = 0;

  virtual void AddMeasurements(const Estimator::Measurements&) = 0;

 protected:
  GroundParam param_;
  std::unique_ptr<Estimator> estimator_ = nullptr;
  float mu_{1};
};

#endif  // GROUND_SURFACE_ESTIMATION_GROUND_SURFACE_ESTIMATION_H
