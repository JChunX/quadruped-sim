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

find_package(Boost REQUIRED COMPONENTS system iostreams)
find_package(Eigen3 REQUIRED NO_MODULE)
find_package(mujoco REQUIRED)

find_package(glfw3 3.3 REQUIRED)
#find_package(OpenGL REQUIRED)

if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

add_executable(QuadrupedSim)
target_sources(QuadrupedSim PRIVATE 
  src/main.cpp
  src/QuadrupedSim.cpp
  src/Input.cpp
)

target_include_directories(QuadrupedSim PRIVATE "include" "src")

target_link_libraries(QuadrupedSim ${Boost_LIBRARIES})
target_link_libraries(QuadrupedSim mujoco::mujoco)
target_link_libraries(QuadrupedSim Eigen3::Eigen)
target_link_libraries(QuadrupedSim glfw)
#target_link_libraries(QuadrupedSim OpenGL::GL)

install(TARGETS QuadrupedSim DESTINATION bin)