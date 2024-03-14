cmake_minimum_required(VERSION 3.0.0)
project(asymptotic VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(sorts_asymptotic sorts.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
