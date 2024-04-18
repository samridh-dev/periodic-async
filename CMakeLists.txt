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
