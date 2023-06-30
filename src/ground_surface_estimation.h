//
// Created by czy on 23-6-28.
//

#ifndef GROUND_SURFACE_ESTIMATION_GROUND_SURFACE_ESTIMATION_H
#define GROUND_SURFACE_ESTIMATION_GROUND_SURFACE_ESTIMATION_H
#include <memory>

#include "algorithm/surface_estimate_base.h"
#include "common/system_common.h"
#include "ground_paramters.h"

class GroundEstimator {
 public:
  explicit GroundEstimator(const GroundParam&);

  virtual ~GroundEstimator() = default;

  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  virtual void Estimate() = 0;

  virtual void AddMeasurements(const Measurements&) = 0;

  GroundSurface::Ptr GetGroundSurface() const;

  virtual bool HasMeasurements() const;

  virtual void ClearMeasurements();

  const Measurements& GetMeasurements() const;

  const Weights& GetWeights() const;

  const float& GetMu() const;

  void Reset();

 protected:
  std::unique_ptr<Estimator> CreateImpl(const SurfaceMethod& method);

 protected:
  GroundParam param_;
  std::unique_ptr<Estimator> estimator_ = nullptr;
  float mu_{1};
};

#endif  // GROUND_SURFACE_ESTIMATION_GROUND_SURFACE_ESTIMATION_H
