//
// Created by czy on 23-7-2.
//

#ifndef GROUND_SURFACE_ESTIMATION_SURFACE_ESTIMATE_POINT_TO_PLANE_H
#define GROUND_SURFACE_ESTIMATION_SURFACE_ESTIMATE_POINT_TO_PLANE_H
#include "base_param.h"
#include "ceres_param.h"
#include "surface_estimate_base.h"

///@brief: 使用点到平面的距离构建最小二乘优化平面参数
///@note: d = (n[0]*x + n[1]*y + n[2]*z + n[3]) / sqrt(n[0]*n[0] + n[1]*n[1] + n[2]*n[2])
class SurfaceEstimatePP final : public Estimator {
 public:
  SurfaceEstimatePP(const CeresParam&, const EstimateParam&);
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
  void Estimate() final;
  std::unique_ptr<GroundSurface> GetGroundSurface() const final;
  void Reset() override;

 private:
  void AddMeasurements_(int) final;
  void ClearMeasurements_() final;
  CeresParam ceres_param_;
  std::unique_ptr<ceres::Problem> problem_ = nullptr;
  Plane<double> plane_ = Plane<double>(0.0f, 0.0f, 0.0f, 1.0f);
};

#endif  // GROUND_SURFACE_ESTIMATION_SURFACE_ESTIMATE_POINT_TO_PLANE_H
