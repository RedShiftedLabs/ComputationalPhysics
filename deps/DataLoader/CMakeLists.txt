# DataLoader Library
add_library(DataLoader INTERFACE)
add_library(DataLoader::DataLoader ALIAS DataLoader)

target_include_directories(DataLoader INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(DataLoader INTERFACE cxx_std_20)

# Platform-specific compile definitions
if(WIN32)
  target_compile_definitions(DataLoader INTERFACE
    _USE_MATH_DEFINES
    NOMINMAX
  )
endif()

# Cross-platform dependencies
if(UNIX AND NOT APPLE)
  target_link_libraries(DataLoader INTERFACE m)
elseif(WIN32 AND CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  target_link_libraries(DataLoader INTERFACE m)
endif()