//
// Created by czy on 23-6-24.
//

#ifndef GROUND_SURFACE_ESTIMATION_SURFACE_ESTIMATE_BASE_H
#define GROUND_SURFACE_ESTIMATION_SURFACE_ESTIMATE_BASE_H

#include "common_param.h"

class Estimator {
  using Measurements = Eigen::Matrix3Xf;
  using Weights = Eigen::VectorXf;

  Estimator(const EstimateParam& param);

  virtual ~Estimator();

  void AddMeasurements(const Measurements& measurements);

  void AddMeasurements(const Measurements& measurements,
                       const Weights& weights);

  const Measurements& GetMeasurements() const;

  const Weights& GetWeights() const;

  void SetWeights(const Weights& weights);

  void SetParam(const EstimateParam& param);

  const EstimateParam& GetParameters() const;

  bool HasMeasurements() const;

  virtual void Estimate() = 0;

  virtual void ClearMeasurements();

  virtual void Reset();

  /// todo: Get Surface

 protected:
  EstimateParam estimate_param_;

  Measurements measurements_;
  Weights weights_;
};

#endif  // GROUND_SURFACE_ESTIMATION_SURFACE_ESTIMATE_BASE_H
