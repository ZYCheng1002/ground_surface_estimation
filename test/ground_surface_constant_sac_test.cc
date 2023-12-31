//
// Created by idriver-czy on 2023/6/30.
//
#include <gflags/gflags.h>
#include <glog/logging.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

#include "ground_surface_estimation_constant.h"
#include "tools/ground_filter.h"
#include "tools/timer.h"
DEFINE_string(pcd_path, "./data/map.pcd", "config file path");
DEFINE_string(config_path, "./config/config.yaml", "config file path");
int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  FLAGS_stderrthreshold = google::INFO;
  FLAGS_colorlogtostderr = true;
  google::ParseCommandLineFlags(&argc, &argv, true);
  GlobalConfig::LoadConfig(FLAGS_config_path);
  CloudXYZITypePtr cloud_in(new CloudXYZIType());
  pcl::io::loadPCDFile(FLAGS_pcd_path, *cloud_in);
  /// 点云转 eigen
  auto cloud_eigen = cloud_in->getMatrixXfMap(3, 8, 0);
  LOG(INFO) << "Current cloud size: " << cloud_eigen.size();
  /// 全部采用默认值
  GroundParam ground_param;
  ground_param.Init();
  GroundEstimatorCon ground_estimate_gm(ground_param);
  ground_estimate_gm.AddMeasurements(cloud_eigen);
  ground_estimate_gm.Estimate();
  auto ground_surface = ground_estimate_gm.GetGroundSurface();
  /// 生成地面点云
  CloudXYZITypePtr cloud(new CloudXYZIType);
  Convert(ground_surface, ground_surface->GetRange(), 1, *cloud);
  for (int i = 0; i < cloud->size(); ++i) {
    cloud->points[i].intensity = 100;
  }
  auto result_cloud = *cloud_in + *cloud;
  pcl::io::savePCDFile("./data/ground_generate.pcd", result_cloud);
  /// 分离地面
  Timer::Evaluate([&]() { Separate(ground_surface, 0.21, *cloud_in); }, "point cloud ground separate");

  pcl::io::savePCDFile("./data/1.pcd", *cloud_in);
  /// 去除地面点云
  struct MyCmp {
    bool operator()(float dist, float threshold) const { return dist <= threshold; }
  };
  Timer::Evaluate([&]() { Filter<MyCmp, PointXYZI>(ground_surface, 0.2, *cloud_in); }, "point cloud ground remove");
  pcl::io::savePCDFile("./data/without_ground.pcd", *cloud_in);
  Timer::PrintAll();
}