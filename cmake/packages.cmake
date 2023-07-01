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
if (DEFINED ${CERES_LIB})
    find_package(Ceres REQUIRED PATHS ${CERES_LIB})
else ()
    find_package(Ceres REQUIRED)
endif ()
message(STATUS ${Ceres_VERSION})
include_directories(${CERES_INCLUDE_DIRS})


# set thirdparty
set(ThirdParty
        ${PCL_LIBRARIES}
        ${CERES_LIBRARIES}
        glog
        gflags
        yaml-cpp
        TBB::tbb
        )