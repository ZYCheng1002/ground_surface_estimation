add_library(${PROJECT_NAME}.estimate SHARED
        surface_estimate_base.cc
        surface_estimate_sac.cc
        surface_estimate_polynominal.cc
        surface_estimate_point_to_plane.cc
        )
target_link_libraries(${PROJECT_NAME}.estimate ${ThirdParty})