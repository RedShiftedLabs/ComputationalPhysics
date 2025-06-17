cmake_minimum_required(VERSION 3.16)
project(ComputationalPhysics VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Cross-platform compiler flags
if(MSVC)
  set(CMAKE_CXX_FLAGS_DEBUG "/Od /Zi /W4")
  set(CMAKE_CXX_FLAGS_RELEASE "/O2 /DNDEBUG")
else()
  set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra -pedantic")

  if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -march=native")
  else()
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
  endif()
endif()

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

# Find OpenMP for physics simulations
find_package(OpenMP QUIET)

# Platform-specific settings
if(WIN32)
  # Windows-specific settings
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT chapter1_sims)

  if(MSVC)
    add_compile_definitions(_USE_MATH_DEFINES)
  endif()
endif()

# Include dependencies
add_subdirectory(deps)

# Include source chapters
add_subdirectory(src)

# Global target to build all simulations
add_custom_target(all_sims
    DEPENDS chapter1_sims chapter2_sims
    COMMENT "Building all physics simulations"
)

# Configuration summary
message(STATUS "=== Build Configuration ===")
message(STATUS "System: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Processor: ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "OpenMP: ${OpenMP_CXX_FOUND}")
message(STATUS "Output directory: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "===========================")