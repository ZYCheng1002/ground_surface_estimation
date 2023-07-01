//
// Created by czy on 23-7-1.
//

#include "surface_estimate_polynominal.h"

#include <ceres/autodiff_cost_function.h>
#include <ceres/loss_function.h>

struct Residual {
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  static constexpr int dimension = 8;
  // 平面的多项式表达
  // f(x, y, z) = ax^2 + by^2 + cz^2 + dxy + exz + fyz + gx + hy + iz + j
  Residual(const Eigen::Array3Xf& m, const Eigen::ArrayXf& weights) : heights_{m.row(2)}, weights_{weights} {
    measurements_.resize(dimension, m.cols());
    measurements_.row(0).setOnes();
    measurements_.row(1) = m.row(0);                      ///< x
    measurements_.row(2) = m.row(1);                      ///< x
    measurements_.row(3) = m.row(0) * m.row(1);           ///< x y
    measurements_.row(4) = m.row(0).square();             ///< x^2
    measurements_.row(5) = m.row(1).square();             ///< y^2
    measurements_.row(6) = m.row(0).square() * m.row(1);  ///< x^2 y
    measurements_.row(7) = m.row(0) * m.row(1).square();  ///< x y^2
    DLOG(INFO) << "Measurements:\n" << measurements_.leftCols(15);
    DLOG(INFO) << "Heights:\n" << heights_.head<15>().transpose();
    DLOG(INFO) << "Weights:\n" << weights_.head<15>().transpose();
    DLOG_ASSERT(measurements_.cols() == heights_.size());
    DLOG_ASSERT(heights_.size() == weights.size());
  }

  void UpdateWeights(const Eigen::ArrayXf& weights) { weights_ = weights; }

  template <typename T>
  bool operator()(const T* c, T* residual) const {
    using namespace Eigen;
    Map<Array<T, Dynamic, 1>>{residual, heights_.size()} =
        ((Map<const Matrix<T, 1, dimension>>{c} * measurements_.cast<T>()).transpose().array() - heights_.cast<T>()) *
        weights_.cast<T>();
    return true;
  }

  static ceres::CostFunction* Create(const Eigen::Array3Xf& measurements, const Eigen::ArrayXf& weights) {
    return new ceres::AutoDiffCostFunction<Residual, ::ceres::DYNAMIC, dimension>(new Residual(measurements, weights),
                                                                                  measurements.cols());
  }

 private:
  Eigen::Matrix<float, dimension, Eigen::Dynamic> measurements_;
  Eigen::ArrayXf heights_;
  Eigen::ArrayXf weights_;
};

SurfaceEstimatePoly::SurfaceEstimatePoly(const CeresParam& ceres_param, const EstimateParam& estimate_param)
    : Estimator(estimate_param),

      ceres_param_(ceres_param) {
  Reset();
  ClearMeasurements_();
}

void SurfaceEstimatePoly::AddMeasurements_(int num_measurements) {
  problem_->AddResidualBlock(
      Residual::Create(measurements_.rightCols(num_measurements), weights_.tail(num_measurements)),
      new ceres::TrivialLoss,
      poly_ceres_.data());
}

void SurfaceEstimatePoly::Estimate() {
  ceres::Solver::Summary summary;
  ceres::Solve(ceres_param_.solver, problem_.get(), &summary);
  LOG(INFO) << summary.FullReport();
  if (!summary.IsSolutionUsable()) {
    LOG(ERROR) << "Solution not usable";
  }
}

void SurfaceEstimatePoly::Reset() { ClearMeasurements(); }

std::unique_ptr<GroundSurface> SurfaceEstimatePoly::GetGroundSurface() const {
  return std::make_unique<Polynomial>(poly_ceres_.cast<float>(), Estimator::estimate_param_.range);
}

void SurfaceEstimatePoly::ClearMeasurements_() {
  poly_ceres_[0] = -estimate_param_.plane_initial.offset();
  problem_ = std::make_unique<ceres::Problem>(ceres_param_.problem);
}