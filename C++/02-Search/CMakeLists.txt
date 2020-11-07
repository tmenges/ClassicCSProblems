cmake_minimum_required(VERSION 3.17)
project(02_Search)

set(CMAKE_CXX_STANDARD 20)

set(BOOST_ROOT "/usr/local/Cellar/boost/1.74.0")
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(Boost_USE_STATIC_LIBS ON)

set(other_flags "${other_flags} -fvisibility-inlines-hidden")
set(other_flags "${other_flags} -fvisibility=hidden")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${other_flags}")


find_package(Boost 1.74.0 REQUIRED COMPONENTS log log_setup)
message("Boost include dirs: " ${Boost_INCLUDE_DIRS})
message("Boost library dirs: " ${Boost_LIBRARY_DIRS})
message("Boost libraries: " ${Boost_LIBRARIES})

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find boost!")
endif()

include_directories(. ${Boost_INCLUDE_DIRS})

add_executable(02_Search
        bfs.h
        dfs.h
        main.cpp
        maze.cpp
        maze.h
        search.cpp
        search.h)

target_link_libraries(02_Search ${Boost_LIBRARIES})
