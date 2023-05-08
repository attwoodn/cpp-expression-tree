cmake_minimum_required(VERSION 3.10)
project(expression_tree 
    DESCRIPTION "C++11 expression tree implementation, used for evaluating instances of user-defined types"
    VERSION 0.0.1
    LANGUAGES CXX)

include(CTest)

if (NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 11)
endif()

include_directories( include )
add_subdirectory( tests )