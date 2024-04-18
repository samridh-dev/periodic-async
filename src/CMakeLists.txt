cmake_minimum_required(VERSION 3.18)

if (ENABLE_BUILD_EXAMPLE)

  file(GLOB SOURCE_EXEC "*.cpp")
  if (NOT SOURCE_EXEC)
    message(FATAL_ERROR "no source files for example executable found.")
  endif()

  add_executable(example ${SOURCE_EXEC})
  if (ENABLE_BINARY_FOLDER)
    set_target_properties(example 
      PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
    )
  endif()

endif()

