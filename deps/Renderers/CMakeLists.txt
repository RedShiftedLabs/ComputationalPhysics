add_library(Renderers INTERFACE)
add_library(Renderers::Renderers ALIAS Renderers)

target_include_directories(Renderers INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>
)

# if you ever need compile features:
target_compile_features(Renderers INTERFACE cxx_std_20)
