add_executable(ground_surface_sac_test ground_surface_sac_test.cc)
target_link_libraries(ground_surface_sac_test ${PROJECT_NAME}.ground_estimation)

add_executable(ground_surface_constant_sac_test ground_surface_constant_sac_test.cc)
target_link_libraries(ground_surface_constant_sac_test
        ${PROJECT_NAME}.ground_estimation
        ${PROJECT_NAME}.tool
        ${PROJECT_NAME}.common
        )