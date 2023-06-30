add_library(${PROJECT_NAME}.common SHARED  global_config.cc)
target_link_libraries(${PROJECT_NAME}.common ${ThirdParty})