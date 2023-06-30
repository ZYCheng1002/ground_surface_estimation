//
// Created by idriver-czy on 2023/6/30.
//

#ifndef GROUND_SURFACE_ESTIMATION_NUM_TYPES_H
#define GROUND_SURFACE_ESTIMATION_NUM_TYPES_H
#include <Eigen/Core>

using Measurements = Eigen::Matrix3Xf;
using Weights = Eigen::VectorXf;
using Hyperplane = Eigen::Hyperplane<float, 3>;
using AlignedBox2f = Eigen::AlignedBox2f;

/// 基础平面(基类)
class GroundSurface {
 public:
  using Ptr = std::unique_ptr<GroundSurface>;
  using ConstPtr = std::unique_ptr<const GroundSurface>;
  enum class Type {
    plane             = 0,
    uniform_b_spline  = 1,
    polynomial        = 2,
    undefined         = 3
  };

 public:
  explicit GroundSurface(const Type& type) : type_(type) {}

  virtual ~GroundSurface() = default;

  const Type& GetType() const { return type_; }

  virtual Eigen::AlignedBox2f GetRange() const = 0;

  ///@brief: 输入点p，计算该点到平面的距离
  float Distance(const Eigen::Vector3f& p) const {
    return p.z() - Height(p.head<2>());
  }

  virtual float Height(const Eigen::Vector2f& p) const = 0;

  virtual Eigen::Vector3f Normal(const Eigen::Vector2f& p) const = 0;

  friend std::ostream& operator<<(std::ostream& os,
                                  const GroundSurface& ground_surface) {
    return os << ground_surface.ToString();
  }

 private:
  virtual std::string ToString() const = 0;
  Type type_;
};

class SurfacePlane : public GroundSurface{
 public:
  explicit SurfacePlane(const Hyperplane& representation, const AlignedBox2f& range)
      : GroundSurface{GroundSurface::Type::plane}, representation_{representation}, range_{range} {
  }

  const Hyperplane& GetRepresentation() const {
    return representation_;
  }

  Eigen::AlignedBox2f GetRange() const final {
    return range_;
  }

  ///@brief: height = -(ax + by + d) / c
  float Height(const Eigen::Vector2f& p) const final {
    return -(representation_.offset() + representation_.normal().head<2>().dot(p)) / representation_.normal().z();
  }

  Eigen::Vector3f Normal(const Eigen::Vector2f& p) const final {
    return representation_.normal();
  }

 private:
  std::string ToString() const final {
    std::ostringstream oss;
    oss << "Plane: " << representation_.coeffs().transpose();
    return oss.str();
  }

  Hyperplane representation_{Eigen::Vector3f::UnitZ(), 0};
  AlignedBox2f range_;
};


#endif  // GROUND_SURFACE_ESTIMATION_NUM_TYPES_H
