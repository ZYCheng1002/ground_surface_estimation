//
// Created by czy on 23-6-26.
//

#include "surface_estimate_sac.h"
#include "common/point_type.h"

#include <pcl/common/angles.h>
#include <glog/logging.h>
SurfaceEstimateSac::SurfaceEstimateSac(const SacParam& p,
                                       const EstimateParam& p_common)
    : Estimator(p_common), sac_param_(p) {
  segmentation_.setOptimizeCoefficients(sac_param_.optimize_coefficients);
  segmentation_.setModelType(pcl::SACMODEL_PLANE);
  segmentation_.setAxis(p_common.plane_initial.normal());
  segmentation_.setDistanceThreshold(sac_param_.inlier_threshold);
  segmentation_.setEpsAngle(pcl::deg2rad(sac_param_.eps_angle));
  segmentation_.setMaxIterations(sac_param_.max_iterations);
  segmentation_.setProbability(sac_param_.probability);
  segmentation_.setInputCloud(this->cloud_);
  Reset();
}

void SurfaceEstimateSac::AddMeasurements_(int num_measurements) {
  cloud_->resize(measurements_.cols());
  cloud_->getMatrixXfMap().topRows<3>().rightCols(num_measurements) = measurements_.rightCols(num_measurements);
  // debug
  // pcl::io::savePCDFile("./data/eigen.pcd", *cloud_);
}

void SurfaceEstimateSac::Estimate() {
  pcl::PointIndices indices;
  pcl::ModelCoefficients coefficients;
  segmentation_.segment(indices, coefficients);
  const auto& p{coefficients.values};
  plane_ = Plane{Eigen::Vector3f{p[0], p[1], p[2]}, p[3]};
  LOG(ERROR) << "plane: " << plane_.coeffs();
}

std::unique_ptr<GroundSurface> SurfaceEstimateSac::GetGroundSurface() const {
  return std::make_unique<SurfacePlane>(plane_, Estimator::estimate_param_.range);
}

void SurfaceEstimateSac::ClearMeasurements_() {
  cloud_->clear();
}

void SurfaceEstimateSac::Reset() {
  ClearMeasurements();
  plane_ = Estimator::estimate_param_.plane_initial;
}