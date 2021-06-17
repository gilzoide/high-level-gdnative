cmake_minimum_required(VERSION 3.0)

project(gdnhlc)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  add_compile_options (-fdiagnostics-color=always)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  add_compile_options (-fcolor-diagnostics)
endif()

add_library(example SHARED example.c)
target_include_directories(example PUBLIC godot-headers)
target_include_directories(example PUBLIC ..)

