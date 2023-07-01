//
// Created by idriver-czy on 2023/6/30.
//

#ifndef GROUND_SURFACE_ESTIMATION_GROUND_FILTER_H
#define GROUND_SURFACE_ESTIMATION_GROUND_FILTER_H
#include <tbb/parallel_for.h>

#include "common/num_types.h"
#include "common/point_type.h"

/// @brief: 生成range范围的地面地面点云
template <typename Point_>
void Convert(const GroundSurface::Ptr& ground_surface,
             const AlignedBox2f& range,
             const float sampling_distance,
             pcl::PointCloud<Point_>& cloud) {
  const Eigen::Vector2i points_per_dim{(range.sizes() / sampling_distance).cast<int>()};
  cloud.resize(points_per_dim.prod());
  for (int x = 0; x < points_per_dim.x(); x++) {
    for (int y = 0; y < points_per_dim.y(); y++) {
      auto& p{cloud.points[x * points_per_dim.y() + y]};
      p.x = static_cast<float>(x) * sampling_distance + range.min().x();
      p.y = static_cast<float>(y) * sampling_distance + range.min().y();
      p.z = ground_surface->Height(p.getVector3fMap().template head<2>());
    }
  }
}

template <typename Point_>
void MakeUnordered(pcl::PointCloud<Point_>& in_out) {
  in_out.height = 1;
  in_out.width = in_out.points.size();
  in_out.is_dense = false;
}

/**
 * Remove all points where the comparison between that point's ground distance and a threshold is true.
 * If Cmp_=std::less<>, then all points with distance below threshold are removed.
 * If Cmp_=std::greater<>, then all points with distance above threshold are removed.
 * @tparam Point_ Point type
 * @tparam Cmp_ Comparison type
 * @param ground_surface Ground surface object
 * @param threshold The threshold used for comparison
 * @param in_out Point cloud where points are possibly removed
 */
template <typename Cmp_, typename Point_>
void Filter(const GroundSurface::Ptr& ground_surface, const float& threshold, pcl::PointCloud<Point_>& in_out) {
  using namespace std;
  Cmp_ cmp;
  in_out.points.erase(
      remove_if(begin(in_out.points),
                end(in_out.points),
                [&](const Point_& p) { return cmp(ground_surface->Distance(p.getVector3fMap()), threshold); }),
      end(in_out.points));
  MakeUnordered(in_out);
}

void Separate(const GroundSurface::Ptr& ground_surface,
              const float& threshold,
              pcl::PointCloud<pcl::PointXYZI>& cloud_in) {
  tbb::parallel_for<size_t>(0, cloud_in.size(), [&](const auto& c) {
    auto& p{cloud_in.points[c]};
    auto d{ground_surface->Distance(p.getVector3fMap())};
    if (d < threshold) {
      p.intensity = 256;
    } else {
      p.intensity = 0;
    }
  });
}

#endif  // GROUND_SURFACE_ESTIMATION_GROUND_FILTER_H
