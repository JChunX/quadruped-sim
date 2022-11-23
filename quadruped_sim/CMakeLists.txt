cmake_minimum_required(VERSION 3.13)

project(QuadrupedSim VERSION 1.0)
add_subdirectory(models)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(APPLE)
    add_definitions(-Wno-deprecated-declarations) 
endif()

set(Boost_USE_DEBUG_LIBS         OFF)
set(Boost_USE_RELEASE_LIBS       ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

find_package(Boost REQUIRED)

if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

add_executable(QuadrupedSim)
target_sources(QuadrupedSim PRIVATE src/main.cpp)

target_include_directories(QuadrupedSim PRIVATE "include" "src")

# add_subdirectory(src/core)
target_link_libraries(QuadrupedSim ${Boost_LIBRARIES})

install(TARGETS QuadrupedSim DESTINATION bin)