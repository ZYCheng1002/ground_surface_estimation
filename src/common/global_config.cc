//
// Created by idriver-czy on 2023/6/30.
//

#include "global_config.h"

std::shared_ptr<GlobalConfig> g_config = nullptr;
std::shared_ptr<YAML_IO> GlobalConfig::Get() {
  if (g_config == nullptr) {
    g_config.reset(new GlobalConfig);
  }
  return g_config->yaml_io_;
}

bool GlobalConfig::LoadConfig(const std::string& yaml_path) {
  if (g_config == nullptr) {
    g_config.reset(new GlobalConfig);
  }
  g_config->yaml_io_ = std::make_shared<YAML_IO>(yaml_path);
}