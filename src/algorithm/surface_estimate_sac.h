//
// Created by czy on 23-6-26.
//

#ifndef GROUND_SURFACE_ESTIMATION_SURFACE_ESTIMATE_SAC_H
#define GROUND_SURFACE_ESTIMATION_SURFACE_ESTIMATE_SAC_H
#include <pcl/point_types.h>
#include <pcl/segmentation/sac_segmentation.h>

#include "sac_param.h"
#include "surface_estimate_base.h"
// struct SacParam;
class SurfaceEstimateSac : public Estimator {
 public:
  using Plane = Eigen::Hyperplane<float, 3>;
  SurfaceEstimateSac(const SacParam&, const EstimateParam&);
  void Estimate() final;
  std::unique_ptr<GroundSurface> GetGroundSurface() const final;
  void Reset() final;

 private:
  void AddMeasurements_(int) final;
  void ClearMeasurements_() final;

  SacParam sac_param_;
  pcl::SACSegmentation<pcl::PointXYZ> segmentation_;
  const typename pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_{
      new pcl::PointCloud<pcl::PointXYZ>};
  Plane plane_;
};

#endif  // GROUND_SURFACE_ESTIMATION_SURFACE_ESTIMATE_SAC_H
