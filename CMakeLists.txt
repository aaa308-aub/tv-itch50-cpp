cmake_minimum_required(VERSION 3.20)
project(tv_itch50_cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SOURCES
        "src/tv_itch/*.cpp"
        "src/tv_itch/ios/*.cpp"
        "src/tv_itch/mmap/*.cpp"
        "src/tv_itch/spec/*.cpp"
        "src/tv_itch/utils/*.cpp"
)

add_library(tv_itch50_cpp STATIC ${SOURCES})

target_include_directories(tv_itch50_cpp
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Remove the hashtag below if your architecture is big-endian.
#target_compile_definitions(tv_itch50_cpp PRIVATE TV_ITCH50_CPP_BIG_ENDIAN)