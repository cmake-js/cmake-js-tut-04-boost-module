cmake_minimum_required(VERSION 2.8)

# Name of the project (will be the name of the plugin)
project (addon)

# Boost dependency
# Include BoostLib module
SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/node_modules/boost-lib/cmake")
include(BoostLib)

# C++11 required for actual Boost versions.
if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

# Locate/Download Boost (semver)
require_boost_libs(">= 1.58.0" "coroutine")
include_directories(${Boost_INCLUDE_DIRS})

# Essential include files to build a node addon,
# you should add this line in every CMake.js based project.
include_directories(${CMAKE_JS_INC})

# Declare the location of the source files
file(GLOB SOURCE_FILES "src/*.cpp")

# This line will tell CMake that we're building a shared library
# from the above source files
# named after the project's name
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

# This line will give our library file a .node extension without any "lib" prefix
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")

# Essential library files to link to a node addon,
# you should add this line in every CMake.js based project.
# Define Boost dependencies there.
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB};${Boost_LIBRARIES})
