# Physics Library
add_library(Physics INTERFACE)
add_library(Physics::Physics ALIAS Physics)

target_include_directories(Physics INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(Physics INTERFACE cxx_std_20)
target_link_libraries(Physics INTERFACE Physics)

# Cross-platform math library linking
if(UNIX AND NOT APPLE)
  # Linux needs explicit math library
  target_link_libraries(Physics INTERFACE m)
elseif(WIN32 AND CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  # MinGW might need math library
  target_link_libraries(Physics INTERFACE m)
endif()

# Platform-specific compile definitions
if(WIN32)
  target_compile_definitions(Physics INTERFACE
    _USE_MATH_DEFINES # For M_PI, etc.
    NOMINMAX # Prevent Windows.h min/max macros
  )
endif()