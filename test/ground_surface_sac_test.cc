//
// Created by czy on 23-6-29.
//

#include <gflags/gflags.h>
#include <glog/logging.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/io/pcd_io.h>

#include "ground_surface_estimation_geman_mcclure.h"
#include "tools/ground_filter.h"
DEFINE_string(pcd_path, "./data/map.pcd", "config file path");
using PointType = pcl::PointXYZI;
using CloudType = pcl::PointCloud<PointType>;
using CloudTypePtr = CloudType::Ptr;
int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  FLAGS_stderrthreshold = google::INFO;
  FLAGS_colorlogtostderr = true;
  google::ParseCommandLineFlags(&argc, &argv, true);

  CloudTypePtr cloud_in (new CloudType());
  pcl::io::loadPCDFile(FLAGS_pcd_path, *cloud_in);
  /// 点云转 eigen
  auto cloud_eigen = cloud_in->getMatrixXfMap(3, 8, 0);
  LOG(INFO) << cloud_eigen.size();
  /// 全部采用默认值
  GroundParam ground_param;
  GroundEstimatorGM ground_estimate_gm(ground_param);
  ground_estimate_gm.AddMeasurements(cloud_eigen);
  ground_estimate_gm.Estimate();

}