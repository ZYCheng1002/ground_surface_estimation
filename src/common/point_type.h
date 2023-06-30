//
// Created by idriver-czy on 2023/6/30.
//

#ifndef GROUND_SURFACE_ESTIMATION_POINT_TYPE_H
#define GROUND_SURFACE_ESTIMATION_POINT_TYPE_H
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>

using PointXYZ = pcl::PointXYZ;
using CloudXYZType = pcl::PointCloud<PointXYZ>;
using CloudXYZTypePtr = CloudXYZType::Ptr;

using PointXYZI = pcl::PointXYZI;
using CloudXYZIType = pcl::PointCloud<PointXYZI>;
using CloudXYZITypePtr = CloudXYZIType::Ptr;

#endif  // GROUND_SURFACE_ESTIMATION_POINT_TYPE_H
