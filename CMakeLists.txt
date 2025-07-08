cmake_minimum_required(VERSION 3.10)

add_subdirectory(vendor)

project(computer_graphics_from_scratch)

include(cmake/configuration.cmake)

add_subdirectory(rasterizer)
