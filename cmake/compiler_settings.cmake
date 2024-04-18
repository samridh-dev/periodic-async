set(CMAKE_CXX_STANDARD 11)

if(ENABLE_DEBUG)
  message(STATUS "Setting build type to 'Debug'.")
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Set build to Debug." FORCE)
else()
  if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Release'.")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "set build to Release." FORCE)
  endif()
endif()

# Set compiler flags for Debug build
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  message(STATUS "WOO!")
  set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Wextra -Wpedantic")
endif()

# Set compiler flags for Release build
if(CMAKE_BUILD_TYPE STREQUAL "Release")
  message(STATUS "BOO!")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

