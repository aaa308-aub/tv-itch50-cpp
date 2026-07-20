cmake_minimum_required(VERSION 3.20)
project(tv_itch50_cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES
  "src/itch/ios/*.cpp"
  "src/itch/mmap/*.cpp"
)

add_library(tv_itch50_cpp STATIC ${SOURCES})

target_include_directories(tv_itch50_cpp
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
