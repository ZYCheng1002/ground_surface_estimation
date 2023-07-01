# find eigen
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIRS})

# find pcl
find_package(PCL REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})

# tbb
find_package(TBB REQUIRED)
message(STATUS "TBB veision: " ${TBB_VERSION})

# ceres
set(CERES_LIB ${PROJECT_SOURCE_DIR}/thirdparty/ceres)
set(CERES_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/thirdparty/ceres/include)
find_package(Ceres REQUIRED PATHS ${CERES_LIB})
include_directories(${Ceres_INCLUDE_DIRS})
message(STATUS "Ceres version: " ${Ceres_VERSION})

# set thirdparty
set(ThirdParty
        ${PCL_LIBRARIES}
        ${CERES_LIBRARIES}
        glog
        gflags
        yaml-cpp
        TBB::tbb
        )