//
// Created by czy on 23-6-29.
//

#include <gflags/gflags.h>
#include <glog/logging.h>

#include "ground_surface_estimation_geman_mcclure.h"
DEFINE_string(config_yaml, "./config/mapping.yaml", "config file path");

int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  FLAGS_stderrthreshold = google::INFO;
  FLAGS_colorlogtostderr = true;
  google::ParseCommandLineFlags(&argc, &argv, true);
  /// 读取点云

  /// 点云转 eigen

  /// 全部采用默认值
  GroundParam ground_param;
  GroundEstimatorGM ground_estimate_gm(ground_param);

}