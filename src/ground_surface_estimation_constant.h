//
// Created by czy on 2023/6/30.
//

#ifndef GROUND_SURFACE_ESTIMATION_GROUND_SURFACE_ESTIMATION_CONSTANT_H
#define GROUND_SURFACE_ESTIMATION_GROUND_SURFACE_ESTIMATION_CONSTANT_H
#include "ground_surface_estimation.h"
class GroundEstimatorCon: public GroundEstimator {
 public:
  GroundEstimatorCon(const GroundParam&);

  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  void AddMeasurements(const Measurements&) final;

  void Estimate() final;
};

#endif  // GROUND_SURFACE_ESTIMATION_GROUND_SURFACE_ESTIMATION_CONSTANT_H
