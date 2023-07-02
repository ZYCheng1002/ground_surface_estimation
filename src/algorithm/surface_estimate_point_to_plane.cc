//
// Created by czy on 23-7-2.
//

#include "surface_estimate_point_to_plane.h"

///@brief: residual point to plane
struct ResidualPP {
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  ResidualPP(const Eigen::MatrixXf& measurements, const Eigen::MatrixXf covariance)
      : measurements_(measurements), weights_(covariance) {}

  template <typename T>
  bool operator()(const T* const p, T * residual) const {
    /**
    Eigen::Map<const Eigen::Matrix<T, Eigen::Dynamic, 3>> points_map(measurements_.cast<T>().data(), measurements_.rows(), 3);
    Eigen::Matrix<T, Eigen::Dynamic, 4> point_linear ;
    point_linear = Eigen::Matrix<T, points_map.rows(), 4>();
    point_linear.setOnes();
    point_linear.topLeftCorner(measurements_.rows(), 3).data() = points_map.data();
    **/
    const T& a = p[0];
    const T& b = p[1];
    const T& c = p[2];
    const T& d = p[3];

    for (int i = 0; i < measurements_.rows(); ++i) {
      /// todo:
    }

  }

  private:
  Eigen::MatrixXf measurements_;
  Eigen::MatrixXf weights_;
};