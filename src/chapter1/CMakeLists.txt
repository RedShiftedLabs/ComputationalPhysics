# Chapter 1 - Basic Physics Simulations

# Helper function to create physics executables
function(add_physics_sim name source)
  add_executable(${name} ${source})

  target_link_libraries(${name} PRIVATE
    Physics::Physics
    Maths::Maths
    Renderers::Renderers
    DataLoader::DataLoader
  )

  # Add OpenMP if available
  if(OpenMP_CXX_FOUND)
    target_link_libraries(${name} PRIVATE OpenMP::OpenMP_CXX)
  endif()

  # Set properties
  set_target_properties(${name} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
  )

  # Windows-specific settings for Visual Studio
  if(WIN32 AND MSVC)
    set_target_properties(${name} PROPERTIES
      VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    )
  endif()
endfunction()

# Create executables for each simulation
add_physics_sim(Circle circle.cpp)
add_physics_sim(Lissajous Lissajous.cpp)
add_physics_sim(Projectile projectile.cpp)
add_physics_sim(ProjectileAirResistance ProjectileAirResistance.cpp)
add_physics_sim(Pendulum SimplePendulum.cpp)
add_physics_sim(Box1D box1D.cpp)
add_physics_sim(Box2D box2D.cpp)

add_executable(DataVisualizer DataVisualizer.cpp)

target_link_libraries(DataVisualizer PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    Maths::Maths
    Physics::Physics
    Renderers::Renderers
    DataLoader::DataLoader
)

set_target_properties(DataVisualizer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

# Create a chapter1 target to build all simulations
add_custom_target(chapter1_sims
    DEPENDS circle lissajous projectile projectile_air pendulum
    COMMENT "Building Chapter 1 simulations"
)