//
// Created by czy on 23-7-1.
//

#ifndef GROUND_SURFACE_ESTIMATION_SURFACE_ESTIMATE_POLYNOMINAL_H
#define GROUND_SURFACE_ESTIMATION_SURFACE_ESTIMATE_POLYNOMINAL_H
#include "base_param.h"
#include "ceres_param.h"
#include "common/system_common.h"
#include "surface_estimate_base.h"

class SurfaceEstimatePoly final : public Estimator {
 public:
  SurfaceEstimatePoly(const CeresParam&, const EstimateParam&);
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
  void Estimate() final;
  std::unique_ptr<GroundSurface> GetGroundSurface() const final;
  void Reset() override;
 private:
  void AddMeasurements_(int) final;
  void ClearMeasurements_() final;

  CeresParam ceres_param_;
  std::unique_ptr<ceres::Problem> problem_ = nullptr;
  Representation<double> poly_ceres_{Representation<double>::Zero()};
};

#endif  // GROUND_SURFACE_ESTIMATION_SURFACE_ESTIMATE_POLYNOMINAL_H
