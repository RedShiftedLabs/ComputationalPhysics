cmake_minimum_required(VERSION 3.16)

add_library(Maths INTERFACE)

target_include_directories(Maths INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(Maths INTERFACE cxx_std_20)

add_library(Maths::Maths ALIAS Maths)

message(STATUS "Maths library configured as header-only interface library")
