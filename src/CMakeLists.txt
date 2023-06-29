add_subdirectory(algorithm)
add_library(${PROJECT_NAME}.ground_estimation ground_surface_estimation.cc ground_surface_estimation_geman_mcclure.cpp)
target_link_libraries(${PROJECT_NAME}.ground_estimation
        ${ThirdParty}
        ${PROJECT_NAME}.estimate
        )