//
// Created by czy on 23-6-28.
//

#include "ground_surface_estimation.h"

#include "algorithm/surface_estimate_sac.h"
#include "algorithm/surface_estimate_polynominal.h"

GroundEstimator::GroundEstimator(const GroundParam& param) {
  param_ = param;
  estimator_ = CreateImpl(param_.method);
}

GroundSurface::Ptr GroundEstimator::GetGroundSurface() const { return estimator_->GetGroundSurface(); }

bool GroundEstimator::HasMeasurements() const { return estimator_->HasMeasurements(); }

void GroundEstimator::ClearMeasurements() { estimator_->ClearMeasurements(); }

const Measurements& GroundEstimator::GetMeasurements() const { return estimator_->GetMeasurements(); }

const Weights& GroundEstimator::GetWeights() const { return estimator_->GetWeights(); }

const float& GroundEstimator::GetMu() const { return mu_; }

void GroundEstimator::Reset() {
  mu_ = param_.mu;
  ClearMeasurements();
  estimator_.reset();
}

std::unique_ptr<Estimator> GroundEstimator::CreateImpl(const SurfaceMethod& method){
  // todo: other surface method
  switch (method) {
    case SurfaceMethod::plane_sac:
      return std::make_unique<SurfaceEstimateSac>(param_.sac_param, param_.estimate_param);
    case SurfaceMethod::polynomial_ceres:
      return std::make_unique<SurfaceEstimatePoly>(param_.ceres_param, param_.estimate_param);
    default:
      return nullptr;
  }
}
