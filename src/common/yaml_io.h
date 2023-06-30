//
// Created by idriver-czy on 2023/6/30.
//

#ifndef GROUND_SURFACE_ESTIMATION_YAML_IO_H
#define GROUND_SURFACE_ESTIMATION_YAML_IO_H
#include <yaml-cpp/yaml.h>
#include <glog/logging.h>
#include <cassert>

class YAML_IO {
 public:
  YAML_IO(const std::string& path) {
    path_ = path;
    yaml_node_ = YAML::LoadFile(path_);
    if (yaml_node_.IsNull()){
      LOG(ERROR) << "Failed to open yaml: " << path;
    }
    is_opened_ = true;
  }

  YAML_IO() = default;

  ~YAML_IO() = default;

  template <typename T>
  T GetValue(const std::string& key) const {
    assert(is_opened_);
    return yaml_node_[key].as<T>();
  }

  template <typename T>
  T GetValue(const std::string& node, const std::string& key) const {
    assert(is_opened_);
    return yaml_node_[node][key].as<T>();
  }

 private:
  std::string path_;
  bool is_opened_ = false;
  YAML::Node yaml_node_;
};

#endif  // GROUND_SURFACE_ESTIMATION_YAML_IO_H
