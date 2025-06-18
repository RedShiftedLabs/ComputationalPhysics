# Src/CMakeLists.txt
add_subdirectory(chapter1)
add_subdirectory(chapter2)

add_executable(PlotGraph PlotGraph.cpp)

target_link_libraries(PlotGraph PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    Maths::Maths
    Physics::Physics
    Renderers::Renderers
    DataLoader::DataLoader
)

set_target_properties(PlotGraph PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)