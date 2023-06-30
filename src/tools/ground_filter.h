//
// Created by idriver-czy on 2023/6/30.
//

#ifndef GROUND_SURFACE_ESTIMATION_GROUND_FILTER_H
#define GROUND_SURFACE_ESTIMATION_GROUND_FILTER_H
#include "common/num_types.h"
#include "common/point_type.h"

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

#endif  // GROUND_SURFACE_ESTIMATION_GROUND_FILTER_H
