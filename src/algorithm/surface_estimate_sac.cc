//
// Created by czy on 23-6-26.
//

#include "surface_estimate_sac.h"

#include <pcl/common/angles.h>
SurfaceEstimateSac::SurfaceEstimateSac(const SacParam& p,
                                       const EstimateParam& p_common)
    : Estimator(p_common), sac_param_(p) {
  segmentation_.setOptimizeCoefficients(p.optimize_coefficients);
  segmentation_.setModelType(pcl::SACMODEL_PLANE);
  segmentation_.setAxis(p_common.plane_initial.normal());
  segmentation_.setDistanceThreshold(p.inlier_threshold);
  segmentation_.setEpsAngle(pcl::deg2rad(p.eps_angle));
  segmentation_.setMaxIterations(p.max_iterations);
  segmentation_.setProbability(p.probability);
  segmentation_.setInputCloud(this->cloud_);
  Reset();
}

void SurfaceEstimateSac::AddMeasurements_(int num_measurements) {
  cloud_->resize(measurements_.cols());
  cloud_->getMatrixXfMap().topRows<3>().rightCols(num_measurements) = measurements_.rightCols(num_measurements);
}

void SurfaceEstimateSac::Estimate() {
  pcl::PointIndices indices;
  pcl::ModelCoefficients coefficients;
  segmentation_.segment(indices, coefficients);
  const auto& p{coefficients.values};
  plane_ = Plane{Eigen::Vector3f{p[0], p[1], p[2]}, p[3]};
}

void SurfaceEstimateSac::ClearMeasurements_() {
  cloud_->clear();
}

void SurfaceEstimateSac::Reset() {
  ClearMeasurements();
  plane_ = Estimator::estimate_param_.plane_initial;
}