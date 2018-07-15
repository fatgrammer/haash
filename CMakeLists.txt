cmake_minimum_required(VERSION 3.10)

project(nt VERSION 1.0.0 LANGUAGES CXX)
add_executable(nt src/main.cc)
add_library(tc src/tcp_connection.cc)
add_library(futils src/futils.cc)
#target_include_directories(nt 
#  PUBLIC
#    $<INSTALL_INTERFACE:include>
#    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#  PRIVATE
#    ${CMAKE_CURRENT_SOURCE_DIR}/src
#)
#target_include_directories(futils
#  PUBLIC
#    $<INSTALL_INTERFACE:include>
#    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#  PRIVATE
#    ${CMAKE_CURRENT_SOURCE_DIR}/src
#)
set(MAIN_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
include_directories(${MAIN_INCLUDE_DIR})
target_link_libraries(nt futils)
target_compile_options(nt PRIVATE -Werror)
target_compile_features(nt PRIVATE cxx_std_17)
