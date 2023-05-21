cmake_minimum_required(VERSION 3.10)
project(expression_tree 
    DESCRIPTION "C++14 expression tree implementation, used for evaluating instances of user-defined types"
    VERSION 1.0.0
    LANGUAGES CXX)

include(CTest)

if (NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if (NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif()

# Generate compile_commands.json for LLVM tooling
option(CMAKE_EXPORT_COMPILE_COMMANDS "Generates compile_commands.json when enabled")
mark_as_advanced(CLEAR CMAKE_EXPORT_COMPILE_COMMANDS)

include_directories( include )
add_subdirectory( tests )