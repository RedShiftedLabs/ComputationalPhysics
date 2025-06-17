# Chapter 2 - Template for future simulations

# Helper function (same as chapter1)
function(add_physics_sim name source)
  add_executable(${name} ${source})

  target_link_libraries(${name} PRIVATE
    Physics::Physics
    Physics::Maths
  )

  if(OpenMP_CXX_FOUND)
    target_link_libraries(${name} PRIVATE OpenMP::OpenMP_CXX)
  endif()

  set_target_properties(${name} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
  )

  # Windows-specific settings
  if(WIN32 AND MSVC)
    set_target_properties(${name} PROPERTIES
      VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    )
  endif()
endfunction()

# Add simulations here as you create them
# add_physics_sim(simulation_name source.cpp)

# Custom target for chapter2
add_custom_target(chapter2_sims
    COMMENT "Building Chapter 2 simulations"
)