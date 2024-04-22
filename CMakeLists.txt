cmake_minimum_required(VERSION 3.18)

include(cmake/unset_conf.cmake)
include(cmake/config.cmake)

project(periodic_async
  VERSION 0.1
  DESCRIPTION "A library to run generic code periodically and asynchronously"
  LANGUAGES CXX
)

include(cmake/compiler_settings.cmake)
include(cmake/include.cmake)


add_subdirectory(src)

if (ENABLE_BUILD_LIBRARY)

  if (ENABLE_BUILD_STATIC) 
    add_library(periodic-async STATIC)
  else()
    add_library(periodic-async SHARED)
  endif()

  target_sources(periodic-async PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/impl.cpp 
  )
  target_include_directories(periodic-async INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
  )

endif()
