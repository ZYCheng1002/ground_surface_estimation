add_library(${PROJECT_NAME}.tool SHARED  timer.cc)
target_link_libraries(${PROJECT_NAME}.tool glog)