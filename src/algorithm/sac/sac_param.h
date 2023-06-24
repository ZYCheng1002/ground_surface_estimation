//
// Created by czy on 23-6-24.
//

#ifndef GROUND_SURFACE_ESTIMATION_SAC_PARAM_H
#define GROUND_SURFACE_ESTIMATION_SAC_PARAM_H
#include <yaml-cpp/yaml.h>

struct SacParam{
    SacParam(const YAML::Node& node){
        /// todo:
    }
    bool optimize_coefficients{true};
    float inlier_threshold{0.2};
    float eps_angle{0.01};
    size_t max_iterations{20};
    float probability{0.99};
};

#endif //GROUND_SURFACE_ESTIMATION_SAC_PARAM_H
