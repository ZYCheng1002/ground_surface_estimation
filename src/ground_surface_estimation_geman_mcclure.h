//
// Created by idriver-czy on 2023/6/29.
//

#ifndef GROUND_SURFACE_ESTIMATION_GROUND_SURFACE_ESTIMATION_GEMAN_MCCLURE_H
#define GROUND_SURFACE_ESTIMATION_GROUND_SURFACE_ESTIMATION_GEMAN_MCCLURE_H
#include "ground_surface_estimation.h"
class GroundEstimatorGM : public GroundEstimator{
 public:
  GroundEstimatorGM(const GroundParam&);

  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  void AddMeasurements(const Estimator::Measurements&) final;

  void Estimate() final;
};

#endif  // GROUND_SURFACE_ESTIMATION_GROUND_SURFACE_ESTIMATION_GEMAN_MCCLURE_H
