//
// Created by idriver-czy on 2023/6/30.
//

#ifndef GROUND_SURFACE_ESTIMATION_GLOBAL_CONFIG_H
#define GROUND_SURFACE_ESTIMATION_GLOBAL_CONFIG_H

#include "yaml_io.h"
class GlobalConfig {
 public:
  static std::shared_ptr<YAML_IO> Get();
  static bool LoadConfig(const std::string& yaml_path);

 private:
  GlobalConfig() = default;
  std::shared_ptr<YAML_IO> yaml_io_ = nullptr;
};

#endif  // GROUND_SURFACE_ESTIMATION_GLOBAL_CONFIG_H
